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

#ifndef PWM_CPP
#define PWM_CPP 1
#include "SensorBase.cpp"
class PWM : public SensorBase{

	private:
		int Dmax = 127;
		int DdeadbandMax = 0;
		int Dcenter = 0;
		int DdeadbandMin = 0;
		int Dmin = 127;
		void pollMotor();

	public:

		unsigned char speed; /**< Current Pulse Value (Default: 0) */
		int motorPort; /**< Port that the PWM Object corresponds to */
		bool disable = 0; /**< If True, Disables the Motor (Default: FALSE) */
		int enableDeadband = 0; /**< If True, Enables the Deadband (Default: FALSE) */

		/**
		 * The Constructor, Sets Up the Class
		 * @param port the port that the object uses
		 */
		PWM(int port);
		/**
			* The Constructor, Sets Up the Class
			* @param port the port that the object uses
			* @param curval the pulse value that the object starts with
		*/
		PWM(int port, int curval);
		/**
			* Maps a motor speed from FRC Style ( -1.0 -> 1.0 ) to VeX Style ( -127 -> 127)
			* @param port the port that the object uses
			* @return value mapped from -1.0 -> 1.0  to -127 -> 127
		*/
		int EasyMapping(int oneScaleValue);
		/**
			 Return the port that the PWM Object corresponds to
			 @return motor port ( 1 -> 10 )
		*/
		int getPort();
		/**
			Return the pulse that the PWM Object is running
			@return motor pulse ( -127 -> 127 )
		*/
		int getPulse();
		/**
			Return the raw speed that the PWM Object is running
			@return raw motor value ( 0 -> 255 )
		*/
		int getRaw();

		/**
			Sets the Deadband Parameters and Enables the Deadband
			@param max Max Value Motor Can Run At
			@param deadbandMax Max Value Motor Runs at 0 Value
			@param deadmandMin Lowest Value Motor Runs at 0 Value
			@param min Lowest Value Motor Can Run At
		*/
		void setDeadband(int max, int deadbandMax, int deadbandMin, int min);
		/**
			Sets the pulse that the PWM Object is running at
			@param pulse motor pulse ( -127 -> 127 )
		*/
		void setPulse(int pulse);
		/**
			Sets the raw speed that the PWM Object is running at
			@param raw raw motor value ( 0 -> 255 )
		*/
		void setRaw(int raw);
		/**
			Enables/Disables The Deadband
			@param runDeadband to run deadband or not
		*/
		void deadbandEnable(bool runDeadband);

};
/**
 *
 */

PWM::PWM (int port) {
	speed = 0;
	if(checkPWMPort(port))
		motorPort = port;
	else if (port > 10)
		port = 10;
	else
		port = 1;
	motorPort = port;
	pollMotor();
}

PWM::PWM (int port, int curval) {
	speed = curval;
	if(checkPWMPort(port))
		motorPort = port;
	else if (port > 10)
		port = 10;
	else
		port = 1;
	motorPort = port;
	pollMotor();
}

int PWM::EasyMapping (int oneScaleValue) {
	return (oneScaleValue - (-1.0)) * (127 - (-127)) / (1.0 - (-1.0)) + (-127);
}

int PWM::getPort () {
	return motorPort;
}

int PWM::getPulse () {
	return speed;
}

int PWM::getRaw () {

	return (speed - (-127)) * (254 - 0) / (127 - (-127)) + (-0) + 1;
}

void PWM::setDeadband(int max, int deadbandMax, int deadbandMin, int min) {
	enableDeadband = 1;
	Dmax = max;
	DdeadbandMax = deadbandMax;
	DdeadbandMin = deadbandMin;
	Dmin = min;
	pollMotor();
}

void PWM::setPulse(int pulse) {
	if( pulse > -127 && pulse < 127)
		speed = pulse;
	pollMotor();
}

void PWM::setRaw(int raw) {
	speed = (raw - (0)) * (127 - (-128)) / (255 - (0)) + (-127);
	pollMotor();
}

void PWM::pollMotor() {
	int zero = 0;
	if(enableDeadband) {
		zero = speed > Dmin ? (speed > Dmax ? 1 : 0) : 0;
		zero = zero ? (speed < DdeadbandMax ? (speed > DdeadbandMin ? 1 : 0) : 0) : 0;
	}
	if(!zero || !enableDeadband)
		motorSet(motorPort, speed);
	else
		motorSet(motorPort, 0);

}

void PWM::deadbandEnable(bool rundeadband) {
	enableDeadband = rundeadband;

}

#endif
