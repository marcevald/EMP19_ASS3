/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (EMP)
*
* MODULENAME.: gpio_lcd.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Setup GPIO for EMP-Board
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
#include "gpio_lcd.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void gpio_lcd( void )
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  int dummy;

  // Enable the GPIO port that is used for the LCD display, and Status-LED
  // 
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOC;

  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  // Set the direction as output (PC4, PC5, PC6 and PC7).
  GPIO_PORTC_DIR_R |= 0xF0;
  // Set the direction as output (PD2, PD3 and PD6)
  GPIO_PORTD_DIR_R |= 0x4C;

  // Enable the GPIO pins for digital function (PC4, PC5, PC6 and PC7).
  GPIO_PORTC_DEN_R |= 0xF0;
  // Enable the GPIO pins for digital function (PD2, PD3 and PD6).
  GPIO_PORTD_DEN_R |= 0x4C;


}


/****************************** End Of Module *******************************/


