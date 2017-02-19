#ifndef SRC_DRIVESYSTEM_H_
#define SRC_DRIVESYSTEM_H_

#include <memory>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "DriveSystem.h"
#include "WPILib.h"
#include "AHRS.h"

class DriveSystem{
private:
	VictorSP *right = new VictorSP(0);
	VictorSP *left = new VictorSP (5);
	VictorSP *right2 = new VictorSP (1);
	VictorSP *left2 = new VictorSP (6);
	VictorSP *right3 = new VictorSP(2);
	VictorSP *left3 = new VictorSP (7);

	VictorSP *conveyormotor = new VictorSP (3);
	VictorSP *intakemotor = new VictorSP (4);
	VictorSP *outakemotor = new VictorSP (8);
	VictorSP *winchmotor = new VictorSP (9);

	Joystick *stick = new Joystick(0);

	Encoder *Right_Encoder = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	Encoder *Left_Encoder = new Encoder(2, 3, false, Encoder::EncodingType::k4X);

	AHRS *ahrs;

	void allMotors(double x){
		left->Set(x);
		left2->Set(x);
		left3->Set(x);
		right->Set(x);
		right2->Set(x);
		right3->Set(x);
	}

	void rightMotors(double x){
			right->Set(x);
			right2->Set(x);
			right3->Set(x);
		}

	void leftMotors(double x){
				left->Set(x);
				left2->Set(x);
				left3->Set(x);
			}

	void EncoderInit(Encoder* enc, bool invertDirection, double scaleFactor){
			enc->SetMaxPeriod(.1);
			enc->SetMinRate(10);
			enc->SetDistancePerPulse(0.001440 * scaleFactor);
			enc->SetReverseDirection(invertDirection);
			enc->SetSamplesToAverage(4);
			enc->Reset();
		}

	void Straight(double distance, double speed);

	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;

public:
	DriveSystem();
	virtual ~DriveSystem();
};

#endif /* SRC_DRIVESYSTEM_H_ */
