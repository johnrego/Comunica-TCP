/*
void debug(byte ec) {
  int limite=7000;
  unsigned long chegada=millis();
  boolean continuar=true; 
  String S="";
  unsigned long ultimochar=0;
  while (continuar) { 
    if (esp.available()) {
      char c = esp.read();
      ultimochar=millis();
      S=S+c;
      if (ec > 0) {
        Serial.print(c);
      }
      if (c==10) {  // LF, fim da linha recebida
        byte p=S.indexOf(13);
        String S1=S.substring(0,p);
        if (S1=="OK"){
         continuar=false;
        }
        if (S1=="ready"){
         continuar=false;
        }
        if (S1=="ERROR"){
         continuar=false;
        }
        S="";
      }  
    }  
    if (millis()-chegada > limite) continuar=false;
  }
}
*/

void comando(String cod){
  if(cod.equals("liga led")){
    digitalWrite(13, HIGH);
  }
  else if(cod.equals("envia")){
    esp.println("AT+CIPSEND=0,10");
    descarta();
    esp.print("envio test");
    descarta();
  }
  else{
    digitalWrite(13, LOW);
  }
}

void descarta(){
  delay(2);
  char c;
  while(esp.available()){
    c = esp.read();
    delay(2);
  }
}

void trata(byte controle){
  boolean achou = false;
  byte cont = 0;
  char c;
  delay(2);
  switch(controle) {
    case 1:
      esp.println("AT+CIFSR");
      delay(2);
      Serial.print("Ip: ");
      while(esp.available()){
        c = esp.read();
        if(c==34){ //Caractere "
          achou = !achou;
          cont++;
        }
        if(achou&&(c!=34)&&(cont<2)){
          Serial.print(c);
        }
        delay(2);
      }
      Serial.println();
    break;
    case 2:
      esp.println("AT+CWLAP=\"brisa-58489\",\"70:b9:21:e7:f8:18\",11");
      delay(40);
      Serial.print("Sinal: ");
      while(esp.available()){
        c = esp.read();
        if((c=='(')||(cont>0)){
          cont++;
        }
        if((cont>17)&&(cont<21)){      
          Serial.print(c);
        }
        delay(2);
      }
      Serial.println(" dBm.");
    break;
  }
}



