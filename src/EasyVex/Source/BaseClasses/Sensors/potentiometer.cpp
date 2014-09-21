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

#ifndef POTENTIOMETER_CPP_
#define POTENTIOMETER_CPP_

#include "sensorbase.cpp"
class Potentiometer : public SensorBase{

private:


public:

	int sensorport = 0;
	int curval = 0;
	Potentiometer(int SensorPort);
	int getValue();
	void calibrate();
	void reset();
	void pollSensor();


};

Potentiometer::Potentiometer(int SensorPort)
{

	if(checkAnalogPort(SensorPort)) {
		sensorport = SensorPort;
		analogCalibrate(SensorPort); }
	else
		sensorport = 13;
	curval = 0;
}

int Potentiometer::getValue()
{
	pollSensor();
	if(sensorport == 13)
		return 0;
	else
		return curval;
}
void Potentiometer::reset()
{
	if(sensorport != 13)
		curval = 0;
}
void Potentiometer::calibrate()
{
	if(sensorport != 13)
		analogCalibrate(sensorport);
}
void Potentiometer::pollSensor()
{
	if(sensorport != 13)
		curval = analogReadCalibrated(sensorport);
}


#endif /* POTENTIOMETER_CPP_ */
