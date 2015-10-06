#include "pid.c"

// inputs from user or autonomous control
bool turnFlywheelOn = false;
float flywheelSpeed = 800*648 /* *360*60/(1000/30) */; // in encoder ticks per control step


// main task to monitor values and control the flywheel motors
task motorControlTask() {
	// PID constants
	const float kP = 127.0 / (800*648);
	const float kD = 0;
	const float kI = 0;

	// PID states
	pidVals pid1, pid2;
	initPID(pid1, flywheel1,flywheelEnc1, kP,kI,kD, true, 1);
	initPID(pid2, flywheel2,flywheelEnc2, kP,kI,kD, true, 1);

	// loop
	while (true) {
		// do a PID step for both motors
		pid1.targetVal = pid2.targetVal = flywheelSpeed;
		updatePID(pid1);
		updatePID(pid2);

		// wait in between (to "ramp down" and be able to calculate speeds)
		wait1Msec(30);
	}
}
