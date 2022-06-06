
#include "ttim.h"
#include "stm32l4xx_hal.h"

#include <stdarg.h>
/* make this ttim interfaces public to be able to print the ttim object structure or debug . */
extern ttim_list_t ttim_list;
extern UART_HandleTypeDef huart1;

TTIM_COUNT_T _ttim_remaining_time( TTIM_HND_T hnd );
bool _ttim_is_any_running();
bool _ttim_is_paused( TTIM_HND_T hnd );
bool _ttim_is_stopped( TTIM_HND_T hnd );
bool _ttim_node_is_valid( ttim_t *node );
bool _ttim_time_is_valid( TTIM_COUNT_T time );
TTIM_HND_T _ttim_get_hnd( void *ptr );


void log_debug( const char *fmt, ... )
{
    char buf[256];
    va_list args;
    va_start( args, fmt );
    int i = vsnprintf( buf, sizeof( buf ), fmt, args );
    va_end( args );
    HAL_UART_Transmit( &huart1, ( uint8_t * )buf, i, HAL_MAX_DELAY );
}


void print_tim_list()
{
    ttim_node_t *node = &ttim_list.entry;
    TTIM_COUNT_T temp = node->t;
    static uint16_t print_idx = 0;
    TTIM_CRITICAL_START()

    log_debug( "[%02u]  tb: %02u {", print_idx, node->t );
    print_idx++;

    while ( 1 )
    {
        node = node->next;

        if ( !_ttim_node_is_valid( ( ttim_t * )node ) )
        {
            break;
        }

        TTIM_HND_T hnd = _ttim_get_hnd( node );

        log_debug( "%u (to: %2u d: %2d) ", hnd, temp, ( _ttim_time_is_valid( node->t ) ? node->t : -1 ) );

        temp += node->t;

        if ( _ttim_node_is_valid( ( ttim_t * )node->next ) )
        {
            // HAL_UART_Transmit( &huart1 , " -> " , 4 , 1000 );
            log_debug( " -> " );
            //            PRINTF( " -> " );
        }
    }

    log_debug( "}\n" );

    TTIM_CRITICAL_END();
}
