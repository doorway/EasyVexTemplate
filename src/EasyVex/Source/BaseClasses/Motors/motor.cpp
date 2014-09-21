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

#include "PWM.cpp"
#include "encoder.cpp"


class Motor : public PWM, public Encoder {

private:

public:


	Motor::Motor(int MotorPort);
	Motor(int MotorPort, int EncoderPort);
	Motor(int MotorPort, int EncoderPort, bool IME);



};


Motor::Motor(int MotorPort) : PWM( MotorPort ), Encoder(13, 0)
{

}
Motor::Motor(int MotorPort, int EncoderPort) : PWM( MotorPort ), Encoder(EncoderPort, 0)
{

}
Motor::Motor(int MotorPort, int EncoderPort, bool IME) : PWM( MotorPort ), Encoder(EncoderPort, IME)
{

}

#endif

