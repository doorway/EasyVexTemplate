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

#ifndef ACCSENSOR_CPP_
#define ACCSENSOR_CPP_

#include "sensorbase.cpp"
class Accelerometer : public SensorBase{

private:
	int sensorport = 0;
	int curval = 0;
	int multipier;
public:

	Accelerometer(int SensorPort);
	int getAcceleration();
	void setCalibrate();
	void reset();
	void pollSensor();


};

Accelerometer::Accelerometer(int SensorPort)
{
	if(checkAnalogPort(SensorPort))
		sensorport = SensorPort;
	else
		sensorport = 13;
	if(sensorport != 13)
		analogCalibrate(sensorport);
	curval = 0;
	multipier = 0;
}
int Accelerometer::getAcceleration()
{
	pollSensor();
	if(sensorport == 13)
		return 0;
	else
		return curval;
}
void Accelerometer::reset()
{
	if(sensorport != 13)
		gyroReset(gyro);
}
void Accelerometer::setMultiplier(int multi)
{
	if(sensorport != 13) {
		analogCalibrate(sensorport);
		reset();
		pollSensor();
	}
}
void Accelerometer::pollSensor()
{
	if(sensorport != 13)
		curval = analogReadCalibratedHR(sensorport);
}



#endif /* GYROSENSOR_CPP_ */
