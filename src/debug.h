#include "fw_uart.h"

#ifdef DEBUG
#define DEBUG_INIT(baud) \
    UART1_Config8bitUart(UART1_BaudSource_Timer1, HAL_State_ON, baud) 
#else
#define DEBUG_INIT(baud)
#endif

#ifdef DEBUG
#define DEBUG_PRINTLN(str) \
    UART1_TxString(str "\r\n");
#else
#define DEBUG_PRINTLN(str)
#endif
