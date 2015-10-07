#pragma config(Sensor, dgtl1,  flywheelEnc1,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  flywheelEnc2,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  encFL,          sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  encFR,          sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  encBL,          sensorQuadEncoder)
#pragma config(Sensor, dgtl11, encBR,          sensorQuadEncoder)
#pragma config(Motor,  port1,           lift1,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           driveFL,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           driveFR,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           driveBL,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           driveBR,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           flywheel1,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           flywheel2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           hopper,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          lift2,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "util.c"

#include "Vex_Competition_Includes.c" //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton() {
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	startTask(motorControlTask);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous() {
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol() {
	bool prev8U = false, prev8D = false; // used for detecting when buttons are pressed (vs held down)

	// main loop
	while (true) {
		//// CONTROL DRIVE WHEELS WITH JOYSTICKS ////
		{
			int fl, fr, bl, br;

			// Ch3: forward/backward
			word ch3 = vexRT[Ch3]; if (abs(ch3)<10) ch3 = 0;
			fl = bl = ch3;
			fr = br = ch3;

			// Ch1: quick turn (rotate)
			word ch1 = vexRT[Ch1]; if (abs(ch1)<10) ch1 = 0;
			fl += ch1; bl += ch1;
			fr += -ch1; br += -ch1;

			// Ch4: strafe
			word ch4 = vexRT[Ch4]; if (abs(ch4)<10) ch4 = 0;
			fl += ch4; br += ch4;
			fr += ch4; bl += ch4;

			// set target control values
			flSpd = fl;
			frSpd = fr;
			blSpd = bl;
			brSpd = br;
		}

		//// OTHER CONTROLS ////
		{
			// hold 6U to turn on intake
			motor[intake] = vexRT[Btn6U]? 127 : 0;

			// press 7D/7U to turn flywheel on/off, respectively
			if (vexRT[Btn7U]) turnFlywheelOn = true;
			if (vexRT[Btn7D]) turnFlywheelOn = false;

			// press 8D/8U to increment/decrement flywheel speed
			if (!prev8U && (prev8U=(bool)vexRT[Btn8U])) flywheelSpeed += 44*648;
			if (!prev8D && (prev8D=(bool)vexRT[Btn8D])) flywheelSpeed -= 44*648;
			//if(flywheelSpeed<0)flywheelSpeed=0;if(flywheelSpeed>127)flywheelSpeed=127; // clamp to [0,127]
		}

		//UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	} // end of main while loop
} // end of usercontrol task
