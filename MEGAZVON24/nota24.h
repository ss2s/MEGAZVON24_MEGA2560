////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

          https://github.com/ss2s/MEGAZVON24_MEGA2560
        \******************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// НОТЫ ДЛЯ МЕЛОДИЙ

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Arduino.h"
#include "MEGAZVON24_CONFIG.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// ТЕХНИЧЕСКИЙ РАЗДЕЛ:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// переменные для работы с функцией millis();
unsigned long startMill = 1UL;
unsigned long currentMill = 1UL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  ВРЕМЕННЫЕ ЗАДЕРЖЕКИ ПО УМОЛЧАНИЮ: настройки вынесены в отдельный файл "MELODIA_ZVONA.h"

// для каждой ноты в отдельности, 2 набор нот
// настройка в файле "MELODIA_ZVONA.h"
unsigned long timtOfBlowUnicNota_1 = DEF_TIME_OF_BLOW_UNIC_NOTA_1;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 1 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_2 = DEF_TIME_OF_BLOW_UNIC_NOTA_2;   // ВРЕМЯ УДАРА ЯЗЫЧКА ВО 2 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_3 = DEF_TIME_OF_BLOW_UNIC_NOTA_3;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 3 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_4 = DEF_TIME_OF_BLOW_UNIC_NOTA_4;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 4 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_5 = DEF_TIME_OF_BLOW_UNIC_NOTA_5;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 5 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_6 = DEF_TIME_OF_BLOW_UNIC_NOTA_6;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 6 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_7 = DEF_TIME_OF_BLOW_UNIC_NOTA_7;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 7 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_8 = DEF_TIME_OF_BLOW_UNIC_NOTA_8;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 8 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_9 = DEF_TIME_OF_BLOW_UNIC_NOTA_9;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 9 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_10 = DEF_TIME_OF_BLOW_UNIC_NOTA_10;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 10 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_11 = DEF_TIME_OF_BLOW_UNIC_NOTA_11;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 11 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_12 = DEF_TIME_OF_BLOW_UNIC_NOTA_12;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 12 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_13 = DEF_TIME_OF_BLOW_UNIC_NOTA_13;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 13 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_14 = DEF_TIME_OF_BLOW_UNIC_NOTA_14;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 14 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_15 = DEF_TIME_OF_BLOW_UNIC_NOTA_15;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 15 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_16 = DEF_TIME_OF_BLOW_UNIC_NOTA_16;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 16 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_17 = DEF_TIME_OF_BLOW_UNIC_NOTA_17;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 17 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_18 = DEF_TIME_OF_BLOW_UNIC_NOTA_18;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 18 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_19 = DEF_TIME_OF_BLOW_UNIC_NOTA_19;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 19 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_20 = DEF_TIME_OF_BLOW_UNIC_NOTA_20;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 20 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_21 = DEF_TIME_OF_BLOW_UNIC_NOTA_21;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 21 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_22 = DEF_TIME_OF_BLOW_UNIC_NOTA_22;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 22 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_23 = DEF_TIME_OF_BLOW_UNIC_NOTA_23;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 23 КОЛОКОЛ (ВРЕМЯ НОТЫ)
unsigned long timtOfBlowUnicNota_24 = DEF_TIME_OF_BLOW_UNIC_NOTA_24;   // ВРЕМЯ УДАРА ЯЗЫЧКА В 24 КОЛОКОЛ (ВРЕМЯ НОТЫ)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// функция макс возвращает большее из двух чисел
unsigned long maxNumber(unsigned long _a, unsigned long _b){

	unsigned long maxN = 0;
	if (_a>_b){
		maxN = _a;
	}else{
		maxN = _b;
	}
	return maxN;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// функция возврата номера реле по имени
inline int remapReleNameToNumber(int _kolokolName){
	int kolokolNumber = _kolokolName;

	switch(_kolokolName){
		case RELE_K1:
		kolokolNumber = 1;
		break;
		case RELE_K2:
		kolokolNumber = 2;
		break;
		case RELE_K3:
		kolokolNumber = 3;
		break;
		case RELE_K4:
		kolokolNumber = 4;
		break;
		case RELE_K5:
		kolokolNumber = 5;
		break;
		case RELE_K6:
		kolokolNumber = 6;
		break;
		case RELE_K7:
		kolokolNumber = 7;
		break;
		case RELE_K8:
		kolokolNumber = 8;
		break;
		case RELE_K9:
		kolokolNumber = 9;
		break;
		case RELE_K10:
		kolokolNumber = 10;
		break;
		case RELE_K11:
		kolokolNumber = 11;
		break;
		case RELE_K12:
		kolokolNumber = 12;
		break;
		case RELE_K13:
		kolokolNumber = 13;
		break;
		case RELE_K14:
		kolokolNumber = 14;
		break;
		case RELE_K15:
		kolokolNumber = 15;
		break;
		case RELE_K16:
		kolokolNumber = 16;
		break;
		case RELE_K17:
		kolokolNumber = 17;
		break;
		case RELE_K18:
		kolokolNumber = 18;
		break;
		case RELE_K19:
		kolokolNumber = 19;
		break;
		case RELE_K20:
		kolokolNumber = 20;
		break;
		case RELE_K21:
		kolokolNumber = 21;
		break;
		case RELE_K22:
		kolokolNumber = 22;
		break;
		case RELE_K23:
		kolokolNumber = 23;
		break;
		case RELE_K24:
		kolokolNumber = 24;
		break;
	}

	return kolokolNumber;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// функция возврата имени реле по номеру
inline int remapReleNumberToName(int _kolokolNumber){
	int kolokolName = _kolokolNumber;

	switch(_kolokolNumber){
		case 1:
		kolokolName = RELE_K1;
		break;
		case 2:
		kolokolName = RELE_K2;
		break;
		case 3:
		kolokolName = RELE_K3;
		break;
		case 4:
		kolokolName = RELE_K4;
		break;
		case 5:
		kolokolName = RELE_K5;
		break;
		case 6:
		kolokolName = RELE_K6;
		break;
		case 7:
		kolokolName = RELE_K7;
		break;
		case 8:
		kolokolName = RELE_K8;
		break;
		case 9:
		kolokolName = RELE_K9;
		break;
		case 10:
		kolokolName = RELE_K10;
		break;
		case 11:
		kolokolName = RELE_K11;
		break;
		case 12:
		kolokolName = RELE_K12;
		break;
		case 13:
		kolokolName = RELE_K13;
		break;
		case 14:
		kolokolName = RELE_K14;
		break;
		case 15:
		kolokolName = RELE_K15;
		break;
		case 16:
		kolokolName = RELE_K16;
		break;
		case 17:
		kolokolName = RELE_K17;
		break;
		case 18:
		kolokolName = RELE_K18;
		break;
		case 19:
		kolokolName = RELE_K19;
		break;
		case 20:
		kolokolName = RELE_K20;
		break;
		case 21:
		kolokolName = RELE_K21;
		break;
		case 22:
		kolokolName = RELE_K22;
		break;
		case 23:
		kolokolName = RELE_K23;
		break;
		case 24:
		kolokolName = RELE_K24;
		break;
	}

	return kolokolName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// функция подбора задержки к колоколу по его номеру
unsigned long findNotaDelayForKolokolNumber(int _kolokolNumber = 0){
	unsigned long fDelay = DEF_TIME_OF_BLOW_TO_THE_BELL;

	switch(_kolokolNumber){
		case 1:
		fDelay = timtOfBlowUnicNota_1;
		break;
		case 2:
		fDelay = timtOfBlowUnicNota_2;
		break;
		case 3:
		fDelay = timtOfBlowUnicNota_3;
		break;
		case 4:
		fDelay = timtOfBlowUnicNota_4;
		break;
		case 5:
		fDelay = timtOfBlowUnicNota_5;
		break;
		case 6:
		fDelay = timtOfBlowUnicNota_6;
		break;
		case 7:
		fDelay = timtOfBlowUnicNota_7;
		break;
		case 8:
		fDelay = timtOfBlowUnicNota_8;
		break;
		case 9:
		fDelay = timtOfBlowUnicNota_9;
		break;
		case 10:
		fDelay = timtOfBlowUnicNota_10;
		break;
		case 11:
		fDelay = timtOfBlowUnicNota_11;
		break;
		case 12:
		fDelay = timtOfBlowUnicNota_12;
		break;
		case 13:
		fDelay = timtOfBlowUnicNota_13;
		break;
		case 14:
		fDelay = timtOfBlowUnicNota_14;
		break;
		case 15:
		fDelay = timtOfBlowUnicNota_15;
		break;
		case 16:
		fDelay = timtOfBlowUnicNota_16;
		break;
		case 17:
		fDelay = timtOfBlowUnicNota_17;
		break;
		case 18:
		fDelay = timtOfBlowUnicNota_18;
		break;
		case 19:
		fDelay = timtOfBlowUnicNota_19;
		break;
		case 20:
		fDelay = timtOfBlowUnicNota_20;
		break;
		case 21:
		fDelay = timtOfBlowUnicNota_21;
		break;
		case 22:
		fDelay = timtOfBlowUnicNota_22;
		break;
		case 23:
		fDelay = timtOfBlowUnicNota_23;
		break;
		case 24:
		fDelay = timtOfBlowUnicNota_24;
		break;
	}
	return fDelay;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// функция подбора задержки к колоколу по его имени
unsigned long findNotaDelayForKolokolName(int _kolokolName = 0){
	unsigned long fDelay = DEF_TIME_OF_BLOW_TO_THE_BELL;

	switch(_kolokolName){
		case RELE_K1:
		fDelay = timtOfBlowUnicNota_1;
		break;
		case RELE_K2:
		fDelay = timtOfBlowUnicNota_2;
		break;
		case RELE_K3:
		fDelay = timtOfBlowUnicNota_3;
		break;
		case RELE_K4:
		fDelay = timtOfBlowUnicNota_4;
		break;
		case RELE_K5:
		fDelay = timtOfBlowUnicNota_5;
		break;
		case RELE_K6:
		fDelay = timtOfBlowUnicNota_6;
		break;
		case RELE_K7:
		fDelay = timtOfBlowUnicNota_7;
		break;
		case RELE_K8:
		fDelay = timtOfBlowUnicNota_8;
		break;
		case RELE_K9:
		fDelay = timtOfBlowUnicNota_9;
		break;
		case RELE_K10:
		fDelay = timtOfBlowUnicNota_10;
		break;
		case RELE_K11:
		fDelay = timtOfBlowUnicNota_11;
		break;
		case RELE_K12:
		fDelay = timtOfBlowUnicNota_12;
		break;
		case RELE_K13:
		fDelay = timtOfBlowUnicNota_13;
		break;
		case RELE_K14:
		fDelay = timtOfBlowUnicNota_14;
		break;
		case RELE_K15:
		fDelay = timtOfBlowUnicNota_15;
		break;
		case RELE_K16:
		fDelay = timtOfBlowUnicNota_16;
		break;
		case RELE_K17:
		fDelay = timtOfBlowUnicNota_17;
		break;
		case RELE_K18:
		fDelay = timtOfBlowUnicNota_18;
		break;
		case RELE_K19:
		fDelay = timtOfBlowUnicNota_19;
		break;
		case RELE_K20:
		fDelay = timtOfBlowUnicNota_20;
		break;
		case RELE_K21:
		fDelay = timtOfBlowUnicNota_21;
		break;
		case RELE_K22:
		fDelay = timtOfBlowUnicNota_22;
		break;
		case RELE_K23:
		fDelay = timtOfBlowUnicNota_23;
		break;
		case RELE_K24:
		fDelay = timtOfBlowUnicNota_24;
		break;
	}
	return fDelay;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ТЕХНИЧЕСКИЙ РАЗДЕЛ:

// 1 НАБОР НОТ
// функция нота,принимает три параметра через запятую(номер колокола, время звучания ноты, время до вызова следующей ноты)
// по умолчанию: колокол 1, время звучания ноты 300мс, таймаут между нотами 3000мс
// пример использования функции:[nota(7, 250, 2000);] 7 колокол, время ноты 250мс, таймаут до следующей ноты 2с

int nota(int _kolokol = RELE_K1,
unsigned long _timeOfBlowToTheBell = DEF_TIME_OF_BLOW_TO_THE_BELL,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){

	_kolokol = remapReleNumberToName(_kolokol);

	digitalWrite(_kolokol, HHH);
	delay(_timeOfBlowToTheBell);
	digitalWrite(_kolokol, LLL);
	delay(_delayUntilNextNota);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 2 НАБОР НОТ
// НОТЫ ПО УМОЛЧАНИЮ: для каждой ноты можно настроить время работы реле по умолчанию
// задается в настройках вверху скетча
// функция нота по умолчанию,принимает один параметр (время до вызова следующей ноты)

void nota1(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота1 
	nota(1, timtOfBlowUnicNota_1, _delayUntilNextNota);}

void nota2(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота2 
	nota(2, timtOfBlowUnicNota_2, _delayUntilNextNota);}

void nota3(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота3 
	nota(3, timtOfBlowUnicNota_3, _delayUntilNextNota);}

void nota4(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота4 
	nota(4, timtOfBlowUnicNota_4, _delayUntilNextNota);}

void nota5(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота5 
	nota(5, timtOfBlowUnicNota_5, _delayUntilNextNota);}

void nota6(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота6 
	nota(6, timtOfBlowUnicNota_6, _delayUntilNextNota);}

void nota7(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота7 
	nota(7, timtOfBlowUnicNota_7, _delayUntilNextNota);}

void nota8(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота8 
	nota(8, timtOfBlowUnicNota_8, _delayUntilNextNota);}

void nota9(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота9 
	nota(9, timtOfBlowUnicNota_9, _delayUntilNextNota);}

void nota10(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота10 
	nota(10, timtOfBlowUnicNota_10, _delayUntilNextNota);}

void nota11(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота11 
	nota(11, timtOfBlowUnicNota_11, _delayUntilNextNota);}

void nota12(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота12 
	nota(12, timtOfBlowUnicNota_12, _delayUntilNextNota);}

void nota13(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота13 
	nota(13, timtOfBlowUnicNota_13, _delayUntilNextNota);}

void nota14(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота14 
	nota(14, timtOfBlowUnicNota_14, _delayUntilNextNota);}

void nota15(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота15 
	nota(15, timtOfBlowUnicNota_15, _delayUntilNextNota);}

void nota16(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота16 
	nota(16, timtOfBlowUnicNota_16, _delayUntilNextNota);}

void nota17(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота17 
	nota(17, timtOfBlowUnicNota_17, _delayUntilNextNota);}

void nota18(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота18 
	nota(18, timtOfBlowUnicNota_18, _delayUntilNextNota);}

void nota19(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота19 
	nota(19, timtOfBlowUnicNota_19, _delayUntilNextNota);}

void nota20(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота20 
	nota(20, timtOfBlowUnicNota_20, _delayUntilNextNota);}

void nota21(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота21 
	nota(21, timtOfBlowUnicNota_21, _delayUntilNextNota);}

void nota22(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота22 
	nota(22, timtOfBlowUnicNota_22, _delayUntilNextNota);}

void nota23(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота23 
	nota(23, timtOfBlowUnicNota_23, _delayUntilNextNota);}

void nota24(unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA){  // нота24 
	nota(24, timtOfBlowUnicNota_24, _delayUntilNextNota);}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// КОМБО НОТЫ: для одновременного вызова нескольких колоколов принимает параметры номера колоколов + задержка до сл. нот

void combo2(
int _kolokol1 = 1,
int _kolokol2 = 2,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA)
{
	_kolokol1 = remapReleNumberToName(_kolokol1);
	_kolokol2 = remapReleNumberToName(_kolokol2);

	digitalWrite(_kolokol1,HHH);
	digitalWrite(_kolokol2,HHH);

	while(1){

	}

	delay(DEF_TIME_OF_BLOW_TO_THE_BELL);
	digitalWrite(_kolokol1,LLL);
	digitalWrite(_kolokol2,LLL);

	delay(_delayUntilNextNota);
}

void combo3(
int _kolokol1 = 1,
int _kolokol2 = 2,
int _kolokol3 = 3,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA)
{
	_kolokol1 = remapReleNumberToName(_kolokol1);
	_kolokol2 = remapReleNumberToName(_kolokol2);
	_kolokol3 = remapReleNumberToName(_kolokol3);

	digitalWrite(_kolokol1, HHH);
	digitalWrite(_kolokol2, HHH);
	digitalWrite(_kolokol3, HHH);

	delay(DEF_TIME_OF_BLOW_TO_THE_BELL);
	digitalWrite(_kolokol1, LLL);
	digitalWrite(_kolokol2, LLL);
	digitalWrite(_kolokol3, LLL);

	delay(_delayUntilNextNota);
}

void combo4(
int _kolokol1 = 1,
int _kolokol2 = 2,
int _kolokol3 = 3,
int _kolokol4 = 4,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA)
{
	_kolokol1 = remapReleNumberToName(_kolokol1);
	_kolokol2 = remapReleNumberToName(_kolokol2);
	_kolokol3 = remapReleNumberToName(_kolokol3);
	_kolokol4 = remapReleNumberToName(_kolokol4);

	digitalWrite(_kolokol1, HHH);
	digitalWrite(_kolokol2, HHH);
	digitalWrite(_kolokol3, HHH);
	digitalWrite(_kolokol4, HHH);

	delay(DEF_TIME_OF_BLOW_TO_THE_BELL);
	digitalWrite(_kolokol1, LLL);
	digitalWrite(_kolokol2, LLL);
	digitalWrite(_kolokol3, LLL);
	digitalWrite(_kolokol4, LLL);

	delay(_delayUntilNextNota);
}

void combo5(
int _kolokol1 = 1,
int _kolokol2 = 2,
int _kolokol3 = 3,
int _kolokol4 = 4,
int _kolokol5 = 5,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA)
{
	_kolokol1 = remapReleNumberToName(_kolokol1);
	_kolokol2 = remapReleNumberToName(_kolokol2);
	_kolokol3 = remapReleNumberToName(_kolokol3);
	_kolokol4 = remapReleNumberToName(_kolokol4);
	_kolokol5 = remapReleNumberToName(_kolokol5);

	digitalWrite(_kolokol1, HHH);
	digitalWrite(_kolokol2, HHH);
	digitalWrite(_kolokol3, HHH);
	digitalWrite(_kolokol4, HHH);
	digitalWrite(_kolokol5, HHH);

	delay(DEF_TIME_OF_BLOW_TO_THE_BELL);
	digitalWrite(_kolokol1, LLL);
	digitalWrite(_kolokol2, LLL);
	digitalWrite(_kolokol3, LLL);
	digitalWrite(_kolokol4, LLL);
	digitalWrite(_kolokol5, LLL);

	delay(_delayUntilNextNota);
}

void combo6(
int _kolokol1 = 1,
int _kolokol2 = 2,
int _kolokol3 = 3,
int _kolokol4 = 4,
int _kolokol5 = 5,
int _kolokol6 = 6,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA)
{
	_kolokol1 = remapReleNumberToName(_kolokol1);
	_kolokol2 = remapReleNumberToName(_kolokol2);
	_kolokol3 = remapReleNumberToName(_kolokol3);
	_kolokol4 = remapReleNumberToName(_kolokol4);
	_kolokol5 = remapReleNumberToName(_kolokol5);
	_kolokol6 = remapReleNumberToName(_kolokol6);

	digitalWrite(_kolokol1, HHH);
	digitalWrite(_kolokol2, HHH);
	digitalWrite(_kolokol3, HHH);
	digitalWrite(_kolokol4, HHH);
	digitalWrite(_kolokol5, HHH);
	digitalWrite(_kolokol6, HHH);

	delay(DEF_TIME_OF_BLOW_TO_THE_BELL);
	digitalWrite(_kolokol1, LLL);
	digitalWrite(_kolokol2, LLL);
	digitalWrite(_kolokol3, LLL);
	digitalWrite(_kolokol4, LLL);
	digitalWrite(_kolokol5, LLL);
	digitalWrite(_kolokol6, LLL);

	delay(_delayUntilNextNota);
}

void combo7(
int _kolokol1 = 1,
int _kolokol2 = 2,
int _kolokol3 = 3,
int _kolokol4 = 4,
int _kolokol5 = 5,
int _kolokol6 = 6,
int _kolokol7 = 7,
unsigned int _delayUntilNextNota = DEF_DEL_UNT_NEXT_NOTA)
{
	_kolokol1 = remapReleNumberToName(_kolokol1);
	_kolokol2 = remapReleNumberToName(_kolokol2);
	_kolokol3 = remapReleNumberToName(_kolokol3);
	_kolokol4 = remapReleNumberToName(_kolokol4);
	_kolokol5 = remapReleNumberToName(_kolokol5);
	_kolokol6 = remapReleNumberToName(_kolokol6);
	_kolokol7 = remapReleNumberToName(_kolokol7);

	digitalWrite(_kolokol1, HHH);
	digitalWrite(_kolokol2, HHH);
	digitalWrite(_kolokol3, HHH);
	digitalWrite(_kolokol4, HHH);
	digitalWrite(_kolokol5, HHH);
	digitalWrite(_kolokol6, HHH);
	digitalWrite(_kolokol7, HHH);

	delay(DEF_TIME_OF_BLOW_TO_THE_BELL);
	digitalWrite(_kolokol1, LLL);
	digitalWrite(_kolokol2, LLL);
	digitalWrite(_kolokol3, LLL);
	digitalWrite(_kolokol4, LLL);
	digitalWrite(_kolokol5, LLL);
	digitalWrite(_kolokol6, LLL);
	digitalWrite(_kolokol7, LLL);

	delay(_delayUntilNextNota);
}