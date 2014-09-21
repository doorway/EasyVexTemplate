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

#ifndef ULTRASONIC_CPP_
#define ULTRASONIC_CPP_
#include "sensorbase.cpp"
class Ultrasonic : public SensorBase{

private:
	Gyro gyro;

public:

	int sensorport = 0;
	int curval = 0;
	int multipier;
	Ultrasonic(int SensorPort);
	int getAngle();
	void setMultiplier(int multi);
	void reset();
	void pollSensor();


};

Ultrasonic::Ultrasonic(int SensorPort)
{
	if(checkAnalogPort(SensorPort))
		sensorport = SensorPort;
	else
		sensorport = 13;
	if(sensorport != 13)
		gyro = gyroInit(sensorport, 0);
	curval = 0;
	multipier = 0;
}

int Ultrasonic::getAngle()
{
	pollSensor();
	if(sensorport == 13)
		return 0;
	else
		return curval;
}
void Ultrasonic::reset()
{
	if(sensorport != 13)
		gyroReset(gyro);
}
void Ultrasonic::setMultiplier(int multi)
{
	if(sensorport != 13) {
		gyro = gyroInit(sensorport, multi);
		reset();
		pollSensor();
	}
}
void Ultrasonic::pollSensor()
{
	if(sensorport != 13)
		curval = gyroGet(gyro);
}



#endif /* ULTRASONIC_CPP_ */
