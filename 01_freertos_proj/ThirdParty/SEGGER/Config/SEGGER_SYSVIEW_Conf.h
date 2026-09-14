/*********************************************************************
*                   (c) SEGGER Microcontroller GmbH                  *
*                        The Embedded Experts                        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
*         SEGGER SystemView  * Real-time application analysis        *
*              https://github.com/SEGGERMicro/SystemView             *
*                                                                    *
**********************************************************************

---------------------------END-OF-HEADER------------------------------

Purpose : SEGGER SystemView configuration file.
          Set defines which deviate from the defaults (see SEGGER_SYSVIEW_ConfDefaults.h) here.          

Additional information:
  Required defines which must be set are:
    SEGGER_SYSVIEW_GET_TIMESTAMP
    SEGGER_SYSVIEW_GET_INTERRUPT_ID
  For known compilers and cores, these might be set to good defaults
  in SEGGER_SYSVIEW_ConfDefaults.h.
  
  SystemView needs a (nestable) locking mechanism.
  If not defined, the RTT locking mechanism is used,
  which then needs to be properly configured.
*/

#ifndef SEGGER_SYSVIEW_CONF_H
#define SEGGER_SYSVIEW_CONF_H

/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/

/*********************************************************************
*
*       Define: SEGGER_SYSVIEW_SECTION
*
*  Description
*    Section to place the SystemView RTT Buffer into.
*  Default
*    undefined: Do not place into a specific section.
*  Notes
*    If SEGGER_RTT_SECTION is defined, the default changes to use
*    this section for the SystemView RTT Buffer, too.
*/
#if !(defined SEGGER_SYSVIEW_SECTION) && (defined SEGGER_RTT_BUFFER_SECTION)
  #define SEGGER_SYSVIEW_SECTION                  SEGGER_RTT_BUFFER_SECTION
#endif


/*********************************************************************
* TODO: Add your defines here.                                       *
**********************************************************************
*/
// Reserve channel 0 for terminal output; stream trace on channel 1.
#define SEGGER_SYSVIEW_RTT_CHANNEL             1
#define SEGGER_SYSVIEW_POST_MORTEM_MODE        0
#define SEGGER_SYSVIEW_RTT_BUFFER_SIZE         4096
#define SEGGER_SYSVIEW_USE_INTERNAL_RECORDER    1
#define SEGGER_SYSVIEW_START_ON_INIT            0
extern void HIF_UART_EnableTXEInterrupt(void);

/*
 * CRITICAL for continuous UART recording.
 * When new SystemView data arrives, restart UART transmission.
 */
#define SEGGER_SYSVIEW_ON_EVENT_RECORDED(NumBytes) \
  do {                                             \
    (void)(NumBytes);                              \
    HIF_UART_EnableTXEInterrupt();                 \
  } while (0)

#endif  // SEGGER_SYSVIEW_CONF_H

/*************************** End of file ****************************/
