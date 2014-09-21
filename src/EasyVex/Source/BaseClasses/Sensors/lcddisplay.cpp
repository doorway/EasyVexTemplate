/*
This file is part of EasyVex.

EasyVex is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

EasyVex is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with EasyVex.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef LCDSENSOR_CPP_
#define LCDSENSOR_CPP_

#include "sensorbase.cpp"
class LCDDisplay : public SensorBase{
private:

	int sensorport;
	
public:
	int Top = 1;
	int Bottom = 2;
	char TopLine[16];
	char BottomLine[16];
	LCDDisplay(int port);
	void clear();
	void println(int line, char startcol, char * string);
	void updateLCD();
	
};

LCDDisplay::LCDDisplay(int port)
{
	sensorport = port;
}
void LCDDisplay::clear()
{
	for(int i = 0; i < 16; i++)
	{
		TopLine[i]  = ' ';
		BottomLine[i]  = ' ';
	}
	updateLCD();
}
void LCDDisplay::println(int line, char startcol, char * string)
{
	for(int i = startcol; i < 16; i++)
	{
		if(line == 1)
		{
			TopLine[i]  = string[i];
		}
		else
		{
			BottomLine[i]  = string[i];
		}
	}
}
void LCDDisplay::updateLCD()
{
}