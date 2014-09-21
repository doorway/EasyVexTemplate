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
#ifndef LIFTSYSTEM_H
#define LIFTSYSTEM_H


class LiftSystem
{
public:


	LiftSystem(int leftMotorChannel, int rightMotorChannel); /* DONE */
	LiftSystem(Motor leftMotor, Motor rightMotor); /* DONE */
	
	LiftSystem(int leftFrontMotorChannel, int leftBackMotorChannel, int rightFrontMotorChannel, int rightBackMotorChannel); /* DONE */
	LiftSystem(Motor leftFrontMotor, Motor leftBackMotor, Motor rightFrontMotor, Motor rightBackMotor); /* DONE */
	
	void control(JoystickButton up, JoystickButton down, int speed = 127); /* DONE */			
	void control(bool up, bool down, int speed = 127); /* DONE */
	void setMotorOutput(float output); /* DONE */
	void setReversedMotor(int motor, bool isInverted); /* DONE */
	void setMotorEncoder(int motor, int encoderPort, bool IME); /* DONE */
	void setMotorEncoder(int motor, int encoderPort); /* DONE */


protected:
	void InitLiftSystem();
	int maxMotors = 4;
	int reversedMotors[maxMotors];
	int m_maxOutput;
	Motor m_frontLeftMotor;
	Motor m_frontRightMotor;
	Motor m_rearLeftMotor;
	Motor m_rearRightMotor;
	
private:
	int GetNumMotors()
	{
		int motors = 0;
		if (m_frontLeftMotor) motors++;
		if (m_frontRightMotor) motors++;
		if (m_rearLeftMotor) motors++;
		if (m_rearRightMotor) motors++;
		return motors;
	}
};



#endif