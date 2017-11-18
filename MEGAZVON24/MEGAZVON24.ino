////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

          https://github.com/ss2s/MEGAZVON24_MEGA2560
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
// ТЕРМОРЕГУЛЯТОР ENABLE:
#define DEF_PODOGREV_ENABLE 0  // ФУНКЦИЯ ПОДОГРЕВА БОКСА С УСТРОЙСТВОМ. ЕСЛИ 1 ПОДОГРЕВ ВКЛЮЧЕН, 0 ВЫКЛЮЧЕН.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include "res24.h"              // файл ресурсов

#include "config24.h"           // файл конфигурации
#include "melody24.h"           // файл с мелодиями

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"            // Arduino lib
//#include <LiquidCrystal.h>      // библиотека дисплея с кнопками

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
String temperatureDS3231; // переменная для хранения температуры
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
// здесь была настройка нот* сейчас в файле melody24.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// // инициализация дисплея с кнопками настройки в файле конфигурации
// LiquidCrystal lcd(DEF_LCD_INIT_PIN);

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
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// здесь были функции нот и мелодии* сейчас в файле melody24.h
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// В ЭТОМ РАЗДЕЛЕ НАСТРАИВАЕТСЯ РАСПИСАНИЕ МЕЛОДИЙ ПЕРЕЗВОНА И ЧАСЫ:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// часы: будильник
void alarmFunction()  // Функция, вызываемая при срабатывании будильника
{
  isAlarm = true;     // Присваиваем значение "истина" переменной для обработки срабатывания будильника
}

// часы: время
void chekVremya(){
	DateTime = clock.getDateTime();  // Считываем c часов текущие значения даты и времени в сущность DateTime
  	Alarm1 = clock.getAlarm1();  // Считываем c первого будильника текущие настройки даты и времени в сущность Alarm1
  	Serial.println(clock.dateFormat("d.m.Y H:i:s - l   ", DateTime));               // Определяем формат вывода даты
  	Serial.println("Temperature: " + String(clock.readTemperature()));              // Выводим значения температуры
  	Serial.println("Alarm: " + String(clock.dateFormat("__ __:__:s", Alarm1)));     // Выводим настройки будильника                                
  	Serial.println();  // Перевод строки

  	if (isAlarm){             // Если поступил сигнал о сработке будильника

    	isAlarm = false;      // меняем состояние события обработки индикатора на "false"
    	clock.clearAlarm1();  // Очищаем состояние сработки будильника
  	} 

  	delay(1000);  // Задержка в 1 секунду
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// расписание:
int chekPerezvon(){
	hours = DateTime.hour;
	minutes = DateTime.minute;
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

// ФУНКЦИЯ МЕНЮ:
void menu(){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  	pinMode(LED_BUILTIN, OUTPUT);  // фиксим 13 диод
	Serial.begin(9600);

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
	lcd.print("   MEGAZVON24");
	lcd.setCursor(2,1);
	lcd.write(byte(1));
	lcd.print(" melodiaEX2");
	delay(2000);

	// инициализация комплектующих

	// // часы:
	// // Инициализируем работу с объектом библиотеки DS3231
	// clock.begin();
	// // Определяем назначение вывода SQW (INT) для генерации прерываний при сработке будильников
 //    clock.enableOutput(false);
 //    // Устанавливаем время на часах, основываясь на времени компиляции скетча
	// clock.setDateTime(__DATE__, __TIME__);
	// // Установка времени вручную (Год, Месяц, День, Час, Минута, Секунда) ↓
	// //  clock.setDateTime(2017, 11, 15, 0, 0, 0);
	// //  setAlarm1(Дата или день, Час, Минута, Секунда, Режим)
	// // Устанавливаем первый будильник на срабатывание в 1 сек. каждой минуты. Режим DS3231_MATCH_S
 //  	clock.setAlarm1(0, 0, 0, 1, DS3231_MATCH_S);
 // 	// Задаем функцию для обработки прерывания 0 (на пине 2)                        
 //  	//attachInterrupt(0, alarmFunction, FALLING);
 //  	// часы end

	

    // терморегулятор
	#if DEF_PODOGREV_ENABLE != 0
	pinMode(DEF_TERMO_RELE_PIN, OUTPUT);
	#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

	melodiaEX2();

	lcd.clear();
	lcd.setCursor(2,1);
	lcd.write(byte(1));
	lcd.print(" melodiaEX2");

	delay(1000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
