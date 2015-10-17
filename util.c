#include "pid.c"

// inputs from user or autonomous control
bool turnFlywheelOn = false;
float flywheelSpeed = 64; // in encoder ticks per control step

float flSpd=0, frSpd=0, blSpd=0, brSpd=0;


// PID constants for flywheels
const float kP = 1.0;//127.0 / (800*648);
const float kD = 0;
const float kI = 0;
// PID constants for drive wheels
const float kPd = 0.2;//127.0 / (800*648);
const float kDd = 0.0;
const float kId = 0.0;
// constant to convert from joystick input to PID target val
const float kDrive = 0.2;

pidVals pid1,pid2, pidFL,pidFR,pidBL,pidBR;


// main task to control motors with PID
void motorControlInit() {

	// PID states
	initPID(pid1, flywheel1,flywheelEnc1, kP,kI,kD, true, 1);
	initPID(pid2, flywheel2,flywheelEnc2, kP,kI,kD, true, 1);
	//initPID(pidFL, driveFL,encFL, kPd,kId,kDd, false);
	//initPID(pidFR, driveFR,encFR, kPd,kId,kDd, false);
	initPID(pidBL, driveBL,encBL, kPd,kId,kDd, false);
	initPID(pidBR, driveBR,encBR, kPd,kId,kDd, false);

	//SensorValue[encFL] = 0;
	//SensorValue[encFR] = 0;
	SensorValue[encBL] = 0;
	SensorValue[encBR] = 0;
}

// loop
int val[4];
void motorControlUpdate() {//motor[flywheel1] = 127;return;
		/// do a PID step all controlled motors motors
		// FLYWHEELS
		pid1.targetVal = pid2.targetVal = turnFlywheelOn?flywheelSpeed:0;
		//updatePID(pid1);
		//updatePID(pid2);
		// DRIVE WHEELS
		/*pidFL.targetVal += flSpd*kDrive-(val[0]=SensorValue[encFL]);
		SensorValue[encFL] -= val[0];
		updatePID(pidFL);
		pidFR.targetVal += frSpd*kDrive-(val[1]=SensorValue[encFR]);
		SensorValue[encFR] -= val[1];
		updatePID(pidFR);*/
		pidBL.targetVal += blSpd*kDrive-(val[2]=SensorValue[encBL]);
		SensorValue[encBL] -= val[2];
		updatePID(pidBL);
		pidBR.targetVal += brSpd*kDrive-(val[3]=SensorValue[encBR]);
		SensorValue[encBR] -= val[3];
		updatePID(pidBR);//*/

		// wait in between (to "ramp down" and be able to calculate speeds)
		wait1Msec(30);
	//}
}
