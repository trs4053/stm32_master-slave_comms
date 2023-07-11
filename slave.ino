#include <SoftwareSerial.h>

struct values {
  int corner_angle;
  int wheel_velocity;
};

void pass(int x){

  Serial.print("Pass: ");
  Serial.println(x);
}

void fail(int x){

  Serial.print("Fail: ");
  Serial.println(x);
}


class Slave {
public:
  int slave_no;
  int enable;
  SoftwareSerial& serialx;
  

  Slave(int slave_address, SoftwareSerial& soft_serial, int enable)
    : enable(enable), serialx(soft_serial), slave_no(slave_address) {}

  void init() {
    serialx.begin(300);
    pinMode(enable, OUTPUT);
    serialx.setTimeout(500);
  }


  values getvalues(){
  digitalWrite(enable, LOW);
  values v={0,0};
  int slave_add=0;
  if (serialx.available()){
    pass(1);
    if (serialx.read() == 'I') {
      pass(2);
      slave_add = serialx.parseInt();
      if (slave_no == slave_add) {
        pass(3);
        if (serialx.read() == 'V') {
          v.wheel_velocity = serialx.parseInt();
        } 
        else if (serialx.read() == 'A') {
          v.corner_angle = serialx.parseInt();
        }   
      }

      else {
        fail(3);
        return {0,0};}
    }
    else{fail(2);}
  }
  else{fail(1);} 

  return v;
}

};


SoftwareSerial serialx(PA10,PA9);
Slave slave1(1, serialx, PA15);


void setup(){
  Serial.begin(300);
  slave1.init();
  //serialx.setTimeout(100);
}

void loop(){
  values a={0,0};
  a = slave1.getvalues();

  
  Serial.print("Corner angle: ");
  Serial.println(a.corner_angle);

  Serial.print("Wheel velocity: ");
  Serial.println(a.wheel_velocity);

}
