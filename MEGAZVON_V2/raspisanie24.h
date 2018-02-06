////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

          https://github.com/ss2s/MEGAZVON24_MEGA2560
        \******************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//                                                                                                        ___     
//                                                                                                      /'___`\   
//        ___ ___       __      __        __      ____     __  __    ___     ___               __  __  /\_\ /\ \  
//      /' __` __`\   /'__`\  /'_ `\    /'__`\   /\_ ,`\  /\ \/\ \  / __`\ /' _ `\            /\ \/\ \ \/_/// /__ 
//      /\ \/\ \/\ \ /\  __/ /\ \L\ \  /\ \L\.\_ \/_/  /_ \ \ \_/ |/\ \L\ \/\ \/\ \           \ \ \_/ |   // /_\ \
//      \ \_\ \_\ \_\\ \____\\ \____ \ \ \__/.\_\  /\____\ \ \___/ \ \____/\ \_\ \_\           \ \___/   /\______/
//       \/_/\/_/\/_/ \/____/ \/___L\ \ \/__/\/_/  \/____/  \/__/   \/___/  \/_/\/_/  _______   \/__/    \/_____/ 
//                              /\____/                                              /\______\                    
//                              \_/__/                                               \/______/                     

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float g3231t;
bool flagManualPR = 0;
bool prazdnik = 1;

bool flag0m = 0;
bool flag15m = 0;
bool flag30m = 0;
bool flag45m = 0;
bool fllag12h = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DS3231 clock;           // Связываем объект clock с библиотекой DS3231
RTCDateTime DateTime;   // Определяем переменную DateTime, как описанную структурой RTCDateTime
RTCAlarmTime Alarm1;          // Определяем сущность структуры RTCAlarmTime (описанной в библиотеке DS3231)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void chekPerezvonEXT();
void chekVremya();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// температура ..
float get3231Temp(){
  byte tMSB, tLSB; 
  float temp3231;

  Wire.beginTransmission(0x68);
  Wire.write(0x11);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 2);

  if(Wire.available()) {
    tMSB = Wire.read(); //2's complement int portion
    tLSB = Wire.read(); //fraction portion

    temp3231 = (tMSB & B01111111); //do 2's math on Tmsb
    temp3231 += ( (tLSB >> 6) * 0.25 ); //only care about bits 7 & 8
  }
  else {
    //oh noes, no data!
  }

  return temp3231;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// функция отбивания времени колоколом
void timeBellRound(int _hours = 0){
	int tbrHours = _hours;
	int tbrKolokol = remapReleNameToNumber(RELE_HOUR_BLOW);
	unsigned long tbrKolokolDelay = findNotaDelayForKolokolNumber(tbrKolokol);
	unsigned int tbrHobDelay = HOUR_OF_BLOW_DELAY / 2;
	if(tbrHours > 12){
		tbrHours -= 12;
	}
	for(int i=0;i<tbrHours;i++){
		lcd.clear();
		lcd.setCursor(7,1);
		lcd.write(byte(5));
		lcd.print(i+1);
		delay(tbrHobDelay);
		enota(tbrKolokol, tbrKolokolDelay, tbrHobDelay);
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
		//g3231t = get3231Temp();
		//lcd.print(g3231t);

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
	if(prazdnik == 1 && flagBT == 0){
		lcd.setCursor(12,1);
		lcd.write(byte(2));
	}else if(flagBT == 1){
		lcd.setCursor(11,1);
		lcd.print("BT");
		lcd.write(byte(6));
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
	unsigned int bHobDelay = BUDNICNIY_DELAY_DEF / 2;

	lcd.clear();
	lcd.setCursor(2,0);
	lcd.write(byte(0));
	lcd.setCursor(4,0);
	lcd.print("budnichniy");
	delay(1000);

	while(bCikl){
		enota(bKolokol, tobBKolokol, bHobDelay);
		lcd.clear();
		lcd.setCursor(2,0);
		lcd.write(byte(0));
		lcd.setCursor(4,0);
		lcd.print("budnichniy");
		delay(bHobDelay);
		chekVremya();
		if(rminute == 0){
			bCikl = 0;
		}
	}

	lcd.clear();
	chekPerezvonEXT();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// РАСПИСАНИЕ:
void playMelodyByIndex(byte _index){
	byte index = _index;

	if(index == 0){
		return;
	}else if(index > 70){
		return;
	}else if(index > 0 && index <= 44){

		FmasMelodiaPlayFromFile(index);
	}else if(index > 44 && index <= 70){

		switch(index){

			case 45:
				melodiaEX1();
			break;
			case 46:
				melodiaEX2();
			break;
			case 47:
				melodiaEX3();
			break;
			case 48:
				melodiaRes1();  //
			break;
			case 49:
				melodiaRes2();
			break;
			case 50:
				melodiaRes3();
			break;
			case 51:
				melodiaRes4();
			break;
			case 52:
				melodiaRes5();
			break;
			case 53:
				melodiaRes6();
			break;
			case 54:
				melodiaRes7();
			break;
			case 55:
				melodia1();
			break;
			case 56:
				melodia2();
			break;
			case 57:
				melodia3();
			break;
			case 58:
				melodia4();
			break;
			case 59:
				melodia5();
			break;
			case 60:
				melodia6();
			break;
			case 61:
				melodia7();
			break;
			case 62:
				melodia8();
			break;
			case 63:
				melodia9();
			break;
			case 64:
				melodia10();
			break;
			case 65:
				melodia11();
			break;
			case 66:
				melodia12();
			break;
			case 67:
				melodia15();
			break;
			case 68:
				melodia30();
			break;
			case 69:
				melodia45();
			break;
			case 70:
				budnichniy();
			break;
		}
	}
}

void chekRaspisanie(int _CRhour, int _CRminute){
	int CRhour = _CRhour;
	int CRminute = _CRminute;
	int CRx;
	if(CRhour == 0){CRhour = 24;}

	if(rminute == 0){
		if(raspisanie[0] > 0){
			if(raspisanie[CRhour] > 0){
				playMelodyByIndex(raspisanie[CRhour]);
			}
		}
		if(raspisanie[29] > 0){
			if(raspisanie[CRhour] > 0){
				delay(1000);
				timeBellRound(CRhour);
			}
		}
	}
	if(rminute != 0){
		if(raspisanie[25] == 1){
			CRx = CRhour + 1;
			if(CRx > 24){CRx = 1;}
			if(raspisanie[CRhour] > 0 && raspisanie[CRx] > 0){
				if(rminute == 15){
					playMelodyByIndex(raspisanie[26]);
				}else if(rminute == 30){
					playMelodyByIndex(raspisanie[27]);
				}else if(rminute == 45){
					playMelodyByIndex(raspisanie[28]);
				}
			}
		}
	}
}

void chekPerezvonEXT(){
	chekVremya();
	if(flagManualPR == 0){
		if(rdayOfWeek>5){
			prazdnik = 1;
		}else{
			prazdnik = 0;
		}
	}
	if(rminute == 0 && flag0m == 0){
		flag0m  = 1;
 		flag15m = 0;
 		flag30m = 0;
 		flag45m = 0;
 		lcd.clear();
		lcd.setCursor(6,1);
		lcd.write(byte(1));
		lcd.setCursor(8,1);
		lcd.print(rhour);
		lcd.print("H");
		delay(1000);
		lcd.clear();
		if(rhour == 1){
			flagManualPR = 0;
			if(rdayOfWeek>5){prazdnik = 1;}else{prazdnik = 0;}
		}

 		chekRaspisanie(rhour, rminute);

 		rminute = 61;
		timeToDisplay();
	}else if(rminute == 15 && flag15m == 0){
		flag0m  = 0;
 		flag15m = 1;
 		flag30m = 0;
 		flag45m = 0;
 		lcd.clear();
		lcd.setCursor(6,1);
		lcd.write(byte(1));
		lcd.setCursor(8,1);
		lcd.print("15M");
		delay(1000);
		lcd.clear();

 		chekRaspisanie(rhour, rminute);

 		rminute = 61;
		timeToDisplay();
	}else if(rminute == 30 && flag30m == 0){
		flag0m  = 0;
 		flag15m = 0;
 		flag30m = 1;
 		flag45m = 0;
 		lcd.clear();
		lcd.setCursor(6,1);
		lcd.write(byte(1));
		lcd.setCursor(8,1);
		lcd.print("30M");
		delay(1000);
		lcd.clear();

 		chekRaspisanie(rhour, rminute);

 		rminute = 61;
		timeToDisplay();
	}else if(rminute == 45 && flag45m == 0){
		flag0m  = 0;
 		flag15m = 0;
 		flag30m = 0;
 		flag45m = 1;
 		lcd.clear();
		lcd.setCursor(6,1);
		lcd.write(byte(1));
		lcd.setCursor(8,1);
		lcd.print("45M");
		delay(1000);
		lcd.clear();

 		chekRaspisanie(rhour, rminute);

 		#if BUDNICNIY_ENABLE == 1
 		if(rhour == 8 && prazdnik == 0){
 			if(raspisanie[30] > 0){
 				playMelodyByIndex(raspisanie[31]);
 			}
 		}else{
 			rminute = 61;
			timeToDisplay();
 		}
 		#else
 			rminute = 61;
			timeToDisplay();
 		#endif
	}
}
