/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "dev_config.h"
#include "ExpressionDisplay.h"
#include "Gpio.h"
#include "KeyEvent.h"
#include "Keyboard.h"
#include "EPD.h"

ExpressionDisplay display = ExpressionDisplay();
//Spi test_spi;

// MAIN
extern "C" int main(void)
{

  Spi test_spi;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  DEV_Init();

  Epaper paper = Epaper();
  paper.open();

  /* Initialize all configured peripherals */

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
	  display.key_event(&keypress);
  }

  string line;
  for (uint8_t i=0; i<display.num_lines(); i++) {
	  line = display.line(i)->to_string();
  }

  while (1)
  {
	Delay_ms(1000);
	paper.clear();
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
