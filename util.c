#include "pid.c"

// inputs from user or autonomous control
bool turnFlywheelOn = false;
float flywheelSpeed = 800*648 /* *360*60/(1000/30) */; // in encoder ticks per control step

float flSpd=0, frSpd=0, blSpd=0, brSpd=0;


// main task to control motors with PID
task motorControlTask() {
	// PID constants for flywheels
	const float kP = 127.0 / (800*648);
	const float kD = 0;
	const float kI = 0;
	// PID constants for drive wheels
	const float kPd = 127.0 / (800*648);
	const float kDd = 0;
	const float kId = 0;

	// PID states
	pidVals pid1,pid2, pidFL,pidFR,pidBL,pidBR;
	initPID(pid1, flywheel1,flywheelEnc1, kP,kI,kD, true, 1);
	initPID(pid2, flywheel2,flywheelEnc2, kP,kI,kD, true, 1);
	initPID(pidFL, driveFL,encFL, kPd,kId,kDd, false);
	initPID(pidFR, driveFR,encFR, kPd,kId,kDd, false);
	initPID(pidBL, driveBL,encBL, kPd,kId,kDd, false);
	initPID(pidBR, driveBR,encBR, kPd,kId,kDd, false);

	// loop
	while (true) {
		/// do a PID step all controlled motors motors
		// flywheels
		pid1.targetVal = pid2.targetVal = flywheelSpeed;
		updatePID(pid1);
		updatePID(pid2);
		// drive wheels
		const float kDrive = 1.0;
		pidFL.targetVal += flSpd*kDrive-SensorValue[encFL];
		SensorValue[encFL] = 0;
		updatePID(pidFL);
		pidFR.targetVal += frSpd*kDrive-SensorValue[encFR];
		SensorValue[encFR] = 0;
		updatePID(pidFR);
		pidBL.targetVal += blSpd*kDrive-SensorValue[encBL];
		SensorValue[encBL] = 0;
		updatePID(pidBL);
		pidBR.targetVal += brSpd*kDrive-SensorValue[encBR];
		SensorValue[encBR] = 0;
		updatePID(pidBR);

		// wait in between (to "ramp down" and be able to calculate speeds)
		wait1Msec(30);
	}
}
