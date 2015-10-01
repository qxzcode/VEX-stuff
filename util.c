bool turnFlywheelOn = false;
word flywheelSpeed = 80;

struct pidState {
	float kp, ki, kd;
	float err, errDeriv, errSum;
};
float updatePID(pidState &pid, float error) {
	pid.errDeriv = error - pid.err;
	pid.errSum += error;
	pid.err = error;
	return pid.kp*pid.err + pid.ki*pid.errSum + pid.kd*pid.errDeriv;
}

task flywheelTask() {
	// monitor turnFlywheelOn and control the motor safely
	word fw1MotorVal = 0, fw2MotorVal = 0;
	pidState pid1, pid2;
	pid1.kp = pid2.kp = 1;
	pid1.ki=pid1.kd=pid2.ki=pid2.kd = 0;
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

	float targetSpd;
	const float kP = 1.0f;
	while (true) {
		float fw1Spd = (float)SensorValue[flywheelEnc1] / 50;
		SensorValue[flywheelEnc1] = 0;

		float P = kP*(targetSpd-fw1Spd)

		wait1Msec(50);
	}
}
