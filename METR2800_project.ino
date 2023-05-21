
// Motor Wheel Pins
const int LEFT_BACK_WHEEL_FORWARDS = 40;
const int LEFT_BACK_WHEEL_BACKWARDS = 38;
const int LEFT_FRONT_WHEEL_FORWARDS = 34;
const int LEFT_FRONT_WHEEL_BACKWARDS = 36;
const int LEFT_FRONT_WHEEL_SPEED = 11;
const int RIGHT_BACK_WHEEL_FORWARDS = 46;
const int RIGHT_BACK_WHEEL_BACKWARDS = 48;
const int RIGHT_FRONT_WHEEL_FORWARDS = 52;
const int RIGHT_FRONT_WHEEL_BACKWARDS = 50;

int wheel_motor_pins[8] = {LEFT_BACK_WHEEL_FORWARDS, LEFT_FRONT_WHEEL_FORWARDS, RIGHT_FRONT_WHEEL_FORWARDS, RIGHT_BACK_WHEEL_FORWARDS, LEFT_FRONT_WHEEL_BACKWARDS, LEFT_BACK_WHEEL_BACKWARDS, RIGHT_BACK_WHEEL_BACKWARDS, RIGHT_FRONT_WHEEL_BACKWARDS};

// Sensor Pins 
const int LEFT_SENSOR_TRIGGER = 23;
const int LEFT_SENSOR_ECHO = 25;
const int RIGHT_SENSOR_TRIGGER = 37;
const int RIGHT_SENSOR_ECHO = 39;
const int LEDGE_SENSOR_TRIGGER = 51;
const int LEDGE_SENSOR_ECHO = 53;

int sensor_pins[6] = {LEFT_SENSOR_TRIGGER, RIGHT_SENSOR_TRIGGER, LEDGE_SENSOR_TRIGGER, LEFT_SENSOR_ECHO, RIGHT_SENSOR_ECHO, LEDGE_SENSOR_ECHO};

float left_sensor_recordings[20];
float right_sensor_recordings[20];
float ledge_sensor_recordings[20];
float distance_ledge = 3;
float distance_left = 100;
float distance_right = 100;
bool measure_distance_left = false;
bool measure_distance_right = false; 
bool measure_distance_ledge = false;

// Scooper Motor Pins

const int EXTENDER_FORWARDS = 32;
const int EXTENDER_BACKWARDS = 30;
const int EXTENDER_SPEED = 12;
const int BALL_REMOVER_FORWARDS = 26;
const int BALL_REMOVER_BACKWARDS = 28;
const int BALL_REMOVER_SPEED = 8;
const int LIFTER_FORWARDS = 24;
const int LIFTER_BACKWARDS = 22;
const int LIFTER_SPEED = 9;

int scooper_motor_pins[9] = {EXTENDER_FORWARDS, EXTENDER_BACKWARDS, EXTENDER_SPEED, BALL_REMOVER_FORWARDS, BALL_REMOVER_BACKWARDS, BALL_REMOVER_SPEED, LIFTER_FORWARDS, LIFTER_BACKWARDS, LIFTER_SPEED};

// Testing Pins 
const int EXTEND_ARM = 41;
const int RETRACT_ARM = 43;
const int LIFT_ARM = 45;
const int DROP_ARM = 47;

// Times for different exercises

const int TENNIS_ARM_LIFTING_TIME = 5000;
// const int SQUASH_ARM_LIFTING_TIME = x;
const int TENNIS_ARM_EXTENDING_TIME = 28000;
// const int SQUASH_ARM_EXTENDING_TIME = x;
// const int FINAL_RIGHT_MOVEMENT_TIME = x;
// const int QUARTER_TURN_TIME = x;
// const int HALF_TURN_TIME = x;
// const int MIDDLING_TIME = x;
const int RACKING_TIME = 2000;

// MISC
const int DEBUGGING_LED = 10;
int state = 11;

void setup() {

  // Set Wheel Motor Pins

  for(int i = 0; i < 8; i++) {
    pinMode(wheel_motor_pins[i], OUTPUT);
    pinMode(wheel_motor_pins[i], LOW);
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

  pinMode(LEFT_FRONT_WHEEL_SPEED, OUTPUT);
  digitalWrite(LEFT_FRONT_WHEEL_SPEED, HIGH);

  pinMode(DEBUGGING_LED, OUTPUT);
  digitalWrite(DEBUGGING_LED, HIGH);


  pinMode(DEBUGGING_LED, OUTPUT);
  digitalWrite(DEBUGGING_LED, HIGH);


  pinMode(BALL_REMOVER_SPEED, OUTPUT);
  digitalWrite(BALL_REMOVER_SPEED, HIGH);

  pinMode(EXTENDER_SPEED, OUTPUT);
  digitalWrite(EXTENDER_SPEED, HIGH);

  pinMode(LIFTER_SPEED, OUTPUT);
  digitalWrite(LIFTER_SPEED, HIGH);

  // Test Pins 

  pinMode(EXTEND_ARM, INPUT_PULLUP);
  pinMode(RETRACT_ARM, INPUT_PULLUP);
  pinMode(LIFT_ARM, INPUT_PULLUP);
  pinMode(DROP_ARM, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  Serial.println("Simho Smells");

  if (!digitalRead(EXTEND_ARM)) {
    stopWheels(20);
    digitalWrite(EXTENDER_FORWARDS, HIGH);
  } else if (!digitalRead(RETRACT_ARM)) {
    stopWheels(20);
    digitalWrite(EXTENDER_BACKWARDS, HIGH);
  } else if (!digitalRead(LIFT_ARM)) {
    stopWheels(20);
    digitalWrite(LIFTER_FORWARDS, HIGH);
  } else if (!digitalRead(DROP_ARM)) {
    stopWheels(20);
    digitalWrite(LIFTER_BACKWARDS, HIGH);
  } else {

    digitalWrite(EXTENDER_FORWARDS, LOW);
    digitalWrite(EXTENDER_BACKWARDS, LOW);
    digitalWrite(LIFTER_FORWARDS, LOW);
    digitalWrite(LIFTER_BACKWARDS, LOW);

    recordSensorReadings();
    
    switch (state) {
      case 11:
        // Start - Drop Arm
        
        dropArm(2800);
        delay(100);
        
        state = 12;
        
        break;
        
      case 12: 
        // Drive forwards to pickup balls 
        
        wheelsGoForwards(5000);
        stopWheels(20);

        state = 13;
      
        break;

      case 13: 
        // Lift arm to above ledge height

        liftArm(850);
        delay(100);

        state = 14;

        break;

      case 14: 
         // Rotate wheels left to be in line with ledge
         
         wheelsRotateLeft(5000);
         stopWheels(20);

         state = 15;

         break;

      case 15:
        // Drive forwards to force straight allignment 

        wheelsGoForwards(3000);
        stopWheels(20);

        state = 16;
      
        break;

      case 16: 
        // Drive right to the ledge and stop to be in line with silo

        measure_distance_ledge = true;
  
        if (distance_ledge > 10) {
        stopWheels(20);
        state = 17;
        measure_distance_ledge = false; 
        }
        else {
          wheelsGoRight(20);
        }
        break;

      case 17: 
        // Drive backwards to give room for extension 

        wheelsGoBackwards(2000);
        stopWheels(200);

        state = 18;

        break;

      case 18:
        // Extend arm just above ledge height 
  
        extendArm(17600);
        delay(100);
  
        state = 19;
        
        break;
        
      case 19:
        // Lift arm to above tennis ball slio height 
        
        liftArm(4500);
        delay(100);
        
        state = 20;
        
        break;
        
      case 20:
        // Drive lifted arm to silo edge
        
        wheelsGoForwards(3000);
        stopWheels(20);
  
        state = 21;
        
        break;
  
      case 21:
        //Rack and unrack to deposit tennis balls
  
        rackOut(2500);
        delay(100);
  
        rackIn(1500);
        delay(100);
  
        state = 22;
  
        break;

      case 22: 
        // Drive backwards to retract

        wheelsGoBackwards(3000);
        stopWheels(20);

        state = 23;

        break;

      case 23:
        //Drop arm for retraction against silo 

        dropArm(1250);
        delay(100);

        state = 24; 

        break;

      case 24:
        // Drive forwards while retracting

        wheelsGoForwards(20);

        retractArm(3500);

        stopWheels(20);

        state = 25;

        break;

      case 25: 
        // Lift a little for full retraction potential

        liftArm(1500);

        delay(100);

        state = 26;

        break;

      case 26:

        retractArm(3100);

        delay(100);

        state = 27;

        break;

      case 27: 

        wheelsGoBackwards(2500);
        stopWheels(20);

        state = 28;

        break;

      case 28:

        dropArm(3150);

        delay(100);

        state = 29;
      
        break;

      case 29: 

        wheelsGoLeft(500);
        stopWheels(20);

        wheelsRotateLeft(5000);
        stopWheels(20);

        wheelsGoBackwards(500);
        stopWheels(20);

        wheelsGoLeft(4000);
        stopWheels(20);

        state = 30;

        break;

      case 30: 
        // Pickup squash balls 

        wheelsGoForwards(3000);
        stopWheels(20);

        liftArm(1200);
        delay(100);

        state = 31;

        break;

      case 31: 
        //Rotate to direction of squash silo

        wheelsGoRight(500);
        stopWheels(20);

        wheelsRotateLeft(5000);
        stopWheels(20);

        wheelsGoForwards(2000);
        stopWheels(20);

        state = 32;

        break;

      case 32:
        // Drive to ledge to create allignment 
      
        measure_distance_ledge = true;
  
        if (distance_ledge > 10) {
        stopWheels(20);
        state = 33;
        measure_distance_ledge = false; 
        }
        else {
          wheelsGoRight(20);
        }
        break;

      case 33:
        // Drive left to align with squash ball silo 

        wheelsGoRight(2500);
        stopWheels(20);

        state = 34;

        break;

      case 34:
        // Extend arm to reach squash silo

        extendArm(13000);
        delay(100);

        state = 35;

        break;

      case 35: 
        //Rack and unrack to deposit squash balls
  
        rackOut(2500);
        delay(100);
  
        rackIn(1500);
        delay(100);
  
        state = 36;
  
        break;

      case 36:
        // Drive to start/stop zone and finish!!!!!

        wheelsGoRight(700);
        stopWheels(20);

        wheelsGoBackwards(6000);
        stopWheels(20);

        break;
  }
 }
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

void stopWheels(int delay_time){

  for(int i = 0; i < 8; i++) {
    
    digitalWrite(wheel_motor_pins[i], LOW);
  }

  delay(delay_time);
}

void wheelsRotateLeft(int delay_time) {

  for(int i = 2; i < 6; i++) {
    
    digitalWrite(wheel_motor_pins[i], HIGH);
  }

  delay(delay_time);
  
}

void wheelsRotateRight(int delay_time) {

  digitalWrite(LEFT_BACK_WHEEL_FORWARDS, HIGH);
  digitalWrite(LEFT_FRONT_WHEEL_FORWARDS, HIGH);
  digitalWrite(RIGHT_BACK_WHEEL_BACKWARDS, HIGH);
  digitalWrite(RIGHT_FRONT_WHEEL_BACKWARDS, HIGH);

  delay(delay_time);
  
}

void liftArm(int delay_time) {

  digitalWrite(LIFTER_FORWARDS, HIGH);

  delay(delay_time);

  digitalWrite(LIFTER_FORWARDS, LOW);

}

void dropArm(int delay_time) {

  digitalWrite(LIFTER_BACKWARDS, HIGH);

  delay(delay_time);

  digitalWrite(LIFTER_BACKWARDS, LOW);

}

void extendArm(int delay_time) {
  
  digitalWrite(EXTENDER_FORWARDS, HIGH);

  delay(delay_time);

  digitalWrite(EXTENDER_FORWARDS, LOW);

}

void retractArm(int delay_time) {
  
  digitalWrite(EXTENDER_BACKWARDS, HIGH);

  delay(delay_time);

  digitalWrite(EXTENDER_BACKWARDS, LOW);

}

void rackOut(int delay_time) {

  digitalWrite(BALL_REMOVER_FORWARDS, HIGH);

  delay(delay_time);

  digitalWrite(BALL_REMOVER_FORWARDS, LOW);

}

void rackIn(int delay_time) {

  digitalWrite(BALL_REMOVER_BACKWARDS, HIGH);

  delay(delay_time);

  digitalWrite(BALL_REMOVER_BACKWARDS, LOW);

}
  

float sensorDistance(int trigger_pin, int echo_pin) {

  unsigned long duration;
  float distance; 

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

  delay(5);
  
  return distance;
}


void flashDebuggingLed() {

  digitalWrite(DEBUGGING_LED, HIGH);

  delay(200);

  digitalWrite(DEBUGGING_LED, LOW);
}


void recordSensorReadings() {

  float start_time = millis();

  // Takes multiple measurements and stores in an array
  for (int sample = 0; sample < 20; sample++) {

    if (measure_distance_ledge) {
      ledge_sensor_recordings[sample] = sensorDistance(LEDGE_SENSOR_TRIGGER, LEDGE_SENSOR_ECHO);
    }

    if (measure_distance_left) {
      left_sensor_recordings[sample] = sensorDistance(LEFT_SENSOR_TRIGGER, LEFT_SENSOR_ECHO);
    }

    if (measure_distance_right) {
      right_sensor_recordings[sample] = sensorDistance(RIGHT_SENSOR_TRIGGER, RIGHT_SENSOR_ECHO);
    }
  }

  //Sort the array in ascening order 
  for (int i = 0; i < 19; i++) {
    for (int j = i + 1; j < 20; j++) {

      if (measure_distance_left) {
        if (left_sensor_recordings[i] > left_sensor_recordings[j]) {
        float swap = left_sensor_recordings[i];
        left_sensor_recordings[i] = left_sensor_recordings[j];
        left_sensor_recordings[j] = swap;
        }
      }

      if (measure_distance_right) {
        if (right_sensor_recordings[i] > right_sensor_recordings[j]) {
        float swap = right_sensor_recordings[i];
        right_sensor_recordings[i] = right_sensor_recordings[j];
        right_sensor_recordings[j] = swap;
        } 
      }

      if (measure_distance_ledge) {
        if (ledge_sensor_recordings[i] > ledge_sensor_recordings[j]) {
        float swap = ledge_sensor_recordings[i];
        ledge_sensor_recordings[i] = ledge_sensor_recordings[j];
        ledge_sensor_recordings[j] = swap;
        }
      }
    }  
  }

  // Filter Noise - Average of 10 middle samples

  double left_sum = 0;
  double right_sum = 0;
  double ledge_sum = 0;
  
  for (int sample = 5; sample < 15; sample++) {

    if (measure_distance_left) {
      left_sum += left_sensor_recordings[sample];
      distance_left = left_sum / 10;
    }

    if (measure_distance_right) {
      right_sum += right_sensor_recordings[sample];
      distance_right = right_sum / 10;
    }

    if (measure_distance_ledge) {
      ledge_sum += ledge_sensor_recordings[sample];
      distance_ledge = ledge_sum / 10;
    }
  }

  Serial.print("Time Taken: ");
  Serial.println(millis() - start_time);
}
