/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (EMP)
*
* MODULENAME.: lcd.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Hitachi HD44780U LCD driver library
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 130319  MEE   Module created.
*
*****************************************************************************/


/***************************** Include files *******************************/
#include <stdint.h>
#include "emp_type.h"
#include "tm4c123gh6pm.h"
#include "lcd.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void send_command( INT8U com )
/*****************************************************************************
*   Input    : -Command to send
*   Output   : -
*   Function : Sends command to display
******************************************************************************/
{
    rs_off();
    enable_off();
    GPIO_PORTC_DATA_R &= 0x0F;
    GPIO_PORTC_DATA_R |= (( com & 0xF0 ) );
    delay_micro(5);
    enable_on();
    delay_micro(5);
    enable_off();

    GPIO_PORTC_DATA_R &= 0x0F;
    GPIO_PORTC_DATA_R |= ( ( com & 0x0F ) << 4 );
    delay_micro(5);
    enable_on();
    delay_micro(5);
    enable_off();
    rs_off();
    delay_micro(5);
}

   void send_command_4bit( INT8U com )
/*****************************************************************************
*   Input    : -Command to send !!4 bit only!!
*   Output   : -
*   Function : Sends command to display
******************************************************************************/
{
    rs_off();
    enable_off();
    GPIO_PORTC_DATA_R &= 0x0F; // Turn everithing on 4bit bus off.
    GPIO_PORTC_DATA_R |= (com << 4);
    enable_on();
    delay_micro(5);
    enable_off();
    delay_micro(5);
}
   


void lcd_init( void )
/*****************************************************************************
*   Input    : -Charachter in INT8U format
*   Output   : -
*   Function : Write Character To Display
******************************************************************************/
{
    delay_milli(40);

    send_command_4bit(0x3);
    delay_milli(5);
    send_command_4bit(0x3);
    delay_micro(120);
    send_command_4bit(0x3);

    send_command_4bit(0x2); // Set 4-bit mode

    send_command(0x28); // 4-bit mode, 2/16 display, 5x8 font

    send_command(0x08); // Display off
    
    send_command(0x0C); // Display On, Cursor Off  

    send_command(0x06); // Entry Mode

    send_command(0x01); // Home

    delay_milli(1);     // Delay to give LCD controller time to Catch Up.
    
}


void enable_on( void )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Run enable, when data is on the lines.
******************************************************************************/
{
        // Turn on Enable pin
        GPIO_PORTD_DATA_R |= 0b00001000;

}

void enable_off( void )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Run enable, when data is on the lines.
******************************************************************************/
{
        // Turn on Enable pin
        GPIO_PORTD_DATA_R &= ~( 0b00001000 );

}


void rs_on( void )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Run enable, when data is on the lines.
******************************************************************************/
{
        // Turn on RS pin
        GPIO_PORTD_DATA_R |= 0b00000100;

}

void rs_off( void )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Run enable, when data is on the lines.
******************************************************************************/
{
        // Turn off RS pin
        GPIO_PORTD_DATA_R &= ~( 0b00000100 );

}


void delay_micro( INT8U n )
/*****************************************************************************
*   Input    : - Microseconds to delay
*   Output   : -
*   Function :  Delay for n miliseconds
******************************************************************************/
{
        for(INT16U i = 0; i < n; i++)
        {
            for(INT16U j = 0; j < 3; j++)
            {
                //Do Nothting
            }
            
        }  

}

void delay_milli( INT8U n )
/*****************************************************************************
*   Input    : - Milliseconds to delay
*   Output   : -
*   Function : Delay for n miliseconds
******************************************************************************/
{
        for(INT16U i = 0; i < n; i++)
        {
            for(INT16U j = 0; j < 3180; j++)
            {
                
            }
            
        }
}

void send_data( INT8U data )
/*****************************************************************************
*   Input    : -Command to send !!4 bits only!!
*   Output   : -
*   Function : Sends command to display
******************************************************************************/
{
    rs_on();
    enable_off();
    GPIO_PORTC_DATA_R &= 0x0F;
    GPIO_PORTC_DATA_R |= ( ( data & 0xF0 ) );
    delay_micro(5);
    enable_on();
    delay_micro(5);
    enable_off();
    GPIO_PORTC_DATA_R &= 0x0F;
    GPIO_PORTC_DATA_R |= ( ( data & 0x0F ) << 4 );
    delay_micro(5);
    enable_on();
    delay_micro(5);
    enable_off();
    rs_off();
    delay_micro(5);
}

void clear_screen( void )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Clears LCD Screen
******************************************************************************/
{
    send_command(0x01);
    delay_milli(1); 
}

void write_string(const char *str )
/*****************************************************************************
*   Input    : - String to display
*   Output   : -
*   Function : Display a string on Display
******************************************************************************/
{
    register char c;

    while ( (c = *str++) )
    {
        send_data(c);
    }
     
}

void set_cursor( INT8U x, INT8U y)
/*****************************************************************************
*   Input    : - X, Y position of cursor. X is horizontal position, Y is Vertical Position.
*   Output   : -
*   Function : Puts the Cursor where described by x, y coordinates.
******************************************************************************/
{
        send_command(0x80 + x);
        send_command(0x40 + y);    
}
/****************************** End Of Module *******************************/


