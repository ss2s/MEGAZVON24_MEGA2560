////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

          https://github.com/ss2s/MEGAZVON24_MEGA2560
        \******************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                                            // ВАЖНАЯ ИНФОРМАЦИЯ //


// ПОЧТИ ВСЕ НАСТРОЙКИ ВЫНЕСЕНЫ В ОТДЕЛЬНЫЙ ФАЙЛ "MEGAZVON24_CONFIG.h"
// НАСТРОЙКА ДЛИТЕЛЬНОСТИ КАЖДОЙ НОТЫ В ФАЙЛЕ "MEGAZVON24_CONFIG.h"

// НАСТРОЙКИ ТЕРМОРЕГУЛЯТОРА В ОСНОВНОЙ ПРОГРАММЕ
// НАСТРОЙКИ ДИСПЛЕЯ В ОСНОВНОЙ ПРОГРАММЕ


// все нужные файлы находятся в папке с прошивкой


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ТЕРМОРЕГУЛЯТОР ENABLE:
#define DEF_PODOGREV_ENABLE 0  // ФУНКЦИЯ ПОДОГРЕВА БОКСА С УСТРОЙСТВОМ. ЕСЛИ 1 ПОДОГРЕВ ВКЛЮЧЕН, 0 ВЫКЛЮЧЕН.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MEGAZVON24CONFIG.h"  // файл конфигурации

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"            // Arduino lib
#include <LiquidCrystal.h>      // библиотека дисплея с кнопками

#if DEF_PODOGREV_ENABLE != 0
#include "Dht11.h"              // библиотека термометра
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ЧАСЫ DS3231:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>         // библиотека I2C
#include "DS3231.h"       // библиотека часов
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DS3231 clock;             // Связываем объект clock с библиотекой DS3231
RTCDateTime DateTime;     // Определяем сущность структуры RTCDateTime (описанной в библиотеке DS3231)
RTCAlarmTime Alarm1;      // Определяем сущность структуры RTCAlarmTime (описанной в библиотеке DS3231)

int minutes;              // переменная для хранения минут
int hours;                // переменная для хранения часов
boolean isAlarm = false;  // Логическая переменная для обработки сигнала о срабатывании будильника 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// НАСТРОЙКИ ТЕРМОРЕГУЛЯТОР:
#if DEF_PODOGREV_ENABLE != 0
// распиновка терморегулятора
#define DEF_DHT_DATA_PIN 55    // датчик температуры
#define DEF_TERMO_RELE_PIN 50  // выход реле терморегулятора

// НАСТРОЙКА ТЕРМОРЕГУЛЯТОРА (ТЕМПЕРАТУРЫ ВКЛЮЧЕНИЯ ВЫКЛЮЧЕНИЯ ТЕРМОРЕГУЛЯТОРА)
// настройки температуры включения выключения терморегулятора
byte turnONtemp  = 0;  // температура включения подогрева
byte turnOFFtemp = 5;  // температура выключения подогрева

// переменные терморегулятора
byte TEMP = 0;  // температура
byte HMDT = 0;  // влажность
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// НАСТРОЙКИ ВРЕМЕННЫХ ЗАДЕРЖЕК ПО УМОЛЧАНИЮ: настройки вынесены в отдельный файл "MELODIA_ZVONA.h"

// для каждой ноты в отдельности, 2 набор нот
// настройка в файле "MELODIA_ZVONA.h"
int timtOfBlowUnicNota_1 = DEF_TIME_OF_BLOW_UNIC_NOTA_1;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 1 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_2 = DEF_TIME_OF_BLOW_UNIC_NOTA_2;   // ВРЕМЯ УДАРА ЯЗЫЧКА ВО 2 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_3 = DEF_TIME_OF_BLOW_UNIC_NOTA_3;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 3 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_4 = DEF_TIME_OF_BLOW_UNIC_NOTA_4;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 4 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_5 = DEF_TIME_OF_BLOW_UNIC_NOTA_5;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 5 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_6 = DEF_TIME_OF_BLOW_UNIC_NOTA_6;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 6 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_7 = DEF_TIME_OF_BLOW_UNIC_NOTA_7;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 7 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_8 = DEF_TIME_OF_BLOW_UNIC_NOTA_8;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 8 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_9 = DEF_TIME_OF_BLOW_UNIC_NOTA_9;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 9 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_10 = DEF_TIME_OF_BLOW_UNIC_NOTA_10;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 10 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_11 = DEF_TIME_OF_BLOW_UNIC_NOTA_11;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 11 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_12 = DEF_TIME_OF_BLOW_UNIC_NOTA_12;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 12 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_13 = DEF_TIME_OF_BLOW_UNIC_NOTA_13;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 13 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_14 = DEF_TIME_OF_BLOW_UNIC_NOTA_14;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 14 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_15 = DEF_TIME_OF_BLOW_UNIC_NOTA_15;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 15 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_16 = DEF_TIME_OF_BLOW_UNIC_NOTA_16;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 16 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_17 = DEF_TIME_OF_BLOW_UNIC_NOTA_17;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 17 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_18 = DEF_TIME_OF_BLOW_UNIC_NOTA_18;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 18 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_19 = DEF_TIME_OF_BLOW_UNIC_NOTA_19;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 19 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_20 = DEF_TIME_OF_BLOW_UNIC_NOTA_20;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 20 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_21 = DEF_TIME_OF_BLOW_UNIC_NOTA_21;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 21 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_22 = DEF_TIME_OF_BLOW_UNIC_NOTA_22;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 22 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_23 = DEF_TIME_OF_BLOW_UNIC_NOTA_23;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 23 КОЛОКОЛ (ВРЕМЯ НОТЫ)
int timtOfBlowUnicNota_24 = DEF_TIME_OF_BLOW_UNIC_NOTA_24;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 24 КОЛОКОЛ (ВРЕМЯ НОТЫ)

// ПРОЧИЕ НАСТРОЙКИ

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// инициализация дисплея с кнопками
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ТЕХНИЧЕСКИЕ ФУНКЦИИ:

// функция проверки кнопок
byte key(){  // 1-723, 2-482, 3-133, 4-310, 5-0;
	int val = analogRead(DEF_LCD_KEY_PIN);
	if(val < 67) return 5;             // right
	else if(val < 221) return 4;       // left
	else if(val < 396) return 3;       // up
	else if(val < 602) return 2;       // down
	else if(val < 873) return 1;       // select
	else if(val <= 1023) return 0;     // no pressed
}

inline void buttonChekForLoop(){  // обработчик нажатий кнопок в цикле loop
	byte val = key();
	if(val = 0){        // no pressed = no action
	}else if(val = 1){  // select
		menu();
	}else if(val = 2){  // down
	}else if(val = 3){  // up
	}else if(val = 4){  // left
	}else if(val = 5){  // right
	}
}

inline void buttonChekForMenu(){  // обработчик нажатий кнопок в menu
	byte val = key();
	if(val = 0){        // no pressed = no action
	}else if(val = 1){  // select
	}else if(val = 2){  // down
	}else if(val = 3){  // up
	}else if(val = 4){  // left
	}else if(val = 5){  // right
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEF_PODOGREV_ENABLE != 0
// функция проверки температуры
byte chekTemp(){
    return TEMP;
}

// функция регулировки температуры
void termoRegulator(){
	chekTemp();
	if(TEMP <= turnONtemp){
	digitalWrite(DEF_TERMO_RELE_PIN, HIGH);
	}else if(TEMP > turnOFFtemp){
	digitalWrite(DEF_TERMO_RELE_PIN, LOW);
	}
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 1 НАБОР НОТ
// функция нота,принимает три параметра через запятую(имя колокола, время звучания ноты, время до вызова следующей ноты)
// по умолчанию: колокол 1, время звучания ноты 300мс, таймаут между нотами 3000мс
// пример использования функции:[nota(RELE_K7, 250, 2000);] 7 колокол, время ноты 250мс, таймаут до следующей ноты 2с

int nota(byte _kolokol = RELE_K1,
unsigned int _timeOfBlowToTheBell = DEF_TIME_OF_BLOW_TO_THE_BELL,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){

	digitalWrite(_kolokol, HHH);
	delay(_timeOfBlowToTheBell);
	digitalWrite(_kolokol, LLL);
	delay(_delayUntilNextNota);
}

// 2 НАБОР НОТ
// НОТЫ ПО УМОЛЧАНИЮ: для каждой ноты можно настроить время работы реле по умолчанию
// задается в настройках вверху скетча
// функция нота по умолчанию,принимает один параметр (время до вызова следующей ноты)

void nota1(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота1 
	nota(RELE_K1, timtOfBlowUnicNota_1, _delayUntilNextNota);}

void nota2(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота2 
	nota(RELE_K2, timtOfBlowUnicNota_2, _delayUntilNextNota);}

void nota3(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота3 
	nota(RELE_K3, timtOfBlowUnicNota_3, _delayUntilNextNota);}

void nota4(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота4 
	nota(RELE_K4, timtOfBlowUnicNota_4, _delayUntilNextNota);}

void nota5(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота5 
	nota(RELE_K5, timtOfBlowUnicNota_5, _delayUntilNextNota);}

void nota6(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота6 
	nota(RELE_K6, timtOfBlowUnicNota_6, _delayUntilNextNota);}

void nota7(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота7 
	nota(RELE_K7, timtOfBlowUnicNota_7, _delayUntilNextNota);}

void nota8(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота8 
	nota(RELE_K8, timtOfBlowUnicNota_8, _delayUntilNextNota);}

void nota9(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота9 
	nota(RELE_K9, timtOfBlowUnicNota_9, _delayUntilNextNota);}

void nota10(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота10 
	nota(RELE_K10, timtOfBlowUnicNota_10, _delayUntilNextNota);}

void nota11(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота11 
	nota(RELE_K11, timtOfBlowUnicNota_11, _delayUntilNextNota);}

void nota12(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота12 
	nota(RELE_K12, timtOfBlowUnicNota_12, _delayUntilNextNota);}

void nota13(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота13 
	nota(RELE_K13, timtOfBlowUnicNota_13, _delayUntilNextNota);}

void nota14(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота14 
	nota(RELE_K14, timtOfBlowUnicNota_14, _delayUntilNextNota);}

void nota15(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота15 
	nota(RELE_K15, timtOfBlowUnicNota_15, _delayUntilNextNota);}

void nota16(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота16 
	nota(RELE_K16, timtOfBlowUnicNota_16, _delayUntilNextNota);}

void nota17(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота17 
	nota(RELE_K17, timtOfBlowUnicNota_17, _delayUntilNextNota);}

void nota18(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота18 
	nota(RELE_K18, timtOfBlowUnicNota_18, _delayUntilNextNota);}

void nota19(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота19 
	nota(RELE_K19, timtOfBlowUnicNota_19, _delayUntilNextNota);}

void nota20(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота20 
	nota(RELE_K20, timtOfBlowUnicNota_20, _delayUntilNextNota);}

void nota21(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота21 
	nota(RELE_K21, timtOfBlowUnicNota_21, _delayUntilNextNota);}

void nota22(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота22 
	nota(RELE_K22, timtOfBlowUnicNota_22, _delayUntilNextNota);}

void nota23(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота23 
	nota(RELE_K23, timtOfBlowUnicNota_23, _delayUntilNextNota);}

void nota24(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота24 
	nota(RELE_K24, timtOfBlowUnicNota_24, _delayUntilNextNota);}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// В ЭТОМ РАЗДЕЛЕ СОЗДАВАТЬ МЕЛОДИИ:

// функция мелодия состоит из последовательных вызовов функции нота. по сути является определенной мелодией

// мелодия EX1 пример мелодии с 1 набором нот
void melodiaEX1(){
	// здесь писать ноты
	nota(RELE_K11, 250, 2000);  // 1 нота, реле 11 (время включения реле 250мс, задержка до следующей ноты 2000мс)
	nota(RELE_K3, 280, 2000);   // 2 нота, реле 3 (время включения реле 280мс, задержка до следующей ноты 2000мс)
	nota(RELE_K2, 250, 3000);   // 3 нота, реле 2 (время включения реле 250мс, задержка до следующей ноты 3000мс)
	nota(RELE_K12, 300, 5000);  // 4 нота, реле 12 (время включения реле 300мс, задержка до следующей ноты 5000мс)
	nota(RELE_K1, 300, 2000);   // 5 нота, реле 1 (время включения реле 300мс, задержка до следующей ноты 2000мс)
}

// мелодия EX2 пример мелодии со 2 набором нот
// для написания мелодий лучше использовать второй набор нот. первый для настройки колоколов и создания уникальных нот
void melodiaEX2(){
	// здесь писать ноты
	nota11(2000);  // 1 нота, реле 11 (время включения реле задано в настройках нот, задержка до следующей ноты 2000мс)
	nota3(2000);   // 2 нота, реле 3 (время включения реле задано в настройках нот, задержка до следующей ноты 2000мс)
	nota2(3000);   // 3 нота, реле 2 (время включения реле задано в настройках нот, задержка до следующей ноты 3000мс)
	nota12(5000);  // 4 нота, реле 12 (время включения реле задано в настройках нот, задержка до следующей ноты 5000мс)
	nota1(2000);   // 5 нота, реле 1 (время включения реле задано в настройках нот, задержка до следующей ноты 2000мс)
}

// МЕЛОДИЯ КАЖДЫЙ ЧАС:

// мелодия1
void melodia1(){
	// здесь писать ноты
}

// мелодия2
void melodia2(){}

// мелодия3
void melodia3(){}

// мелодия4
void melodia4(){}

// мелодия5
void melodia5(){}

void melodia6(){}

// мелодия7
void melodia7(){}

// мелодия8
void melodia8(){}

// мелодия9
void melodia9(){}

// мелодия10
void melodia10(){}

// мелодия11
void melodia11(){}

// мелодия12
void melodia12(){}

// МЕЛОДИИ КАЖДЫЕ 15 минут:

// мелодия15
void melodia15(){}

// мелодия30
void melodia30(){}

// мелодия45
void melodia45(){}

// ДОПОЛНИТЕЛЬНЫЕ МЕЛОДИИ:

// мелодияRes1
void melodiaRes1(){}
// мелодияRes2
void melodiaRes2(){}
// мелодияRes3
void melodiaRes3(){}
// мелодияRes4
void melodiaRes4(){}
// мелодияRes5
void melodiaRes5(){}
// мелодияRes6
void melodiaRes6(){}
// мелодияRes7
void melodiaRes7(){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// В ЭТОМ РАЗДЕЛЕ НАСТРАИВАЕТСЯ РАСПИСАНИЕ МЕЛОДИЙ ПЕРЕЗВОНА И ЧАСЫ:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// часы:
void alarmFunction()  // Функция, вызываемая при срабатывании будильника
{
  isAlarm = true;     // Присваиваем значение "истина" переменной для обработки срабатывания будильника
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// расписание:
int chekPerezvon(){}

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

// ФУНКЦИЯ МЕНЮ:
void menu(){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

	// инициализация пользовательских символов
  	lcd.createChar(0, customCharBell0);
  	lcd.createChar(1, customCharNota1);
  	lcd.createChar(2, customCharLeftArrow2);
  	lcd.createChar(3, customCharRightArrow3);

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

	// инициализация комплектующих

	

    // терморегулятор
	#if DEF_PODOGREV_ENABLE != 0
	pinMode(DEF_TERMO_RELE_PIN, OUTPUT);
	#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
	melodiaEX1();
	delay (10000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
