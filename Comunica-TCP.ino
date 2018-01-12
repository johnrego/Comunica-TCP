#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3);
char r;

void setup(){
  pinMode(13, OUTPUT);
  delay(1000);
  Serial.begin(9600);
  esp.begin(19200);
  Serial.println("Sistema Iniciado.");
  trata(1);
  trata(2);
  esp.println("AT+CIPMUX=1");
  descarta();
  esp.println("AT+CIPSERVER=1,80");
  descarta();
  Serial.println("Sevidor Online.");
}

void loop(){
  if(esp.available()){
    boolean a = false;
    String msg = "";
    r = esp.read();
    if(r=='+'){
      while((r!=10&&(r!=13))){ //Sai quando rebebe LN ou CR
        delay(2);
        r = esp.read();
        if(a&&(r!=13)){
          msg += r;
        }
        if(r==':'){
          a = !a;
        }
      }
      a = !a;
      if(!msg.equals(13)){
        Serial.print(msg);
        Serial.println();
        comando(msg);
      }
      msg = "";
      descarta();
    }
  }
  if(Serial.available()){
    r = Serial.read();
    esp.println("AT+CIPSERVER=0");
    descarta();
    Serial.println("Sevidor Offline.");
  }
}

