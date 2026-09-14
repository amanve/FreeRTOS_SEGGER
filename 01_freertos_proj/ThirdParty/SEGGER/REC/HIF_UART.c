/*
 * HIF_UART.c
 *
 *  Created on: 13-Sept-2026
 *      Author: Aman Verma
 */
#include "SEGGER_SYSVIEW.h"
#include "SEGGER_RTT.h"
#include "HIF_UART.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"

static UART_ON_RX_FUNC_P _cbOnRx;
static UART_ON_TX_FUNC_P _cbOnTx;

//static const U8 _abHelloMsg[_TARGET_HELLO_SIZE] = { 'S', 'V', (SEGGER_SYSVIEW_VERSION / 10000), (SEGGER_SYSVIEW_VERSION / 1000) % 10 };  // "Hello" message expected by SysView: [ 'S', 'V', <PROTOCOL_MAJOR>, <PROTOCOL_MINOR> ]

/*********************************************************************
*
*       HIF_UART_WaitForTxEnd
*/
void HIF_UART_WaitForTxEnd(void) {
  //
  // Wait until transmission has finished (e.g. before changing baudrate).
  //
  while ((USART_SR & (1 << USART_TXE)) == 0);  // Wait until transmit buffer empty (Last byte shift from data to shift register)
  while ((USART_SR & (1 << USART_TC)) == 0);   // Wait until transmission is complete
}

/*********************************************************************
*
*       USART1_IRQHandler
*
*  Function descriptio
*    Interrupt handler.
*    Handles both, Rx and Tx interrupts
*
*  Notes
*    Runs at the FreeRTOS syscall priority and is masked by RTT locks.
*/
void USART2_IRQHandler(void);
void USART2_IRQHandler(void) {
  int UsartStatus;
  U8 v;
  int r;

  UsartStatus = USART_SR;                              // Examine status register
  if (UsartStatus & ((1 << USART_RXNE) | USART_RX_ERROR_FLAGS)) {               // Data received?
    v = USART_DR;                                      // Read data
    if ((UsartStatus & USART_RX_ERROR_FLAGS) == 0) {   // Only process data if no error occurred
      (void)v;                                         // Avoid warning in BTL
      if (_cbOnRx) {
        _cbOnRx(v);
      }
    }
  }
  if ((UsartStatus & (1 << USART_TXE)) && (USART_CR1 & (1 << USART_TXEIE))) {                // Tx (data register) empty? => Send next character Note: Shift register may still hold a character that has not been sent yet.
    //
    // Under special circumstances, (old) BTL of Flasher does not wait until a complete string has been sent via UART,
    // so there might be an TxE interrupt pending *before* the FW had a chance to set the callbacks accordingly which would result in a NULL-pointer call...
    // Therefore, we need to check if the function pointer is valid.
    //
    if (_cbOnTx == NULL) {  // No callback set? => Nothing to do...
      return;
    }
    r = _cbOnTx(&v);
    if (r == 0) {                          // No more characters to send ?
      USART_CR1 &= ~(1UL << USART_TXEIE);  // Disable further tx interrupts
    } else {
      USART_SR;      // Makes sure that "transmission complete" flag in USART_SR is reset to 0 as soon as we write USART_DR. If USART_SR is not read before, writing USART_DR does not clear "transmission complete". See STM32F4 USART documentation for more detailed description.
      USART_DR = v;  // Start transmission by writing to data register
    }
  }
}

/*********************************************************************
*
*       HIF_UART_EnableTXEInterrupt()
*/
void HIF_UART_EnableTXEInterrupt(void) {
  USART_CR1 |= (1 << USART_TXEIE);  // enable Tx empty interrupt => Triggered as soon as data register content has been copied to shift register
}



/*********************************************************************
*
*       HIF_UART_Init()
*/
void HIF_UART_Init(U32 Baudrate, UART_ON_TX_FUNC_P cbOnTx, UART_ON_RX_FUNC_P cbOnRx) {
  U32 v;
  U32 Div;
  //
  // Configure USART RX/TX pins for alternate function AF7
  //
  RCC_APB1ENR |= (1 <<  17);        // Enable USART2 clock
  RCC_AHB1ENR |= (1 <<  0);        // Enable IO port A clock
  v  = GPIO_AFRL;
  v &= ~((15UL << ((GPIO_UART_TX_BIT) << 2)) | (15UL << ((GPIO_UART_RX_BIT) << 2)));
  v |=   ((7UL << ((GPIO_UART_TX_BIT) << 2)) | (7UL << ((GPIO_UART_RX_BIT) << 2)));
  GPIO_AFRL = v;
  //
  // Configure USART RX/TX pins for alternate function usage
  //
  v  = GPIO_MODER;
  v &= ~((3UL << (GPIO_UART_TX_BIT << 1)) | (3UL << (GPIO_UART_RX_BIT << 1)));
  v |=  ((2UL << (GPIO_UART_TX_BIT << 1)) | (2UL << (GPIO_UART_RX_BIT << 1)));         // PA10: alternate function
  GPIO_MODER = v;
  //
  // Initialize USART
  //
  USART_CR1 = 0
            | (1 << 15)                         // OVER8  = 1; Oversampling by 8
            | (1 << 13)                         // UE     = 1; USART enabled
            | (0 << 12)                         // M      = 0; Word length is 1 start bit, 8 data bits
            | (0 << 10)                         // PCE    = 0; No parity control
            | (1 <<  5)                         // RXNEIE = 1; RXNE interrupt enabled
            | (1 <<  3)                         // TE     = 1; Transmitter enabled
            | (1 <<  2)                         // RE     = 1; Receiver enabled
            ;
  USART_CR2 = 0
            | (0 << 12)                         // STOP = 00b; 1 stop bit
            ;
  USART_CR3 = 0
            | (0 << 11)                         // ONEBIT = 0; Three sample bit method
            | (0 <<  7)                         // DMAT   = 0; interrupt-driven transmission
            ;
  //
  // Set baudrate
  //
  Div = Baudrate * 8;                       // We use 8x oversampling.
  Div = ((2 * (UART_BASECLK)) / Div) + 1;   // Calculate divider for baudrate and round it correctly.
  Div = Div / 2;
  if (Div > 0xFFF) {
    Div = 0xFFF;        // Limit to 12 bit (mantissa in BRR)
  }
  if (Div >= 1) {
    USART_BRR = 0xFFF0 & (Div << 4);    // Use only mantissa of fractional divider
  }
  //
  // Setup callbacks which are called by ISR handler and enable interrupt in NVIC
  //
  _cbOnRx = cbOnRx;
  _cbOnTx = cbOnTx;
  // Let FreeRTOS and RTT critical sections protect the recorder state.
  NVIC_SetPriority(USART_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  NVIC_EnableIRQ(USART_IRQn);
}
