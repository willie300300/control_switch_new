/*
   描述：控制7個開關
   
*/

  
int relay1 = 13;
int relay2 = 12;
int relay3 = 11;
int relay4 = 10;
int relay5 = 9;
int relay6 = 8;
int relay7 = 7;
int button1 = 6;
int button2 = 5;
int lastButtonState1 = LOW;
int lastButtonState2 = LOW;
long lastDebounceTime1 = 0;
long lastDebounceTime2 = 0;                    
long debounceDelay = 50;
int bs1;
int bs2;


void setup() {
    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    pinMode(relay4, OUTPUT);
    pinMode(relay5, OUTPUT);
    pinMode(relay6, OUTPUT);
    pinMode(relay7, OUTPUT);
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    
}


void loop() {
    int button1_State = digitalRead(button1);
    int button2_State = digitalRead(button2);
    
    // ======按鈕一開始======
    
    if (button1_State != lastButtonState1){
        lastDebounceTime1 = millis();
    }
    if ((millis() - lastDebounceTime1) > debounceDelay) {
        if (button1_State != bs1) {
            bs1 = button1_State;
            if (bs1 == HIGH) {
                control_relay1();  
                control_relay2();
                control_relay3();
                control_relay4();
                control_relay5();
                control_relay6();
                control_relay7();
            }
        }
    }
    lastButtonState1 = button1_State;

    // ======按鈕二開始======

    if (button2_State != lastButtonState2){
        lastDebounceTime2 = millis();
    }
    if ((millis() - lastDebounceTime2) > debounceDelay) {
        if (button2_State != bs2) {
            bs2 = button1_State;
            if (bs2 == HIGH) {
                control_relay1();  
                control_relay2();
                control_relay3();
                control_relay4();
                control_relay5();
                control_relay6();
                control_relay7();
            }
        }
    }
    lastButtonState2 = button2_State;
    
        
}


void control_relay1(){
    digitalWrite(relay1,HIGH);
    delay(1000);
    digitalWrite(relay1,LOW);
    delay(1000);
}


void control_relay2(){
    digitalWrite(relay2,HIGH);
    delay(1000);
    digitalWrite(relay2,LOW);
    delay(1000);
}


void control_relay3(){
    digitalWrite(relay3,HIGH);
    delay(1000);
    digitalWrite(relay3,LOW);
    delay(1000);
}


void control_relay4(){
    digitalWrite(relay4,HIGH);
    delay(1000);
    digitalWrite(relay4,LOW);
    delay(1000);
}


void control_relay5(){
    digitalWrite(relay5,HIGH);
    delay(1000);
    digitalWrite(relay5,LOW);
    delay(1000);
}


void control_relay6(){
    digitalWrite(relay6,HIGH);
    delay(1000);
    digitalWrite(relay6,LOW);
    delay(1000); 
}


void control_relay7(){
    digitalWrite(relay7,HIGH);
    delay(1000);
    digitalWrite(relay7,LOW);
    delay(1000); 
}
