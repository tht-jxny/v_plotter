#include <ESP32Servo.h>
#include "config.h"

// Necessary runtime variables:
int current_servo_angle = SERVO_ANGLE_PEN_UP;
float current_left_length = LEFT_STANDARD_LENGTH;
float current_right_length = RIGHT_STANDARD_LENGTH;
float target_left_length = LEFT_STANDARD_LENGTH; // Maybe obsolete
float target_right_length = RIGHT_STANDARD_LENGTH; // Maybe obsolete
int left_addition_factor = 0;
int right_addition_factor = 0;


Servo lift_servo; // Creats servo object

void initialize_devices() {
  pinMode(PIN_LEFT_STEP, OUTPUT);
  pinMode(PIN_LEFT_DIR, OUTPUT);
  pinMode(PIN_RIGHT_STEP, OUTPUT);
  pinMode(PIN_RIGHT_DIR, OUTPUT);
  lift_servo.attach(PIN_SERVO);
  lift_servo.write(current_servo_angle);
}

void lift_pen() {
 current_servo_angle = SERVO_ANGLE_PEN_UP;
 lift_servo.write(SERVO_ANGLE_PEN_UP);
}

void lower_pen() {
  current_servo_angle = SERVO_ANGLE_PEN_DOWN;
  lift_servo.write(SERVO_ANGLE_PEN_DOWN);
}

void calculate_belt_lengths(float x, float y){
  x = x * COORDINATE_SCALE + X_OFFSET;
  y = y * COORDINATE_SCALE + Y_OFFSET;
  target_left_length = sqrt(x*x+y*y);
  target_right_length = sqrt((MOTOR_AXLE_DISTANCE-x)*(MOTOR_AXLE_DISTANCE-x)+y*y);
}

void move_to() {
  if ((target_left_length < (sqrt(CANVAS_WIDHT*CANVAS_WIDHT+CANVAS_HEIGHT*CANVAS_HEIGHT)+LEFT_STANDARD_LENGTH)) and (target_right_length < (sqrt(CANVAS_WIDHT*CANVAS_WIDHT+CANVAS_HEIGHT*CANVAS_HEIGHT)+RIGHT_STANDARD_LENGTH))){ // Check if coordinates

    // Set motor directions:
    // Movement for left motor (cw means decreasing length of tooth belt):
    if (target_left_length < current_left_length) {
      digitalWrite(PIN_LEFT_DIR, HIGH); // motor direction cw
      left_addition_factor = -1;
    } else {
      digitalWrite(PIN_LEFT_DIR, LOW); // motor direction ccw
      left_addition_factor = 1;
    }
    // Movement for right motor (cw means increasing length of tooth belt):
    if (target_right_length < current_right_length) {
      digitalWrite(PIN_RIGHT_DIR, LOW); // motor direction ccw
      right_addition_factor = -1;
    } else{
      digitalWrite(PIN_RIGHT_DIR, HIGH); // motor direction cw 
      right_addition_factor = 1;
    }

    // Spin motors the right amount of time:
    
    while (!((int(target_left_length) == int(current_left_length)) && (int(target_right_length) == int(current_right_length)))){
      if (int(target_left_length) != int(current_left_length)){
        digitalWrite(PIN_LEFT_STEP, HIGH);
        delayMicroseconds(MOTOR_DELAY);
        digitalWrite(PIN_LEFT_STEP, LOW);
        delayMicroseconds(MOTOR_DELAY);
        current_left_length++; //= current_left_length + left_addition_factor * (1/STEP_DISTANCE);
      }
      if (int(target_right_length) != int(current_right_length)){
        digitalWrite(PIN_LEFT_STEP, HIGH);
        delayMicroseconds(MOTOR_DELAY);
        digitalWrite(PIN_LEFT_STEP, LOW);
        delayMicroseconds(MOTOR_DELAY);
        current_right_length++; //= current_right_length + right_addition_factor * (1/STEP_DISTANCE);
      }
    Serial.println("Status (R;L):");
    Serial.println(String(target_right_length));
    Serial.println(String(current_right_length));
    Serial.println(String(target_left_length));
    Serial.println(String(current_left_length));
  }
  Serial.println("Moved to desired location!");
  }
}

void move_to_origin() {
  calculate_belt_lengths(0,0);
  move_to();
}


                  
void setup() {
  Serial.begin(115200);
  initialize_devices();
}


void loop() {
  Serial.println("moving pen");
  lift_pen();
  delay(2000);
  lower_pen();
  delay(2000);
  // Moving means calculating the belt lengths to reach; then determining the speed / delay of each motor; then spin motors
  // Speed of motors differ because they have to finish the move at the same time -> Create a line 
  calculate_belt_lengths(100,  100);
  move_to();
  delay(2000);
  calculate_belt_lengths(100, 50);
  move_to();
  delay(2000);
  calculate_belt_lengths(50, 100);
  move_to();
  delay(2000);
  move_to_origin();
  delay(2000);
}


  
