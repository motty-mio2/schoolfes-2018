import processing.serial.*;

Serial myPort;

int read_d = 0;
int ypon;

int rco = 255;
int gco = 0;
int bco = 0;

float circle_X = 320;
float circle_Y = 320;
int touch;

void setup() {
  size(640, 640);
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

  //  read_d = int(random(0, 4));
  //  read_d = int(random(0, 4));

  if (touch == 1) {
    rco = int(random(0, 256));
    gco = int(random(0, 256));
    bco = int(random(0, 256));
  }
  
  /*
  if (4 <= read_d && read_d <= 7) { 
    circle_Y += 5;
  } else if (8 <= read_d) {
    circle_Y -= 5;
  }
  */
  
  circle_Y = map(ypon,0,255,640,0);
  
  switch (read_d % 4) {
  case 1: 
    circle_X += 5; 
    break;
  case 2: 
    circle_X -= 5; 
    break;
  default: 
    break;
  }

  print(read_d);
  println();

  noFill();
  strokeWeight(5);
  stroke(rco, gco, bco);
  ellipse(circle_X, circle_Y, 150, 150);
}

void serialEvent(Serial myPort) {
  if (myPort.available()>2) {
    read_d = myPort.read();
    ypon = myPort.read();
    touch = myPort.read();
    myPort.write(65);
  }
}
