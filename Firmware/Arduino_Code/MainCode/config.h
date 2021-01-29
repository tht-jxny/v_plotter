#ifndef H_CONFIG
#define H_CONFIG

#include <Arduino.h>

// GPIO numbers where the components are connected:
const int PIN_LEFT_STEP = 5;
const int PIN_LEFT_DIR = 23;
const int PIN_RIGHT_STEP = 19;
const int PIN_RIGHT_DIR = 18;
const int PIN_SERVO = 26;

// Possible servo positions/angles:
const int SERVO_ANGLE_PEN_UP = 0;
const int SERVO_ANGLE_PEN_DOWN = 90;

// Delay between two motor movements (>35 for sixteenth step mode; >950 for full step mode):
const int MOTOR_DELAY = 300;

// Number of steps that translate to a 1 mm movement (needs to be measured):
const int STEP_DISTANCE = 108;

// Scale factor to scale given coordinates:
const int COORDINATE_SCALE = 1;

// Distance between both motor axles in millimetres (needs to be measured):
const int MOTOR_AXLE_DISTANCE = 532;

// Length of both tooth belts in millimetres when in origin position:
const int LEFT_STANDARD_LENGTH = 185;
const int RIGHT_STANDARD_LENGTH = 430;

// Size of canvas in millimetres:
const int CANVAS_WIDHT = 400;
const int CANVAS_HEIGHT = 400;

// Origin has  in truth the following coordinates:
const float X_OFFSET = ((LEFT_STANDARD_LENGTH*LEFT_STANDARD_LENGTH)-(RIGHT_STANDARD_LENGTH*RIGHT_STANDARD_LENGTH)+(MOTOR_AXLE_DISTANCE*MOTOR_AXLE_DISTANCE))/(2*MOTOR_AXLE_DISTANCE);
const float Y_OFFSET = sqrt(LEFT_STANDARD_LENGTH*LEFT_STANDARD_LENGTH-X_OFFSET*X_OFFSET);
#endif // H_CONFIG
