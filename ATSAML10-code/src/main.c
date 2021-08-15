/*******************************************************************************
  Main Source File

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system

  Peripherals:
    SPI: Epaper comm
    I2C: I/O Expander comm
    EIC: Wakeup sources from I/O expander
 *******************************************************************************/

/********************
 Include Files
 *******************/

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// Systick timeout callback
void timeout (uintptr_t context) {
    LED_Toggle();    
}


// Main application
int main ( void ) {
    //RSTC_RESET_CAUSE reset_cause;
            
    // Initialize all modules
    SYS_Initialize ( NULL );
    
    // Check cause of last reset
    //reset_cause = RSTC_ResetCauseGet();
    //if(reset_cause == RSTC_RCAUSE_POR_Msk) {
    //    
    //}
    
    // Start Systick. Probably don't need in my application
    // SYSTICK_TimerCallbackSet(&timeout, (uintptr_t) NULL);
    // SYSTICK_TimerStart();
    
    /* Seed RNG */
    
    /* Load NVM??? */
    
    /* Setup Display */
    
    while(1) {
        // Disable I2C?
        // Disable SPI
        // Enter standby mode. We'll sit here until a key is pressed
        PM_StandbyModeEnter();
        
        /* Get Button Presses */
        
        /* Update Expression */
        
        /* Update Display */
    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );
}
