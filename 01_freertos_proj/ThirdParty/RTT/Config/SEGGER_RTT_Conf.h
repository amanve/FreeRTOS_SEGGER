/*********************************************************************
*                   (c) SEGGER Microcontroller GmbH                  *
*                        The Embedded Experts                        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
*        SEGGER RTT * Real Time Transfer for embedded targets        *
*                  https://github.com/SEGGERMicro/RTT                *
*                                                                    *
**********************************************************************

---------------------------END-OF-HEADER------------------------------
Purpose : User configuration file for RTT.
          For available configuration,
          refer to SEGGER_RTT_ConfDefaults.h.

----------------------------------------------------------------------
*/

#ifndef SEGGER_RTT_CONF_H
#define SEGGER_RTT_CONF_H


/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/

// Match FreeRTOS BASEPRI: priority 5 with four implemented priority bits.
// The recorder UART must also run at priority 5 or lower urgency.
#define SEGGER_RTT_MAX_INTERRUPT_PRIORITY (0x50)
#define SEGGER_RTT_MAX_NUM_UP_BUFFERS      (3)
#define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS    (3)

#endif
/*************************** End of file ****************************/
