/*
 * HIF_UART.h
 *
 *  Created on: 13-Sept-2026
 *      Author: Aman Verma
 */

#ifndef SEGGER_REC_HIF_UART_H_
#define SEGGER_REC_HIF_UART_H_

#include <stdint.h>
#define OS_FSYS 100000000L   // Hardcoded MCU core frequency
#define RCC_BASE_ADDR       0x40023800

#define OFF_AHB1ENR         0x30        // AHB1 peripheral clock enable register
#define OFF_APB1ENR         0x40        // APB1 peripheral clock enable register
#define OFF_APB2ENR         0x44        // APB2 peripheral clock enable register

#define RCC_AHB1ENR         *(volatile uint32_t*)(RCC_BASE_ADDR + OFF_AHB1ENR)
#define RCC_APB1ENR         *(volatile uint32_t*)(RCC_BASE_ADDR + OFF_APB1ENR)
#define RCC_APB2ENR         *(volatile uint32_t*)(RCC_BASE_ADDR + OFF_APB2ENR)

#define GPIOA_BASE_ADDR     0x40020000

#define OFF_MODER           0x00        // GPIOx_MODER    (GPIO port mode register)
#define OFF_OTYPER          0x04        // GPIOx_OTYPER   (GPIO port output type register)
#define OFF_OSPEEDR         0x08        // GPIOx_OSPEEDR  (GPIO port output speed register)
#define OFF_PUPDR           0x0C        // GPIOx_PUPDR    (GPIO port pull-up/pull-down register)
#define OFF_IDR             0x10        // GPIOx_IDR      (GPIO port input data register)
#define OFF_ODR             0x14        // GPIOx_ODR      (GPIO port output data register)
#define OFF_BSRR            0x18        // GPIOx_BSRR     (GPIO port bit set/reset register)
#define OFF_LCKR            0x1C        // GPIOx_LCKR     (GPIO port configuration lock register)
#define OFF_AFRL            0x20        // GPIOx_AFRL     (GPIO alternate function low register)
#define OFF_AFRH            0x24        // GPIOx_AFRH     (GPIO alternate function high register)

#define USART1_BASE_ADDR    0x40011000
#define USART2_BASE_ADDR    0x40004400

#define OFF_SR              0x00        // Status register
#define OFF_DR              0x04        // Data register
#define OFF_BRR             0x08        // Baudrate register
#define OFF_CR1             0x0C        // Control register 1
#define OFF_CR2             0x10        // Control register 2
#define OFF_CR3             0x14        // Control register 3


#define UART_BASECLK        OS_FSYS / 2       // USART2 runs on APB1 clock
#define GPIO_BASE_ADDR      GPIOA_BASE_ADDR
#define USART_BASE_ADDR     USART2_BASE_ADDR
#define GPIO_UART_TX_BIT    2                // USART2 TX: Pin pa2
#define GPIO_UART_RX_BIT    3                 // USART2 RX: Pin pa3
#define USART_IRQn          USART2_IRQn

#define GPIO_MODER          *(volatile uint32_t*)(GPIO_BASE_ADDR + OFF_MODER)
#define GPIO_AFRH           *(volatile uint32_t*)(GPIO_BASE_ADDR + OFF_AFRH)
#define GPIO_AFRL           *(volatile uint32_t*)(GPIO_BASE_ADDR + OFF_AFRL)

#define USART_SR            *(volatile uint32_t*)(USART_BASE_ADDR + OFF_SR)
#define USART_DR            *(volatile uint32_t*)(USART_BASE_ADDR + OFF_DR)
#define USART_BRR           *(volatile uint32_t*)(USART_BASE_ADDR + OFF_BRR)
#define USART_CR1           *(volatile uint32_t*)(USART_BASE_ADDR + OFF_CR1)
#define USART_CR2           *(volatile uint32_t*)(USART_BASE_ADDR + OFF_CR2)
#define USART_CR3           *(volatile uint32_t*)(USART_BASE_ADDR + OFF_CR3)

#define USART_RXNE              5     // Read data register not empty flag (CR1)
#define USART_TC                6     // Transmission complete flag (CR1)
#define USART_RX_ERROR_FLAGS  0xB     // Parity, framing, overrun error flags (CR1)
#define USART_RXNEIE            5     // Read data register not empty interrupt enable (CR1)
#define USART_TCIE              6     // Transmission complete interrupt enable (CR1)
#define USART_TXE               7     // Transmit data register empty (Does NOT indicate that byte has already been sent just indicates that it has been copied to the shift register)
#define USART_TXEIE             7     // Transmit data register empty interrupt enable


typedef void UART_ON_RX_FUNC(uint8_t Data);
typedef int  UART_ON_TX_FUNC(uint8_t* pChar);

typedef UART_ON_TX_FUNC* UART_ON_TX_FUNC_P;
typedef UART_ON_RX_FUNC* UART_ON_RX_FUNC_P;

void HIF_UART_Init(uint32_t Baudrate, UART_ON_TX_FUNC_P cbOnTx, UART_ON_RX_FUNC_P cbOnRx);
void HIF_UART_EnableTXEInterrupt(void);

#endif /* SEGGER_REC_HIF_UART_H_ */
