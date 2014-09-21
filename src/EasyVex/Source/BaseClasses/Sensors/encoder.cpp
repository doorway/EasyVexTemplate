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
#ifndef ENCODER_CPP
#define ENCODER_CPP 1
#include "SensorBase.cpp"
class Encoder : public SensorBase{

private:
	int lastcount = 0;
	int lasttime = 0;

public:

	int sensorport = 0;
	bool IME;
	Encoder(int SensorPort, bool IME);
	int getCounts();
	int getRaw();
	int getDirection();

	void reset();
	void pollEncoder();


};


Encoder::Encoder(int SensorPort, bool IME_in)
{
	lastcount = 0;
	lasttime = 0;
	if(checkI2CPort(SensorPort) || checkDigitalPort(SensorPort) || SensorPort == 13)
		sensorport = SensorPort;
	else
		sensorport = 13;
	IME = IME_in;
}
int Encoder::getCounts()
{
	if(sensorport == 13)
		return 0;
	else
	{

	}
	return 0;
}

int Encoder::getRaw()
{
	if(this->sensorport == 13)
		return 0;
	else
	{

	}
	return 0;

}

int Encoder::getDirection()
{
	if(this->sensorport == 13)
		return 0;
	else
	{

	}
	return 0;
}

void Encoder::reset()
{

	if(!(this->sensorport == 13))
	{

	}
}

void Encoder::pollEncoder()
{

	if(!(this->sensorport == 13))
	{

	}
}
#endif

