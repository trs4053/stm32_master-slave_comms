void master_send(int slave_address, int wheel_velocity, int corner_angle){

  Serial.print("I");  //start transmission, next value is slave number
  Serial.print(slave_address);  //slave number
  Serial.print("A");  //next value is corner Angle
  Serial.print(corner_angle);
  Serial.print("V");  //next value is wheel Velocity
  Serial.print(wheel_velocity);
  Serial.print("F");  //end of transmission

  Serial.flush();
}

void master_send(int slave_address, int wheel_velocity, int corner_angle, SoftwareSerial& Serialx, int enable){

  digitalWrite(enable, HIGH);
  Serialx.print("I");  //start transmission, next value is slave number
  Serialx.print(slave_address);  //slave number
  Serialx.print("A");  //next value is corner Angle
  Serialx.print(corner_angle);
  Serialx.print("V");  //next value is wheel Velocity
  Serialx.print(wheel_velocity);
  Serialx.print("F");  //end of transmission

  Serial.flush();
}
