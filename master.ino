#include <SoftwareSerial.h>


void master_send(int slave_address, int wheel_velocity, int corner_angle, SoftwareSerial& Serialx, int enable){

  digitalWrite(enable, HIGH);
  Serialx.print("I");  //start transmission, next value is slave number
  Serialx.print(slave_address);  //slave number
  Serialx.print("A");  //next value is corner Angle
  Serialx.print(corner_angle);
  Serialx.print("V");  //next value is wheel Velocity
  Serialx.print(wheel_velocity);
  Serialx.print("F");  //end of transmission
  Serialx.flush();
}


SoftwareSerial serialx(PA10,PA9);

void setup(){

  serialx.begin(300);
  pinMode(PA15, OUTPUT);
  //serialx.setTimeout(250);
  
}

void loop(){
  master_send(1, 50, 36, serialx, PA15);
}
