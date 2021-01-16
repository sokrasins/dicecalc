/*
 * Gui.cpp
 *
 *  Created on: Jan 15, 2021
 *      Author: sok
 */

#include "Gui.h"

#include "EPD.h"
#include "ExpressionDisplay.h"
#include "LineEntry.h"

Gui::Gui() :
m_num_expr(1)
{
	this->m_img = Image(EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
	this->m_img.set_mirroring(MIRROR_HORIZONTAL);
	this->m_img.clear(WHITE);
	this->draw_status_bar();

	this->m_disp = Epaper();
}

void Gui::open() {
	this->m_disp.open();
	this->m_disp.init(EPD_UPDATE_FULL);
	this->m_disp.display_base(this->m_img);
	this->m_disp.init(EPD_UPDATE_PARTIAL);
}

void Gui::update(ExpressionDisplay& expr) {
	UpdateMode mode = EPD_UPDATE_PARTIAL;

	this->m_img.clear(WHITE);

	this->draw_status_bar();

	int cur_lines = expr.num_lines();
	if (cur_lines != this->m_num_expr) {
		mode = EPD_UPDATE_FULL;
	}

	this->m_num_expr = cur_lines;
	int last_line = cur_lines - MAX_EXPRESSIONS;
	if (last_line < 0) { last_line = 0; }


	bool first = true;
	uint16_t x_coord, y_coord = 100;
	for (; cur_lines > last_line; cur_lines--) {
		LineEntry *last_line = expr.line(cur_lines-1);
		string line_string = last_line->to_string();
		x_coord = EXPRESSION_BORDER;

		if(last_line->is_result()) {
			uint8_t len = line_string.length();
			x_coord = EPD_HEIGHT - EXPRESSION_BORDER - len*Font20.Width;
		}
		this->m_img.draw_string(x_coord, y_coord, line_string.c_str(), &Font20, WHITE, BLACK);
	    if (first) {
	    	x_coord += line_string.length() * Font20.Width;
	    	this->m_img.draw_char(x_coord, y_coord, '_', &Font20, BLACK, WHITE);
	    	first = false;
	    }

		y_coord -= 20;
	}

	if (mode == EPD_UPDATE_PARTIAL) {
		this->m_disp.display_part(this->m_img);
	} else {
		this->m_disp.init(EPD_UPDATE_FULL);
		this->m_disp.display_base(this->m_img);
		this->m_disp.init(EPD_UPDATE_PARTIAL);
	}
}

void Gui::draw_status_bar() {
	string banner = "Dice Roller";
	int x_text = (EPD_HEIGHT - banner.length()*Font12.Width) / 2;
	this->m_img.draw_rect(0, 0, EPD_HEIGHT, 15, BLACK, POINT_SIZE_1X1, DRAW_FILL_FULL);
	this->m_img.draw_string(x_text, 2, banner.c_str(), &Font12, BLACK, WHITE);
}

