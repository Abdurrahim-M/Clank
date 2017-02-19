#include "DriveSystem.h"

class Commands : private DriveSystem{

private:
	void StraightDrive(double distance, double speed){
		double leftEncoder = Left_Encoder->GetDistance();
		double rightEncoder = Right_Encoder->GetDistance();
		double avgEnc = (leftEncoder + rightEncoder)/2.0;
		float angle = ahrs->GetYaw();

		if(avgEnc < distance){
			leftMotors(((-0.01)*(angle))+speed);
			rightMotors(-(((0.01)*(angle))+speed));
		}else{
			allMotors(0);
		}
	}
	void Turn(double target_degrees, double speed){

		double angle = ahrs->GetAngle();

		if(target_degrees > 0){
			while(angle < target_degrees ){
				rightMotors(-speed);
				leftMotors(speed);
			}
		}else if(target_degrees < 0){
			while(angle > target_degrees ){
				rightMotors(speed);
				leftMotors(-speed);
			}
		}else{
			allMotors(0);
		}
}
	void Stop(){
		allMotors(0);
	}
};

class Modes : private Commands{
	void leftSide(){
			StraightDrive(1, 0.4);
			Turn(45, 0.4);
			StraightDrive(0.5, 0.4);
		}

	void center(){
			StraightDrive(1, 0.4);
		}

	void rightSide(){
		StraightDrive(1, 0.4);
		Turn(45, 0.4);
		StraightDrive(0.5, 0.4);
	}
};
