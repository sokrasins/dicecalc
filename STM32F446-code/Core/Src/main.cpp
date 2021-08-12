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
#include "Prng.h"

ExpressionDisplay expression_list;
Entropy ent;
Console console;
Keyboard kbd;
Gui gui;

// Interface between timer ISR and entropy object
void entropy_cb(void) {
	ent.interrupt_cb();
}

void keyboard_cb(void) {
	//volatile uint32_t time = HAL_GetTick();
	kbd.check_for_changes();
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

  Prng &rng = Prng::get_instance();
  uint8_t seed[32] = {0};	// TODO: seed with real entropy
  rng.set_seed(seed);

  KeyEvent evt;
  while(kbd.get_event(&evt)) {
	  // Drain current list of keyevents
  }

  while (1)
  {
	  bool update = false;
	  while(kbd.get_event(&evt)) {
		  update = true;
		  expression_list.key_event(&evt);
	  }

	  if (update) {
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
