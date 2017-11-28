////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

          https://github.com/ss2s/MEGAZVON24_MEGA2560
        \******************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool flagManualPR = 0;
bool flag0m = 0;
bool flag15m = 0;
bool flag30m = 0;
bool flag45m = 0;
bool fllag12h = 0;
bool prazdnik = 1;
int rsecond;
int rminute = 61;  // Переменная для отслеживания изменения минут
int rhour;         // переменная для хранения часов
int rday;
int rdayOfWeek;
int rmonth;
int ryear;
String rdayofYear;
String temperatureDS3231; // переменная для хранения температуры
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DS3231 clock;           // Связываем объект clock с библиотекой DS3231
RTCDateTime DateTime;   // Определяем переменную DateTime, как описанную структурой RTCDateTime
RTCAlarmTime Alarm1;          // Определяем сущность структуры RTCAlarmTime (описанной в библиотеке DS3231)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void chekVremya();
// функция отбивания времени колоколом
void timeBellRound(int _hours = 0){
	int tbrHours = _hours;
	int tbrNomerRele = remapReleNameToNumber(RELE_HOUR_BLOW);
	if(tbrHours > 12){
		tbrHours -= 12;
	}
	for(int i=0;i<tbrHours;i++){
		nota(tbrNomerRele, DEF_TIME_OF_BLOW_UNIC_NOTA_HOUR_OF_BLOW, HOUR_OF_BLOW_DELAY);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void timeToDisplay(){
	DateTime = clock.getDateTime();            // Считываем c часов текущие значения даты и времени в сущность DateTime
	if (int(DateTime.minute) != rminute){// Если текущее значение минут отличается от значения в переменной отслеживания
    	rminute = int(DateTime.minute);  //  Меняем значение в переменной отслеживания минут на текущее
		lcd.clear();
		lcd.print(clock.dateFormat("d.m.Y H:i", DateTime));
		lcd.setCursor(0,1);
		lcd.print("temp ");
		lcd.print(String(clock.readTemperature()));

		chekVremya();
		lcd.setCursor(15,1);
		lcd.print(rdayOfWeek);
		if(flagManualPR == 0){
		if(rdayOfWeek>5){
			prazdnik = 1;
		}else{
			prazdnik = 0;
		}
	}
		
	}
	if(prazdnik == 1){
		lcd.setCursor(12,1);
		lcd.write(byte(2));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// часы: время
void chekVremya(){
	DateTime = clock.getDateTime();  // Считываем c часов текущие значения даты и времени в сущность DateTime
	rsecond = int(DateTime.second);
	rminute = int(DateTime.minute);  //  Меняем значение в переменной отслеживания минут на текущее
	rhour = int(DateTime.hour);
	rday = int(DateTime.day);
	rdayOfWeek = int(DateTime.dayOfWeek);
	rmonth = int(DateTime.month);
	ryear = int(DateTime.year);
	rdayofYear = clock.dateFormat("z", DateTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void budnichniy(){  // будничный колокол

	bool bCikl = 1;
	int bKolokol = remapReleNameToNumber(RELE_BUDNICNIY);
	unsigned long tobBKolokol = findNotaDelayForKolokolNumber(bKolokol);

	lcd.clear();
	lcd.setCursor(2,0);
	lcd.write(byte(0));
	lcd.setCursor(4,0);
	lcd.print("budnicniy");

	while(bCikl){
		nota(bCikl, tobBKolokol, 3000);
		chekVremya();
		if(rminute == 0){
			bCikl = 0;
		}
	}

	lcd.clear();
	chekPerezvon();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// РАСПИСАНИЕ:

void chekPerezvon(){
	chekVremya();
	if(flagManualPR == 0){
		if(rdayOfWeek>5){
			prazdnik = 1;
		}else{
			prazdnik = 0;
		}
	}
	if(rminute == 0 && flag0m == 0){
		flag0m = 1;
 		flag15m = 0;
 		flag30m = 0;
 		flag45m = 0;

		if(rhour == 1){
			flagManualPR = 0;
			if(rdayOfWeek>5){prazdnik = 1;}else{prazdnik = 0;}
		}else if(rhour == 2){

		}else if(rhour == 3){

		}else if(rhour == 4){

		}else if(rhour == 5){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 6){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 7){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 8){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 9){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 10){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 11){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 12){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 13){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 14){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 15){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 16){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 17){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 18){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 19){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 20){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 21){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 22){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 23){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}else if(rhour == 0){
			melodiaEX3();
			delay(1000);
			timeBellRound(rhour);  // функция отбивает время колоколом
		}
	}else if(rminute == 15 && flag15m == 0){
		flag0m = 0;
 		flag15m = 1;
 		flag30m = 0;
 		flag45m = 0;

 		melodia15();

	}else if(rminute == 30 && flag30m == 0){
		flag0m = 0;
 		flag15m = 0;
 		flag30m = 1;
 		flag45m = 0;

 		melodia30();

	}else if(rminute == 45 && flag45m == 0){
		flag0m = 0;
 		flag15m = 0;
 		flag30m = 0;
 		flag45m = 1;

 		melodia45();

 		#if BUDNICNIY_ENABLE == 1
 		if(rhour == 20 && prazdnik == 0){
 			budnichniy();
 		}
 		#endif
	}
}

int chasZvona(){}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// дополнительные функции расписания:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Date formats (Day)
------------------

 * d : Day of the month, 2 digits with leading zeros (01 to 31)
 * D : A textual representation of a day, three letters (Mon through Sun)
 * j : Day of the month without leading zeros (1 to 31)
 * l : A full textual representation of the day of the week (Sunday through Saturday)
 * N : ISO-8601 numeric representation of the day of the week (1 for Monday through 7 for Sunday)
 * S : English ordinal suffix for the day of the month, 2 characters (st, nd, rd or th. Works well with j)
 * w : Numeric representation of the day of the week (0 for Sunday through 6 for Saturday)
 * z : The day of the year (0 through 365)

Date formats (Month)
--------------------

 * F : A full textual representation of a month, such as January or March (January through December)
 * m : Numeric representation of a month, with leading zeros (01 through 12)
 * M : A short textual representation of a month, three letters (Jan through Dec)
 * n : Numeric representation of a month, without leading zeros (1 through 12)
 * t : Number of days in the given month (28 through 31)

Date formats (Year)
-------------------

 * L : Whether it's a leap year (1 if it is a leap year, 0 otherwise)
 * Y : A full numeric representation of a year, 4 digits (Examples: 1999 or 2003)
 * y : A two digit representation of a year (Examples: 99 or 03)

Date formats (Time)
-------------------

 * a : Lowercase Ante meridiem and Post meridiem (am or pm)
 * A : Uppercase Ante meridiem and Post meridiem (AM or PM)
 * g : 2-hour format of an hour without leading zeros (1 through 12)
 * G : 24-hour format of an hour without leading zeros (0 through 23)
 * h : 12-hour format of an hour with leading zeros (01 through 12)
 * H : 24-hour format of an hour with leading zeros (00 through 23)
 * i : Minutes with leading zeros (00 to 59)
 * s : Seconds, with leading zeros (00 through 59)

Dare formats (Full Date/Time)
-----------------------------

 * U : Seconds since the Unix Epoch (January 1 1970 00:00:00 GMT)



Alarm modes:
-----------------------------
  Set Alarm - Every second.
  DS3231_EVERY_SECOND is available only on Alarm1.
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 0, 0, 0, DS3231_EVERY_SECOND);

  Set Alarm - Every full minute.
  DS3231_EVERY_MINUTE is available only on Alarm2.
  setAlarm2(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm2(0, 0, 0, 0, DS3231_EVERY_MINUTE);
  
  Set Alarm1 - Every 20s in each minute
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 0, 0, 20, DS3231_MATCH_S);

  Set Alarm2 - Every 01m in each hour
  setAlarm2(Date or Day, Hour, Minute, Mode, Armed = true)
  clock.setAlarm2(0, 0, 1,     DS3231_MATCH_M);

  Set Alarm - Every 01m:25s in each hour
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 0, 1, 25, DS3231_MATCH_M_S);

  Set Alarm - Every 01h:10m:30s in each day
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(0, 1, 10, 30, DS3231_MATCH_H_M_S);

  Set Alarm - 07h:00m:00s in 25th day in month
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(25, 7, 0, 0, DS3231_MATCH_DT_H_M_S);

  Set Alarm - 10h:45m:30s in every Friday (1 - Mon, 7 - Sun)
  setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  clock.setAlarm1(5, 10, 40, 30, DS3231_MATCH_DY_H_M_S);
 */
