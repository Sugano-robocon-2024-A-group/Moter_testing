#include <PS4Controller.h>
#include <Arduino.h>
#include <CAN.h>
#include <ESP32Servo.h>  // ESP32用のサーボライブラリ
#include "tuushin.h"  // tuushin.hをインクルード
#include "encoder.h"
#include "functions_kai.h"//運転関連のものはここに入っている。

//使用ボタン設定
/*
  int PS4_Circle=0;
  int PS4_Triangle=0;
  int PS4_R1=0;
  int PS4_L1=0;*/

//int currentAngle = 0;        
//

//int Ashimawari_Command=0;//コマンド
int j=1;

// 許容誤差と移動距離目標
const int allowableError = 5;
// エンコーダ関連の設定
const float wheelDiameter = 80.0;
const float encoderPulsesPerRevolution = 750;
const float distancePerCount = (PI * wheelDiameter) / encoderPulsesPerRevolution;

float currentDistance;

//static unsigned long lastTime = 0; // 前回の実行開始時間を保持
//unsigned long currentTime = millis();

  
// setup関数: 初期設定を行う。CANバスの初期化と、送受信の設定を呼び出す
void setup() {
  //シリアル通信、PS4準備
  Serial.begin(115200);  // シリアル通信開始
  //PS4.begin("1c:69:20:e6:20:d2");//ここにアドレス
  Serial.println("Ready.");
  while (!Serial);  // シリアル接続待機

  //エンコーダ準備 エンコーダピンの設定
  for (int i = 0; i < 2; i++){
    pinMode(encoderA[i], INPUT_PULLUP);
    pinMode(encoderB[i], INPUT_PULLUP);
  }

  init_pwm_setup();

  digitalWrite(motor_pwm[j], HIGH);
  digitalWrite(motor_dir1[j], HIGH);
  digitalWrite(motor_dir2[j], LOW); 
  
  // 割り込みの設定

  //attachInterrupt(digitalPinToInterrupt(encoderA[0]), []() { handleEncoder(0); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[1]), []() { handleEncoder(1); }, CHANGE);

}

// loop関数 やること　CAN送信、（前輪Encoder読み、前輪回転）、いろいろやる。
void loop(){
  currentDistance = encoderCount[1] * distancePerCount;
  //Serial.printf("%f\n",currentDistance);
  static unsigned long lastTime = 0; // 前回の実行開始時間を保持
  unsigned long currentTime = millis();

  if (currentTime - lastTime >= 1000) {
    lastTime = currentTime;
    Serial.printf("%f\n",currentDistance);
    // ここに1秒ごとに実行したい処理を記述
    //Serial.println("1秒経過しました");
  }
  // 1秒以内に他のタスクを実行する場合はここに記述
}

/*
*/
