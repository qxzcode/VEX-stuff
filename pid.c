// struct to hold PID state for a motor
struct pidVals {
	short motorID, encoderID;
	short motorVal;
	float kP, kI, kD;
	float lastErr, sumErr;
	float targetVal;
	short rampDown;
	bool speed;
};

void initPID(pidVals &pid, short motorID, short encoderID, float kP, float kI, float kD, bool speed, short rampDown=0, float targetVal=0) {
	pid.motorID = motorID;
	pid.encoderID = encoderID;
	pid.kP = kP;
	pid.kI = kI;
	pid.kD = kD;
	pid.rampDown = rampDown;
	pid.targetVal = targetVal;
	pid.speed = speed;
	pid.motorVal = pid.lastErr = pid.sumErr = 0;
}

void updatePID(pidVals &pid) {
	// calculate current error
	float actualVal = (float)SensorValue[pid.encoderID];
	if (pid.speed) SensorValue[pid.encoderID] = 0;
	float err = pid.targetVal-actualVal;

	// calculate PID terms
	float P = pid.kP*err;
	float D = pid.kD*(err-pid.lastErr);
	pid.lastErr = err;
	pid.sumErr += err;
	float I = pid.kI*pid.sumErr;

	// set motor to calculated output value, ramping down if specified
	short targetVal = pid.speed? pid.motorVal+P+I+D : P+I+D;
	if (targetVal<pid.motorVal && pid.rampDown>0)
		pid.motorVal -= pid.rampDown;
	else
		pid.motorVal = targetVal;
	motor[pid.motorID] = pid.motorVal;
}
