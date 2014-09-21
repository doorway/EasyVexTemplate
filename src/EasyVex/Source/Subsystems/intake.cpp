#include "intake.h"

void Intake::InitIntake() {
	m_frontLeftMotor = NULL;
	m_frontRightMotor = NULL;
	m_rearRightMotor = NULL;
	m_rearLeftMotor = NULL;
	m_maxOutput = 127;
	for (int i=0; i < maxMotors; i++)
	{
		m_invertedMotors[i] = 0;
	}
}


Intake::Intake(int leftMotorChannel, int rightMotorChannel)
{
	InitIntake();
	m_LeftMotor = new Motor(leftMotorChannel);
	m_RightMotor = new Motor(rightMotorChannel);
	setMotorOutput(0.0);
}
Intake::Intake(Motor leftMotor, Motor rightMotor)
{
	InitIntake();
	m_LeftMotor = leftMotor;
	m_RightMotor = rightMotor;
	setMotorOutput(0.0);
}

void Intake::controlIntake(JoystickButton up, JoystickButton down, int speed = 127)
{
	control(getDigital(up), getDigital(down), speed);
} /* DONE */			
void Intake::control(bool up, bool down, int speed = 127)
{
	if(up)
	{
		setMotorOutput(speed);
	}
	else if(down)
	{
		setMotorOutput(speed * -1);
	}
	else
	{
		setMotorOutput(deadspeed);
	}
} /* DONE */
void Intake::setMotorOutput(float output)
{
	if(GetNumMotors() == 4) 
	{
		m_frontLeftMotor->setPulse(leftOutput * reversedMotors[0]);
		m_frontRightMotor->setPulse(rightOutput * reversedMotors[1]);
		m_rearLeftMotor->setPulse(leftOutput * reversedMotors[2]);
		m_rearRightMotor->setPulse(rightOutput * reversedMotors[3]);
	}
	else
	{
		m_frontLeftMotor->setPulse(leftOutput * reversedMotors[0]);
		m_frontRightMotor->setPulse(rightOutput * reversedMotors[1]);
	}
}
void Intake::setReversedMotor(int motor, bool isInverted)
{
	reversedMotors[motor] = isInverted == true ? 1 : -1;
}
void Intake::setMotorEncoder(int motor, int encoderPort, bool IME)
{
	if(motor == 1)
	{
		m_frontLeftMotor = new Motor(m_frontLeftMotor->getPort(), encoderPort, IME);
	}
	else if(motor == 2)
	{
		m_frontRightMotor = new Motor(m_frontRightMotor->getPort(), encoderPort, IME);
	}
	else if(motor == 3)
	{
		m_rearLeftMotor = new Motor(m_rearLeftMotor->getPort(), encoderPort, IME);
	}
	else
	{
		m_rearRightMotor = new Motor(m_rearRightMotor->getPort(), encoderPort, IME);
	}
}
void Intake::setMotorEncoder(int motor, int encoderPort)
{
	if(motor == 1)
	{
		m_frontLeftMotor = new Motor(m_frontLeftMotor->getPort(), encoderPort);
	}
	else if(motor == 2)
	{
		m_frontRightMotor = new Motor(m_frontRightMotor->getPort(), encoderPort);
	}
	else if(motor == 3)
	{
		m_rearLeftMotor = new Motor(m_rearLeftMotor->getPort(), encoderPort);
	}
	else
	{
		m_rearRightMotor = new Motor(m_rearRightMotor->getPort(), encoderPort);
	}
}
