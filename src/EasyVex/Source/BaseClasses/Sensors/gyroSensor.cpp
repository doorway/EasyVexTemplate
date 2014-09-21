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
#ifndef GYROSENSOR_CPP_
#define GYROSENSOR_CPP_

#include "sensorbase.cpp"
class GyroSensor : public SensorBase{

private:
	Gyro gyro;

public:

	int sensorport = 0;
	int curval = 0;
	int multipier;
	GyroSensor(int SensorPort);
	GyroSensor(int SensorPort, int multi);
	int getAngle();
	void setMultiplier(int multi);
	void reset();
	void pollSensor();


};

GyroSensor::GyroSensor(int SensorPort)
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
GyroSensor::GyroSensor(int SensorPort, int multi)
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
int GyroSensor::getAngle()
{
	pollSensor();
	if(sensorport == 13)
		return 0;
	else
		return curval;
}
void GyroSensor::reset()
{
	if(sensorport != 13)
		gyroReset(gyro);
}
void GyroSensor::setMultiplier(int multi)
{
	if(sensorport != 13) {
		gyro = gyroInit(sensorport, multi);
		reset();
		pollSensor();
	}
}
void GyroSensor::pollSensor()
{
	if(sensorport != 13)
		curval = gyroGet(gyro);
}



#endif /* GYROSENSOR_CPP_ */
