#include "Wire.h"

const int MPU_ADDR = 0x68;
int16_t aceleracion_x,aceleracion_y,aceleracion_z;
int16_t gyro_x,gyro_y,gyro_z;
int16_t temperatura;

char tmp_str[7];

char* convert_int16_to_str(int16_t i){
  sprintf(tmp_str,"%6d",i);
  return tmp_str;
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x68);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR,7*2,true);

  aceleracion_x=Wire.read()<<8|Wire.read();
  aceleracion_y=Wire.read()<<8|Wire.read();
  aceleracion_z=Wire.read()<<8|Wire.read();
  temperatura=Wire.read()<<8|Wire.read();
  gyro_x=Wire.read()<<8|Wire.read();
  gyro_y=Wire.read()<<8|Wire.read();
  gyro_z=Wire.read()<<8|Wire.read(); 

  Serial.print("aX = ");Serial.print(convert_int16_to_str(aceleracion_x));
  Serial.print(" | aY = ");Serial.print(convert_int16_to_str(aceleracion_y));
  Serial.print(" | aZ = ");Serial.print(convert_int16_to_str(aceleracion_z));

  Serial.print(" | tmp = ");Serial.print(temperatura/340.00+36.53);

  Serial.print(" | gX = ");Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = ");Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = ");Serial.print(convert_int16_to_str(gyro_z));

  delay(700);
  
}
