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


class BasicRobot {
public:
	BasicRobot();
	
	void robotInit();
	void disabledInit();
	void disabledLoop();
	void autoInit();
	void mainAutoCode();
	void driverInit();
	void mainDriverCode();
	
	TaskHandle disableLP;
	TaskHandle autoLP;
	TaskHandle driverLP;
	TaskHandle compLP;
	
	bool IsEnabled();
	bool IsDisabled();
	bool IsAutonomous();
	bool IsOperatorControl();
	
	
	void competitionLoop();
	void startCompetition();

};

BasicRobot::BasicRobot()
{
	disableLP = taskCreate(disabledLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	autoLP = taskCreate(mainAutoCode, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	driverLP = taskCreate(driverLP, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	compLP = taskCreate(competitionLoop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	taskSuspend(disableLP);
	taskSuspend(autoLP);
	taskSuspend(driverLP);
	taskSuspend(compLP);
}

void BasicRobot::robotInit()
{
	print("Running robotInit Function, OVERLOAD ME");
}

void BasicRobot::disabledInit()
{
	print("Running disabledInit Function, OVERLOAD ME");
}

void BasicRobot::disabledLoop()
{
	print("Running disabledLoop Function, OVERLOAD ME");
}
void BasicRobot::autoInit()
{
	print("Running autoInit Function, OVERLOAD ME");
}
void BasicRobot::mainAutoCode()
{
	print("Running mainAutoCode Function, OVERLOAD ME");
}
void BasicRobot::driverInit()
{
	print("Running driverInit Function, OVERLOAD ME");
}
void BasicRobot::mainDriverCode()
{
	print("Running mainDriverCode Function, OVERLOAD ME");
}

	
bool BasicRobot::IsEnabled()
{
	return isEnabled();
}
bool BasicRobot::IsDisabled()
{
	return isEnabled() ? 0 : 1;
}
bool BasicRobot::IsAutonomous()
{
	return isEnabled() ? (isAutonomous() ? 1 : 0): 0;	
}
bool BasicRobot::IsOperatorControl()
{
	return isEnabled() ? (isAutonomous() ? 0 : 1) : 0;	
}
	

void BasicRobot::competitionLoop()
{
	int auto_init_ran = 0;
	int driver_init_ran = 0;
	robotInit();
	while(1)
	{
		if(IsAutonomous())
		{
			if(!auto_init_ran)
				autoInit();
				auto_init_ran = 1;
			taskResume(autoLP);
		}
		else if(IsOperatorControl())
		{
			if(!driver_init_ran)
				driverInit();
				driver_init_ran = 1;
			taskResume(driverLP);
		}
		else
		{
			taskResume(disableLP);
			taskSuspend(autoLP);
			taskSuspend(driverLP);
			taskSuspend(compLP);
		}
	}
}
void BasicRobot::startCompetition()
{
	taskResume(compLP);
}