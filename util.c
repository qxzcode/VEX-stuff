bool turnFlywheelOn = false;
word flywheelSpeed = 80;

task flywheelTask() {
	// monitor turnFlywheelOn and control the motor safely
	word fwMotorVal = 0;
	while (true) {
		// target speed for the motor
		word targetSpd = turnFlywheelOn? flywheelSpeed : 0;

		// if it's greater than current, set it, otherwise "ramp down"
		if (targetSpd >= fwMotorVal)
			fwMotorVal = targetSpd;
		else {
			fwMotorVal--;
			wait1Msec(30);
		}

		// set the motor value
		motor[flywheel1] = motor[flywheel2] = fwMotorVal;
	}
}
