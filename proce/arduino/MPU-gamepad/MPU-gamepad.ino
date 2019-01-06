#include <Wire.h>
#include <MR_QMC5883.h>

MR_QMC5883 compass;

int flu  = 3;
int count = 10;

float ADJUST = 180 / 3.14159265358979; //ラジアン・角度変換

int minX = 0;
int maxX = 0;
int minY = 0;
int maxY = 0;
int offX = 0;
int offY = 0;

int hor_d; //水平面
int touch; //ボタン
int Regg; //抵抗値

void setup() {
  pinMode(13, OUTPUT);
  pinMode(1, INPUT_PULLUP);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  Regg = map(analogRead(3), 8, 1023, 0, 255);

  if (digitalRead(1) == 0) {
    digitalWrite(13, HIGH);
    touch = 1;
  } else {
    digitalWrite(13, LOW);
    touch = 0;
  }

  if (Serial.available() > 0) {
    Serial.write(hor_d); //X-axis
    Serial.write(); //Y-axis
    Serial.write(Regg);
    Serial.write(touch);
    Serial.read();
  }

  delay(10);
}
