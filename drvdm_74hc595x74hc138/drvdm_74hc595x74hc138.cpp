/*
 drvdm_74hc595x74hc138.cpp
 Driver_595_138 Class for dot-matrix printing on matrix driven by 74HC595 and 74HC138
 Created on: 2012-01-15

 library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 Author: Weihong Guan
 Blog: http://aguegu.net
 E-mail: weihong.guan@gmail.com
 Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 http://creativecommons.org/licenses/by-nc-sa/3.0/

 source host: https://github.com/aguegu/dot-matrix
 */

#include "drvdm_74hc595x74hc138.h"

DrvDm74hc595X74hc138::DrvDm74hc595X74hc138(DotMatrix & dm, uint8_t pin_c_in,
		uint8_t pin_c_oe, uint8_t pin_c_st, uint8_t pin_c_sh, uint8_t pin_r_oe,
		uint8_t pin_r_a2, uint8_t pin_r_a1, uint8_t pin_r_a0,
		uint16_t scan_span) :
		_dm(dm), chip_col(pin_c_in, pin_c_sh, pin_c_st, pin_c_oe), chip_row(
				pin_r_a2, pin_r_a1, pin_r_a0, pin_r_oe)
{
	_row_count = _dm.countRow();
	_bytes_per_row = _dm.countBytePerRow();

	chip_col.setShiftMode();
}

DrvDm74hc595X74hc138::~DrvDm74hc595X74hc138()
{

}

void DrvDm74hc595X74hc138::display()
{
	static byte r = 0;

	chip_col.shiftSendRev(_dm.output() + _bytes_per_row * r, _bytes_per_row);
	chip_row.setOE(false);

	chip_col.shiftLatch();

	chip_row.setValue(r);

	chip_row.setOE(true);

	r++;
	if (r == _row_count)
		r = 0;
}