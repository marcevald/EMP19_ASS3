#include <stdint.h>
#include "emp_type.h"
#include "lcd.h"
#include "gpio_lcd.h"
#include "tm4c123gh6pm.h"
#include "swtimers.h"
#include "systick.h"
#include "uart0.h"


extern INT16S tic;


int main()
{
  INT8U alive_timer = TIM_500_MSEC;

  disable_global_int();
  init_systick();
  gpio_lcd();
  lcd_init();
  uart0_init(9600, 8, 1, 0);
  enable_global_int();
  
  INT32U counter_clock  = 0;
  INT32U timer_min      = TIM_1_MIN;
  INT32U timer_hour     = TIM_1_HOUR;
  INT16U timer_sec      = TIM_1_SEC;

  INT32U hours          = 0;
  INT32U minutes        = 0;

  INT8U toggle          = 1;
/*
  set_cursor(6,0);
  send_data('0');
  send_data('0');
  send_data(':');
  send_data('0');
  send_data('0');
  clear_screen();
*/
    while(1)
    {
    while( !tic );
	// The following will be executed every 5mS
    tic--;
       
        // The following blinks the red status LED on EMP-Board.
        if( ! --alive_timer )
        {
        alive_timer        = TIM_500_MSEC;
        GPIO_PORTD_DATA_R ^= 0x40;
        }

        if (uart0_rx_rdy()) 
        {
            if (uart0_getc() == '0') 
            {
                clear_screen();
            }
            else
            {
                send_data(uart0_getc());
            }
        }

    //counter_clock++;
    //if ( counter_clock == 17280000)
   // {
     //   counter_clock = 0;
    //}

/*
    if ( !--timer_sec ) 
    {   
        toggle ^= 1;

        if ( toggle ) 
        {
            set_cursor(8,0);
            send_data(':');
        }
        else
        {
            set_cursor(8,0);
            send_data(' ');
        }

        timer_sec = TIM_1_SEC;
    }

/////////////////////////////////////////////////////////////////////////
  
    if ( !--timer_min ) 
    {   
        minutes++;

        //Calculate chars + 48 to make right ASCII char - 48 = '0'
        INT8U char1 = ( minutes / 10 ) + 48;
        INT8U char2 = ( minutes % 10 ) + 48;

        if (minutes == 60) 
        {
            minutes = 0;
        }

        if ( minutes < 10 ) 
        {
            set_cursor(9,0);
            send_data('0');
            send_data(char2);        
        }
        else
        {
            set_cursor(9,0);
            send_data(char1);
            send_data(char2); 
        }

        timer_min = TIM_1_MIN;
    }
///////////////////////////////////////////////////////////////////////
    if ( !--timer_hour ) 
    {   
        hours++;

        //Calculate chars + 48 to make right ASCII char - 48 = '0'
        INT8U char1 = ( hours / 10 ) + 48;
        INT8U char2 = ( hours % 10 ) + 48;

        if (hours == 24) 
        {
            hours = 0;
        }

        if ( hours < 10 ) 
        {
            set_cursor(6,0);
            send_data('0');
            send_data(char2);        
        }
        else
        {
            set_cursor(6,0);
            send_data(char1);
            send_data(char2); 
        }

        timer_hour = TIM_1_HOUR;
    }
    */

    }        
}
    
       