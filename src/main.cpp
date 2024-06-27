#include "main.h"
#include "lemlib/api.hpp"
#include <utility>

pros::Controller		master(pros::E_CONTROLLER_MASTER);

pros::MotorGroup		left_drive({-12, -13, -15},
									pros::v5::MotorGears::blue,
									pros::v5::MotorUnits::degrees);
pros::MotorGroup		right_drive({17, 18, 20},
									pros::v5::MotorGears::blue,
									pros::v5::MotorUnits::degrees);


// pros::Motor				intake(19,
// 								pros::v5::MotorGears::blue,
// 								pros::v5::MotorUnits::degrees);

pros::MotorGroup		intake({19, -5},
								pros::v5::MotorGears::blue,
								pros::v5::MotorUnits::degrees);

pros::Motor				puncher(21,
								pros::v5::MotorGears::red,
								pros::v5::MotorUnits::degrees);

pros::adi::DigitalOut	front_left_wing('F', false);
pros::adi::DigitalOut	front_right_wing('E', false);
pros::adi::DigitalOut	back_left_wing('H', false);
pros::adi::DigitalOut	back_right_wing('G', false);

pros::Imu				imu(8);
pros::Rotation			y_tracking(7);
pros::Rotation			x_tracking(6);

lemlib::Drivetrain drivetrain {
	&left_drive, // left motor group
	&right_drive, // right motor group
	13, // " track width
	lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
	360, // drivetrain rpm is 360
	8
};

lemlib::TrackingWheel x_tracking_wheel(
	&x_tracking, // encoder
	lemlib::Omniwheel::NEW_2,
	3.85 // " offset from tracking center
);


lemlib::TrackingWheel y_tracking_wheel(
	&y_tracking, // encoder
	lemlib::Omniwheel::NEW_2,
	-2.05 // " offset from tracking center
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
	9, // kP
	0, // kI
	20, // kD
	3, // anti windup
	1, // small error range, in inches
	100, // small error range timeout, in milliseconds
	3, // large error range, in inches
	500, // large error range timeout, in milliseconds
	20 // maximum acceleration (slew)
};

// turning pid (untuned)
lemlib::ControllerSettings angularController {
	7,
	0,
	40,
	3, // anti windup
	1, // small error range, in inches
	100, // small error range timeout, in milliseconds
	3, // large error range, in inches
	500, // large error range timeout, in milliseconds
	0 // maximum acceleration (slew)
};

lemlib::Chassis chassis(
	drivetrain,
	lateralController,
	angularController,
	sensors
);



void initialize() {
	if(COMPETITION_AUTONOMOUS) {
		pros::lcd::initialize(); // initialize brain screen
		chassis.calibrate();
		while(imu.is_calibrating()) {
			pros::delay(20);
		}
	}
	back_left_wing.set_value(false);
	back_right_wing.set_value(false);
	front_left_wing.set_value(false);
	front_right_wing.set_value(false);
	left_drive.set_brake_mode(MOTOR_BRAKE_COAST);
	right_drive.set_brake_mode(MOTOR_BRAKE_COAST);
}

void disabled() {}

void competition_initialize() {}


void matchLoad(double millivolts, double seconds) { 
	int wantTime = seconds * 1000 + pros::millis();
	while ( pros::millis() < wantTime ) {
		puncher.move_voltage(millivolts);
	}
	puncher.move_voltage(0);
};


// void close_side_auton() {
	
// 	chassis.setPose(-33, -58, 0);
// 	// fling triball with wing
// 	front_right_wing.set_value(true);
// 	pros::delay(200);
// 	front_right_wing.set_value(false);
// 	// grab first triball
// 	intake.move_voltage(12000);
// 	chassis.moveToPoint(-28, -27, 700,);
// 	chassis.turnToPoint(-28, -8.5, 400);
// 	chassis.moveToPoint(-28, -8.5, 800, 360);
// 	intake.move_voltage(0);

// 	// go back a little bit so we don't cross the center line
// 	chassis.moveToPoint(-28, -12, 1000);

// 	// turn to second triball and push over
// 	chassis.turnToPoint(0, -12, 1000);
// 	intake.move_voltage(-12000);
// 	pros::delay(300);
// 	front_left_wing.set_value(true);
// 	front_right_wing.set_value(true);
// 	// push
// 	chassis.moveToPoint(-6, -12, 1000);
// 	intake.move_voltage(0);
// 	front_left_wing.set_value(false);
// 	front_right_wing.set_value(false);

// 	chassis.moveToPoint(-23, -30, 1000);
// 	chassis.turnToPoint(-53, -44, 1000, true);
// 	chassis.moveToPoint(-53, -44, 3000);
// 	back_left_wing.set_value(true);
// 	chassis.turnToPoint(-40, -61, 1000, true);
// 	chassis.moveToPoint(-40, -61, 1000);
// 	back_left_wing.set_value(false);
// 	chassis.turnToPoint(1, -58, 1000, true);
// 	chassis.moveToPoint(1, -58, 2000);
	
	
// }

// void ballz(){
// 	chassis.setPose(36.772, -59.647, 0);

// 	//Fling matchload
// 	// front_right_wing.set_value(true);
// 	// pros::delay(200);
// 	// front_right_wing.set_value(false);

// 	//Intake under crossbar
// 	chassis.turnToPoint(0, -67, 1000, false);
// 	intake.move_voltage(12000);
// 	chassis.moveToPoint(6, -59, 2000);
// 	pros::delay(600);
// 	intake.move_voltage(0);

// 	//Descore
// 	chassis.moveToPoint(47, -54, 2000);

	


// }

// void newSixBall() {
// 	chassis.setPose(14, -58, 270);
// 	intake.move_voltage(12000);
// 	// grab first triball
// 	chassis.moveToPoint(5, -59, 1000);
// 	intake.move_voltage(0);
// 	// go back to descore
// 	chassis.moveToPoint(48, -46, 1000, 150);
// 	// // go to right place to descore
// 	// chassis.turnToPoint(50, -44, 1000, true);
// 	// chassis.moveToPoint(50, -44, 1000);
// 	// descore
// 	back_left_wing.set_value(true);
// 	// go to right place to descore
// 	chassis.turnToPoint(53, -41, 300, true);
// 	chassis.moveToPoint(53, -41, 300);
// 	// fling triball to descore
// 	chassis.turnToPoint(30, -26, 300, true, 500);
// 	chassis.turnToPoint(68, -26, 400, true);
// 	back_left_wing.set_value(false);
// 	pros::delay(300);
// 	// push into goal
// 	chassis.moveToPoint(68, -26, 1000, 360);
// 	// go forward and spin
// 	chassis.moveToPoint(68, -34, 500, 360);
// 	chassis.turnToPoint(100, -23, 300);
// 	chassis.turnToPoint(chassis.getPose().x, -23, 700);
// 	// score third triball
// 	intake.move_voltage(-12000);
// 	pros::delay(500);
// 	chassis.moveToPoint(67, -19, 600, 360);
// 	// chassis.moveToPoint(60, -33, 700, 360);
// 	// chassis.moveToPoint(60, -23, 1000, 360);
// 	intake.move_voltage(0);
// 	chassis.moveToPoint(63, -48, 600);
// 	// go to mid
// 	chassis.turnToPoint(5, -33, 400);
// 	intake.move_voltage(12000);
// 	chassis.moveToPoint(5, -33, 1000, 360);
// 	// outtake towards goal
// 	chassis.turnToPoint(45, 0, 700);
// 	intake.move_voltage(-8000);
// 	pros::delay(600);
// 	intake.move_voltage(0);
// 	// go to other triball
// 	chassis.turnToPoint(2, -1, 500);
// 	intake.move_voltage(12000);
// 	chassis.moveToPoint(2, -1, 800, 150);
// 	// move back a bit
// 	chassis.moveToPoint(7, -8, 600, 360);
// 	// turn towards goal
// 	chassis.turnToPoint(14, 17, 100, false, 200);
// 	chassis.turnToPoint(42, -8, 700, false, 200);
// 	// push into goal
// 	intake.move_voltage(-12000);
// 	pros::delay(600);
// 	front_left_wing.set_value(true);
// 	front_right_wing.set_value(true);
// 	chassis.moveToPoint(42, chassis.getPose().y, 900, {true, 360, 10, 100}, false);
// 	front_left_wing.set_value(false);
// 	front_right_wing.set_value(false);
// 	chassis.turnToPoint(15, -15, 700, true, 200);
// 	intake.move_voltage(0);
// 	chassis.moveToPoint(15, -15, 3000, 360);
// }

void skillz() {
	// chassis.calibrate();
	// while(imu.is_calibrating()) {
	// 	pros::delay(20);
	// }
	left_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
	right_drive.set_brake_mode(MOTOR_BRAKE_BRAKE);
	chassis.setPose(-43.138, 57.787, 45);

	// go to matchload position
	chassis.moveToPose(-62.131, 37.582, 0, 2000, {.forwards=false, .minSpeed=90});
	chassis.moveToPose(-62.131, -35.965, 0, 600, {.forwards=false, .minSpeed=60});
	chassis.moveToPose(-62.131, 38.592, 0, 750);
	//chassis.setPose(-60.919, 30.732, 0);
	
	chassis.moveToPose(-55.888, 43.739, 115, 1000);
	chassis.moveToPoint(-67, 46, 1000, {.forwards=false});
	//chassis.swingToPoint(48, 11, DriveSide::RIGHT, 800);
	chassis.turnToPoint(48, 11, 800);
	back_left_wing.set_value(true);
	// chassis.moveToPoint(chassis.getPose().x - 10*std::cos(chassis.getPose().theta),
	// 					chassis.getPose().y + 10*std::sin(chassis.getPose().theta),
	// 					1000,
	// 					{.forwards=false});
	// matchLoad(7500, 2);
	back_left_wing.set_value(false);
	// back_left_wing.set_value(false);
	intake.move_voltage(-12000);
	chassis.moveToPoint(-29, 30, 4000, {.minSpeed=500});

	//chassis.moveToPose(-24, 20, 90, 5000, {.forwards=true, .minSpeed=500});
	chassis.turnToHeading(90, 1200);
	front_right_wing.set_value(true);
	front_left_wing.set_value(true);
	pros::delay(600);
	chassis.cancelAllMotions();
	left_drive.move(12000);
	right_drive.move_velocity(12000);
	pros::delay(500);
	left_drive.move(0);
	right_drive.move(0);
	//chassis.moveToPose(0, 30, 90, 1000, {.minSpeed = 500});
	//chassis.moveToPose(10, 23, 90,2000, {.forwards=true, .minSpeed=500});
	// front_right_wing.set_value(false);
	// front_left_wing.set_value(false);
	intake.move_voltage(0);
	front_right_wing.set_value(false);
	front_left_wing.set_value(false);
	chassis.moveToPose(-13, 25, 0, 1000);
	chassis.turnToHeading(0, 800);
	back_left_wing.set_value(true);
	chassis.moveToPoint(-10, -33, 2000, {.forwards=false, .minSpeed=127});
	chassis.moveToPoint(-10, -40, 1000, {.forwards=false, .maxSpeed=60});

	back_left_wing.set_value(false);
	chassis.turnToPoint(-34, -30, 700);
	chassis.moveToPose(-45, -37, 270, 	12000, {.minSpeed=30});
	chassis.moveToPose(-40, -44, 225, 	12000, {.minSpeed=30});
	chassis.moveToPose(-38, -60, 180, 2000, {.minSpeed=30});
	chassis.moveToPoint(-34, -64, 1000, {.minSpeed=30});
	chassis.turnToHeading(100, 2000);
 	chassis.moveToPose(31, -65, 90, 3000, {.minSpeed=127});


	// go to alley
	chassis.moveToPoint(38, -65, 2000, {.maxSpeed=80});
	front_left_wing.set_value(true);
	chassis.moveToPoint(43.138, -67.787, 2000, {.maxSpeed=80});
	chassis.moveToPose(68, -48, 225, 2000, {.maxSpeed=80});

	//shove things (Ayman Version)
	chassis.moveToPoint(33, -43, 2500);
	front_right_wing.set_value(true);
	chassis.moveToPose(26, -40, 30, 4000, {.maxSpeed=60});
	front_left_wing.set_value(true);
	chassis.moveToPoint(52, -18, 2000, {.minSpeed=127});
	front_right_wing.set_value(false);
	//potentially reset odom before or after shove
	//code following is if no reset odom
	chassis.moveToPose(19, -16, 20, 2000);
	back_left_wing.set_value(true);
	back_right_wing.set_value(true);
	chassis.moveToPoint(57, -10, 1000, {.minSpeed=127});
	back_left_wing.set_value(false);
	back_right_wing.set_value(false);
	chassis.moveToPose(18.7, 5.6, 0, 3000, {.forwards=false});
	chassis.moveToPose(28.406, 29.438, 165, 2000);
	back_left_wing.set_value(true);
	back_right_wing.set_value(true);
	chassis.moveToPose(52.753, -2.4, 90, 2000);
	//front_left_wing.set_value(false);

	// // push from front
	// chassis.turnToPoint(46, -46, 2000, {.maxSpeed=90}, false);
	// chassis.moveToPoint(52, -42, 1500, {.maxSpeed=90}, false);
	// back_left_wing.set_value(true);
	// back_right_wing.set_value(true);
	// chassis.turnToPoint(34, -30, 1500, {.maxSpeed=60}, false);
	// chassis.moveToPoint(34, -30, 5000, {.forwards=false}, false);
	// chassis.turnToPoint(-100, -30, 1500, {.maxSpeed=60}, false);
	// chassis.moveToPoint(20, -30, 5000, {.forwards=false}, false);
	// chassis.turnToPoint(18, 100, 1000, {}, false);
	// chassis.moveToPoint(18, -10, 1000, {.forwards=false}, false);
	// chassis.turnToPoint(100, -14, 1000, {}, false);
	// // first push
	// chassis.moveToPoint(47, -14, 1000, {.forwards=false}, false);
	// back_left_wing.set_value(false);
	// back_right_wing.set_value(false);
	// chassis.turnToPoint(-100, -14, 1000, {}, false);
	// chassis.moveToPoint(20, -14, 1000, {}, false);
	// back_left_wing.set_value(true);
	// back_right_wing.set_value(true);
	// chassis.turnToPoint(20, -100, 300, {}, false);
	// chassis.turnToPoint(-100, -10, 300, {}, false);
	// chassis.turnToPoint(18, 100, 1000, {}, false);
	// chassis.moveToPoint(18, 8, 3000, {.forwards=false}, false);
	// chassis.turnToPoint(100, 8, 1000, {}, false);
	// chassis.moveToPoint(49, 8, 1000, {.forwards=false}, false);
}

// void tuning() {
// 	chassis.setPose(0, 0, 0);
// 	// chassis.turnToHeading(90, 10000);
// 	chassis.moveToPoint(0, 48, 10000);
// }

void tuning() {
	chassis.setPose(0, 0, 0);
	// chassis.turnToHeading(90, 100000);
	chassis.moveToPoint(0, 48, 100000);
}

void autonomous() {
	skillz();
}

void opcontrol() {
	left_drive.set_brake_mode(MOTOR_BRAKE_COAST);
	right_drive.set_brake_mode(MOTOR_BRAKE_COAST);
	double drive, turn;
	bool back_left_state, back_right_state, front_left_state, front_right_state = false;
	back_left_wing.set_value(false);
	back_right_wing.set_value(false);
	front_left_wing.set_value(false);
	front_right_wing.set_value(false);
	
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


		if (master.get_digital(DIGITAL_R2)) {
			intake.move_voltage(12000);
		} else if (master.get_digital(DIGITAL_R1)) {
			intake.move_voltage(-12000);
		} else {
			intake.move_voltage(0);
		}

		if (master.get_digital(DIGITAL_Y)) {
			puncher.move_voltage(7500);
		} else {
			puncher.move_voltage(0);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
	 		back_left_wing.set_value(true);
			back_right_wing.set_value(true);
		} else {
			back_left_wing.set_value(false);
			back_right_wing.set_value(false);
		}

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			front_left_wing.set_value(true);
			front_right_wing.set_value(true);
		} else {
			front_left_wing.set_value(false);
			front_right_wing.set_value(false);
		}

		master.print(0, 1, "x: %f", chassis.getPose().x);
		master.print(1, 1, "y: %f", chassis.getPose().y);
		master.print(2, 1, "heading: %f", chassis.getPose().theta);
		master.clear();
	}
}