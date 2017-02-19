#include <memory>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "DriveSystem.h"
#include "DriveSystem.cpp"
#include "WPILib.h"
#include "AHRS.h"
#include "AutoCommands.h"


class Robot: frc::IterativeRobot, private DriveSystem{
public:
	void RobotInit() {
	ahrs = new AHRS(SPI::Port::kMXP);
	ahrs->SetAngleAdjustment(2);
	CameraServer::GetInstance()->StartAutomaticCapture(0);
	CameraServer::GetInstance()->StartAutomaticCapture(1);
	}

	void DisabledInit() {


	}

	void DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	//Resetting gyro angle when the robot is in disabled mode
	ahrs->Reset();
	Right_Encoder->Reset();
	Left_Encoder->Reset();

	}

	void AutonomousInit() {
	//intialzing encoders with right config. Function found in robot.h
	EncoderInit(this->Left_Encoder, false, 1.0);
	EncoderInit(this->Right_Encoder, true, 1.33);
	Right_Encoder->Reset();
	Left_Encoder->Reset();
	ShowData();

	}

	void AutonomousPeriodic();

	void ShowData(){
	double leftEncoder = Left_Encoder->GetDistance();
	double rightEncoder = Right_Encoder->GetDistance();
	double avgEnc = (leftEncoder + rightEncoder) /2.0;
	float angle = ahrs->GetYaw();

	frc::SmartDashboard::PutNumber("Average Encoder Distance", avgEnc);
	frc::SmartDashboard::PutNumber("Right Encoder Distance", rightEncoder);
	frc::SmartDashboard::PutNumber("Left Encoder Distance", leftEncoder);
	frc::SmartDashboard::PutNumber("Angle", angle);

	}

	void TeleopInit() {

	EncoderInit(this->Left_Encoder, false, 1.0);
	EncoderInit(this->Right_Encoder, true, 0.33);
	Right_Encoder->Reset();
	Left_Encoder->Reset();
	ShowData();

	}

	void TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	ShowData();

	//drive system
	double throttle = stick->GetThrottle();
	double y = stick->GetRawAxis(1);
	double z = stick->GetRawAxis(2);

	//changes acceleration to slower
	z = z*((((-throttle)+1)/2));
	y = y*((((-throttle)+1)/2));

	//driving formula
	double leftmotor = z - y;
	double rightmotor = z + y;

	rightMotors(rightmotor);
	leftMotors(leftmotor);

	//intake/outake system
	double RB = stick->GetRawButton(1);
	double LB = stick->GetRawButton(2);

	if (RB) {
		intakemotor->Set(1);
		conveyormotor->Set(1);

	}else if (LB) {
		intakemotor->Set(1);
		conveyormotor->Set(-1);
		outakemotor->Set(1);

	}else if (RB==0 && LB==0){
		intakemotor->Set(0);
		conveyormotor->Set(0);
		outakemotor->Set(0);
	}

	//winch system
	double WinchUp = stick->GetRawButton(5);
	double WinchDown = stick->GetRawButton(6);

	if (WinchUp) {
		winchmotor->Set(-1);

	}else if (WinchDown) {
		winchmotor->Set(1);

	}else if (WinchUp==0 && WinchDown==0) {
		winchmotor->Set(0);
	}

	}

	void TestInit() {

	}

	void TestPeriodic() {
	frc::LiveWindow::GetInstance()->Run();

}
};
START_ROBOT_CLASS(Robot)
