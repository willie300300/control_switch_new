/*
   描述：控制7個開關
   
*/
  
  
int ledPin1 = 13;
int ledPin2 = 12;
int ledPin3 = 11;
int ledPin4 = 10;
int ledPin5 = 9;
int ledPin6 = 8;
int ledPin7 = 7;


void setup() {
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
    pinMode(ledPin5, OUTPUT);
    pinMode(ledPin6, OUTPUT);
    pinMode(ledPin7, OUTPUT);
}


void loop() {
    digitalWrite(ledPin1,HIGH);
    delay(1000);
    digitalWrite(ledPin1,LOW);
    delay(1000);
    
    digitalWrite(ledPin2,HIGH);
    delay(1000);
    digitalWrite(ledPin2,LOW);
    delay(1000);
            
    digitalWrite(ledPin3,HIGH);
    delay(1000);
    digitalWrite(ledPin3,LOW);
    delay(1000);

    digitalWrite(ledPin4,HIGH);
    delay(1000);
    digitalWrite(ledPin4,LOW);
    delay(1000);

    digitalWrite(ledPin5,HIGH);
    delay(1000);
    digitalWrite(ledPin5,LOW);
    delay(1000);

    digitalWrite(ledPin6,HIGH);
    delay(1000);
    digitalWrite(ledPin6,LOW);
    delay(1000);   

    digitalWrite(ledPin7,HIGH);
    delay(1000);
    digitalWrite(ledPin7,LOW);
    delay(1000);                             
}
