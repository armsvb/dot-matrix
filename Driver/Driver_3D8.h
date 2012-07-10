/*
 * Driver3D8.h
 *
 *  Created on: 2012-6-14
 *      Author: agu
 */

#ifndef DRIVER_3D8_H_
#define DRIVER_3D8_H_

#include "DotMatrix.h"
#include "Driver_1818_138.h"

class Driver_3D8:public Driver_1818_138
{
public:
	Driver_3D8(DotMatrix & dm, uint8_t pin_din, uint8_t pin_clk, uint8_t pin_latch, uint8_t pin_en, uint8_t pin_rext,
			uint8_t pin_a2, uint8_t pin_a1, uint8_t pin_a0, uint16_t scan_speed = 0x600);


	void display(byte times = 0x01) const;

	void setMode(byte mode = 0);

	virtual ~Driver_3D8();

private:

	void (Driver_3D8::*_setCol)(byte row) const;

	void setColxyz(byte row) const;
	void setColzxy(byte row) const;
	void setColyzx(byte row) const;
};

#endif /* DRIVER3D8_H_ */
