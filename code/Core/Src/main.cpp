/* Includes ------------------------------------------------------------------*/
#include <Device.h>
#include <Gpio.h>
#include "main.h"

#include "ExpressionDisplay.h"
#include "KeyEvent.h"
#include "Keyboard.h"
#include "Console.h"
#include "EPD.h"
#include "Entropy.h"

ExpressionDisplay expression_list;

Entropy ent;

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
  ent = Entropy();
  ent.open();

  /* Initialize all configured peripherals */
  Epaper disp = Epaper();
  disp.open();

  uint8_t num_keys = 9;
  KeyType seq[] = {
		  KEY_2,
		  KEY_0,
		  KEY_D12,
		  KEY_PLUS,
		  KEY_4,
		  KEY_2,
		  KEY_TIMES,
		  KEY_0,
		  KEY_ENTER,
  };

  // New calc line
  KeyEvent keypress;
  keypress.state = KEYSTATE_DOWN;

  for (uint8_t i=0; i<num_keys; i++) {
	  keypress.key = seq[i];
	  expression_list.key_event(&keypress);
  }

  string line;
  for (uint8_t i=0; i<expression_list.num_lines(); i++) {
	  line = expression_list.line(i)->to_string();
  }

  while (1)
  {
    Delay_ms(1000);
    ent.clear_samps();
    ent.collect();
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
