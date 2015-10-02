// inputs from user or autonomous control
bool turnFlywheelOn = false;
float flywheelSpeed = 1.0 *360/1000; // in degrees of motor rotation per millisecond


// subroutine for "ramping down" behavior
void setFlywheelVal(short motorID, word &currentVal, word targetVal) {
	// if target is greater than current, set it, otherwise "ramp down"
	if (targetVal >= currentVal)
		currentVal = targetVal;
	else {
		currentVal--;
	}

	// set the motor value
	motor[motorID] = currentVal;
}

// main task to monitor values and control the flywheel motors
task flywheelTask() {
	// these store the current set motor[] values
	word fw1MotorVal = 0, fw2MotorVal = 0;

	// PID constants
	const float kP = 1.0;

	// loop
	while (true) {
		// control for flywheel motor 1
		float actualSpd = (float)SensorValue[flywheelEnc1] / 30;
		SensorValue[flywheelEnc1] = 0;

		float err = flywheelSpeed-actualSpd;
		float P = kP*err;
		setFlywheelVal(flywheel1, fw1MotorVal, fw1MotorVal+P);


		// control for flywheel motor 2
		actualSpd = (float)SensorValue[flywheelEnc2] / 30;
		SensorValue[flywheelEnc2] = 0;

		err = flywheelSpeed-actualSpd;
		P = kP*err;
		setFlywheelVal(flywheel2, fw2MotorVal, fw2MotorVal+P);

		// wait in between (to "ramp down" and be able to calculate speeds)
		wait1Msec(30);
	}
}
