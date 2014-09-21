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

#ifndef SENSORBASE_CPP_
#define SENSORBASE_CPP_

class SensorBase
{

private:

public:
	SensorBase();
	bool checkPWMPort(int port);
	bool checkAnalogPort(int port);
	bool checkDigitalPort(int port);
	bool checkI2CPort(int port);
};
SensorBase::SensorBase()
{

}
bool SensorBase::checkPWMPort(int port)
{
	if(port >= 1 && port <= 10 )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool SensorBase::checkAnalogPort(int port)
{
	if(port >= 1 && port <= 8 )
		{
			return true;
		}
		else
		{
			return false;
		}
}
bool SensorBase::checkDigitalPort(int port)
{
	if(port >= 1 && port <= 12 )
		{
			return true;
		}
		else
		{
			return false;
		}
}
bool SensorBase::checkI2CPort(int port)
{
	if(port >= 1 && port <= 8 )
		{
			return true;
		}
		else
		{
			return false;
		}
}
#endif /* SENSORBASE_CPP_ */
