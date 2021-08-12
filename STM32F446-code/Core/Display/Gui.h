/*
 * Gui.h
 *
 *  Created on: Jan 15, 2021
 *      Author: sok
 */

#ifndef DISPLAY_GUI_H_
#define DISPLAY_GUI_H_

#include "EPD.h"
#include "ExpressionDisplay.h"
#include "Image.h"

#define MAX_EXPRESSIONS 5
#define EXPRESSION_BORDER 5
#define RESULT_CHARS 3
#define RESULT_BORDER_WIDTH 2

class Gui {
	Epaper m_disp;
	Image m_img;
	int m_num_expr;

	void draw_status_bar();
	void draw_result_border();

	int result_x();
public:
	Gui();
	void open();
	void update(ExpressionDisplay& expr);
};

#endif /* DISPLAY_GUI_H_ */
