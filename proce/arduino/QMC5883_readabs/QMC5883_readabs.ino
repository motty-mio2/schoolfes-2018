#include <Wire.h>
#include <MR_QMC5883.h>

MR_QMC5883 compass;

int flu  = 3;
int count =10;

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
float center = 0;
float delta_d;

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

  if (center <= 180) {
    delta_d = center + 180;
  } else {
    delta_d = center - 180;
  }
}

void loop() {
  float deg_hor_all = 0;
  int i;
  for(i=0;i<=9;i++){
   Vector mag = compass.readRaw();
   deg_hor_all += atan2(mag.YAxis, mag.XAxis) * ADJUST + 180;
  }
  float deg_hor = deg_hor_all / 10;
  
  if (deg_hor >= delta_d) {
    deg_hor -= 360;
  }

  hor_d = map((deg_hor - center), -90, 90, 0, 255);

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