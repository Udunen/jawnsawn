#include "main.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"


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

// pros::Imu				imu(9);
// pros::Rotation			y_tracking(7);
// pros::Rotation			x_tracking(6);

// lemlib::Drivetrain drivetrain {
// 	&left_drive, // left motor group
// 	&right_drive, // right motor group
// 	00000000000000000, // " track width
// 	3.25, // using new 3.25" omnis
// 	360, // drivetrain rpm is 360
// 	000000000000000
// };

// lemlib::TrackingWheel x_tracking_wheel(
// 	&x_tracking, // encoder
// 	3.25,
// 	00000000000000 // " offset from tracking center
// );

// lemlib::TrackingWheel y_tracking_wheel(
// 	&y_tracking, // encoder
// 	3.25,
// 	000000000000000 // " offset from tracking center
// );

// lemlib::OdomSensors sensors {
// 	&y_tracking_wheel, // vertical tracking wheel 1
// 	nullptr, // vertical tracking wheel 2
// 	&x_tracking_wheel, // horizontal tracking wheel 1
// 	nullptr, // we don't have a second tracking wheel, so we set it to nullptr
// 	&imu // inertial sensor
// };

// // forward/backward PID (untuned)
// lemlib::ControllerSettings lateralController {
// 	00000000000000, // kP
// 	00000000000000, // kI
// 	00000000000000, // kD
// 	0, // WindupRange
// 	1, // smallErrorRange
// 	100, // smallErrorTimeout
// 	3, // largeErrorRange
// 	500, // largeErrorTimeout
// 	10 // slew rate
// };

// // turning pid (untuned)
// lemlib::ControllerSettings angularController {
// 	00000000000000,
// 	00000000000000,
// 	00000000000000,
// 	0,
// 	1,
// 	100,
// 	3,
// 	500,
// 	10
// };

// lemlib::Chassis chassis(
// 	drivetrain,
// 	lateralController,
// 	angularController,
// 	sensors
// );



void initialize() {
	pros::lcd::initialize();
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

// void skillz() {
// 	// chassis.calibrate();
// 	// while(imu.is_calibrating()) {
// 	// 	pros::delay(20);
// 	// }
// 	chassis.setPose(-37.484, -56.18, 90);

// 	// go to matchload position
// 	chassis.turnToPoint(-58.4, -38.199, 500, {}, false);
// 	chassis.moveToPoint(-58.4, -38.199, 3500, {.maxSpeed=90}, false);
// 	chassis.turnToPoint(100, -40, 500, {}, false);
// 	back_left_wing.set_value(true);
// 	back_right_wing.set_value(true);
// 	matchLoad(9000, 25);
// 	back_left_wing.set_value(false);
// 	back_right_wing.set_value(false);
// 	chassis.moveToPoint(-54.5, -37.199, 400, {}, false);
// 	pros::delay(400);

// 	// go to alley
// 	chassis.turnToPoint(-34.484, -60, 500, {.maxSpeed=90}, false);
// 	chassis.moveToPoint(-37.484, -60, 5000, {.forwards=false, .maxSpeed=80}, false);
// 	chassis.turnToPoint(38, -62, 1000, {}, false);
// 	chassis.moveToPoint(38, -62, 5000, {.forwards=false, .maxSpeed=80}, false);
// 	back_left_wing.set_value(true);
// 	back_right_wing.set_value(true);
// 	chassis.turnToPoint(47, -58, 1000, {.maxSpeed=60}, false);
// 	chassis.moveToPoint(47, -58, 5000, {.forwards=false, .maxSpeed=80}, false);
// 	back_left_wing.set_value(false);
// 	back_right_wing.set_value(false);
// 	chassis.turnToPoint(55.5, -49.5, 1000, {.maxSpeed=60}, false);
// 	chassis.moveToPoint(55.5, -49.5, 5000, {.forwards=false, .maxSpeed=80}, false);
// 	left_drive.move_relative(-1.35, 100);
// 	chassis.turnToPoint(60, 0, 1000, {.maxSpeed=60}, false);
// 	back_left_wing.set_value(true);
// 	back_right_wing.set_value(true);
// 	chassis.moveToPoint(60, -34, 1500, {.forwards=false, .maxSpeed=90}, false);
// 	back_left_wing.set_value(false);
// 	back_right_wing.set_value(false);

// 	pros::delay(500);
// 	chassis.moveToPoint(60, -50, 3000, {.maxSpeed=90}, false);
// 	left_drive.move_voltage(-11000);
// 	right_drive.move_voltage(-11000);
// 	pros::delay(500);
// 	left_drive.move_voltage(0);
// 	right_drive.move_voltage(0);
// 	pros::delay(300);

// 	chassis.moveToPoint(60, -50, 3000, {.maxSpeed=90}, false);
// 	left_drive.move_voltage(-11000);
// 	right_drive.move_voltage(-11000);
// 	pros::delay(500);
// 	left_drive.move_voltage(0);
// 	right_drive.move_voltage(0);
// 	pros::delay(300);

// 	// push from front
// 	chassis.turnToPoint(46, -46, 2000, {.maxSpeed=90}, false);
// 	chassis.moveToPoint(52, -42, 1500, {.maxSpeed=90}, false);
// 	back_left_wing.set_value(true);
// 	back_right_wing.set_value(true);
// 	chassis.turnToPoint(34, -30, 1500, {.maxSpeed=60}, false);
// 	chassis.moveToPoint(34, -30, 5000, {.forwards=false}, false);
// 	chassis.turnToPoint(-100, -30, 1500, {.maxSpeed=60}, false);
// 	chassis.moveToPoint(20, -30, 5000, {.forwards=false}, false);
// 	chassis.turnToPoint(18, 100, 1000, {}, false);
// 	chassis.moveToPoint(18, -10, 1000, {.forwards=false}, false);
// 	chassis.turnToPoint(100, -14, 1000, {}, false);
// 	// first push
// 	chassis.moveToPoint(47, -14, 1000, {.forwards=false}, false);
// 	back_left_wing.set_value(false);
// 	back_right_wing.set_value(false);
// 	chassis.turnToPoint(-100, -14, 1000, {}, false);
// 	chassis.moveToPoint(20, -14, 1000, {}, false);
// 	back_left_wing.set_value(true);
// 	back_right_wing.set_value(true);
// 	chassis.turnToPoint(20, -100, 300, {}, false);
// 	chassis.turnToPoint(-100, -10, 300, {}, false);
// 	chassis.turnToPoint(18, 100, 1000, {}, false);
// 	chassis.moveToPoint(18, 8, 3000, {.forwards=false}, false);
// 	chassis.turnToPoint(100, 8, 1000, {}, false);
// 	chassis.moveToPoint(49, 8, 1000, {.forwards=false}, false);
// }

void autonomous() {

}

void opcontrol() {
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
			puncher.move_voltage(9000);
		} else {
			puncher.move_voltage(0);
		}

		if (master.get_digital_new_press(DIGITAL_DOWN)) {
			if(back_left_state) {
				back_left_wing.set_value(false);
				back_left_state = false;
			} else {
				back_left_wing.set_value(true);
				back_left_state = true;
			}
		}

		if (master.get_digital_new_press(DIGITAL_LEFT)) {
			if(front_left_state) {
				front_left_wing.set_value(false);
				front_left_state = false;
			} else {
				front_left_wing.set_value(true);
				front_left_state = true;
			}
		}

		if (master.get_digital_new_press(DIGITAL_RIGHT)) {
			if(front_right_state) {
				front_right_wing.set_value(false);
				front_right_state = false;
			} else {
				front_right_wing.set_value(true);
				front_right_state = true;
			}
		}

		if (master.get_digital_new_press(DIGITAL_UP)) {
			if(back_right_state) {
				back_right_wing.set_value(false);
				back_right_state = false;
			} else {
				back_right_wing.set_value(true);
				back_right_state = true;
			}
		}
	}
}