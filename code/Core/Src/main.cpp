/* Includes ------------------------------------------------------------------*/
#include <Device.h>
#include <Gpio.h>
#include "main.h"

#include <string.h>

#include "ExpressionDisplay.h"
#include "KeyEvent.h"
#include "Keyboard.h"
#include "Console.h"
#include "EPD.h"
#include "Entropy.h"
#include "Gui.h"

ExpressionDisplay expression_list;
Entropy ent;
Console console;
Keyboard kbd;
Gui gui;

// Interface between timer ISR and entropy object
void entropy_cb(void) {
	ent.interrupt_cb();
}

// MAIN
extern "C" int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  DEV_Init();

  expression_list = ExpressionDisplay();
  expression_list.new_line();

  ent = Entropy();
  ent.open();

  console = Console();
  console.open(USART2);

  kbd = Keyboard();
  kbd.open();

  gui = Gui();
  gui.open();
  gui.update(expression_list);

  KeyEvent key_event;

  while(kbd.check_for_changes(&key_event)) {
	  // Drain current list of keyevents
  }

  while (1)
  {
    if (kbd.check_for_changes(&key_event)) {
    	expression_list.key_event(&key_event);
    	gui.update(expression_list);
    }
  }

}

// Handle application errors
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
}
