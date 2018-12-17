import processing.serial.*;

Serial myPort;

int read_d;
int touch;
int ypon;

int rco = 255;
int gco = 0;
int bco = 0;

float circle_X = 320;
float circle_Y = 320;

void setup() {
  size(640, 640);
    frameRate(30);
  background(255);
  myPort = new Serial(this, "COM8", 9600);
  myPort.write(65);
}

void draw() {
  background(255);
  strokeWeight(1);
  stroke(200);
  line(0, height/2, width, height/2);
  line(width/2, 0, width/2, height);

  circle_Y = map(ypon,0,255,height,0) + random(-5,5);

  if (touch == 1) {
    rco = int(random(0, 256));
    gco = int(random(0, 256));
    bco = int(random(0, 256));
  }

  switch (read_d % 4) {
    case 1: circle_X += 5; break;
    case 2: circle_X -= 5; break;
  default: break;
  }

  noFill();
  strokeWeight(5);
  stroke(rco, gco, bco);
  ellipse(circle_X, circle_Y, 50, 50);
}

void serialEvent(Serial myPort) {
  if (myPort.available()>2) {
    read_d = myPort.read();
    ypon = myPort.read();
    touch = myPort.read();
    myPort.write(65);
  }
}
