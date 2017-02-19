#include <memory>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Robot.h"
#include "DriveSystem.h"
#include "DriveSystem.cpp"
#include "WPILib.h"
#include "AHRS.h"
#include "AutoCommands.h"

class Execute : private Modes{
private:
	int mode = frc::SmartDashboard::GetNumber("Autonomous Modee", mode);
	void Execute(mode){
		switch (mode){
			case 1:
				leftSide();
				break;
			case 2:
				center();
				break;
			case 3:
				rightSide();
				break;
}}

public:
	void Robot::AutonomousPeriodic() {
		Execute();
	}
};
