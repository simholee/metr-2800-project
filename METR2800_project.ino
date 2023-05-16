
// Motor Wheel Pins
const int LEFT_BACK_WHEEL_FORWARDS = 38;
const int LEFT_BACK_WHEEL_BACKWARDS = 40;
const int LEFT_FRONT_WHEEL_FORWARDS = 36;
const int LEFT_FRONT_WHEEL_BACKWARDS = 34;
const int RIGHT_BACK_WHEEL_FORWARDS = 46;
const int RIGHT_BACK_WHEEL_BACKWARDS = 48;
const int RIGHT_FRONT_WHEEL_FORWARDS = 50;
const int RIGHT_FRONT_WHEEL_BACKWARDS = 52;

int wheel_motor_pins[8] = {LEFT_BACK_WHEEL_FORWARDS, LEFT_FRONT_WHEEL_FORWARDS, RIGHT_FRONT_WHEEL_FORWARDS, RIGHT_BACK_WHEEL_FORWARDS, LEFT_FRONT_WHEEL_BACKWARDS, LEFT_BACK_WHEEL_BACKWARDS, RIGHT_BACK_WHEEL_BACKWARDS, RIGHT_FRONT_WHEEL_BACKWARDS};

// Sensor Pins 
const int LEFT_SENSOR_TRIGGER = 23;
const int LEFT_SENSOR_ECHO = 25;
const int RIGHT_SENSOR_TRIGGER = 37;
const int RIGHT_SENSOR_ECHO = 39;
const int LEDGE_SENSOR_TRIGGER = 51;
const int LEDGE_SENSOR_ECHO = 53;

int sensor_pins[6] = {LEFT_SENSOR_TRIGGER, RIGHT_SENSOR_TRIGGER, LEDGE_SENSOR_TRIGGER, LEFT_SENSOR_ECHO, RIGHT_SENSOR_ECHO, LEDGE_SENSOR_ECHO};

// Scooper Motor Pins

const int EXTENDER_FORWARDS = 30;
const int EXTENDER_BACKWARDS = 32;
const int EXTENDER_SPEED = 12;
const int BALL_REMOVER_FORWARDS = 26;
const int BALL_REMOVER_BACKWARDS = 28;
const int BALL_REMOVER_SPEED = 8;
const int LIFTER_FORWARDS = 22;
const int LIFTER_BACKWARDS = 24;
const int LIFTER_SPEED = 9;

int scooper_motor_pins[9] = {EXTENDER_FORWARDS, EXTENDER_BACKWARDS, EXTENDER_SPEED, BALL_REMOVER_FORWARDS, BALL_REMOVER_BACKWARDS, BALL_REMOVER_SPEED, LIFTER_FORWARDS, LIFTER_BACKWARDS, LIFTER_SPEED};

int state = 0;

// Times for different exercises

const int TENNIS_ARM_LIFTING_TIME = 3000;
const int SQUASH_ARM_LIFTING_TIME = x;
const int TENNIS_ARM_EXTENDING_TIME = x;
const int SQUASH_ARM_EXTENDING_TIME = x;
const int FINAL_RIGHT_MOVEMENT_TIME = x;
const int QUARTER_TURN_TIME = x;
const int HALF_TURN_TIME = x;
const int MIDDLING_TIME = x;


void setup() {

  // Set Wheel Motor Pins

  for(int i = 0; i < 8; i++) {
    pinMode(wheel_motor_pins[i], OUTPUT);
  }
 
  // Set Sensor Pins

  for (int i = 0; i < 6; i++) {

    if (i < 3) {
      pinMode(sensor_pins[i], OUTPUT);
    }
    else {
      pinMode(sensor_pins[i], INPUT);
    }
  }

  // Set Scooper Motor Pins

  for(int i = 0; i < 9; i++) {
    pinMode(scooper_motor_pins[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  Serial.println("Pissing my pants rn fr");
  state = 11;

  
  switch (state) {
    case 11:
      // drop arm [start]
      Serial.println("State 0");
      
      dropArm(TENNIS_ARM_LIFTING_TIME);
      delay(500);
      
      state = 12;
      
      break;
      
    case 12: 
      // drive right
      Serial.println("State 1");
      
      int distance_ledge = sensorDistance(LEDGE_SENSOR_TRIGGER, LEDGE_SENSOR_ECHO);
      
      if (distance_ledge > 5) {
        stopWheels(20);
        state = 13;
      }
      else {
        wheelsGoRight(20);
      }
      break;
      
    case 13: 
      // drive forward
      Serial.println("State 2");
      
      int distance_left = sensorDistance(LEFT_SENSOR_TRIGGER, LEFT_SENSOR_ECHO);

      Serial.println(distance_left);
      
      if (distance_left < 18) {
        stopWheels(20);
        state = 21;
        Serial.println("I am here, look at me");
      }
      else {
        wheelsGoForward(20);
      }
      
      break;
      
    case 21:
      // lift arm [tennis ball]
      Serial.println("State 3");
      
      liftArm(TENNIS_ARM_LIFTING_TIME);
      delay(500);
      
      state = 22;
      
      break;
      
      // DO WE NEED TO DRIVE FORWARD HERE???
    case 22:
      // go forward or something idk
      
      
      state = 23;
      
      break;
      
    case 23:
      // extend arm [tennis ball]
      Serial.println("State 4");
      extendArm(TENNIS_ARM_EXTENDING_TIME);
      delay(500);
      
      state = 24;
      
      break;
      
    case 24:
      // rack and unrack
      Serial.println("State 5");
      
      rackOut();
      delay(500);
      
      rackIn();
      delay(500);
      
      state = 25;
      
      break;
      
    case 25:
      // retract arm [tennis ball]
      Serial.println("State 7");
      
      retractArm(TENNIS_ARM_EXTENDING_TIME);
      delay(500);
      
      state = 26;
      
      break;
      
    case 26:
      // drop arm [tennis ball]
      Serial.println("State 6");
      
      dropArm(TENNIS_ARM_LIFTING_TIME);
      delay(500);
      
      state = 31;
      
      break;
      
    case 31:
      // drive backwards
      Serial.println("State 8");
      
      int distance_left = sensorDistance(LEFT_SENSOR_TRIGGER, LEFT_SENSOR_ECHO);
      
      Serial.println(distance_left);
      
      if (distance_left > 40) {  // Distance???????
        stopWheels(20);
        state = 32;
      }
      else {
        wheelsGoBackwards(20);
      }
      
      break;
      
    case 32:
      // do a spin
      // turn until both censors are equal??
      Serial.println("State 9");
      
      wheelsRotateLeft(HALF_TURN_TIME);
      delay(500);
      
      state = 33;
      
      
      /*
      int distance_left = sensorDistance(LEFT_SENSOR_TRIGGER, LEFT_SENSOR_ECHO);
      int distance_right = sensorDistance(RIGHT_SENSOR_TRIGGER, RIGHT_SENSOR_ECHO);

      wheelsRotateLeft (LITTLE_LESS_THAN_HALF_TURN_TIME);
      
      Serial.println(distance_left);
      
      if (distance_right > distance_left) {
        stopWheels(20);
        state = 33;
        Serial.println("I am here, look at me");
      }
      else {
        wheelsRotateLft(20);
      }
      */
      
      break;
      
    case 33:
      // drive rightwards -> Until when?? maybe a hundredish milliseconds after initial sensoring
      Serial.println("State 10");
      
      int distance_right = sensorDistance(RIGHT_SENSOR_TRIGGER, RIGHT_SENSOR_ECHO);

      Serial.println(distance_right);
      
      if (distance_right < 30) { // check the numbers on this depending on how close the squash balls are
        wheelsGoRight(MIDDLING_TIME);
        stopWheels(20);
        state = 41;
      }
      else {
        wheelsGoRight(20);
      }
      
      break;
      
    case 41:
      // drive forwards - sensor use
      Serial.println("State 11");
      
      int distance_left = sensorDistance(LEFT_SENSOR_TRIGGER, LEFT_SENSOR_ECHO);

      Serial.println(distance_left);
      
      if (distance_left < 18) {
        stopWheels(20);
        state = 42;
        Serial.println("I am here, look at me");
      }
      else {
        wheelsGoForwards(20);
      }
      
      break;
      
    case 42:
      // drive rightwards
      Serial.println("State 12");
      
      wheelsGoRight(FINAL_RIGHT_MOVEMENT_TIME);
      delay(500);
      
      state = 51;
      
      break;
    case 51:
      // lift arm [squash ball]
      Serial.println("State 13");
      
      liftArm(SQUASH_ARM_LIFTING_TIME);
      delay(500);
      
      state = 52;
      
      break;
      
    case 52:
      // extend arm [squash ball]
      Serial.println("State 14")
      
      extendArm(SQUASH_ARM_EXTENDING_TIME);
      delay(500);
      
      state = 53;
      
      break;

    case 53:
      // rack and unrack
      Serial.println("State 15");
      
      rackOut();
      delay(500);
      
      rackIn();
      delay(500);
      
      state = 54;
      
      break;
      
    case 54:
      // retract arm [squash ball]
      Serial.println("State 17");
      
      retractArm(SQUASH_ARM_EXTENDING_TIME);
      delay(500);
      
      state = 55;
      
      break;
      
    case 55:
      // drop arm [squash ball]
      Serial.println("State 16");
      
      dropArm(SQUASH_ARM_LIFTING_TIME);
      delay(500);
      
      state = 61;
      
      break;
    case 61:
      // need to go back to the start/stop area
      break;
  }

/**
  switch (state) {

    case 0: 
      int distance_ledge = sensorDistance(LEDGE_SENSOR_TRIGGER, LEDGE_SENSOR_ECHO);
      
      if (distance_ledge > 5) {
        stopWheels(20);
        state = 1;
      }
      else {
        wheelsGoRight(20);
      }
      break;
      
    case 1: 
    
      Serial.println("I am here");
      
      int distance_left = sensorDistance(LEFT_SENSOR_TRIGGER, LEFT_SENSOR_ECHO);
      int distance_right = sensorDistance(RIGHT_SENSOR_TRIGGER, RIGHT_SENSOR_ECHO);
      
      if (distance_left < 18 && distance_right < 18) {
        stopWheels(20);
        state = 2;
      }
      else {
        wheelsGoForward(20);
      }
      break;
  }
*/
  
/**
  int distance_ledge = sensorDistance(LEDGE_SENSOR_TRIGGER, LEDGE_SENSOR_ECHO);
  Serial.println(distance_ledge);

  if (distance_ledge > 5) {
    stopWheels(20);
  }
  else {
    wheelsGoRight(20);
  }
*/

  
/**
  int distance_left = sensorDistance(LEFT_SENSOR_TRIGGER, LEFT_SENSOR_ECHO);
  int distance_right = sensorDistance(RIGHT_SENSOR_TRIGGER, RIGHT_SENSOR_ECHO);

  if (distance_left < 5 && distance_right < 5) {
    stopWheels(20);
  }
  else {
    wheelsGoForward(20);
  }
*/

  

/**
  wheelsGoForward(4000);

  wheelsGoLeft(4000);

  wheelsGoBackwards(4000);

  wheelsGoRight(4000);

  wheelsRoateLeft(4000);
*/
}

void stopWheels(int delay_time){

  for(int i = 0; i < 8; i++) {
    
    digitalWrite(wheel_motor_pins[i], LOW);
  }

  delay(delay_time);
}


void wheelsGoForwards(int delay_time) {


  for(int i = 0; i < 4; i++) {
    
    digitalWrite(wheel_motor_pins[i], HIGH);
  }

  delay(delay_time);

}

void wheelsGoBackwards(int delay_time) {

  for(int i = 4; i < 8; i++) {
    
    digitalWrite(wheel_motor_pins[i], HIGH);
  }

  delay(delay_time);
}


void wheelsGoLeft(int delay_time) {

  for(int i = 0; i < 8; i += 2) {
    
    digitalWrite(wheel_motor_pins[i], HIGH);
  }

  delay(delay_time);
  
}

void wheelsGoRight(int delay_time) {


  for(int i = 1; i < 8; i += 2) {
    
    digitalWrite(wheel_motor_pins[i], HIGH);
  }

  delay(delay_time);
  
}

void wheelsRotateLeft(int delay_time) {

  for(int i = 2; i < 6; i++) {
    
    digitalWrite(wheel_motor_pins[i], HIGH);
  }

  delay(delay_time);
  
}

void liftArm(int delay_time) {
  int motor_speed = x;

  analogWrite(scooper_motor_pins[9], motor_speed);
  digitalWrite(scooper_motor_pins[7], HIGH);

  delay(delay_time);

  digitalWrite(scooper_motor_pins[7], LOW);

}

void dropArm(int delay_time) {
  int motor_speed = x; // motor speed (0-255)

  analogWrite(scooper_motor_pins[9], motor_speed);
  digitalWrite(scooper_motor_pins[8], HIGH);

  delay(delay_time);

  digitalWrite(scooper_motor_pins[8], LOW);

}

void extendArm(int delay_time) {
  int motor_speed = x; // motor speed (0-255)

  analogWrite(scooper_motor_pins[3], motor_speed);
  digitalWrite(scooper_motor_pins[1], HIGH);

  delay(delay_time);

  digitalWrite(scooper_motor_pins[1], LOW);

}

void retractArm(int delay_time) {
  int motor_speed = x; // motor speed (0-255)

  analogWrite(scooper_motor_pins[3], motor_speed);
  digitalWrite(scooper_motor_pins[2], HIGH);

  delay(delay_time);

  digitalWrite(scooper_motor_pins[2], LOW);

}

void rackOut() {
  int motor_speed = x; // motor speed (0-255)
  int delay_time = x; // time of motor operation (ms)

  analogWrite(scooper_motor_pins[6], motor_speed);
  digitalWrite(scooper_motor_pins[4], HIGH);

  delay(delay_time);

  digitalWrite(scooper_motor_pins[4], LOW);

}

void rackIn() {
  int motor_speed = x; // motor speed (0-255)
  int delay_time = x; // time of motor operation (ms)

  analogWrite(scooper_motor_pins[6], motor_speed);
  digitalWrite(scooper_motor_pins[5], HIGH);

  delay(delay_time);

  digitalWrite(scooper_motor_pins[5], LOW);

}
  

int sensorDistance(int trigger_pin, int echo_pin) {

  unsigned long duration;
  int distance; 

  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo_pin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  delay(20);
  
  return distance;
}
