/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#define TEMP_SENSOR_SLAVE_ADDR          0x004F
#define TEMP_SENSOR_REG_ADDR            0x00

static volatile bool isTemperatureRead = false;
static uint8_t i2cWrData = TEMP_SENSOR_REG_ADDR;
static uint8_t i2cRdData[2] = {0};

static void i2cEventHandler(uintptr_t contextHandle)
{
    if (SERCOM2_I2C_ErrorGet() == SERCOM_I2C_ERROR_NONE)
    {
        isTemperatureRead = true;
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    uint16_t temp = 0;

    // SYSTICK Settings
    SYSTICK_TimerStart();

    // SERCOM2 Settings
    SERCOM2_I2C_CallbackRegister(i2cEventHandler, 0);

    while ( true )
    {
        SERCOM2_I2C_WriteRead(TEMP_SENSOR_SLAVE_ADDR, &i2cWrData, 1, i2cRdData, 2);

        temp = (i2cRdData[0] << 8) | i2cRdData[1];
        printf("Temp: %d.%d C\r\n", temp/256, (temp*100/256)%100);

        SYSTICK_DelayMs(100);

        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

