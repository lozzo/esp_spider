#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

////////////////////////////////////////
Servo myservo[8];
char servo_pin[8] = {0,2,10,4,13,12,14,16};

const char* ssid = "fucktencent";
const char* passwd = "qweasdzxc@";

WiFiServer server(80);
/////////////////////////////////////////


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
  MDNS.addService("http", "tcp", 80);
        Serial.println(WiFi.localIP());


//  //舵机初始化                                                
 for (int j = 0 ; j < 8; j++) {
   myservo[j].attach(servo_pin[j]);
   //servo(90,1);
   
   
  }


Serial.println("initializaed");
}


void servo(int, int) {
  int pos;
  int servo_speed;
  Servo myservo;
  for (pos = 0; pos <= 180; pos += servo_speed) {
    myservo.write(pos);
    delay(15);
  }
  for(pos = 180; pos>=0; pos-=servo_speed){                                
    myservo.write(pos);             
    delay(15);                      
  } 
}


//主函数
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (1) {
    while (!client.available()) {
      delay(1);
    }
    String req = client.readStringUntil('\r');
    Serial.println(req);
    
     //字符串解析
    int req_arry[16] ;
    while (req != "|") {
      int num = req.substring(0, req.indexOf(',')).toInt();
      req = req.substring(req.indexOf(',') + 1);
      Serial.println(num);
      int i = 0;
      req_arry[i] = num;
      i += 1;
    }
    int t = 0;
    int e = 0;
    servo[e](req_arry[t], req_arry[t + 1]);
    t += 2;
   e += 1;

  }

}
