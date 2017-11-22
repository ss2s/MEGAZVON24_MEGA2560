////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.
          https://github.com/ss2s/MEGAZVON24_MEGA2560

          created by : ss2s
          author of idea : Aleksandr K
        \******************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                            // ВАЖНАЯ ИНФОРМАЦИЯ //

// ВСЕ НАСТРОЙКИ ВЫНЕСЕНЫ В ОТДЕЛЬНЫЙ ФАЙЛ "MEGAZVON24_CONFIG.h"
// НАСТРОЙКА ДЛИТЕЛЬНОСТИ КАЖДОЙ НОТЫ В ФАЙЛЕ "MEGAZVON24_CONFIG.h"
// НАСТРОЙКИ МЕЛОДИЙ В ФАЙЛЕ "melody24.h"

// НАСТРОЙКИ ТЕРМОРЕГУЛЯТОРА В ОСНОВНОЙ ПРОГРАММЕ

// все нужные файлы находятся в папке с прошивкой

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Arduino.h"            // Arduino lib
#include "config24.h"           // файл конфигурации
#include "res24.h"              // файл ресурсов
#include <LiquidCrystal.h>      // библиотека дисплея с кнопками
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ЧАСЫ DS3231:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <Wire.h>         // библиотека I2C
//#include "DS3231.h"       // библиотека часов
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// инициализация дисплея с кнопками настройки в файле конфигурации
LiquidCrystal lcd(DEF_LCD_INIT_PIN);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "nota24.h"             // ноты
#include "melody24.h"           // файл с мелодиями
#include "raspisanie24.h"       // расписание

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int minutes;              // переменная для хранения минут
int hours;                // переменная для хранения часов
String temperatureDS3231; // переменная для хранения температуры
boolean isAlarm = false;  // Логическая переменная для обработки сигнала о срабатывании будильника 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// пользовательские символы:
byte customCharBell0[8] = {  // колокольчик для дисплея
	0b00000,
	0b00100,
	0b01110,
	0b01110,
	0b11111,
	0b11111,
	0b00100,
	0b00000
};

byte customCharNota1[8] = {  // нота для дисплея
	0b01110,
	0b01111,
	0b01001,
	0b01001,
	0b11001,
	0b11011,
	0b00011,
	0b00000
};

byte customCharLeftArrow2[8] = {  // стрелка влево для дисплея
	0b00000,
	0b00000,
	0b00100,
	0b01000,
	0b11111,
	0b01000,
	0b00100,
	0b00000
};

byte customCharRightArrow3[8] = {  // стрелка вправо для дисплея
	0b00000,
	0b00000,
	0b00100,
	0b00010,
	0b11111,
	0b00010,
	0b00100,
	0b00000
};

byte customCharMenuArrow4[8] = {
	0b00100,
	0b01110,
	0b11111,
	0b00000,
	0b00000,
	0b11111,
	0b01110,
	0b00100
};

byte customCharChasi5[8] = {
	0b00000,
	0b00000,
	0b01110,
	0b10101,
	0b10111,
	0b10001,
	0b01110,
	0b00000
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ТЕХНИЧЕСКИЕ ФУНКЦИИ:

// функция проверки кнопок
byte key(){  // 1-723, 2-482, 3-133, 4-310, 5-0;
	int val = analogRead(A0);
	byte keyVal = 0;
	if(val < 67) keyVal = 5;             // right
	else if(val < 221) keyVal = 4;       // up
	else if(val < 396) keyVal = 3;       // down
	else if(val < 602) keyVal = 2;       // left
	else if(val < 873) keyVal = 1;       // select // 873
	else if(val <= 1023) keyVal = 0;     // no press
	Serial.print(keyVal);
	Serial.print(" ");
	Serial.println(val);
	return keyVal;
}

void buttonChekForLoop(){  // обработчик нажатий кнопок в цикле loop
	byte val = key();

	if(val == 0){

	}else if(val == 1){  // select
		menu24();
	}else if(val == 2){  // left

	}else if(val == 3){  // down

	}else if(val == 4){  // up

	}else if(val == 5){  // right

	}
}

void buttonChekForMenu(){  // обработчик нажатий кнопок в menu
	byte val = key();
	if(val == 0){        // no pressed = no action
	}else if(val == 1){  // select
	}else if(val == 2){  // left
	}else if(val == 3){  // down
	}else if(val == 4){  // up
	}else if(val == 5){  // right
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// В ЭТОМ РАЗДЕЛЕ НАСТРАИВАЕТСЯ РАСПИСАНИЕ МЕЛОДИЙ ПЕРЕЗВОНА И ЧАСЫ:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// часы: будильник

// часы: время
void chekVremya(){
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// расписание:
int chekPerezvon(){
}

int chasZvona(){}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// дополнительные функции расписания:
// функция отбивания времени колоколом
void timeBellRound(int _hours = 1){
	for(int i=0;i<_hours;i++){
		nota(RELE_HOUR_BLOW, DEF_TIME_OF_BLOW_UNIC_NOTA_HOUR_OF_BLOW, HOUR_OF_BLOW_DELAY);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// КОМПОНЕНТЫ МЕНЮ:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// функция рисования для функции удара в любой колокол с настройками из меню
inline void drawBellForMenu(int _bfmKolocol = 12, unsigned long _bfmTimeOfBlow = DEF_TIME_OF_BLOW_TO_THE_BELL){

	int dbfmKolocol = _bfmKolocol;
	unsigned long dbfmTimeOfBlow = _bfmTimeOfBlow;
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.write(byte(0));
	lcd.setCursor(2,0);
	lcd.print(dbfmKolocol);
	lcd.setCursor(4,0);
	lcd.print(" del ");
	lcd.setCursor(9,0);
	lcd.print(dbfmTimeOfBlow);
	lcd.setCursor(14,0);
	lcd.print("OK");
}

// функция удара в любой колокол с настройками из меню
void bellForMenu(){

	unsigned int buttonDelay = 200;

	int bfmKolocol = 12;  // переменная для хранения номера колокола
	unsigned long bfmTimeOfBlow = DEF_TIME_OF_BLOW_TO_THE_BELL;  // переменная для хранения выдержки язычка
	bool bfmCikl = 1;  // переменная для управления циклом while
	byte bfmVirtualPos = 1;   // виртуальная позиция указателя меню
	byte bfmRealPos = 0;   // реальная позиция указателя меню
	byte bfmKey = 0;   // значение кнопок для обработки в цикле while
	unsigned long bfmTimeOfBlowMnojitel = 1;  // множитель для мс. в меню

	drawBellForMenu();

	lcd.setCursor(0,1);
	lcd.write(byte(4));

	while(bfmCikl){
		bfmKey = key();


		if(bfmKey > 0){
			if(bfmKey == 1){  // s
				if(bfmVirtualPos == 1){
					bfmCikl = 0;  // выход из меню удара в колокол
				}else if(bfmVirtualPos == 2){
					nota(bfmKolocol, bfmTimeOfBlow, DEF_DEL_UNT_NEXT_NOTA);  // играть выбранную ноту
				}else if(bfmVirtualPos == 3){
					bfmTimeOfBlowMnojitel *= 10;
					if(bfmTimeOfBlowMnojitel > 100){bfmTimeOfBlowMnojitel = 1;}
				}else if(bfmVirtualPos == 4){
					nota(bfmKolocol, bfmTimeOfBlow, DEF_DEL_UNT_NEXT_NOTA);  // играть выбранную ноту
				}
				
				delay(buttonDelay);

			}else if(bfmKey == 2){  // l
				bfmVirtualPos --;
				if(bfmVirtualPos <= 0){bfmVirtualPos = 4;}
				delay(buttonDelay);
			}else if(bfmKey == 3){  // d
				if(bfmVirtualPos == 1){
					bfmCikl = 0;  // выход из меню удара в колокол
				}else if(bfmVirtualPos == 2){
					bfmKolocol --;
					if(bfmKolocol <= 0){bfmKolocol = 24;}
				}else if(bfmVirtualPos == 3){
					bfmTimeOfBlow -= bfmTimeOfBlowMnojitel;
					if(bfmTimeOfBlow <= 0){bfmTimeOfBlow = 9999;}
				}else if(bfmVirtualPos == 4){
					nota(bfmKolocol, bfmTimeOfBlow, DEF_DEL_UNT_NEXT_NOTA);  // играть выбранную ноту
				}
				delay(buttonDelay);
			}else if(bfmKey == 4){  // u
				if(bfmVirtualPos == 1){
					bfmCikl = 0;  // выход из меню удара в колокол
				}else if(bfmVirtualPos == 2){
					bfmKolocol ++;
					if(bfmKolocol > 24){bfmKolocol = 1;}
				}else if(bfmVirtualPos == 3){
					bfmTimeOfBlow += bfmTimeOfBlowMnojitel;
					if(bfmTimeOfBlow > 9999){bfmTimeOfBlow = 1;}
				}else if(bfmVirtualPos == 4){
					nota(bfmKolocol, bfmTimeOfBlow, DEF_DEL_UNT_NEXT_NOTA);  // играть выбранную ноту
				}
				delay(buttonDelay);
			}else if(bfmKey == 5){  // r
				bfmVirtualPos ++;
				if(bfmVirtualPos > 4){bfmVirtualPos = 0;}
				delay(buttonDelay);
			}

			switch (bfmVirtualPos){
			    case 1:
			      bfmRealPos = 0;
			      break;
			    case 2:
			      bfmRealPos = 2;
			      break;
			    case 3:
			      bfmRealPos = 9;
			      break;
			    case 4:
			      bfmRealPos = 14;
			      break;
			}

			drawBellForMenu(bfmKolocol, bfmTimeOfBlow);
			lcd.setCursor(bfmRealPos,1);
			lcd.write(byte(4));
			if(bfmVirtualPos == 3){
				lcd.print(bfmTimeOfBlowMnojitel);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ФУНКЦИЯ МЕНЮ:
void menu24(){
	lcd.clear();
	lcd.setCursor(6,0);
	lcd.print("MENU");
	delay(1000);
	bellForMenu();
	
	// while(1){
	// 	lcd.clear();
	// 	delay(1000);
	// 	lcd.setCursor(0,1);
	// 	lcd.print(" RESET to exit");
	// 	delay(1500);
	// }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  	//pinMode(LED_BUILTIN, OUTPUT);  // фиксим 13 диод
	Serial.begin(9600);

	// инициализация пользовательских символов
  	lcd.createChar(0, customCharBell0);
  	lcd.createChar(1, customCharNota1);
  	lcd.createChar(2, customCharLeftArrow2);
  	lcd.createChar(3, customCharRightArrow3);
  	lcd.createChar(4, customCharMenuArrow4);
  	lcd.createChar(5, customCharChasi5);

	// инициализация колоколов
	pinMode(RELE_K1, OUTPUT);
	pinMode(RELE_K2, OUTPUT);
	pinMode(RELE_K3, OUTPUT);
	pinMode(RELE_K4, OUTPUT);
	pinMode(RELE_K5, OUTPUT);
	pinMode(RELE_K6, OUTPUT);
	pinMode(RELE_K7, OUTPUT);
	pinMode(RELE_K8, OUTPUT);
	pinMode(RELE_K9, OUTPUT);
	pinMode(RELE_K10, OUTPUT);
	pinMode(RELE_K11, OUTPUT);
	pinMode(RELE_K12, OUTPUT);
	pinMode(RELE_K13, OUTPUT);
	pinMode(RELE_K14, OUTPUT);
	pinMode(RELE_K15, OUTPUT);
	pinMode(RELE_K16, OUTPUT);
	pinMode(RELE_K17, OUTPUT);
	pinMode(RELE_K18, OUTPUT);
	pinMode(RELE_K19, OUTPUT);
	pinMode(RELE_K20, OUTPUT);
	pinMode(RELE_K21, OUTPUT);
	pinMode(RELE_K22, OUTPUT);
	pinMode(RELE_K23, OUTPUT);
	pinMode(RELE_K24, OUTPUT);

	digitalWrite(RELE_K1, LLL);
	digitalWrite(RELE_K2, LLL);
	digitalWrite(RELE_K3, LLL);
	digitalWrite(RELE_K4, LLL);
	digitalWrite(RELE_K5, LLL);
	digitalWrite(RELE_K6, LLL);
	digitalWrite(RELE_K7, LLL);
	digitalWrite(RELE_K8, LLL);
	digitalWrite(RELE_K9, LLL);
	digitalWrite(RELE_K10, LLL);
	digitalWrite(RELE_K11, LLL);
	digitalWrite(RELE_K12, LLL);
	digitalWrite(RELE_K13, LLL);
	digitalWrite(RELE_K14, LLL);
	digitalWrite(RELE_K15, LLL);
	digitalWrite(RELE_K16, LLL);
	digitalWrite(RELE_K17, LLL);
	digitalWrite(RELE_K18, LLL);
	digitalWrite(RELE_K19, LLL);
	digitalWrite(RELE_K20, LLL);
	digitalWrite(RELE_K21, LLL);
	digitalWrite(RELE_K22, LLL);
	digitalWrite(RELE_K23, LLL);
	digitalWrite(RELE_K24, LLL);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	lcd.begin(16, 2);
    lcd.clear();
    lcd.clear();
	lcd.print("   MEGAZVON24");
	lcd.setCursor(2,1);
	lcd.write(byte(1));
	lcd.print(" melodiaEX2");
	delay(2000);

	// инициализация комплектующих
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

  	// byte lVal = key();
  	// lcd.clear();
  	// lcd.print(lVal);
  	// lcd.print(" ");
  	// lcd.print(analogRead(A0));
  	// delay(100);

	buttonChekForLoop();

	// lcd.clear();
	// lcd.setCursor(2,0);
	// lcd.write(byte(1));
	// lcd.print(" melodiaEX2");
	// delay(1000);

	melodiaEX3();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
