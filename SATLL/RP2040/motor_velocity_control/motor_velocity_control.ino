// Open loop motor control example
#include <SimpleFOC.h>

#define INT_PIN   9
#define CURRENT_PIN A0
#define current_lim_mA 400
long startTime; // variable to store the start time

const long duration = 100; // duration of 1 seconds in milliseconds

float current = 0; //variable to store the current reading in
float min_curr_reading = 0;


// BLDC motor & driver instance
// BLDCMotor motor = BLDCMotor(pole pair number);
// BLDC motor & driver instance
BLDCMotor motor = BLDCMotor(7, 5.47); 
BLDCDriver3PWM driver = BLDCDriver3PWM(7,3,1,6,2,0); //3 pwm pins

MagneticSensorSPI sensor = MagneticSensorSPI(AS5147_SPI, 17); //change to SPI CS for encoder 

InlineCurrentSense current_sense = InlineCurrentSense(0.01f, 50.0f, A0, A2);

//target variable
float target_velocity = 0;

// instantiate the commander
Commander command = Commander(Serial);
void doTarget(char* cmd) { command.scalar(&target_velocity, cmd); }
void doLimit(char* cmd) { command.scalar(&motor.voltage_limit, cmd); }

void onMotor(char* cmd){ command.motor(&motor, cmd); }

void setup() {
  sensor.init();
  motor.linkSensor(&sensor);
  driver.voltage_power_supply = 7.4;
  driver.init();
  motor.linkDriver(&driver);
  motor.foc_modulation = FOCModulationType::SinePWM;
  motor.controller = MotionControlType::torque;

  // contoller configuration based on the control type
  motor.PID_velocity.P = 0.2f;
  motor.PID_velocity.I = 10; //was 10
  motor.PID_velocity.D = 0;
  // default voltage_power_supply
  motor.voltage_limit = 7.4;
  // velocity low pass filtering time constant
  motor.LPF_velocity.Tf = 0.1f; //was 0.02f
  Serial.begin(115200);
  // comment out if not needed
  motor.useMonitoring(Serial);
  motor.monitor_variables = _MON_TARGET | _MON_VEL ; 
 
   min_curr_reading = analogRead(CURRENT_PIN);
    // downsampling
  motor.monitor_downsample = 3500; // default 10
  // initialise motor
  motor.init();
  // align encoder and start FOC
  motor.initFOC();

  command.add('M', onMotor, "motor");
  // Run user commands to configure and the motor (find the full command list in docs.simplefoc.com)
  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");
  Serial.println(F("WAITING FOR MOTOR COMMANDS"));


  delay(1000);
}

void loop() {

  // open loop velocity movement
  // using motor.voltage_limit and motor.velocity_limit
  // to turn the motor "backwards", just set a negative target_velocity
  motor.move(target_velocity);

    //PhaseCurrent_s currents = current_sense.getPhaseCurrents();
    //float current_magnitude = current_sense.getDCCurrent();
/*
    Serial.print(currents.a*1000); // milli Amps
    Serial.print("\t");
    Serial.print(currents.b*1000); // milli Amps
    Serial.print("\t");
    Serial.print(currents.c*1000); // milli Amps
    */
    Serial.print("\t");
    //Serial.println(current_magnitude*1000); // milli Amps
    current = ((analogRead(CURRENT_PIN)-min_curr_reading)/0.310)/1.1;
    Serial.print(current); // milli Amps
      if(current > current_lim_mA){
         motor.move(0);
         target_velocity = 0;
      }
    Serial.print(" mA");
    Serial.print("\t");
  
    sensor.update();
    // display the angle and the angular velocity to the terminal
    Serial.print(sensor.getAngle());
    Serial.print("\t");
    Serial.println(sensor.getVelocity());

  // user communication
  command.run();



}