#ifndef TTIM_CONFIG_H
#define TTIM_CONFIG_H

#include "stm32l4xx_hal.h"

/* GENERAL =============================================================================================================================== */

#define TTIM_CB_MODE                TTIM_CB_MODE_PARAM
#define TTIM_MM_MODE                TTIM_MM_MODE_STATIC
#define TTIM_COUNT                  4

/* Critical section */
#define TTIM_CRITICAL_START()       uint32_t  primask_bit = __get_PRIMASK(); \
                                    __set_PRIMASK(1) ;
#define TTIM_CRITICAL_END()         __set_PRIMASK(primask_bit);


/* TIMEBASE LL CONFIGURATION USING TIM6 AND STM32CUBE HA ================================================================================= */
extern LPTIM_HandleTypeDef hlptim1;

#define TTIM_TIMEBASE_INIT()        //already done in the main.
#define TTIM_TIMEBASE_START(TIME)   LPTIM_Start(TIME)
#define TTIM_TIMEBASE_IS_RUNNING()
#define TTIM_TIMEBASE_STOP()        HAL_LPTIM_SetOnce_Stop_IT(&hlptim1)
#define TTIM_TIMEBASE_ELAPSED()     HAL_LPTIM_ReadCounter(  &hlptim1 )


#endif // TTIM_CONFIG_H
