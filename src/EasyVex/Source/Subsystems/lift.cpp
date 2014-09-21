#include "lift.h"

void LiftSystem::InitLiftSystem() {
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


LiftSystem::LiftSystem(int leftMotorChannel, int rightMotorChannel)
{
	InitLiftSystem();
	m_frontLeftMotor = new Motor(leftMotorChannel);
	m_frontRightMotor = new Motor(rightMotorChannel);
	setMotorOutput(0.0);
}
LiftSystem::LiftSystem(Motor leftMotor, Motor rightMotor)
{
	InitLiftSystem();
	m_frontLeftMotor = leftMotor;
	m_frontRightMotor = rightMotor;
	setMotorOutput(0.0);
}
	
LiftSystem::LiftSystem(int leftFrontMotorChannel, int leftBackMotorChannel, int rightFrontMotorChannel, int rightBackMotorChannel)
{
	InitLiftSystem();
	m_frontLeftMotor = new Motor(leftFrontMotorChannel);
	m_frontRightMotor = new Motor(rightFrontMotorChannel);
	m_rearLeftMotor = new Motor(leftBackMotorChannel);
	m_rearRightMotor = new Motor(rightBackMotorChannel);
	setMotorOutput(0.0);
}
LiftSystem::LiftSystem(Motor leftFrontMotor, Motor leftBackMotor, Motor rightFrontMotor, Motor rightBackMotor)
{
	InitLiftSystem();
	//?// xccxxcdsxxzsdc();
	m_frontLeftMotor = leftFrontMotor;
	m_frontRightMotor = rightFrontMotor;
	m_rearLeftMotor = leftBackMotor;
	m_rearRightMotor = rightBackMotor;
	setMotorOutput(0.0);
}

void LiftSystem::controlLift(JoystickButton up, JoystickButton down, int speed = 127, int deadspeed = 0)
{
	control(getDigital(up), getDigital(down), speed, deadspeed);
} /* DONE */			
void LiftSystem::control(bool up, bool down, int speed = 127, int deadspeed = 0)
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
void LiftSystem::setMotorOutput(float output)
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
void LiftSystem::setReversedMotor(int motor, bool isInverted)
{
	reversedMotors[motor] = isInverted == true ? 1 : -1;
}
void LiftSystem::setMotorEncoder(int motor, int encoderPort, bool IME)
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
void LiftSystem::setMotorEncoder(int motor, int encoderPort)
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
