#include <SoftwareSerial.h>

struct values {
  int corner_angle;
  int wheel_velocity;
};

class Slave {

public:
  int slave_no;
  int enable;
  SoftwareSerial& serialx;
  

  Slave(int slave_address, SoftwareSerial& soft_serial, int enable)
    : enable(enable), serialx(soft_serial), slave_no(slave_address) {}

  void init() {
    serialx.begin(9600);
    pinMode(enable, OUTPUT);
  }

  values getvalues(){
  values v={0,0};
  int slave_add=0;
  if (serialx.available()){
    if (serialx.read() == 'I') {
      slave_add = serialx.parseInt();
      if (slave_no == slave_add) {
        if (serialx.read() == 'V') {
          v.wheel_velocity = serialx.parseInt();
        } 
        else if (serialx.read() == 'A') {
          v.corner_angle = serialx.parseInt();
        }   
      }

      else {return {0,0};}
    }
  }
  return v;
}


 
};

/**
SoftwareSerial serialx(PA10,PA9);
Slave slave1(serialx,PA15);

void setup(){
  slave1.init();
}

void loop(){
  values a = slave1.getvalues();
  Serial.println(a.corner_angle);
  Serial.println(a.wheel_velocity);
}
*/

