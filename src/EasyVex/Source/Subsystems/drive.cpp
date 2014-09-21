#include "drive.h"

void RobotDrive::InitRobotDrive() {
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


DriveSystem::DriveSystem(int leftMotorChannel, int rightMotorChannel)
{
	InitRobotDrive();
	m_frontLeftMotor = new Motor(leftMotorChannel);
	m_frontRightMotor = new Motor(rightMotorChannel);
	SetLeftRightMotorOutputs(0.0, 0.0);
}
DriveSystem::DriveSystem(Motor leftMotor, Motor rightMotor)
{
	InitRobotDrive();
	m_frontLeftMotor = leftMotor;
	m_frontRightMotor = rightMotor;
	SetLeftRightMotorOutputs(0.0, 0.0);
}
	
DriveSystem::DriveSystem(int leftFrontMotorChannel, int leftBackMotorChannel, int rightFrontMotorChannel, int rightBackMotorChannel)
{
	InitRobotDrive();
	m_frontLeftMotor = new Motor(leftFrontMotorChannel);
	m_frontRightMotor = new Motor(rightFrontMotorChannel);
	m_rearLeftMotor = new Motor(leftBackMotorChannel);
	m_rearRightMotor = new Motor(rightBackMotorChannel);
	SetLeftRightMotorOutputs(0.0, 0.0);
}
DriveSystem::DriveSystem(Motor leftFrontMotor, Motor leftBackMotor, Motor rightFrontMotor, Motor rightBackMotor)
{
	InitRobotDrive();
	m_frontLeftMotor = leftFrontMotor;
	m_frontRightMotor = rightFrontMotor;
	m_rearLeftMotor = leftBackMotor;
	m_rearRightMotor = rightBackMotor;
	SetLeftRightMotorOutputs(0.0, 0.0);
}
DriveSystem::Drive(int speed, int turn)
{
	int leftOutput;
	int rightOutput;
	if (curve < 0)
	{
		float value = log(-turn);
		float ratio = (value - 0.5)/(value + 0.5);
		if (ratio == 0) ratio =.0000000001;
		leftOutput = speed / ratio;
		rightOutput = speed;
	}
	else if (curve > 0)
	{
		float value = log(turn);
		float ratio = (value - m_sensitivity)/(value + m_sensitivity);
		if (ratio == 0) ratio =.0000000001;
		leftOutput = speed;
		rightOutput = speed / ratio;
	}
	SetLeftRightMotorOutputs(leftOutput, rightOutput);
}
void DriveSystem::TankDrive(JoystickAxis leftStick, JoystickAxis rightStick, bool squaredInputs = true)
{
	int leftValue = getAnalog(leftStick);
	int rightValue = getAnalog(rightStick);
	TankDrive(leftValue, rightValue, squaredInputs);
}
void DriveSystem::TankDrive(Stick leftStick, Stick rightStick, bool squaredInputs = true)
{
	int leftValue = getAnalog(leftStick.Y);
	int rightValue = getAnalog(rightStick.Y);
	TankDrive(leftValue, rightValue, squaredInputs);
}
void DriveSystem::TankDrive(float leftValue, float rightValue, bool squaredInputs = true)
{
	// square the inputs (while preserving the sign) to increase fine control while permitting full power
	if(squaredInputs)
	{
		leftValue = map(leftValue, -127, 127, -1, 1);
		rightValue = map(rightValue, -127, 127, -1, 1);
		if (leftValue >= 0.0)
		{
			leftValue = (leftValue * leftValue);
		}
		else
		{
			leftValue = -(leftValue * leftValue);
		}
		if (rightValue >= 0.0)
		{
			rightValue = (rightValue * rightValue);
		}
		else
		{
			rightValue = -(rightValue * rightValue);
		}
		leftValue = map(leftValue, -1, 1, -127, 127);
		rightValue = map(leftValue, -1, 1, -127, 127);
	}
	SetMotorOutputs(leftValue, rightValue);
}
void DriveSystem::ArcadeDrive(Stick arcstick, bool squaredInputs = true)
{
	int X = getAnalog(arcstick.X);
	int Y = getAnalog(arcstick.Y);
	ArcadeDrive(X, Y, squaredInputs);
}
void DriveSystem::ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs = true)
{
	int leftMotorOutput = 0;
	int rightMotorOutput = 0;
	if(squaredInputs)
	{
		moveValue = map(moveValue, -127, 127, -1, 1);
		rotateValue = map(rotateValue, -127, 127, -1, 1);
		if (moveValue >= 0.0)
		{
			moveValue = (moveValue * moveValue);
		}
		else
		{
			moveValue = -(moveValue * moveValue);
		}
		if (rotateValue >= 0.0)
		{
			rotateValue = (rotateValue * rotateValue);
		}
		else
		{
			rotateValue = -(rotateValue * rotateValue);
		}
		moveValue = map(moveValue, -1, 1, -127, 127);
		rotateValue = map(rotateValue, -1, 1, -127, 127);
	}
	
	if (moveValue > 0.0)
	{
		if (rotateValue > 0.0)
			{
				leftMotorOutput = moveValue - rotateValue;
				rightMotorOutput = max(moveValue, rotateValue);
			}
		else
			{
				leftMotorOutput = max(moveValue, -rotateValue);
				rightMotorOutput = moveValue + rotateValue;
			}
		}
	else
	{
		if (rotateValue > 0.0)
		{
			leftMotorOutput = - max(-moveValue, rotateValue);
			rightMotorOutput = moveValue + rotateValue;
		}
		else
		{
			leftMotorOutput = moveValue - rotateValue;
			rightMotorOutput = - max(-moveValue, -rotateValue);
		}
	}
	SetMotorOutputs(leftMotorOutput, rightMotorOutput);
}

void MecanumDrive(float x, float y, float rotation, float gyroAngle = 0.0)
{
	double xIn = map(x, -127, 127, -1, 1);
	double yIn = map(y, -127, 127, -1, 1);
	rotation = map(rotation, -127, 127, -1, 1);

	double wheelSpeeds[maxMotors];
	wheelSpeeds[0] = xIn + yIn + rotation;
	wheelSpeeds[1] = -xIn + yIn - rotation;
	wheelSpeeds[2] = -xIn + yIn + rotation;
	wheelSpeeds[3] = xIn + yIn - rotation;


	m_frontLeftMotor->setPulse(wheelSpeeds[0] * reversedMotors[0] * m_maxOutput);
	m_frontRightMotor->setPulse(wheelSpeeds[1] * reversedMotors[1] * m_maxOutput);
	m_rearLeftMotor->setPulse(wheelSpeeds[2] * reversedMotors[2] * m_maxOutput);
	m_rearRightMotor->setPulse(wheelSpeeds[3] * reversedMotors[3] * m_maxOutput);
}
void HolonomicDrive(float magnitude, float direction, float rotation)
{
	magnitude = map(magnitude, -127, 127, -1, 1);
	direction = map(direction, -127, 127, -1, 1);
	rotation = map(rotation, -127, 127, -1, 1);
	
	magnitude = magnitude * sqrt(2.0);
	// The rollers are at 45 degree angles.
	double dirInRad = (direction + 45.0) * 3.14159 / 180.0;
	double cosD = cos(dirInRad);
	double sinD = sin(dirInRad);

	double wheelSpeeds[maxMotors];
	wheelSpeeds[0] = sinD * magnitude + rotation;
	wheelSpeeds[1] = cosD * magnitude - rotation;
	wheelSpeeds[2] = cosD * magnitude + rotation;
	wheelSpeeds[3] = sinD * magnitude - rotation;


	m_frontLeftMotor->Set(wheelSpeeds[0] * reversedMotors[0] * m_maxOutput);
	m_frontRightMotor->Set(wheelSpeeds[1] * reversedMotors[1] * m_maxOutput);
	m_rearLeftMotor->Set(wheelSpeeds[2] * reversedMotors[2] * m_maxOutput);
	m_rearRightMotor->Set(wheelSpeeds[3] * reversedMotors[3] * m_maxOutput);
	
}
void setMotorOutputs(float leftOutput, float rightOutput)
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
void setReversedMotor(int motor, bool isInverted)
{
	reversedMotors[motor] = isInverted == true ? 1 : -1;
}
void DriveSystem::setMotorEncoder(int motor, int encoderPort, bool IME)
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
void DriveSystem::setMotorEncoder(int motor, int encoderPort)
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
void enableDriveDeadband()
{
	if (m_frontLeftMotor) m_frontLeftMotor->enableDeadband();
	if (m_frontRightMotor) m_frontRightMotor->enableDeadband();
	if (m_rearLeftMotor) m_rearLeftMotor->enableDeadband();
	if (m_rearRightMotor) m_rearRightMotor->enableDeadband()
}