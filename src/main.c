#include <stdint.h>
#include "emp_type.h"
#include "lcd.h"
#include "gpio_lcd.h"
#include "tm4c123gh6pm.h"
#include "swtimers.h"
#include "systick.h"


extern INT16S tic;


int main()
{
  INT8U alive_timer = TIM_500_MSEC;

  disable_global_int();
  init_systick();
  gpio_lcd();
  lcd_init();
  enable_global_int();
  
  INT8U test = 0;
  INT8U test2 = 0;
  INT16U timer;
  INT16U timer2;

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

        if (test2 == 0) 
        {
            set_cursor(6,0);
            write_string("25 23");       
            test2++;
        }
        

        
       
        if (test == 0) 
        {
            test++;
            timer = TIM_1_SEC;    
        }

        

         if ( !--timer ) 
        {
            set_cursor(8,0);
            send_data(':');
            timer2 = TIM_1_SEC;

        }


         if ( !--timer2 ) 
        {
            set_cursor(8,0);
            send_data(' ');
            test = 0;
            timer = TIM_1_SEC;

        }
    }        
}
    
       