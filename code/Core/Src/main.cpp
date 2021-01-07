/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "dev_config.h"
#include "ExpressionDisplay.h"
#include "Gpio.h"
#include "KeyEvent.h"
#include "Keyboard.h"

ExpressionDisplay display = ExpressionDisplay();

// MAIN
extern "C" int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  DEV_Init();

  Gpio led = Gpio(LD2_GPIO_Port, LD2_Pin);
  led.enable(GPIO_OUTPUT);

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
	DEV_Delay_ms(200);
	led.toggle();

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
