////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LiquidCrystal.h>  // библиотека дисплея с кнопками

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// НАСТРОЙКА РЕЛЕ: если реле включается нолем поменять местами 1 и 0
#define HHH 1  // HIGH
#define LLL 0  // LOW

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// РАСПИНОВКА: для настройки изменять цифры, те что в конце, перед коментарием

// РАСПИНОВКА КОЛОКОЛОВ:
// для настройки изменять последнюю цифру(номер пина Arduino к которому подключен ударный механизм(язычек))
// значение идущее за #define является именем колокола. к которому нужно обращатся в программе для создания мелодий.
#define DEF_PIN_K1 1
#define DEF_PIN_K2 2
#define DEF_PIN_K3 3
#define DEF_PIN_K4 34
#define DEF_PIN_K5 35
#define DEF_PIN_K6 36
#define DEF_PIN_K7 37
#define DEF_PIN_K8 38
#define DEF_PIN_K9 39
#define DEF_PIN_K10 40
#define DEF_PIN_K11 11
#define DEF_PIN_K12 12
#define DEF_PIN_K13 13
#define DEF_PIN_K14 14
#define DEF_PIN_K15 15
#define DEF_PIN_K16 16
#define DEF_PIN_K17 17
#define DEF_PIN_K18 18
#define DEF_PIN_K19 19
#define DEF_PIN_K20 20
#define DEF_PIN_K21 21
#define DEF_PIN_K22 22
#define DEF_PIN_K23 23
#define DEF_PIN_K24 24

// РАСПИНОВКА КОМПЛЕКТУЮЩИХ:

// ДИСПЛЕЙ
#define LCD_LIGHT_PIN 10  // подсветка дисплея

// ЧАСЫ

// ТЕРМОРЕГУЛЯТОР

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// НАСТРОЙКИ ВРЕМЕННЫХ ЗАДЕРЖЕК ПО УМОЛЧАНИЮ:
#define DEF_TIME_OF_BLOW_TO_THE_BELL 300      // ВРЕМЯ УДАРА ЯЗЫЧКА В КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_DEL_UNT_NEXT_NOTA 3000      // ВРЕМЯ ДО ВЫЗОВА СЛЕДУЮЩЕЙ НОТЫ (ТАЙМАУТ МЕЖДУ НОТАМИ)

// ПРОЧИЕ НАСТРОЙКИ

#define DEF_PODOGREV_ENABLE 0  // ФУНКЦИЯ ПОДОГРЕВА БОКСА С УСТРОЙСТВОМ. ЕСЛИ 1 ПОДОГРЕВ ВКЛЮЧЕН, 0 ВЫКЛЮЧЕН.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// инициализация дисплея с кнопками
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// функция нота,принимает три параметра через запятую(имя колокола, время звучания ноты, время до вызова следующей ноты)
// по умолчанию: колокол 1, время звучания ноты 300мс, таймаут между нотами 3000мс
// пример использования функции:[nota(DEF_PIN_K7, 250, 2000);] 7 колокол, время ноты 250мс, таймаут до следующей ноты 2с

int nota(byte _kolokol = DEF_PIN_K1,
unsigned int _timeOfBlowToTheBell = DEF_TIME_OF_BLOW_TO_THE_BELL,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){

	digitalWrite(_kolokol, HHH);
	delay(_timeOfBlowToTheBell);
	digitalWrite(_kolokol, LLL);
	delay(_delayUntilNextNota);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// функция мелодия состоит из последовательных вызовов функции нота. по сути является определенной мелодией

// мелодия1
int melodia1(){
	nota(DEF_PIN_K11, 250, 2000);
	nota(DEF_PIN_K3, 280, 2000);
	nota(DEF_PIN_K2, 250, 3000);
	nota(DEF_PIN_K12, 300, 5000);
	nota(DEF_PIN_K1, 300, 2000);
	nota(DEF_PIN_K3, 280, 2000);
}

int melodia2(){}
int melodia3(){}
int melodia4(){}
int melodia5(){}
int melodia6(){}
int melodia7(){}
int melodia8(){}
int melodia9(){}
int melodia10(){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

	pinMode(DEF_PIN_K1, OUTPUT);
	pinMode(DEF_PIN_K2, OUTPUT);
	pinMode(DEF_PIN_K3, OUTPUT);
	pinMode(DEF_PIN_K4, OUTPUT);
	pinMode(DEF_PIN_K5, OUTPUT);
	pinMode(DEF_PIN_K6, OUTPUT);
	pinMode(DEF_PIN_K7, OUTPUT);
	pinMode(DEF_PIN_K8, OUTPUT);
	pinMode(DEF_PIN_K9, OUTPUT);
	pinMode(DEF_PIN_K10, OUTPUT);
	pinMode(DEF_PIN_K11, OUTPUT);
	pinMode(DEF_PIN_K12, OUTPUT);
	pinMode(DEF_PIN_K13, OUTPUT);
	pinMode(DEF_PIN_K14, OUTPUT);
	pinMode(DEF_PIN_K15, OUTPUT);
	pinMode(DEF_PIN_K16, OUTPUT);
	pinMode(DEF_PIN_K17, OUTPUT);
	pinMode(DEF_PIN_K18, OUTPUT);
	pinMode(DEF_PIN_K19, OUTPUT);
	pinMode(DEF_PIN_K20, OUTPUT);
	pinMode(DEF_PIN_K21, OUTPUT);
	pinMode(DEF_PIN_K22, OUTPUT);
	pinMode(DEF_PIN_K23, OUTPUT);
	pinMode(DEF_PIN_K24, OUTPUT);
}

void loop() {
	melodia1();
}
