/*
 * bsp.c
 *
 *  Created on: Jun 4, 2022
 *      Author: Buck
 */

#include "stm32l4xx_hal.h"
#include "bsp.h"


extern  LPTIM_HandleTypeDef hlptim1;        //obj reference


/* ensure that MX_TIM2_Init initializes the timer in the best suitable configuration for all the
 * expected ms counts to be feasibles.  */
uint32_t TimeToTicks( uint32_t ms )
{
    /* This function calculates the needed ticks or TIM6 to perform a given number of ms.
     * If the current TIM6 config does not allow to fullfil the required ms  it is reconfigured to provide a correct number of ticks. OPTIONAL
     */
#ifdef LPTIM_FIXED_CLOCK
    const uint32_t freq = LPTIM_FIXED_CLOCK;
#else
    uint32_t freq = HAL_RCCEx_GetPeriphCLKFreq( RCC_PERIPHCLK_LPTIM1 );
#endif

#ifdef LPTIM_FIXED_PRESCALER
    const uint32_t prescaler_div = LPTIM_FIXED_PRESCALER_VALUE;
#else
    uint32_t prescaler_div = hlptim1.Init.Clock.Prescaler;
#endif

    uint32_t period = ( ms * freq ) / ( prescaler_div * 1000 );

    return period;
}

/**
   @brief Callback that will update de timer internal counters and logic

   @param hlptim
 */
void HAL_LPTIM_CompareMatchCallback( LPTIM_HandleTypeDef *hlptim )
{
    ttim_update();
}

/**
   @brief

   @param ms
 */
void LPTIM_Start( uint32_t ms )
{
    HAL_LPTIM_SetOnce_Stop_IT( &hlptim1 );
    uint32_t tick = TimeToTicks( ms );
    HAL_LPTIM_SetOnce_Start_IT( &hlptim1, tick, tick - 20 );
}
