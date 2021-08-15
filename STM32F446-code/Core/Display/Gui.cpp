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
	this->draw_result_border();
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

	this->draw_result_border();
	this->draw_status_bar();

	int cur_lines = expr.num_lines();
	if (cur_lines != this->m_num_expr) {
		mode = EPD_UPDATE_FULL;
	}

	this->m_num_expr = cur_lines;
	int last_line = 0;//cur_lines - MAX_EXPRESSIONS;
	//if (last_line < 0) { last_line = 0; }


	bool first = true;
	uint16_t x_coord, y_coord = 100;
	for (; cur_lines > last_line; cur_lines--) {
		LineEntry *last_line = expr.line(cur_lines-1);
		string line_string = last_line->to_string();
		x_coord = EXPRESSION_BORDER;

		if(last_line->is_result()) {
			y_coord -= 20;
			x_coord = this->result_x();
		}

		if (y_coord <= 0) {
			break;
		}

		this->m_img.draw_string(x_coord, y_coord, line_string.c_str(), &Font20, WHITE, BLACK);
	    if (first) {
	    	x_coord += line_string.length() * Font20.Width;
	    	this->m_img.draw_char(x_coord, y_coord, '_', &Font20, BLACK, WHITE);
	    	first = false;
	    }
	}

	if (mode == EPD_UPDATE_PARTIAL) {
		//this->m_disp.set_power(1);
		this->m_disp.init(EPD_UPDATE_PARTIAL);
		this->m_disp.display_part(this->m_img);
		//this->m_disp.set_power(0);
	} else {
		//this->m_disp.set_power(1);
		this->m_disp.init(EPD_UPDATE_FULL);
		this->m_disp.display_base(this->m_img);
		//this->m_disp.set_power(0);
	}
}

int Gui::result_x() {
	return EPD_HEIGHT -
			 (1 * EXPRESSION_BORDER) -
			 (RESULT_CHARS * Font20.Width);
}

void Gui::draw_status_bar() {
	string expr_banner = "Expression";
	string result_banner = "Roll";
	int result_banner_loc =  this->result_x();

	this->m_img.draw_rect(0, 0, EPD_HEIGHT, 15, BLACK, POINT_SIZE_1X1, DRAW_FILL_FULL);
	this->m_img.draw_string(EXPRESSION_BORDER, 2, expr_banner.c_str(),
			&Font12, BLACK, WHITE);
	this->m_img.draw_string(result_banner_loc, 2, result_banner.c_str(),
			&Font12, BLACK, WHITE);

}

void Gui::draw_result_border() {
	 uint16_t x = this->result_x() - EXPRESSION_BORDER;

	 this->m_img.draw_line(x, EPD_WIDTH, x, 0,
			 BLACK, POINT_SIZE_1X1, LINE_STYLE_SOLID);
}

