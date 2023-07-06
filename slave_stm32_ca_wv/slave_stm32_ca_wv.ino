#include <SoftwareSerial.h>

struct values {
  int corner_angle;
  int wheel_velocity;
};

values get_values(SoftwareSerial& serialx) {
  values v = {0, 0};  // Initialize the struct with default values

  if (serialx.available()) {
    if (serialx.read() == 'V') {
      v.wheel_velocity = serialx.parseInt();
    } else if (serialx.read() == 'A') {
      v.corner_angle = serialx.parseInt();
    }
  }
  return v;
}

class Slave {
private:
  int slave_no;
  int enable;
  SoftwareSerial& serialx;
  
public:
  Slave(int slave_address, SoftwareSerial& soft_serial, int enable)
    : enable(enable), serialx(soft_serial), slave_no(slave_address) {}

  void init() {
    serialx.begin(9600);
    pinMode(enable, OUTPUT);
  }

  bool slaveno() {
  if (serialx.available()) {
    
    if (serialx.read() == 'I') {
      
      int slave_add = serialx.parseInt();
      if (this->slave_no == slave_add) {
        
        return true;
      } 
      else {return false;}
    }
  }
  return false;  // Default return value
}

values getvalues() {
  digitalWrite(enable, LOW);
  if (slaveno()) {
    return get_values(this->serialx);
  }
  return values();  // Default return value
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

