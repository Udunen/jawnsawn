#include "main.h"
#include "lemlib/api.hpp"

pros::Controller	master(pros::E_CONTROLLER_MASTER);

pros::MotorGroup		left_drive({-2, -3, -4},
									pros::v5::MotorGears::blue,
									pros::v5::MotorUnits::degrees);
pros::MotorGroup		right_drive({5, 6, 7},
									pros::v5::MotorGears::blue,
									pros::v5::MotorUnits::degrees);

pros::Motor				intake(8,
								pros::v5::MotorGears::green,
								pros::v5::MotorUnits::degrees);

pros::adi::DigitalOut	front_left_wing('A', false);
pros::adi::DigitalOut	front_right_wing('B', false);
pros::adi::DigitalOut	back_left_wing('C', false);
pros::adi::DigitalOut	back_right_wing('D', false);

pros::Imu				imu(9);
pros::Rotation			y_tracking(10);
pros::Rotation			x_tracking(11);

lemlib::Drivetrain drivetrain {
	&left_drive, // left motor group
	&right_drive, // right motor group
	00000000000000000, // " track width
	3.25, // using new 3.25" omnis
	360, // drivetrain rpm is 360
	000000000000000
};

lemlib::TrackingWheel x_tracking_wheel(
	&x_tracking, // encoder
	3.25,
	00000000000000 // " offset from tracking center
);

lemlib::TrackingWheel y_tracking_wheel(
	&y_tracking, // encoder
	3.25,
	000000000000000 // " offset from tracking center
);

lemlib::OdomSensors sensors {
	&y_tracking_wheel, // vertical tracking wheel 1
	nullptr, // vertical tracking wheel 2
	&x_tracking_wheel, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &imu // inertial sensor
};

// forward/backward PID (untuned)
lemlib::ControllerSettings lateralController {
    00000000000000, // kP
	00000000000000, // kI
    00000000000000, // kD
	0, // WindupRange
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    10 // slew rate
};
 
// turning PID (untuned)
lemlib::ControllerSettings angularController {
    00000000000000, // kP
	00000000000000, // kI
    00000000000000, // kD
	0, // WindupRange
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    10 // slew rate
};

lemlib::Chassis chassis(
	drivetrain,
	lateralController,
	angularController,
	sensors
);


void initialize() {
	chassis.calibrate();
	chassis.setPose(0, 0, 0);
	left_drive.set_brake_mode_all(pros::MotorBrake::brake);
	right_drive.set_brake_mode_all(pros::MotorBrake::brake);
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	double drive, turn;
	
	while(true) {
		drive = master.get_analog(ANALOG_LEFT_Y) / 127.0;
		turn = master.get_analog(ANALOG_RIGHT_X) / 127.0;
		if (drive < 0.5) {
			turn /= 1.4;
		} else {
			turn /= 1.2;
		}
		left_drive.move_voltage((drive + turn)*12000);
		right_drive.move_voltage((drive - turn)*12000);


		if(master.get_digital(DIGITAL_R2)) {
			intake.move_voltage(12000);
		} else if (master.get_digital(DIGITAL_R1)) {
			intake.move_voltage(-12000);
		} else {
			intake.move_voltage(0);
		}


		if( !master.get_digital(DIGITAL_L2) && master.get_digital(DIGITAL_L1) ) {
			back_left_wing.set_value(true);
			back_right_wing.set_value(true);
		} else {
			back_left_wing.set_value(false);
			back_right_wing.set_value(false);
		}
		
		if( !master.get_digital(DIGITAL_L1) && master.get_digital(DIGITAL_L2) ) {
			front_right_wing.set_value(true);
			front_left_wing.set_value(true);
		} else {
			front_right_wing.set_value(false);
			front_left_wing.set_value(false);
		}

		master.print(0, 1, "x: %f", chassis.getPose().x);
		master.print(1, 1, "y: %f", chassis.getPose().y);
		master.print(2, 1, "heading: %f", chassis.getPose().theta);
		master.clear();

	}
}