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

#ifndef DIGITALINPUT_CPP_
#define DIGITALINPUT_CPP_
#include "sensorbase.cpp"
class DigitalInput : public SensorBase{

private:


public:

	int sensorport = 0;
	int curval = 0;
	DigitalInput(int SensorPort);
	int isPressed();
	void pollSensor();


};

DigitalInput::DigitalInput(int SensorPort)
{
	if(checkDigitalPort(SensorPort))
		sensorport = SensorPort;
	else
		sensorport = 13;

	curval = 0;
}
int DigitalInput::isPressed()
{
	pollSensor();
	if(sensorport == 13)
		return 0;
	else
		return curval == 0 ? true : false;
}
void DigitalInput::pollSensor()
{
	if(sensorport != 13)
		curval = digitalRead(sensorport)
}




#endif /* DIGITALINPUT_CPP_ */
