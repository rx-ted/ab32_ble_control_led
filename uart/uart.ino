String comdata="";
#define LED D0
void setup() {
  // put your setup code here, to run once:
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    while(Serial.read() >= 0){}
    Serial.println("Begin");
}

void loop() {
  // put your main code here, to run repeatedly:
  ReceiveWifiMessage();
  if(comdata.length()>0){
    Serial.println(comdata);
    if(comdata == "1"){
        Serial.println("Light");
        digitalWrite(LED, HIGH);   // 将LED点亮（HIGH代表高电压）
    }else{
      Serial.println("Dark");
        digitalWrite(LED, LOW);    // 将LED熄灭（LOW代表低压）
    }
  }
}

/**
* 读取串口缓冲区里面的数据
*/
void ReceiveWifiMessage(){
    comdata="";
    while (Serial.available() > 0 )  
    {
        comdata+=char(Serial.read());
        delay(2);
    }
}
