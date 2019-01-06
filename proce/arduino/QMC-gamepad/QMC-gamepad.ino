#include <Wire.h>
#include <MR_QMC5883.h>

MR_QMC5883 compass;

int start = 0;
int count = 10;

float ADJUST = 180 / 3.14159265358979; //ラジアン・角度変換

float default_direct = 0.0;

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
  Serial.begin(9600);
  while (!compass.begin()) {
    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
    delay(500);
  }
  Serial.println("Initialize QMC5883");
  compass.setRange(QMC5883_RANGE_2GA);
  compass.setMeasurementMode(QMC5883_CONTINOUS);
  compass.setDataRate(QMC5883_DATARATE_50HZ);
  compass.setSamples(QMC5883_SAMPLES_8);

  while(start == 0){
    if (digitalRead(1) == 0){
      Vector mag = compass.readRaw();
      default_direct = atan2(mag.YAxis, mag.XAxis) * ADJUST;
      start = 1;
    }
  }
}

void loop() {
  float deg_hor_all = 0;
  int i;
  for (i = 0; i <= count - 1; i++) {
    Vector mag = compass.readRaw();
    deg_hor_all += atan2(mag.YAxis, mag.XAxis) * ADJUST;
  }
  float deg_hor = deg_hor_all / 10;

  if (deg_hor >= 50) {
    deg_hor = 50;
  } else if (deg_hor <= -50) {
    deg_hor = -50;
  }
  hor_d = map((deg_hor), -50, 50, 0, 255);

  Regg = map(analogRead(3), 8, 1023, 0, 255);

  if (digitalRead(1) == 0) {
    digitalWrite(13, HIGH);
    touch = 1;
  } else {
    digitalWrite(13, LOW);
    touch = 0;
  }

  if (Serial.available() > 0) {
    Serial.write(hor_d);
    Serial.write(Regg);
    Serial.write(touch);
    Serial.read();
  }

  delay(10);
}
