#include "WPILib.h"

/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{

    // Channels for the wheels
    const static int frontLeftChannel	= 1;		// PWM Port Number
    const static int rearLeftChannel	= 0;		// PWM Port Number
    const static int frontRightChannel	= 3;		// PWM Port Number
    const static int rearRightChannel	= 2;		// PWM Port Number
    const static int joystickChannel	= 0;		// First and only Joystick
    const static int gyroChannel		= 0;		// Gyro in Analog Input "0"

	RobotDrive robotDrive;	// robot drive system
	Joystick stick;			// only joystick
	Gyro driveGyro;			// adding one gyro

public:
	float Kp = 0.03;		// Proportional constant for the Gyro
	Robot() :
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick(joystickChannel), driveGyro(0)								// as they are declared above.
	{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);	// invert the right side motors
		robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor,   true);	// you may need to change or remove this to match your robot
	}

	/**
	 * Runs the motors with Mecanum drive.
	 */
	void OperatorControl()
	{
		robotDrive.SetSafetyEnabled(false);
		driveGyro.Reset();							// Zero position based on where the robot is pointing now.
		float angle = driveGyro.GetAngle();			// ***** THIS NEEDS TO BE IN THE WHILE SECTION  ********
		while (IsOperatorControl() && IsEnabled())
		{
        	// Use the joystick X axis for lateral movement, Y axis for forward movement, and Z axis for rotation.
        	// This sample does not use field-oriented drive, so the gyro input is set to zero.
			robotDrive.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), stick.GetZ(), -angle * Kp);

			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}

};

START_ROBOT_CLASS(Robot);
