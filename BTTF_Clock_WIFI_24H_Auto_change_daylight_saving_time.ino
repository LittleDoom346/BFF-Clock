#include <Keypad.h>
#include <Wire.h>
#include <Arduino.h>
#include <TM1637Display.h>
#include <RTClib.h>  // Include the RTClib library for RTC functionality

RTC_DS3231 rtc;  // Create an RTC_DS3231 object

#define CLK_Red 2
#define DIO_Red1 5
#define DIO_Red2 4
#define DIO_Red3 3

#define CLK_Green 23
#define DIO_Green1 8
#define DIO_Green2 7
#define DIO_Green3 6

#define CLK_Yellow 12
#define DIO_Yellow1 11
#define DIO_Yellow2 9
#define DIO_Yellow3 10

#define Red_AM 33
#define Red_PM 32

#define Green_AM 35
#define Green_PM 34

#define Yellow_AM 37
#define Yellow_PM 36

#define button_Red 52
#define button_Yellow 50
#define button_Green 48
#define button_Blue 46
#define button_White 44




const uint8_t ROWS = 4;                   // vier Zeilen
const uint8_t COLS = 3;                   // vier Spalten
byte rowPins[ROWS] = { 51, 41, 43, 47 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 49, 53, 45 };      //connect to the column pinouts of the keypad


// Pinlänge und Pincode festlegen
const byte PINLENGTH = 12;

// Zwischenspeicher für Eingaben
String keyBuffer = "012345678910";
String inputBuffer = "255";

// Symbole auf den Tasten
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


const int DISPLAY_RED_PINS[3][2] = {
  { CLK_Red, DIO_Red1 },
  { CLK_Red, DIO_Red2 },
  { CLK_Red, DIO_Red3 }
};

const int DISPLAY_GREEN_PINS[3][2] = {
  { CLK_Green, DIO_Green1 },
  { CLK_Green, DIO_Green2 },
  { CLK_Green, DIO_Green3 }
};

const int DISPLAY_YELLOW_PINS[3][2] = {
  { CLK_Yellow, DIO_Yellow1 },
  { CLK_Yellow, DIO_Yellow2 },
  { CLK_Yellow, DIO_Yellow3 }
};


TM1637Display red1(DISPLAY_RED_PINS[0][0], DISPLAY_RED_PINS[0][1]);
TM1637Display red2(DISPLAY_RED_PINS[0][0], DISPLAY_RED_PINS[1][1]);
TM1637Display red3(DISPLAY_RED_PINS[0][0], DISPLAY_RED_PINS[2][1]);

TM1637Display green1(DISPLAY_GREEN_PINS[0][0], DISPLAY_GREEN_PINS[0][1]);
TM1637Display green2(DISPLAY_GREEN_PINS[0][0], DISPLAY_GREEN_PINS[1][1]);
TM1637Display green3(DISPLAY_GREEN_PINS[0][0], DISPLAY_GREEN_PINS[2][1]);

TM1637Display yellow1(DISPLAY_YELLOW_PINS[0][0], DISPLAY_YELLOW_PINS[0][1]);
TM1637Display yellow2(DISPLAY_YELLOW_PINS[0][0], DISPLAY_YELLOW_PINS[1][1]);
TM1637Display yellow3(DISPLAY_YELLOW_PINS[0][0], DISPLAY_YELLOW_PINS[2][1]);




const uint8_t january[] = {
  SEG_B | SEG_C | SEG_D | SEG_E,                  // J
  SEG_E | SEG_F | SEG_A | SEG_G | SEG_B | SEG_C,  // A
};

const uint8_t february[] = {
  SEG_A | SEG_G | SEG_F | SEG_E,          // F
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,  // E
};

const uint8_t march[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // M
  SEG_A | SEG_B | SEG_C | SEG_G | SEG_D,          // A        // E
};

const uint8_t april[] = {
  SEG_E | SEG_F | SEG_A | SEG_G | SEG_B | SEG_C,  // A
  SEG_F | SEG_A | SEG_B | SEG_G | SEG_E,          // P
};

const uint8_t may[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // d
  SEG_F | SEG_G | SEG_A | SEG_C | SEG_D,          // o          // E
};

const uint8_t june[] = {
  SEG_B | SEG_C | SEG_D | SEG_E,  // d
  SEG_C | SEG_E | SEG_G,          // o          // E
};

const uint8_t july[] = {
  SEG_B | SEG_C | SEG_D | SEG_E,  // d
  SEG_F | SEG_E | SEG_D,          // o          // E
};

const uint8_t august[] = {
  SEG_E | SEG_F | SEG_A | SEG_G | SEG_B | SEG_C,  // d
  SEG_F | SEG_E | SEG_D | SEG_C | SEG_B,          // o          // E
};

const uint8_t september[] = {
  SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,  // d
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,  // o          // E
};

const uint8_t october[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // d
  SEG_G | SEG_E | SEG_D,                          // o          // E
};

const uint8_t november[] = {
  SEG_C | SEG_E | SEG_G,          // d
  SEG_G | SEG_E | SEG_D | SEG_C,  // o          // E
};

const uint8_t december[] = {
  SEG_G | SEG_E | SEG_D | SEG_C | SEG_B,  // d
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,  // o          // E
};

const uint8_t sett[] = {
  SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,  // d
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,
  SEG_F | SEG_E | SEG_D | SEG_G,
  SEG_F | SEG_E | SEG_D | SEG_G,  // o          // E
};

const uint8_t ings[] = {
  SEG_B | SEG_C,
  SEG_G | SEG_C | SEG_E,  // n
  SEG_A | SEG_C | SEG_F | SEG_E | SEG_D,
  SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,  // o          // E
};

const uint8_t brtn[] = {
  SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,
  SEG_E | SEG_G,  // n
  SEG_F | SEG_E | SEG_D | SEG_G,
  SEG_G | SEG_C | SEG_E,  // E
};

const uint8_t loud[] = {
  SEG_F | SEG_E | SEG_D,
  SEG_E | SEG_G | SEG_C | SEG_D,  // n
  SEG_E | SEG_C | SEG_D,
  SEG_E | SEG_G | SEG_C | SEG_D | SEG_B,  // E
};

const uint8_t beep[] = {
  SEG_F | SEG_E | SEG_D | SEG_C | SEG_G,
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,
  SEG_F | SEG_A | SEG_B | SEG_G | SEG_E,  // E
};

const uint8_t user[] = {
  SEG_F | SEG_B | SEG_E | SEG_D | SEG_C,
  SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,
  SEG_E | SEG_G,
};

const uint8_t real[] = {
  SEG_E | SEG_G,
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,
  SEG_E | SEG_F | SEG_A | SEG_G | SEG_B | SEG_C,
  SEG_F | SEG_E | SEG_D,
};


const uint8_t cust[] = {
  SEG_A | SEG_F | SEG_E | SEG_D,
  SEG_E | SEG_D | SEG_C,
  SEG_A | SEG_F | SEG_G | SEG_C | SEG_D,
  SEG_F | SEG_G | SEG_E | SEG_D,  // E
};

const uint8_t clck[] = {
  SEG_A | SEG_F | SEG_E | SEG_D,
  SEG_F | SEG_E | SEG_D,
  SEG_D | SEG_E | SEG_G,
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_C,  // E
};

const uint8_t on[] = {
  0x0,
  0x0,
  SEG_G | SEG_E | SEG_C | SEG_D,
  SEG_G | SEG_E | SEG_C,
};

const uint8_t off[] = {
  0x0,
  SEG_A | SEG_F | SEG_E | SEG_D | SEG_B | SEG_C,
  SEG_A | SEG_G | SEG_F | SEG_E,
  SEG_A | SEG_G | SEG_F | SEG_E,
};

const uint8_t tme[] = {
  SEG_F | SEG_G | SEG_E | SEG_D,
  SEG_G | SEG_E | SEG_C,
  SEG_G | SEG_C,
  SEG_A | SEG_G | SEG_F | SEG_E | SEG_D,
};


int k;
uint8_t maxbright[] = { 0xff, 0xff, 0xff, 0xff };
uint8_t data[] = { 0x00, 0x00, 0x00, 0x00 };


String mode = "clock";
String selection = "";

String time_red = "102619850121";
String time_green = "";
String time_yellow = "102619850120";

byte month = 0;
byte year = 0;
byte day = 0;
byte hours = 0;
byte minutes = 0;
unsigned long mills = 0;
bool redblink = false;
bool greenblink = false;
bool yellowblink = false;
bool redstate = true;
bool greenstate = true;
bool yellowstate = true;
unsigned long blinktimer = 0;
int timer_colon = millis() / 1000;
int timer_update_time = timer_colon;
bool showcolon = true;
byte modifier = 0b11100000;
int Display_backlight = 3;
int loudness = 20;
String str_loudness = "";
int intervall = 5;
String setting = "";
int settingspage = 0;
int beeping = 1;
String definedMode = "clck";
bool usedelay = true;
int prevmillis = 0;
unsigned long colontimer = millis();
String rtc_lasttime = "";

void setup() {
  Serial.begin(9600);
  Wire.begin();  // Initialize I2C communication
  rtc.begin();   // Initialize RTC
  //rtc.adjust(DateTime(__DATE__, __TIME__));

  pinMode(button_Red, INPUT_PULLUP);
  pinMode(button_Yellow, INPUT_PULLUP);
  pinMode(button_Green, INPUT_PULLUP);
  pinMode(button_Blue, INPUT_PULLUP);
  pinMode(button_White, INPUT_PULLUP);
  update_brightness();


#define LED_Red 39
#define LED_Yellow 37
#define LED_Green 35
#define LED_Blue 40
#define LED_White 42

  pinMode(LED_Red, OUTPUT);
  pinMode(LED_Yellow, OUTPUT);
  pinMode(LED_Green, OUTPUT);
  pinMode(LED_Blue, OUTPUT);
  pinMode(LED_White, OUTPUT);

  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Yellow, HIGH);
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Blue, LOW);
  digitalWrite(LED_White, LOW);


  pinMode(Red_AM, OUTPUT);
  pinMode(Red_PM, OUTPUT);
  pinMode(Green_AM, OUTPUT);
  pinMode(Green_PM, OUTPUT);
  pinMode(Yellow_AM, OUTPUT);
  pinMode(Yellow_PM, OUTPUT);



  digitalWrite(Red_AM, HIGH);
  digitalWrite(Red_PM, HIGH);
  digitalWrite(Green_AM, HIGH);
  digitalWrite(Green_PM, HIGH);
  digitalWrite(Yellow_AM, HIGH);
  digitalWrite(Yellow_PM, HIGH);


  /*
  red1.showNumberDecEx(1105, 0b00100000, true, 4, 0);
  green1.showNumberDecEx(8888, 0b00100000, true, 4, 0);
  yellow1.showNumberDecEx(1211, 0b00100000, true, 4, 0);


  red2.showNumberDecEx(0324, 0b01000000, true, 4, 0);
  green2.showNumberDecEx(7777, 0b01000000, true, 4, 0);
 // yellow2.showNumberDecEx(1985, 0b01000000, true, 4, 0);
  yellow2.showNumberDec(1985, true, 4, 0);    

  red3.showNumberDecEx(8888, modifier, true, 4, 0);
  green3.showNumberDecEx(8888, modifier, true, 4, 0);
  yellow3.showNumberDecEx(2121, modifier, true, 4, 0);
*/
  red1.clear();
  red2.clear();
  red3.clear();
  green1.clear();
  green2.clear();
  green3.clear();
  yellow1.clear();
  yellow2.clear();
  yellow3.clear();
  display_row_set_time(1, time_red);
  display_row_set_time(2, rtc_get_time());
  rtc_lasttime = rtc_get_time();
  time_green = rtc_lasttime;
  display_row_set_time(3, time_yellow);
}


void loop() {
  if (mode == "clock") {
    if (definedMode == "clck"){
      if (not time_green.equals(rtc_get_time())) {
        time_green = rtc_get_time();
        display_row_set_time(2, rtc_get_time());
      }
    }
    if (colontimer + 500 <= millis()) {
      colontimer = millis();
      if (modifier == 0b0000000) {
        modifier = 0b11100000;
      } else {
        modifier = 0b0000000;
      }
      display_hour_min_set_time(1, time_red.substring(8, 12));
      display_hour_min_set_time(2, time_green.substring(8, 12));
      display_hour_min_set_time(3, time_yellow.substring(8, 12));
    }
  }


  checkblinking();
  checkKeypad();
  checkPressedButtons();
}

void checkblinking() {
  if (redblink) {
    if (blinktimer + 500 <= millis()) {
      blinktimer = millis();
      if (redstate == true) {
        red1.setBrightness(0);
        red2.setBrightness(0);
        red3.setBrightness(0);
        digitalWrite(LED_Red, LOW);
        redstate = false;
      } else {
        red1.setBrightness(Display_backlight-1);
        red2.setBrightness(Display_backlight-1);
        red3.setBrightness(Display_backlight-1);
        digitalWrite(LED_Red, HIGH);
        redstate = true;
      }
    }
    if (mode == "settings") {
      red1.setSegments(sett);
      red2.setSegments(ings);
    } else {
      display_row_set_time(1, time_red);
    }
  } else {
    digitalWrite(LED_Red, HIGH);
    redstate = true;
  }
  if (greenblink) {
    if (blinktimer + 500 <= millis()) {
      blinktimer = millis();
      if (greenstate == true) {
        green1.setBrightness(0);
        green2.setBrightness(0);
        green3.setBrightness(0);
        digitalWrite(LED_Green, LOW);
        greenstate = false;
      } else {
        green1.setBrightness(Display_backlight);
        green2.setBrightness(Display_backlight);
        green3.setBrightness(Display_backlight);
        digitalWrite(LED_Green, HIGH);
        greenstate = true;
      }
    }
    if (mode == "settings") {
      show_settings(settingspage);
    }
  } else {
    digitalWrite(LED_Green, HIGH);
    greenstate = true;
  }

  if (yellowblink) {
    if (blinktimer + 500 <= millis()) {
      blinktimer = millis();
      if (yellowstate == true) {
        yellow1.setBrightness(0);
        yellow2.setBrightness(0);
        yellow3.setBrightness(0);
        digitalWrite(LED_Yellow, LOW);
        yellowstate = false;
      } else {
        yellow1.setBrightness(Display_backlight);
        yellow2.setBrightness(Display_backlight);
        yellow3.setBrightness(Display_backlight);
        digitalWrite(LED_Yellow, HIGH);
        yellowstate = true;
      }
    }
    if (mode == "settings") {
      show_settings(settingspage);
    }
  } else {
    digitalWrite(LED_Yellow, HIGH);
    yellowstate = true;
  }
}


void checkKeypad() {
  char customKey = keypad.getKey();
  if (customKey) {
    Serial.println(customKey);
  }
  if (customKey == '*') {
    Serial.println(mode);
    Serial.println(settingspage);
    Serial.println(setting);
    if (mode == "settings") {
      update_brightness();
      if (setting == "brightness") {
        setting = "loudness";
        settingspage = 0;
        yellowblink = true;
        greenblink = false;
        show_settings(settingspage);
      } else if (setting == "loudness") {
        setting = "beep";
        settingspage = 1;
        yellowblink = false;
        greenblink = true;
        show_settings(settingspage);

      } else if (setting == "beep") {
        setting = "mode";
        settingspage = 1;
        yellowblink = true;
        greenblink = false;
        show_settings(settingspage);

      } else if (setting == "mode") {
        setting = "brightness";
        settingspage = 0;
        yellowblink = false;
        greenblink = true;
        show_settings(settingspage);
      }
    }
    if (mode != "settings") {
      mode = "settings";
      setting = "brightness";
      settingspage = 0;
      greenblink = true;
      red1.clear();
      green1.clear();
      yellow1.clear();
      red2.clear();
      green2.clear();
      yellow2.clear();
      red3.clear();
      green3.clear();
      yellow3.clear();
      show_settings(settingspage);
    }

  } else if (customKey == '#') {
    if (mode == "input") {
      mode = "clock";
      time_red = keyBuffer;
      display_row_set_time(1, time_red);
    } else if (mode == "clock") {
      mode = "input";
      keyBuffer = time_red;
      digitalWrite(LED_Red, LOW);
      delay(50);
      digitalWrite(LED_Red, HIGH);
      display_row_set_time(1, time_red);
    } else if (mode == "settings") {
      mode = "clock";
      greenblink = false;
      yellowblink = false;
      update_brightness();
      display_row_set_time(1, time_red);
      display_row_set_time(2, rtc_get_time());
      rtc_lasttime = rtc_get_time();
      time_green = rtc_lasttime;
      display_row_set_time(3, time_yellow);
    }
  }

  if (mode == "input") {
    if (customKey && (int(customKey) >= 48) && (int(customKey) <= 57)) {
      addToBuffer(customKey);
      digitalWrite(LED_Red, LOW);
      delay(50);
      digitalWrite(LED_Red, HIGH);
    }
  } else if (mode == "settings") {
    if (settingspage == 0) {
      if (setting == "brightness") {
        if (customKey && (int(customKey) >= 49) && (int(customKey) <= 55)) {
          Display_backlight = String(customKey).toInt();
          show_settings(settingspage);
        }
      } else if (setting == "loudness") {
        if (customKey && (int(customKey) >= 48) && (int(customKey) <= 57)) {
          loudness = map(String(customKey).toInt(), 0, 9, 0, 30);
          show_settings(settingspage);
        }
      }
    } else if (settingspage == 1) {
      if (setting == "beep") {
        if (customKey && (int(customKey) >= 48) && (int(customKey) <= 57)) {
          if (0 <= String(customKey).toInt() <= 1) {
            beeping = String(customKey).toInt();
            show_settings(settingspage);
          }
        }
      } else if (setting == "mode") {
        if (customKey && (int(customKey) >= 48) && (int(customKey) <= 57)) {
          if (String(customKey).toInt() == 1) {
            definedMode = "cust";
            show_settings(settingspage);
          } else if (String(customKey).toInt() == 0) {
            definedMode = "clck";
            show_settings(settingspage);
          }
        }
      }
    }
  }
}

void addToBuffer(char inkey) {
  for (int i = 1; i < PINLENGTH; i++) {
    keyBuffer[i - 1] = keyBuffer[i];
  }
  keyBuffer[PINLENGTH - 1] = inkey;
}


String rtc_get_time() {
  DateTime now = rtc.now();  // Get current date and time from RTC
  String formattedTime = String(now.month() < 10 ? "0" : "") + String(now.month(), DEC) + String(now.day() < 10 ? "0" : "") + String(now.day(), DEC) + String(now.year(), DEC) + String(now.hour() < 10 ? "0" : "") + String(now.hour(), DEC) + String(now.minute() < 10 ? "0" : "") + String(now.minute(), DEC);
  return formattedTime;
}


boolean is_timer_over() {
  if (millis() / 10 + intervall / 10 >= prevmillis) {
    prevmillis = millis() / 10;
    return true;
  }
  return false;
}


void display_hour_min_set_time(int colorcode, String string_to_use) {
  String localhour = string_to_use.substring(0, 2);
  String localminute = string_to_use.substring(2, 4);
  switch (colorcode) {
    case 1:
      red3.showNumberDecEx(string_to_use.toInt(), modifier, true, 4, 0);
      break;
    case 2:
      green3.showNumberDecEx(string_to_use.toInt(), modifier, true, 4, 0);
      break;
    case 3:
      yellow3.showNumberDecEx(string_to_use.toInt(), modifier, true, 4, 0);
      break;
  }
}

void display_row_set_time(int colorcode, String string_to_use) {
  Serial.println(string_to_use);
  String localmonth = string_to_use.substring(0, 2);
  String localday = string_to_use.substring(2, 4);
  String localyear = string_to_use.substring(4, 8);
  String localhour = string_to_use.substring(8, 10);
  String localminute = string_to_use.substring(10, 12);

  switch (colorcode) {
    case 1:
      display_hour_min_set_time(colorcode, localhour + localminute);
      if (usedelay) {
        delay(50);
      }
      red2.showNumberDec(localyear.toInt(), true, 4, 0);
      if (usedelay) {
        delay(100);
      }

      if (localmonth == "01") {
        red1.setSegments(january);
      } else if (localmonth == "02") {
        red1.setSegments(february);
      } else if (localmonth == "03") {
        red1.setSegments(march);
      } else if (localmonth == "04") {
        red1.setSegments(april);
      } else if (localmonth == "05") {
        red1.setSegments(may);
      } else if (localmonth == "06") {
        red1.setSegments(june);
      } else if (localmonth == "07") {
        red1.setSegments(july);
      } else if (localmonth == "08") {
        red1.setSegments(august);
      } else if (localmonth == "09") {
        red1.setSegments(september);
      } else if (localmonth == "10") {
        red1.setSegments(october);
      } else if (localmonth == "11") {
        red1.setSegments(november);
      } else if (localmonth == "12") {
        red1.setSegments(december);
      } else {
        red1.showNumberDecEx(00, 0b01000000, true, 2, 0);
      }
      red1.showNumberDecEx(localday.toInt(), 0b00000000, true, 2, 2);
      break;
    case 2:
      display_hour_min_set_time(colorcode, localhour + localminute);
      if (usedelay) {
        delay(50);
      }
      green2.showNumberDec(localyear.toInt(), true, 4, 0);
      if (usedelay) {
        delay(100);
      }

      if (localmonth == "01") {
        green1.setSegments(january);
      } else if (localmonth == "02") {
        green1.setSegments(february);
      } else if (localmonth == "03") {
        green1.setSegments(march);
      } else if (localmonth == "04") {
        green1.setSegments(april);
      } else if (localmonth == "05") {
        green1.setSegments(may);
      } else if (localmonth == "06") {
        green1.setSegments(june);
      } else if (localmonth == "07") {
        green1.setSegments(july);
      } else if (localmonth == "08") {
        green1.setSegments(august);
      } else if (localmonth == "09") {
        green1.setSegments(september);
      } else if (localmonth == "10") {
        green1.setSegments(october);
      } else if (localmonth == "11") {
        green1.setSegments(november);
      } else if (localmonth == "12") {
        green1.setSegments(december);
      } else {
        green1.showNumberDecEx(00, 0b01000000, true, 2, 0);
      }
      green1.showNumberDecEx(localday.toInt(), 0b00000000, true, 2, 2);
      break;
    case 3:
      display_hour_min_set_time(colorcode, localhour + localminute);
      if (usedelay) {
        delay(50);
      }
      yellow2.showNumberDec(localyear.toInt(), true, 4, 0);
      if (usedelay) {
        delay(100);
      }

      if (localmonth == "01") {
        yellow1.setSegments(january);
      } else if (localmonth == "02") {
        yellow1.setSegments(february);
      } else if (localmonth == "03") {
        yellow1.setSegments(march);
      } else if (localmonth == "04") {
        yellow1.setSegments(april);
      } else if (localmonth == "05") {
        yellow1.setSegments(may);
      } else if (localmonth == "06") {
        yellow1.setSegments(june);
      } else if (localmonth == "07") {
        yellow1.setSegments(july);
      } else if (localmonth == "08") {
        yellow1.setSegments(august);
      } else if (localmonth == "09") {
        yellow1.setSegments(september);
      } else if (localmonth == "10") {
        yellow1.setSegments(october);
      } else if (localmonth == "11") {
        yellow1.setSegments(november);
      } else if (localmonth == "12") {
        yellow1.setSegments(december);
      } else {
        yellow1.showNumberDecEx(00, 0b01000000, true, 2, 0);
      }
      yellow1.showNumberDecEx(localday.toInt(), 0b00000000, true, 2, 2);
      break;
  }
}


void update_brightness() {
  if (not redblink) {
    red1.setBrightness(Display_backlight-1);
    red2.setBrightness(Display_backlight-1);
    red3.setBrightness(Display_backlight-1);
  }
  if (not greenblink) {
    green1.setBrightness(Display_backlight);
    green2.setBrightness(Display_backlight);
    green3.setBrightness(Display_backlight);
  }
  if (not yellowblink) {
    yellow1.setBrightness(Display_backlight);
    yellow2.setBrightness(Display_backlight);
    yellow3.setBrightness(Display_backlight);
  }
}

void show_settings(int page) {
  update_brightness();
  if (page == 0) {
    red1.setSegments(sett);
    red2.setSegments(ings);
    green1.setSegments(brtn);
    yellow1.setSegments(loud);
    green2.showNumberDec(Display_backlight);
    yellow2.showNumberDec(loudness);
  } else if (page == 1) {
    green1.setSegments(beep);
    yellow1.setSegments(clck);
    if (beeping == 0) {
      green2.setSegments(off);
    } else if (beeping == 1) {
      green2.setSegments(on);
    }
    if (definedMode == "clck") {
      yellow2.setSegments(real);
    } else if (definedMode == "cust") {
      yellow2.setSegments(user);
    }
  }
}

bool buttonPressed(String color) {
  if (color == "red" && (digitalRead(button_Red) == HIGH)) {
    Serial.println("Red pressed");
    return true;
  } else if (color == "yellow" && (digitalRead(button_Yellow) == HIGH)) {
    Serial.println("yellow pressed");
    return true;
  } else if (color == "green" && (digitalRead(button_Green) == HIGH)) {
    Serial.println("green pressed");
    return true;

  } else if (color == "blue" && (digitalRead(button_Blue) == HIGH)) {
    Serial.println("blue pressed");
    return true;

  } else if (color == "white" && (digitalRead(button_White) == HIGH)) {
    Serial.println("white pressed");
    return true;
  } else {
    return false;
  }
}


void checkPressedButtons() {
  if (buttonPressed("white")) {
    if (mode == "input" && buttonPressed("white")) {
      Serial.println("Wechsle zu Uhr");
      red1.clear();
      red2.clear();
      red3.clear();
      mode = "clock";
      time_red = keyBuffer;
      digitalWrite(LED_Blue, HIGH);
      digitalWrite(LED_White, HIGH);
      delay(500);
      
      display_row_set_time(1, time_red);
      digitalWrite(LED_Blue, LOW);
      digitalWrite(LED_White, LOW);
    } else if (mode == "settings" && buttonPressed("white")) {
      Serial.println("Wechsle zu Uhr");
      mode = "clock";
      greenblink = false;
      yellowblink = false;
      update_brightness();
       digitalWrite(LED_Blue, HIGH);
      digitalWrite(LED_White, HIGH);


      display_row_set_time(1, time_red);
      display_row_set_time(2, rtc_get_time());
      rtc_lasttime = rtc_get_time();
      time_green = rtc_lasttime;
      display_row_set_time(3, time_yellow);
            digitalWrite(LED_Blue, LOW);
             digitalWrite(LED_White, LOW);
    }
  }

  if (buttonPressed("blue")) {
   if (mode == "clock" && buttonPressed("blue")) {
     timetravel();
   }
  }
}

void timetravel(){
  definedMode = "cust";

  //Serial.println("Time Yellow: " + time_yellow);
  //Serial.println("Time Green: " + time_green);

  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Yellow, HIGH);
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Blue, HIGH);
  digitalWrite(LED_White, HIGH);

  delay(500);

  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Yellow, LOW);
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);
  digitalWrite(LED_White, LOW);

  for (int x = 30; x <= 50; x+=1){
    digitalWrite(LED_Red, HIGH);
    delay(220-x*4);
    digitalWrite(LED_Red, LOW);
    digitalWrite(LED_Yellow, HIGH);
     delay(220-x*4);
    digitalWrite(LED_Yellow, LOW);
    digitalWrite(LED_Green, HIGH);
    delay(220-x*4);
    digitalWrite(LED_Green, LOW);
    digitalWrite(LED_Blue, HIGH);
    delay(220-x*4);
    digitalWrite(LED_Blue, LOW);    
  digitalWrite(LED_White, HIGH);
    delay(220-x*4);
    digitalWrite(LED_White, LOW); 
  }
  delay(100);
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Yellow, HIGH);
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Blue, HIGH);
  digitalWrite(LED_White, HIGH);
  delay(400);

  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Yellow, LOW);
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);
  digitalWrite(LED_White, LOW);
    red1.clear();
  green1.clear();  
    yellow1.clear();

  red2.clear();
    green2.clear();
   yellow2.clear();

 red3.clear();
  green3.clear();
  yellow3.clear();
  delay(200);
  digitalWrite(LED_Red, HIGH);
  digitalWrite(LED_Yellow, HIGH);
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Blue, HIGH);
  digitalWrite(LED_White, HIGH);

  delay(400);
      time_yellow = time_green;
  time_green = time_red;
  digitalWrite(LED_Red, LOW);
  digitalWrite(LED_Yellow, LOW);
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Blue, LOW);
  digitalWrite(LED_White, LOW);
  display_row_set_time(1, time_red);
  display_row_set_time(2, time_green);
  display_row_set_time(3, time_yellow);
}
