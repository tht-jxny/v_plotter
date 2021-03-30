#include <ESP32Servo.h>
#include "config.h"

// Necessary runtime variables:
int current_servo_angle = SERVO_ANGLE_PEN_UP;
float current_left_length = LEFT_STANDARD_LENGTH;
float current_right_length = RIGHT_STANDARD_LENGTH;
float target_left_length = LEFT_STANDARD_LENGTH; // Maybe obsolete
float target_right_length = RIGHT_STANDARD_LENGTH; // Maybe obsolete
int left_addition_factor = 0;
float left_motor_delay = 0;
float right_motor_delay = 0;
float movement_time = 0; // Total time it takes to move
float movement_steps = 0; // Total number of steps to move
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
  Serial.println("2");
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
  Serial.println("3");
  // Draws not outside of canvas
  if ((target_left_length < (sqrt(CANVAS_WIDHT*CANVAS_WIDHT+CANVAS_HEIGHT*CANVAS_HEIGHT)+LEFT_STANDARD_LENGTH)) and (target_right_length < (sqrt(CANVAS_WIDHT*CANVAS_WIDHT+CANVAS_HEIGHT*CANVAS_HEIGHT)+RIGHT_STANDARD_LENGTH))){ 
    float left_travel_distance = target_left_length - current_left_length;
    float right_travel_distance = target_right_length - current_right_length;
    // Set motor directions:
    // Movement for left motor (cw means decreasing length of tooth belt):
    if (left_travel_distance < 0) {
      digitalWrite(PIN_LEFT_DIR, HIGH); // motor direction cw
      left_addition_factor = -1;
    } else {
      digitalWrite(PIN_LEFT_DIR, LOW); // motor direction ccw
      left_addition_factor = 1;
    }
    // Movement for right motor (cw means increasing length of tooth belt):
    if (target_right_length < 0) {
      digitalWrite(PIN_RIGHT_DIR, LOW); // motor direction ccw
      right_addition_factor = -1;
    } else{
      digitalWrite(PIN_RIGHT_DIR, HIGH); // motor direction cw 
      right_addition_factor = 1;
    }
     // Calculate motor delays; Motor with longer distance has to move faster (v_max)
     // Check which motor has to move further:
     if (abs(left_travel_distance) > abs(right_travel_distance)){ // Left motor has to move faster; Keep in mind: speed = distance / time
        movement_time = left_travel_distance / V_MAX;
        movement_steps = left_travel_distance * STEP_DISTANCE;
        left_motor_delay = movement_time/movement_steps; // In seconds; delay = time/steps = (steps/speed)/steps = 1/speed
        float other_motor_speed = right_travel_distance / movement_time; // In mm/s
        right_motor_delay = 1 / (other_motor_speed * STEP_DISTANCE);
        // Chance unit of delays from seconds to microseconds:
        left_motor_delay *= 1000000;
        right_motor_delay *= 1000000;
     } else{ // Right motor has to move faster
        movement_time = right_travel_distance / V_MAX;
        movement_steps = right_travel_distance * STEP_DISTANCE;
        right_motor_delay = movement_time/movement_steps; // In seconds; delay = time/steps = (steps/speed)/steps = 1/speed
        float other_motor_speed = left_travel_distance / movement_time; // In mm/s
        left_motor_delay = 1 / (other_motor_speed * STEP_DISTANCE);
        // Chance unit of delays from seconds to microseconds:
        //left_motor_delay *= 1000000;
        //right_motor_delay *= 1000000;
     }
    Serial.println("1");
    Serial.println(movement_steps);
    // Spin motors the right amount of time: 
    for (int i = 0; i < int(abs(movement_steps)); i++){
      digitalWrite(PIN_LEFT_STEP, HIGH);
      delayMicroseconds(abs(left_motor_delay));
      digitalWrite(PIN_LEFT_STEP, LOW);
      digitalWrite(PIN_RIGHT_STEP, HIGH);
      delayMicroseconds(abs(right_motor_delay));
      digitalWrite(PIN_RIGHT_STEP, LOW);
      
    }
    current_right_length = target_right_length;
    current_left_length = target_left_length;
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


  
