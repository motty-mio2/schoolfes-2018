float x;
float y;
float xx=-1, yy=-1; //マウスの座標
int pt=0; //得点
int cnt; //得点表示の応答速度を早くする為のカウンタ
boolean click=false;

void setup() {
  textSize(24); //文字表示の準備
  size(500, 500);
  background(204);
  frameRate(60); //フレームレートは上げておく
  x=random(0, 450);
  y=random(0, 450);
}


void draw() {
  if ((x<=xx&&xx<=x+50) && (y<=yy&&yy<=y+50)) { //当たり判定
    xx=-1; //判定後はあり得ない値にして重複判定防止
    pt++; //当たったので得点増加
  }

  if (++cnt%180==0) { //180回に一回四角の場所を変える
    background(204);
    x=random(0, 450);
    y=random(0, 450);
    click=false; //この座標でのクリック履歴クリア
    cnt=0; //更新したのでカウンタクリア
  }
  background(204);
  fill(255, 255, 255);
  rect(x, y, 50, 50);
  fill(0, 0, 0);
  text(pt+" Point", 380, 480);
}

void mousePressed() { //マウスがクリックされるとこのメソッドを実行
  if (!click) { // この座標でのクリックが初めて
    xx=mouseX;
    yy=mouseY;
  }
  click=true; // クリック履歴
}
