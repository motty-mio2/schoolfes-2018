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

void setup() {
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
}

void loop() {
  Vector mag = compass.readRaw();
  float deg_hor = atan2(mag.YAxis, mag.XAxis) * ADJUST+180;
  float deg_ver = atan2(mag.ZAxis, sqrt(mag.XAxis * mag.XAxis + mag.YAxis * mag.YAxis)) * ADJUST;

  Serial.print(deg_hor);
  Serial.print(",");
  Serial.println(deg_ver);

  Serial.println();

  delay(100);
}
