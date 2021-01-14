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

extern "C" {
	#include "GUI_Paint.h"
}

ExpressionDisplay expression_list;
Entropy ent;
Console console;
Keyboard kbd;
Epaper disp;

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

  disp = Epaper();
  disp.open();

  disp.init(EPD_UPDATE_FULL);
  //disp.clear();

  /* Initialize all configured peripherals */
  Epaper disp = Epaper();
  disp.open();
  uint16_t image_size = 4000;

  uint8_t screen_image[image_size];
  Paint_NewImage(screen_image, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
  Paint_SelectImage(screen_image);
  Paint_SetMirroring(MIRROR_HORIZONTAL); //
  Paint_Clear(WHITE);

  disp.display_base(screen_image);
  disp.init(EPD_UPDATE_PARTIAL);
  Delay_ms(3000);


  /*
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
  */
/*
  Paint_NewImage(screen_image, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
  Paint_SelectImage(screen_image);
  Paint_SetMirroring(MIRROR_HORIZONTAL); //
  Paint_Clear(WHITE);

  disp.init(EPD_UPDATE_FULL);
  disp.display_base(screen_image);

  disp.init(EPD_UPDATE_PARTIAL);
  Paint_SelectImage(screen_image);

      Paint_ClearWindows(10, 100, 250, 100 + Font20.Height, WHITE);
      Paint_DrawTime(10, 100, &sPaint_time, &Font20, WHITE, BLACK);

      disp.display_part(screen_image);
      Delay_ms(500);//Analog clock 1s

*/
  //disp.init(EPD_UPDATE_FULL);
  //disp.display_base(screen_image);



  KeyEvent key_event;
  uint8_t num_lines = 1;

  while(kbd.check_for_changes(&key_event)) {

  }

  while (1)
  {
	  /*
	  ent.collect();
	  while(ent.collecting()) {
		  Delay_ms(1);
	  }
	  ent.get_samps(rands);
	  Delay_ms(1000);

	  ent.collect();
	  while(ent.collecting()) {
		  Delay_ms(1);
	  }
	  ent.get_samps(&rands[64]);
	  Delay_ms(1000);
	  */
	  /*
	  for (int i=0; i<ENTROPY_BYTES; i++) {
		  msg[2*i] = rands[i] & 0xF;
		  msg[2*1+1] = rands[i] >> 4;
	  }

	  console.log(msg, 256);

	  Delay_ms(1000);
	  */
    if (kbd.check_for_changes(&key_event)) {
    	expression_list.key_event(&key_event);

    	uint8_t cur_lines = expression_list.num_lines();
    	LineEntry *last_line = expression_list.line(cur_lines-1);

    	if (cur_lines > num_lines) {
    		uint8_t end_line = 0;
    		if (cur_lines > 4) {
    			end_line = cur_lines-4;
    		}

    		Paint_Clear(WHITE);
    		uint16_t y_coord = 100;
    		for (uint8_t lineidx = cur_lines; lineidx>end_line; lineidx--) {
    			LineEntry *last_line = expression_list.line(lineidx-1);
    			Paint_DrawString_EN(10, y_coord, last_line->to_string().c_str(), &Font20, WHITE, BLACK);
    			y_coord -= 25;
    		}

    		disp.init(EPD_UPDATE_FULL);
    		disp.display_base(screen_image);
    		num_lines = cur_lines;
    		disp.init(EPD_UPDATE_PARTIAL);
    	} else {
    		Paint_ClearWindows(10, 100, 250, 100 + Font20.Height, WHITE);
    		Paint_DrawString_EN(10, 100, last_line->to_string().c_str(), &Font20, WHITE, BLACK);
    		disp.display_part(screen_image);
    	}
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
