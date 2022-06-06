#pragma once



/* user must ensure that the HW has a 32768 cristal and the RCC is configured properly to source LTPIM */
#define LPTIM_FIXED_CLOCK 32768
/* user must ensure the RCC is configured properly to this value */
#define LPTIM_FIXED_PRESCALER LPTIM_PRESCALER_DIV32

#if LPTIM_FIXED_PRESCALER == LPTIM_PRESCALER_DIV32
#define LPTIM_FIXED_PRESCALER_VALUE 32
#endif

void print_tim_list();