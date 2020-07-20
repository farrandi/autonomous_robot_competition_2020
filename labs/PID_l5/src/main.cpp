#include <Arduino.h>

#define MOTOR_A PA_3
#define MOTOR_B PA_2
#define POTPIN1 PA_7
#define POTPIN2 PB_0
#define SENSOR PA_0
#define ON_PIN PB15

// Found empirically
#define POTD_MAX 1023.0
#define POTD_MIN 480.0
#define POTK_MAX 1023.0
#define POTK_MIN 505.0

#define TAPE_IDEAL 500

volatile int error = 0;
volatile int last_error = 0;
volatile int sensor_reading = 0;
volatile int P = 0;
volatile int D = 0;
volatile int gain = 0;
volatile double kd = 0;
volatile double kp = 0;
volatile double potk = 0;
volatile double potp = 0;
volatile double map_max = 100;

double read_tape(PinName tape);
double map_kd(double val);
double map_kp(double val);
double find_error(double reading);

void setup() {
  pinMode(MOTOR_B, OUTPUT);
  pinMode(MOTOR_A, OUTPUT);
  pinMode(POTPIN1, INPUT);
  pinMode(POTPIN2, INPUT);
  pinMode(SENSOR, INPUT);
  pinMode(ON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(ON_PIN)){
    sensor_reading = read_tape(SENSOR);
    delay(1000);

    kd = map_kd(analogRead(POTPIN1));
    kp = map_kp(analogRead(POTPIN2));

    error = find_error(sensor_reading);

    P = kp*error;
    D = kd*error;

    last_error = error;
    gain = P+D;

    if (gain > 5) {
      pwm_start(MOTOR_B, 1024, gain, RESOLUTION_10B_COMPARE_FORMAT);
      Serial.println("Running forward");
    }
    if (gain < -5) {
      pwm_start(MOTOR_A, 1024, -gain, RESOLUTION_10B_COMPARE_FORMAT);
      Serial.println("Running backwards");
    }

  } else {
    pwm_stop(MOTOR_A);
    pwm_stop(MOTOR_B);
    Serial.println("OFF");
    delay(1000);
  }
}

double read_tape(PinName tape){
  double val = analogRead(tape);
  Serial.println("Sensor reading: ");
  Serial.println(val);
  return val;
}

double map_kd(double val){
  Serial.print("kd: ");
  double result = map_max/(POTD_MAX-POTD_MIN)*(val - POTD_MIN);
  Serial.println(result);
  return result;
}

double map_kp(double val){
  Serial.print("kp: ");
  double result = map_max/(POTK_MAX-POTK_MIN)*(val - POTD_MIN);
  Serial.println(result);
  return result;
}

double find_error(double reading){
  return reading-TAPE_IDEAL;
}