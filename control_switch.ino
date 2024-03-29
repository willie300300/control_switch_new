/*
   描述：控制7個開關  
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  
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
int lastButtonState3 = LOW;
int lastButtonState4 = LOW;
long lastDebounceTime1 = 0;
long lastDebounceTime2 = 0;
long lastDebounceTime3 = 0;
long lastDebounceTime4 = 0;                    
long debounceDelay = 50; //消雜訊用
int bs1 = LOW;
int bs2 = LOW;
int bs3 = LOW;
int bs4 = LOW;
//紅外線遙控器設定
#include <IRremote.h> //调用 IRremote.h 库
int RECV_PIN = 3; //定义 RECV_PIN 变量为 3
IRrecv irrecv(RECV_PIN); //设置 RECV_PIN （也就是 3 引脚）为红外接收端
decode_results results; //定义 results 变量为红外结果存放位置


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
    Serial.begin(9600); //串口波特率设为 9600
    //紅外線遙控器設定
    irrecv.enableIRIn(); // 启动红外解码
    //initialize the LCD
    lcd.begin();
    //Turn on the blacklight and print a message.
    lcd.backlight();
    //lcd.print("Hello, world!");
    //lcd.clear();
    //lcd.print("Cursor blink");
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print("System Ready");
    //delay(1000);
    //lcd.setCursor(0, 1); // 設定游標位置在第二行行首
    //lcd.print("Hello, Maker!");
}


void loop() {

    int button1_State = digitalRead(button1);
    int button2_State = digitalRead(button2);
   

    // ======按鈕一啟動功能(火警派遣按鈕)======   
    if (button1_State != lastButtonState1){
        lastDebounceTime1 = millis();
    }
    if ((millis() - lastDebounceTime1) > debounceDelay) {
        if (button1_State != bs1) {
            bs1 = button1_State;
            if (bs1 == HIGH) {
                lcd_function(1);               
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
                lcd_function(2);                            
                Serial.println("開啟預派遣功能");
                advance();
            }
        }
    }
    lastButtonState2 = button2_State;

    
    // ======按鈕一關閉功能(兩個開關需同時關閉)======   
    if (button1_State != lastButtonState3){
        lastDebounceTime3 = millis();
    }
    if ((millis() - lastDebounceTime3) > debounceDelay) {
        if (button1_State != bs3) {
            bs3 = button1_State;
            if (bs3 == LOW  && bs4 == LOW) {
                lcd_function(3);                 
                Serial.println("關閉功能");
                close_function();
            }
        }
    }
    lastButtonState3 = button1_State;


    // ======按鈕二關閉功能(兩個開關需同時關閉)======
    if (button2_State != lastButtonState4){
        lastDebounceTime4 = millis();
    }
    if ((millis() - lastDebounceTime4) > debounceDelay) {
        if (button2_State != bs4) {
            bs4 = button2_State;
            if (bs4 == LOW  && bs3 == LOW) {
                lcd_function(3);
                Serial.println("關閉功能");
                close_function();
            }
        }
    }
    lastButtonState4 = button2_State;                


    //======遙控器功能======
    //是否接收到解码数据,把接收到的数据存储在变量results中
    if (irrecv.decode(&results)) {  
        //接收到的数据以16进制的方式在串口输出   
        Serial.println(results.value, HEX);
        //一旦接收到电源键的代码, 執行程式碼
        //遙控器「1」=0xFF6897，「0x」是16進位的意思，沒加編譯不會過
        if(results.value == 0xFF6897){
            lcd_function(1); 
            Serial.println("遙控器開啟火警功能");
            fire_alarm();
        }
        //遙控器「2」=0xFF9867
        if(results.value == 0xFF9867){
            lcd_function(2); 
            Serial.println("遙控器開啟預派遣功能");
            advance();
        }
        //遙控器「3」=0xFFB04F
        if(results.value == 0xFFB04F){
            lcd_function(3);
            Serial.println("關閉功能");
            close_function();
        }                           
        irrecv.resume();  // 继续等待接收下一组信号
    }
}


//測試relay時使用
void control_relay1(){
    digitalWrite(relay1, HIGH);
    delay(1000);
    digitalWrite(relay1, LOW);
    delay(1000);
    digitalWrite(relay1, HIGH);
}


//測試relay時使用
void control_relay2(){
    digitalWrite(relay2, HIGH);
    delay(1000);
    digitalWrite(relay2, LOW);
    delay(1000);
    digitalWrite(relay2, HIGH);
}


//測試relay時使用
void control_relay3(){
    digitalWrite(relay3, HIGH);
    delay(1000);
    digitalWrite(relay3, LOW);
    delay(1000);
    digitalWrite(relay3, HIGH);
}


//測試relay時使用
void control_relay4(){
    digitalWrite(relay4, HIGH);
    delay(1000);
    digitalWrite(relay4, LOW);
    delay(1000);
    digitalWrite(relay4, HIGH);
}


//測試relay時使用
void control_relay5(){
    digitalWrite(relay5, HIGH);
    delay(1000);
    digitalWrite(relay5, LOW);
    delay(1000);
    digitalWrite(relay5, HIGH);
}


//測試relay時使用
void control_relay6(){
    digitalWrite(relay6, HIGH);
    delay(1000);
    digitalWrite(relay6, LOW);
    delay(1000);
    digitalWrite(relay6, HIGH); 
}


//測試relay時使用
void control_relay7(){
    digitalWrite(relay7, HIGH);
    delay(1000);
    digitalWrite(relay7, LOW);
    delay(1000);
    digitalWrite(relay7, HIGH); 
}


//火警派遣功能
void fire_alarm(){
    digitalWrite(relay1, HIGH); //開起火警燈
    digitalWrite(relay3, HIGH); //開啟倒數計時器
    //開啟廣播
    digitalWrite(relay5, HIGH); //按下「全區」
    delay(200);
    digitalWrite(relay5, LOW); //關閉「全區」
    delay(200);
    digitalWrite(relay7, HIGH); //按下「廣播」
    //按火警鈴
    digitalWrite(relay2, HIGH); //火警鈴開啟
    delay(800);
    digitalWrite(relay2, LOW); 
    delay(400);
    digitalWrite(relay2, HIGH);
    delay(800);
    digitalWrite(relay2, LOW);
    delay(400);
    digitalWrite(relay2, HIGH);
    delay(800);
    digitalWrite(relay2, LOW);
}


//火警預派遣功能
void advance(){
    digitalWrite(relay1, HIGH); //開起火警燈
    digitalWrite(relay5, HIGH); //按下「全區」
    delay(200);
    digitalWrite(relay5, LOW); //關閉「全區」
    delay(200);
    digitalWrite(relay7, HIGH); //按下「廣播」    
}


//關閉功能
void close_function(){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, HIGH);
    delay(500);
    digitalWrite(relay4, LOW);
    digitalWrite(relay5, LOW);
    digitalWrite(relay6, LOW);
    digitalWrite(relay7, LOW);
}


//LCD顯示功能
void lcd_function(int(X)){
    lcd.clear();
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print("System Ready");
    if (X == 1){
        lcd.setCursor(0, 1);
        lcd.print("fire_alarm");
    }
    if (X == 2){
        lcd.setCursor(0, 1);
        lcd.print("fire_advance");
    }
    if (X == 3){
        lcd.setCursor(0, 1);
        lcd.print("close_function");
    }
}
