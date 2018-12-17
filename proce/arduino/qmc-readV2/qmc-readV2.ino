#include <Wire.h>
#include <MR_QMC5883.h>

MR_QMC5883 compass;

float ADJUST = 180 / 3.14159265358979;

int minX = 0;
int maxX = 0;
int minY = 0;
int maxY = 0;
int offX = 0;
int offY = 0;

int flu  = 3;
int touch;
int Regg;

float deg_hor_old;
float deg_ver_old;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(1, INPUT_PULLUP);
  Serial.begin(9600);
  // Initialize Initialize QMC5883
  while (!compass.begin()) {
    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
    delay(500);
  }
  Serial.println("Initialize QMC5883");
  compass.setRange(QMC5883_RANGE_2GA);
  compass.setMeasurementMode(QMC5883_CONTINOUS);
  compass.setDataRate(QMC5883_DATARATE_50HZ);
  compass.setSamples(QMC5883_SAMPLES_8);

  Vector mag = compass.readRaw();
  deg_hor_old = atan2(mag.YAxis, mag.XAxis);
  deg_ver_old = atan2(mag.ZAxis, sqrt(mag.XAxis * mag.XAxis + mag.XAxis * mag.XAxis));
}

void loop() {
  Vector mag = compass.readRaw();
  float length = sqrt(mag.XAxis * mag.XAxis + mag.YAxis * mag.YAxis + mag.ZAxis * mag.ZAxis);
  float deg_hor = atan2(mag.YAxis, mag.XAxis) * ADJUST;
  float deg_ver = acos(mag.ZAxis / length) * ADJUST;

  float mod_hor = deg_hor - deg_hor_old;
  float mod_ver = deg_ver - deg_ver_old;

  int send_data = 0;

  Regg = map(analogRead(3), 8, 1023, 0, 255);

  if (digitalRead(1) == 0) {
    touch = 1;
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
    touch = 0;
  }

  if ((flu <= mod_hor && mod_hor <= 200) || (mod_hor <= -200)) {
    send_data = 1;
  } else if ((-200 <= mod_hor && mod_hor <= -flu) || (200 <= mod_hor)) {
    send_data = 2;
  } else {
    send_data = 0;
  }

  deg_hor_old = deg_hor;
  deg_ver_old = deg_ver;
  Serial.println(deg_hor);
  Serial.println();
/*
  if (Serial.available() > 0) {
    Serial.write(send_data);
    Serial.write(Regg);
    Serial.write(touch);
    Serial.read();
  }
*/
//  delay(10);
}
