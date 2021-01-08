/* Includes ------------------------------------------------------------------*/
#include <Device.h>
#include <Gpio.h>
#include "main.h"

#include "ExpressionDisplay.h"
#include "KeyEvent.h"
#include "Keyboard.h"
#include "Console.h"
#include "EPD.h"

ExpressionDisplay expression_list = ExpressionDisplay();
//Spi test_spi;

// MAIN
extern "C" int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  DEV_Init();

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
