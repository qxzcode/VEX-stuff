bool turnFlywheelOn = false;
word flywheelSpeed = 80;

struct pidState {
	float kp, ki, kd;
	float err, errDeriv, errSum;
	float update(float error) {
		errDeriv = error - err;
		errSum += error;
		err = error;
		return kp*err + ki*errSum + kd*errDeriv;
	}
};

task flywheelTask() {
	// monitor turnFlywheelOn and control the motor safely
	word fw1MotorVal = 0, fw2MotorVal = 0;
	while (true) {
		// target speed for the motor
		word targetSpd = turnFlywheelOn? flywheelSpeed : 0;

		// if it's greater than current, set it, otherwise "ramp down"
		if (targetSpd >= fw1MotorVal)
			fw1MotorVal = targetSpd;
		else {
			fw1MotorVal--;
			wait1Msec(30);
		}

		// set the motor value
		motor[flywheel1] = motor[flywheel2] = fw1MotorVal;



		// PID stuff
		//flywheelPID(flywheel1, flywheelEnc1, targetSpd, fw1MotorVal);
	}
}
