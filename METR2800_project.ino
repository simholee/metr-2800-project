
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
const int HALF_TURN_TIME = 1000;
// const int MIDDLING_TIME = x;
const int RACKING_TIME = 2000;

// MISC
const int DEBUGGING_LED = 10;
int state = 32;

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

  pinMode(EXTEND_ARM, INPUT);
  pinMode(RETRACT_ARM, INPUT);
  pinMode(LIFT_ARM, INPUT);
  pinMode(DROP_ARM, INPUT);
  
  Serial.begin(9600);
}

void loop() {

  recordSensorReadings();

  if (digitalRead(EXTEND_ARM)) {
    digitalWrite(EXTENDER_FORWARDS, HIGH);
  } else if (digitalRead(RETRACT_ARM)) {
    digitalWrite(EXTENDER_BACKWARDS, HIGH);
  } else if (digitalRead(LIFT_ARM)) {
    digitalWrite(LIFTER_FORWARDS, HIGH);
  } else if (digitalRead(DROP_ARM)) {
    digitalWrite(LIFTER_BACKWARDS, HIGH);
  } else {

    digitalWrite(EXTENDER_FORWARDS, LOW);
    digitalWrite(EXTENDER_BACKWARDS, LOW);
    digitalWrite(LIFTER_FORWARDS, LOW);
    digitalWrite(LIFTER_BACKWARDS, LOW);

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
  
        // Serial.println(distance_ledge);
  
        Serial.println(distance_ledge);
  
        measure_distance_ledge = true;
  
        if (distance_ledge > 10) {
        stopWheels(500);
        state = 13;
        measure_distance_ledge = false; 
        }
        else {
          wheelsGoRight(20);
        }
        break;
        
      case 13: 
        // drive forward
        Serial.println("State 2");
  
        Serial.println(distance_left);
        Serial.println(distance_right);
  
        measure_distance_left = true;
        measure_distance_right = true; 
          
        if (distance_left < 14 && distance_right < 14) {
          stopWheels(20);
          state = 14;
          measure_distance_left = false;
          measure_distance_right = false; 
        }
        else {
          wheelsGoForwards(20);
        }
        
        break;
        
      case 14:
        // lift arm [tennis ball]
        Serial.println("State 3");
        
        liftArm(850);
        delay(200);
        wheelsGoBackwards(1000);
        stopWheels(200);
        
        state = 15;
        
        break;
        
        // DO WE NEED TO DRIVE FORWARD HERE???
      case 15:
  
        extendArm(14000);
        delay(500);
  
        state = 16;
        
        break;
        
      case 16:
        // extend arm [tennis ball]
        liftArm(3600);
        delay(500);
        
        state = 17;
        
        break;
        
      case 17:
        // rack and unrack
        Serial.println("State 5");
        
        wheelsGoForwards(3000);
        stopWheels(20);
  
        state = 18;
        
        break;
  
      case 18:
  
        rackOut(2500);
        delay(200);
  
        rackIn(1500);
        delay(200);
  
        state = 2838;
  
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
        measure_distance_left = true;
        measure_distance_right = true;

        Serial.println(distance_right);

        if (distance_right > 100) {
          wheelsRotateLeft(200);
          stopWheels(2000);
          for (int i=0; i<5; i++) {
            digitalWrite(DEBUGGING_LED, LOW);
            delay(200);
            digitalWrite(DEBUGGING_LED, HIGH);
            delay(200);
          }
          state = 33;
          Serial.println("going");
        }
        else {
          wheelsRotateLeft(20);
        }

        if (state == 33) {
          Serial.println("Next State");
        }
        break;

      case 33:
        
        if (distance_right > 100) {
          wheelsRotateLeft(20);
        }
        else if (distance_right < (distance_left + 3)) {
          stopWheels(20);
          state = 33;
          for (int i=0; i<10; i++) {
            digitalWrite(DEBUGGING_LED, LOW);
            delay(200);
            digitalWrite(DEBUGGING_LED, HIGH);
            delay(200);
          }
          Serial.println("I am here, look at me");
        }
        else {
          wheelsRotateLeft(20);
        }

    /*
    case 33:
      // drive rightwards -> Until when?? maybe a hundredish milliseconds after initial sensoring
      Serial.println("State 10");
      
      int distance_right = sensorDistance(RIGHT_SENSOR_TRIGGER, RIGHT_SENSOR_ECHO);
      Serial.println(distance_right);
      
      if (distance_right < 30) { // check the numbers on this depending on how close the squash balls are
        wheelsGoRight(MIDDLING_TIME); // go back and forth and measure time -> middle that
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
      */
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
