/*
   描述：控制7個開關
   
*/

  
int relay1 = 4; //火警燈開關
int relay2 = 12; //火警鈴開關
int relay3 = 11; //倒數計時器開啟開關
int relay4 = 10; //倒數計時器賦歸開關
int relay5 = 9; //廣播器「全區」按鈕
int relay6 = 8; //廣播器「賦歸」按鈕
int relay7 = 7; //廣播器「廣播」按鈕
int button1 = 6; //火警派遣按鈕
int button2 = 5; //火警預派遣按鈕
int lastButtonState1 = LOW;
int lastButtonState2 = LOW;
long lastDebounceTime1 = 0;
long lastDebounceTime2 = 0;
long lastDebounceTime3 = 0;
long lastDebounceTime4 = 0;                    
long debounceDelay = 50;
int bs1 = LOW;
int bs2 = LOW;
int bs3 = LOW;
int bs4 = LOW;

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
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);
    digitalWrite(relay5, LOW);
    digitalWrite(relay6, LOW);
    digitalWrite(relay7, LOW);
    Serial.begin(9600);
}


void loop() {
    int button1_State = digitalRead(button1);
    int button2_State = digitalRead(button2);
    
    Serial.println(button1_State);

    // ======按鈕一啟動功能(火警派遣按鈕)======
    
    if (button1_State != lastButtonState1){
        lastDebounceTime1 = millis();
    }
    if ((millis() - lastDebounceTime1) > debounceDelay) {
        if (button1_State != bs1) {
            bs1 = button1_State;
            if (bs1 == HIGH) {
                Serial.println("開啟火警功能");
                fire_alarm();
            }
        }
    }
    lastButtonState1 = button1_State;

    // ======按鈕二啟動功能(火警預派遣按鈕)======

    if (button2_State != lastButtonState2){
        lastDebounceTime2 = millis();
    }
    if ((millis() - lastDebounceTime2) > debounceDelay) {
        if (button2_State != bs2) {
            bs2 = button2_State;
            if (bs2 == HIGH) {
                Serial.println("開啟預派遣功能");
                advance(); 

            }
        }
    }
    lastButtonState2 = button2_State;

    
    // ======按鈕一關閉功能(兩個開關需同時關閉)======
    
    if (button1_State != lastButtonState1){
        lastDebounceTime3 = millis();
    }
    if ((millis() - lastDebounceTime3) > debounceDelay) {
        if (button1_State != bs3) {
            bs3 = button1_State;
            if (bs3 == LOW  && bs4 == LOW) {
                Serial.println("關閉功能");
                digitalWrite(relay1, LOW);
                digitalWrite(relay2, LOW);
                digitalWrite(relay3, LOW);
                digitalWrite(relay4, LOW);
                digitalWrite(relay5, LOW);
                digitalWrite(relay6, LOW);
                digitalWrite(relay7, LOW);
            }
        }
    }
    lastButtonState1 = button1_State;

    // ======按鈕二關閉功能(兩個開關需同時關閉)======

    if (button2_State != lastButtonState2){
        lastDebounceTime4 = millis();
    }
    if ((millis() - lastDebounceTime4) > debounceDelay) {
        if (button2_State != bs4) {
            bs4 = button2_State;
            if (bs4 == LOW  && bs3 == LOW) {
                Serial.println("關閉功能");
                digitalWrite(relay1, LOW);
                digitalWrite(relay2, LOW);
                digitalWrite(relay3, LOW);
                digitalWrite(relay4, LOW);
                digitalWrite(relay5, LOW);
                digitalWrite(relay6, LOW);
                digitalWrite(relay7, LOW);
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
    digitalWrite(relay1,HIGH);
}


void control_relay2(){
    digitalWrite(relay2,HIGH);
    delay(1000);
    digitalWrite(relay2,LOW);
    delay(1000);
    digitalWrite(relay2,HIGH);
}


void control_relay3(){
    digitalWrite(relay3,HIGH);
    delay(1000);
    digitalWrite(relay3,LOW);
    delay(1000);
    digitalWrite(relay3,HIGH);
}


void control_relay4(){
    digitalWrite(relay4,HIGH);
    delay(1000);
    digitalWrite(relay4,LOW);
    delay(1000);
    digitalWrite(relay4,HIGH);
}


void control_relay5(){
    digitalWrite(relay5,HIGH);
    delay(1000);
    digitalWrite(relay5,LOW);
    delay(1000);
    digitalWrite(relay5,HIGH);
}


void control_relay6(){
    digitalWrite(relay6,HIGH);
    delay(1000);
    digitalWrite(relay6,LOW);
    delay(1000);
    digitalWrite(relay6,HIGH); 
}


void control_relay7(){
    digitalWrite(relay7,HIGH);
    delay(1000);
    digitalWrite(relay7,LOW);
    delay(1000);
    digitalWrite(relay7,HIGH); 
}


//火警派遣功能
void fire_alarm(){
    digitalWrite(relay1,HIGH); //開起火警燈
    digitalWrite(relay3,HIGH); //開啟倒數計時器
    //開啟廣播
    digitalWrite(relay5,HIGH); //按下「全區」
    delay(200);
    digitalWrite(relay7,HIGH); //按下「廣播」
    //按火警鈴
    digitalWrite(relay2,HIGH); //火警鈴開啟
    delay(1000);
    digitalWrite(relay2,LOW); 
    delay(500);
    digitalWrite(relay2,HIGH);
    delay(1000);
    digitalWrite(relay2,LOW);
    delay(500);
    digitalWrite(relay2,HIGH);
    delay(1000);
    digitalWrite(relay2,LOW);

}


//火警預派遣功能
void advance(){
    digitalWrite(relay1,HIGH); //開起火警燈
    digitalWrite(relay5,HIGH); //按下「全區」
    delay(200);
    digitalWrite(relay7,HIGH); //按下「廣播」    

}
