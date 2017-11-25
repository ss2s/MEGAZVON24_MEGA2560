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
//#include "res24.h"              // файл ресурсов
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

#include <EEPROM.h>
unsigned long EEPROM_ulong_read(int addr);
void EEPROM_ulong_write(int addr, unsigned long data);
void timeOfBlowUnicNotaSet(int _kolokol);
unsigned long timeOfBlowUnicNotaGet(int _kolokol);
void timeOfBlowUnicNotaSetPak();
void timeOfBlowUnicNotaGetPak();

#include "nota24.h"             // ноты
#include "melody24.h"           // файл с мелодиями
#include "raspisanie24.h"       // расписание

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
	// Serial.print(keyVal);
	// Serial.print(" ");
	// Serial.println(val);
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

unsigned long EEPROM_ulong_read(int fAddr) // чтение из EEPROM 4 байта unsigned long
{ 
	int rAddr = fAddr*4;
	byte raw[4];
  for(byte i = 0; i < 4; i++) raw[i] = EEPROM.read(rAddr+i);
  unsigned long &data = (unsigned long&)raw;
  return data;
}
//*****************************************************************
void EEPROM_ulong_write(int fAddr, unsigned long data) // запись в EEPROM 4 байта unsigned long
{
	int rAddr = fAddr*4;
  	byte raw[4];
  	(unsigned long&)raw = data;
  	for(byte i = 0; i < 4; i++) EEPROM.write(rAddr+i, raw[i]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void timeOfBlowUnicNotaSet(int _kolokol){
	int tobKolokol = _kolokol;
	unsigned long tobTimtOfBlowUnicNota = findNotaDelayForKolokolNumber(tobKolokol);
	EEPROM_ulong_write(tobKolokol, tobTimtOfBlowUnicNota);
}

unsigned long timeOfBlowUnicNotaGet(int _kolokol){
	int tobKolokol = _kolokol;
	unsigned long tobTimtOfBlowUnicNota = EEPROM_ulong_read(tobKolokol);

	switch (tobKolokol) {
	    case 1:
	      timtOfBlowUnicNota_1 = tobTimtOfBlowUnicNota;
	      break;
	    case 2:
	      timtOfBlowUnicNota_2 = tobTimtOfBlowUnicNota;
	      break;
	    case 3:
	      timtOfBlowUnicNota_3 = tobTimtOfBlowUnicNota;
	      break;
	    case 4:
	      timtOfBlowUnicNota_4 = tobTimtOfBlowUnicNota;
	      break;
	    case 5:
	      timtOfBlowUnicNota_5 = tobTimtOfBlowUnicNota;
	      break;
	    case 6:
	      timtOfBlowUnicNota_6 = tobTimtOfBlowUnicNota;
	      break;
	    case 7:
	      timtOfBlowUnicNota_7 = tobTimtOfBlowUnicNota;
	      break;
	    case 8:
	      timtOfBlowUnicNota_8 = tobTimtOfBlowUnicNota;
	      break;
	    case 9:
	      timtOfBlowUnicNota_9 = tobTimtOfBlowUnicNota;
	      break;
	    case 10:
	      timtOfBlowUnicNota_10 = tobTimtOfBlowUnicNota;
	      break;
	    case 11:
	      timtOfBlowUnicNota_11 = tobTimtOfBlowUnicNota;
	      break;
	    case 12:
	      timtOfBlowUnicNota_12 = tobTimtOfBlowUnicNota;
	      break;
	    case 13:
	      timtOfBlowUnicNota_13 = tobTimtOfBlowUnicNota;
	      break;
	    case 14:
	      timtOfBlowUnicNota_14 = tobTimtOfBlowUnicNota;
	      break;
	    case 15:
	      timtOfBlowUnicNota_15 = tobTimtOfBlowUnicNota;
	      break;
	    case 16:
	      timtOfBlowUnicNota_16 = tobTimtOfBlowUnicNota;
	      break;
	    case 17:
	      timtOfBlowUnicNota_17 = tobTimtOfBlowUnicNota;
	      break;
	    case 18:
	      timtOfBlowUnicNota_18 = tobTimtOfBlowUnicNota;
	      break;
	    case 19:
	      timtOfBlowUnicNota_19 = tobTimtOfBlowUnicNota;
	      break;
	    case 20:
	      timtOfBlowUnicNota_20 = tobTimtOfBlowUnicNota;
	      break;
	    case 21:
	      timtOfBlowUnicNota_21 = tobTimtOfBlowUnicNota;
	      break;
	    case 22:
	      timtOfBlowUnicNota_22 = tobTimtOfBlowUnicNota;
	      break;
	    case 23:
	      timtOfBlowUnicNota_23 = tobTimtOfBlowUnicNota;
	      break;
	    case 24:
	      timtOfBlowUnicNota_24 = tobTimtOfBlowUnicNota;
	      break;
	}

	return tobTimtOfBlowUnicNota;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void timeOfBlowUnicNotaSetPak(){

	EEPROM_ulong_write(1, DEF_TIME_OF_BLOW_UNIC_NOTA_1);
	EEPROM_ulong_write(2, DEF_TIME_OF_BLOW_UNIC_NOTA_2);
	EEPROM_ulong_write(3, DEF_TIME_OF_BLOW_UNIC_NOTA_3);
	EEPROM_ulong_write(4, DEF_TIME_OF_BLOW_UNIC_NOTA_4);
	EEPROM_ulong_write(5, DEF_TIME_OF_BLOW_UNIC_NOTA_5);
	EEPROM_ulong_write(6, DEF_TIME_OF_BLOW_UNIC_NOTA_6);
	EEPROM_ulong_write(7, DEF_TIME_OF_BLOW_UNIC_NOTA_7);
	EEPROM_ulong_write(8, DEF_TIME_OF_BLOW_UNIC_NOTA_8);
	EEPROM_ulong_write(9, DEF_TIME_OF_BLOW_UNIC_NOTA_9);
	EEPROM_ulong_write(10, DEF_TIME_OF_BLOW_UNIC_NOTA_10);
	EEPROM_ulong_write(11, DEF_TIME_OF_BLOW_UNIC_NOTA_11);
	EEPROM_ulong_write(12, DEF_TIME_OF_BLOW_UNIC_NOTA_12);
	EEPROM_ulong_write(13, DEF_TIME_OF_BLOW_UNIC_NOTA_13);
	EEPROM_ulong_write(14, DEF_TIME_OF_BLOW_UNIC_NOTA_14);
	EEPROM_ulong_write(15, DEF_TIME_OF_BLOW_UNIC_NOTA_15);
	EEPROM_ulong_write(16, DEF_TIME_OF_BLOW_UNIC_NOTA_16);
	EEPROM_ulong_write(17, DEF_TIME_OF_BLOW_UNIC_NOTA_17);
	EEPROM_ulong_write(18, DEF_TIME_OF_BLOW_UNIC_NOTA_18);
	EEPROM_ulong_write(19, DEF_TIME_OF_BLOW_UNIC_NOTA_19);
	EEPROM_ulong_write(20, DEF_TIME_OF_BLOW_UNIC_NOTA_20);
	EEPROM_ulong_write(21, DEF_TIME_OF_BLOW_UNIC_NOTA_21);
	EEPROM_ulong_write(22, DEF_TIME_OF_BLOW_UNIC_NOTA_22);
	EEPROM_ulong_write(23, DEF_TIME_OF_BLOW_UNIC_NOTA_23);
	EEPROM_ulong_write(24, DEF_TIME_OF_BLOW_UNIC_NOTA_24);
	
}
void timeOfBlowUnicNotaGetPak(){

	timtOfBlowUnicNota_1 = EEPROM_ulong_read(1);
	timtOfBlowUnicNota_2 = EEPROM_ulong_read(2);
	timtOfBlowUnicNota_3 = EEPROM_ulong_read(3);
	timtOfBlowUnicNota_4 = EEPROM_ulong_read(4);
	timtOfBlowUnicNota_5 = EEPROM_ulong_read(5);
	timtOfBlowUnicNota_6 = EEPROM_ulong_read(6);
	timtOfBlowUnicNota_7 = EEPROM_ulong_read(7);
	timtOfBlowUnicNota_8 = EEPROM_ulong_read(8);
	timtOfBlowUnicNota_9 = EEPROM_ulong_read(9);
	timtOfBlowUnicNota_10 = EEPROM_ulong_read(10);
	timtOfBlowUnicNota_11 = EEPROM_ulong_read(11);
	timtOfBlowUnicNota_12 = EEPROM_ulong_read(12);
	timtOfBlowUnicNota_13 = EEPROM_ulong_read(13);
	timtOfBlowUnicNota_14 = EEPROM_ulong_read(14);
	timtOfBlowUnicNota_15 = EEPROM_ulong_read(15);
	timtOfBlowUnicNota_16 = EEPROM_ulong_read(16);
	timtOfBlowUnicNota_17 = EEPROM_ulong_read(17);
	timtOfBlowUnicNota_18 = EEPROM_ulong_read(18);
	timtOfBlowUnicNota_19 = EEPROM_ulong_read(19);
	timtOfBlowUnicNota_20 = EEPROM_ulong_read(20);
	timtOfBlowUnicNota_21 = EEPROM_ulong_read(21);
	timtOfBlowUnicNota_22 = EEPROM_ulong_read(22);
	timtOfBlowUnicNota_23 = EEPROM_ulong_read(23);
	timtOfBlowUnicNota_24 = EEPROM_ulong_read(24);
}
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

	unsigned int buttonDelay = 200;  // задержка для меню

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
inline void drawTimtOfBlowUnicNotaForMenu(int _tobKolocol = 12){

	int dtobKolocol = _tobKolocol;
	unsigned long dtobTimeOfBlow = findNotaDelayForKolokolNumber(dtobKolocol);
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.write(byte(5));
	lcd.setCursor(2,0);
	lcd.print(dtobKolocol);
	lcd.setCursor(4,0);
	lcd.print(" set ");
	lcd.setCursor(9,0);
	lcd.print(dtobTimeOfBlow);
	lcd.setCursor(14,0);
	lcd.print("OK");
}
// функция настройки длительности нот
void timtOfBlowUnicNotaForMenu(){
	unsigned int buttonDelay = 200;  // задержка для меню

	int tobKolocol = 12;  // переменная для хранения номера колокола
	unsigned long tobTimeOfBlow = DEF_TIME_OF_BLOW_TO_THE_BELL;  // переменная для хранения выдержки язычка
	bool tobCikl = 1;  // переменная для управления циклом while
	byte tobVirtualPos = 1;   // виртуальная позиция указателя меню
	byte tobRealPos = 0;   // реальная позиция указателя меню
	byte tobKey = 0;   // значение кнопок для обработки в цикле while
	unsigned long tobTimeOfBlowMnojitel = 1;  // множитель для мс. в меню

	drawTimtOfBlowUnicNotaForMenu();

	lcd.setCursor(0,1);
	lcd.write(byte(4));

	while(tobCikl){
		tobKey = key();


		if(tobKey > 0){
			if(tobKey == 1){  // s
				if(tobVirtualPos == 1){
					tobCikl = 0;  // выход из меню настройки времени ноты
				}else if(tobVirtualPos == 3){
					tobTimeOfBlowMnojitel *= 10;
					if(tobTimeOfBlowMnojitel > 100){tobTimeOfBlowMnojitel = 1;}
				}else if(tobVirtualPos == 4){
					timeOfBlowUnicNotaSet(tobKolocol);
				}
				delay(buttonDelay);

			}else if(tobKey == 2){  // l
				tobVirtualPos --;
				if(tobVirtualPos <= 0){tobVirtualPos = 4;}
				delay(buttonDelay);
			}else if(tobKey == 3){  // d
				if(tobVirtualPos == 1){
					tobCikl = 0;  // выход из меню настройки времени ноты
				}else if(tobVirtualPos == 2){
					tobKolocol --;
					if(tobKolocol <= 0){tobKolocol = 24;}
				}else if(tobVirtualPos == 3){

					switch (tobKolocol) {
					    case 1:
					      timtOfBlowUnicNota_1 -= tobTimeOfBlowMnojitel;
					      break;
					    case 2:
					      timtOfBlowUnicNota_2 -= tobTimeOfBlowMnojitel;
					      break;
					    case 3:
					      timtOfBlowUnicNota_3 -= tobTimeOfBlowMnojitel;
					      break;
					    case 4:
					      timtOfBlowUnicNota_4 -= tobTimeOfBlowMnojitel;
					      break;
					    case 5:
					      timtOfBlowUnicNota_5 -= tobTimeOfBlowMnojitel;
					      break;
					    case 6:
					      timtOfBlowUnicNota_6 -= tobTimeOfBlowMnojitel;
					      break;
					    case 7:
					      timtOfBlowUnicNota_7 -= tobTimeOfBlowMnojitel;
					      break;
					    case 8:
					      timtOfBlowUnicNota_8 -= tobTimeOfBlowMnojitel;
					      break;
					    case 9:
					      timtOfBlowUnicNota_9 -= tobTimeOfBlowMnojitel;
					      break;
					    case 10:
					      timtOfBlowUnicNota_10 -= tobTimeOfBlowMnojitel;
					      break;
					    case 11:
					      timtOfBlowUnicNota_11 -= tobTimeOfBlowMnojitel;
					      break;
					    case 12:
					      timtOfBlowUnicNota_12 -= tobTimeOfBlowMnojitel;
					      break;
					    case 13:
					      timtOfBlowUnicNota_13 -= tobTimeOfBlowMnojitel;
					      break;
					    case 14:
					      timtOfBlowUnicNota_14 -= tobTimeOfBlowMnojitel;
					      break;
					    case 15:
					      timtOfBlowUnicNota_15 -= tobTimeOfBlowMnojitel;
					      break;
					    case 16:
					      timtOfBlowUnicNota_16 -= tobTimeOfBlowMnojitel;
					      break;
					    case 17:
					      timtOfBlowUnicNota_17 -= tobTimeOfBlowMnojitel;
					      break;
					    case 18:
					      timtOfBlowUnicNota_18 -= tobTimeOfBlowMnojitel;
					      break;
					    case 19:
					      timtOfBlowUnicNota_19 -= tobTimeOfBlowMnojitel;
					      break;
					    case 20:
					      timtOfBlowUnicNota_20 -= tobTimeOfBlowMnojitel;
					      break;
					    case 21:
					      timtOfBlowUnicNota_21 -= tobTimeOfBlowMnojitel;
					      break;
					    case 22:
					      timtOfBlowUnicNota_22 -= tobTimeOfBlowMnojitel;
					      break;
					    case 23:
					      timtOfBlowUnicNota_23 -= tobTimeOfBlowMnojitel;
					      break;
					    case 24:
					      timtOfBlowUnicNota_24 -= tobTimeOfBlowMnojitel;
					      break;
					}

					if(tobTimeOfBlow <= 0){tobTimeOfBlow = 9999;}
				}else if(tobVirtualPos == 4){
					timeOfBlowUnicNotaSet(tobKolocol);
				}
				delay(buttonDelay);
			}else if(tobKey == 4){  // u
				if(tobVirtualPos == 1){
					tobCikl = 0;  // выход из меню настройки времени ноты
				}else if(tobVirtualPos == 2){
					tobKolocol ++;
					if(tobKolocol > 24){tobKolocol = 1;}
				}else if(tobVirtualPos == 3){

					switch (tobKolocol) {
					    case 1:
					      timtOfBlowUnicNota_1 += tobTimeOfBlowMnojitel;
					      break;
					    case 2:
					      timtOfBlowUnicNota_2 += tobTimeOfBlowMnojitel;
					      break;
					    case 3:
					      timtOfBlowUnicNota_3 += tobTimeOfBlowMnojitel;
					      break;
					    case 4:
					      timtOfBlowUnicNota_4 += tobTimeOfBlowMnojitel;
					      break;
					    case 5:
					      timtOfBlowUnicNota_5 += tobTimeOfBlowMnojitel;
					      break;
					    case 6:
					      timtOfBlowUnicNota_6 += tobTimeOfBlowMnojitel;
					      break;
					    case 7:
					      timtOfBlowUnicNota_7 += tobTimeOfBlowMnojitel;
					      break;
					    case 8:
					      timtOfBlowUnicNota_8 += tobTimeOfBlowMnojitel;
					      break;
					    case 9:
					      timtOfBlowUnicNota_9 += tobTimeOfBlowMnojitel;
					      break;
					    case 10:
					      timtOfBlowUnicNota_10 += tobTimeOfBlowMnojitel;
					      break;
					    case 11:
					      timtOfBlowUnicNota_11 += tobTimeOfBlowMnojitel;
					      break;
					    case 12:
					      timtOfBlowUnicNota_12 += tobTimeOfBlowMnojitel;
					      break;
					    case 13:
					      timtOfBlowUnicNota_13 += tobTimeOfBlowMnojitel;
					      break;
					    case 14:
					      timtOfBlowUnicNota_14 += tobTimeOfBlowMnojitel;
					      break;
					    case 15:
					      timtOfBlowUnicNota_15 += tobTimeOfBlowMnojitel;
					      break;
					    case 16:
					      timtOfBlowUnicNota_16 += tobTimeOfBlowMnojitel;
					      break;
					    case 17:
					      timtOfBlowUnicNota_17 += tobTimeOfBlowMnojitel;
					      break;
					    case 18:
					      timtOfBlowUnicNota_18 += tobTimeOfBlowMnojitel;
					      break;
					    case 19:
					      timtOfBlowUnicNota_19 += tobTimeOfBlowMnojitel;
					      break;
					    case 20:
					      timtOfBlowUnicNota_20 += tobTimeOfBlowMnojitel;
					      break;
					    case 21:
					      timtOfBlowUnicNota_21 += tobTimeOfBlowMnojitel;
					      break;
					    case 22:
					      timtOfBlowUnicNota_22 += tobTimeOfBlowMnojitel;
					      break;
					    case 23:
					      timtOfBlowUnicNota_23 += tobTimeOfBlowMnojitel;
					      break;
					    case 24:
					      timtOfBlowUnicNota_24 += tobTimeOfBlowMnojitel;
					      break;
					}

					if(tobTimeOfBlow > 9999){tobTimeOfBlow = 1;}
				}else if(tobVirtualPos == 4){
					timeOfBlowUnicNotaSet(tobKolocol);
				}
				delay(buttonDelay);
			}else if(tobKey == 5){  // r
				tobVirtualPos ++;
				if(tobVirtualPos > 4){tobVirtualPos = 0;}
				delay(buttonDelay);
			}

			switch (tobVirtualPos){
			    case 1:
			      tobRealPos = 0;
			      break;
			    case 2:
			      tobRealPos = 2;
			      break;
			    case 3:
			      tobRealPos = 9;
			      break;
			    case 4:
			      tobRealPos = 14;
			      break;
			}

			drawTimtOfBlowUnicNotaForMenu(tobKolocol);
			lcd.setCursor(tobRealPos,1);
			lcd.write(byte(4));
			if(tobVirtualPos == 3){
				lcd.print(tobTimeOfBlowMnojitel);
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
	timtOfBlowUnicNotaForMenu();
	rminute = 61;
	timeToDisplay();
	
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

	//timeOfBlowUnicNotaSetPak();  // запись длительностей нот в EEPROM из файла "config24.h" (применяется 1 раз)
	timeOfBlowUnicNotaGetPak();  // чтение длительностей нот из EEPROM в переменную (выполняется при старте МК)

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
	lcd.print(" melodiaEX3");
	delay(500);

	//melodiaEX3();

	lcd.clear();
	lcd.print("select to MENU");
	// инициализация комплектующих

	// ЧАСЫ:
	clock.begin();         // Инициализируем работу с объектом библиотеки DS3231
//clock.enableOutput(false);// Определяем назначение вывода SQW (INT) для генерации прерываний при сработке будильников

//  clock.setDateTime(__DATE__, __TIME__);      // Устанавливаем время на часах, основываясь на времени компиляции скетча
//  clock.setDateTime(2016, 9, 15, 0, 0, 0);      // Установка времени вручную (Год, Месяц, День, Час, Минута, Секунда)
//  setAlarm1(Дата или день, Час, Минута, Секунда, Режим)
//clock.setAlarm1(0, 0, 0, 1, DS3231_MATCH_S);           // Устанавливаем первый будильник на срабатывание в 10 сек.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

	timeToDisplay();  // вывод времени на дисплей
	buttonChekForLoop();  // проверка кнопок
	chekPerezvon();  // проверка расписания
	//timeToSerial();
	delay(1000);

  	// byte lVal = key();
  	// lcd.clear();
  	// lcd.print(lVal);
  	// lcd.print(" ");
  	// lcd.print(analogRead(A0));
  	// delay(100);
	// lcd.clear();
	// lcd.setCursor(2,0);
	// lcd.write(byte(1));
	// lcd.print(" melodiaEX2");
	// delay(1000);
	// delay(10000);  // задержка 10 секунд
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
