/*
	Created on: 2012-01-25
	Updated on: 2012-06-03
	Author: Weihong Guan
	Blog: http://aguegu.net
	E-mail: weihong.guan@gmail.com
	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
	http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "drvdm_74hc595x74hc138.h"
#include "dot-matrix.h"
#include "dot-font.h"
#include "dot-string.h"
#include "vfont_7x3.h"

DotMatrix dm(24, 7);
DrvDm74hc595X74hc138 dmd(dm, A0, A1, A2, A3, 7, 6, 5, 4);
DotFont df(dm);
DotString ds(df, dm.countCol(), true);

extern HardwareSerial Serial;
byte index = 0;

void setup()
{
	pinMode(8, OUTPUT);
	digitalWrite(8, LOW);

	pinMode(9, OUTPUT);
	digitalWrite(9, HIGH);

	dm.clear(0x00);

	df.setPattern(VFONT_7X3, VFONT_7X3_STATE);
	ds.printf("Serial");
	ds.postAt(0,0);

	dmd.setSpeed(0x200);

	Serial.begin(9600);
}

void loop()
{
	dmd.display(0x08);
}

void serialEvent()
{
	while (Serial.available())
	{
		if (index < dm.countCol())
		{
			byte cData = Serial.read();

			ds.setChar(index, cData);
			index++;

			if (cData == 0x0A)
			{
				dm.clear();
				ds.setChar(index-1, 0);
				ds.postAt(0,0);
				Serial.println(ds.getString());
				index = 0;
			}
		}
	}
}