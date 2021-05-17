#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>

#define WIFI_SSID "JioFi2_F3342A"
#define WIFI_PASSWORD "h93bm255kd"
#define FIREBASE_HOST "sl-locks-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "eXb5lzfQGy2v6jxDqqWayIh3glluMqIrcPByr2eZ"

#include <Servo.h>
Servo myservo;

#define led_r 0
#define led_g 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  // connect to wifi.  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  Serial.print("connecting");  
  while (WiFi.status() != WL_CONNECTED) {  
    Serial.print(".");  
    delay(500);  
  }  
  Serial.println();  
  Serial.print("connected: ");  
  Serial.println(WiFi.localIP());  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
 
  myservo.attach(5); 
  pinMode(led_r ,OUTPUT); 
  pinMode(led_g ,OUTPUT);
  digitalWrite(led_r, LOW);
  digitalWrite(led_g, LOW);
}

int n = 0;  
void loop() {
  // set value  
  n=Firebase.getInt("LOCK_STATUS"); 
  Serial.println(n); 
  // handle error  
  if (n==0) {  
   digitalWrite(led_r,HIGH);
   digitalWrite(led_g,LOW);
   myservo.write(45);  
   delay(1000);
   Serial.println("LOCKED");  
   Serial.println(Firebase.error());   
  }  
  else if (n==1){  
   digitalWrite(led_r,LOW); 
   digitalWrite(led_g,HIGH);
   myservo.write(150);
   delay(1000);
   Serial.println("UNLOCKED");  
   Serial.println(Firebase.error()); 
 }  
  else{
   Serial.println("error");
   digitalWrite(led_r,LOW);
   digitalWrite(led_g,LOW); 
}
}
