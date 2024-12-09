//#include <PS4Controller.h>
#include <Arduino.h>
#include <CAN.h>
#include "tuushin.h"
#include "encoder.h"
#include "functions_kai.h"

// エンコーダ関連のピン設定 CPPにあり。
// カウント値をグローバルに定義済み

uint32_t id;          // CAN IDを格納する変数
uint16_t data[8]={0,0,0,0,0,0,0,0};      // 受信データを格納する配列（最大8バイト）
uint16_t length=0;       // 受信データの長さを格納する変数

// 許容誤差と移動距離目標
const int allowableError = 5;
// エンコーダ関連の設定
const float wheelDiameter = 80.0;
const float encoderPulsesPerRevolution = 750;
const float distancePerCount = (PI * wheelDiameter) / encoderPulsesPerRevolution;

float currentDistance;
int j=1;
/*
void onReceive(int packetSize){
// 割り込み時の処理をここに書く
Serial.println("ReceivePacket");
receivePacket(id, data, length);
delay(1000);
}*/

// setup関数: 初期設定を行う。CANバスの初期化と、送受信の設定を呼び出す
void setup() {
  
  Serial.begin(115200);  // シリアル通信開始
   while (!Serial);  // シリアル接続待機

  Serial.println("Start");

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
// loop関数: 受信と送信を繰り返す
void loop() {
  
//receivePacket(id, data, length);
// CANメッセージを受信
//Serial.print("NEXT！");
//handleMoterInput(targetDistance, data[0]);

handleMoterInput(targetDistance, data[0]);

//int packetSize = CAN.parsePacket();
//if (receivePacket) { 
    Serial.print(data[0]);
    //Serial.print(data[1]);データないやつ入れちゃうとエラーして落ちちゃう
    //Serial.print(data[2]);Serial.print(data[3]);
    Serial.println();

// デバッグ用：エンコーダカウントを出力
  for (int i = 0; i < 2; i++)
  {
    Serial.print("Encoder ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(encoderCount[i]);
  }
//encoderCount[0]が右後ろ　encoderCount[1]が左後ろ

//移動関数
bool reachedTarget = true;

    for (int i = 0; i < 2; i++) {
        float currentDistance = encoderCount[i] * distancePerCount;
        float controlSignal = pidCompute(i, targetDistance[i], currentDistance);
       if(controlSignal<100.0){
          controlSignal=0.0;
          }
        Serial.printf("%f ",currentDistance);
        Serial.printf("%f ",targetDistance[i]);
        Serial.printf("%f \n",controlSignal);
        driveMotor(i, controlSignal);
        if (abs(currentDistance - targetDistance[i]) > allowableError) {
            reachedTarget = false;
        }
    }

    if (reachedTarget) {
        stopMotors();
        resetControlVariables();
        
        //ここでTargetも0にする
         for (int j = 0; j < 4; j++) {
        targetDistance[j]=0.0;
         }
        Serial.print("reachedTarget\n");
        handleMoterInput(targetDistance, data[0]);
    }

for (int i = 0; i < 1; i++) {
    data[i] = 0;
    }
//}
 delay(40);  // 1秒の遅延
}

/*f (PS4.isConnected()) {
           // handlePS4Input();//動きを説明する関数（もし入力が入ったら？）
            handlePS4Input(targetDistance);//動きを説明する関数（もし入力が入ったら？）
        }*/
