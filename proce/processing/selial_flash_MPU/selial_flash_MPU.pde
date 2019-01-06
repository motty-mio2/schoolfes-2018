import processing.serial.*;

Serial myPort;

int read_hor = 0;
int touch;
int xpon;
int ypon;
int dial;

int flamer = 300;

float x;
float y;

int pt = 0; //得点
int click = 0;
int cnt; //得点表示の応答速度を早くする為のカウンタ

int rco = 255;
int gco = 0;
int bco = 0;

float circle_X = 320;
float circle_Y = 320;

void setup() {
  textSize(24);
  size(640, 640);
  background(255);
  frameRate(60);
  myPort = new Serial(this, "COM8", 9600);
  myPort.write(65);
}

void draw() {
  background(255);
  strokeWeight(1);
  stroke(200);
  line(0, height/2, width, height/2);
  line(width/2, 0, width/2, height);

  circle_X = map(xpon,0,255,0,width);
  circle_Y = map(ypon,0,255,height,0);// + random(-5,5);

  if (touch == 1) {
    rco = int(random(0, 256));
    gco = int(random(0, 256));
    bco = int(random(0, 256));
    if ((x <= circle_X && circle_X <= x + 50) && (y <= circle_Y && circle_Y <= y + 50) && (click == 0)) { //当たり判定
      pt++; //当たったので得点増加
      click = 1;
      cnt = flamer - 1;
    }
  }

  if (++cnt >= framer) { //180回に一回四角の場所を変える
    background(204);
    x=random(0, height - 50);
    y=random(0, width - 50);
    click = 0; //この座標でのクリック履歴クリア
    cnt = 0; //更新したのでカウンタクリア
  }

  background(204);
  fill(255, 255, 255);
  rect(x, y, 50, 50);
  fill(0, 0, 0);
  text(pt+" Point", 520, 620);

  noFill();
  strokeWeight(5);
  stroke(rco, gco, bco);
  ellipse(circle_X, circle_Y, 20, 20);
}

void serialEvent(Serial myPort) {
  if (myPort.available()>2) {
    xpon = myPort.read();
    ypon = myPort.read();
    dial = myPort.read();
    touch = myPort.read();
    myPort.write(65);
  }
}
