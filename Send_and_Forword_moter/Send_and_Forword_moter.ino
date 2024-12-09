//構造変更版、Send側




/*

 Serial.println("Start");//送信系⇒Encoder読み⇒前進コード
//encoderCount[0]が右前　encoderCount[1]が左前

  // 送信処理を実行
   if (PS4.Circle()){Serial.println("Circle Button");
      PS4_Circle=1;//
      Serial.printf("%d\n", PS4_Circle); 
    }
    if (PS4.Triangle()) {Serial.println("Triangle Button");
      PS4_Triangle=1;//
      Serial.printf("%d\n", PS4_Triangle);
      }
    if (PS4.R1()){Serial.println("R1 Button");
      PS4_R1=1;//
      Serial.printf("%d\n", PS4_R1);
      }
     if (PS4.L1()){Serial.println("L1 Button");
      PS4_L1=1;//]
      Serial.printf("%d\n", PS4_L1);
      }
 if(PS4_Circle==1||PS4_Triangle==1||PS4_R1==1||PS4_L1==1){
  sendToutekiCommand(PS4_Circle, PS4_Triangle, PS4_R1, PS4_L1);//先に送る
  }

  if (PS4.Right()){Ashimawari_Command=3;
      }
      if (PS4.Down()){Ashimawari_Command=2;
      }
      if (PS4.Up()){Ashimawari_Command=1;
      }
      if (PS4.Left()){Ashimawari_Command=4;
      }
      if (PS4.UpRight()){Ashimawari_Command=5;
      }
      if (PS4.DownRight()){Ashimawari_Command=6;
      }
      if (PS4.UpLeft()){Ashimawari_Command=7;
      }
      if (PS4.DownLeft()){Ashimawari_Command=8;
      }
  Serial.printf("%d\n",Ashimawari_Command);//Debug
  delay(10);   
  if(Ashimawari_Command!=0){
  sendPacket(Ashimawari_Command);
  }
  //ここで、もう一つSendを使う
  delay(10);

  //ここで動作処理をする。
  //Encoder読み
// デバッグ用：エンコーダカウントを出力
  for (int i = 0; i < 2; i++)
  {
    Serial.print("Encoder ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(encoderCount[i]);
  }
//encoderCount[0]が右後ろ　encoderCount[1]が左後ろ

//移動関数.これはこっちはAshimawari_Commandなどでうごかして
    if(Ashimawari_Command==1){//これでHIGHにする
        //analogWrite(PIN_SYASYUTU, dutyCycle );
        Serial.print("UP");
      }else if(Ashimawari_Command==2){
        //digitalWrite(PIN_SYASYUTU,LOW);
        Serial.print("BACK");
      }
  
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
         for (int j = 0; j < 4; j++) {targetDistance[j]=0.0;
         }
        Serial.print("reachedTarget\n");
        handleMoterInput(targetDistance, Ashimawari_Command);
    }
  Ashimawari_Command=0;//初期化
  PS4_Circle=0;
  PS4_Triangle=0;
  PS4_R1=0;
  PS4_L1=0;

  delay(150);  // 0.15秒の遅延
  */
