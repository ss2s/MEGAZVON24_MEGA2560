////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

          https://github.com/ss2s/MEGAZVON24_MEGA2560
        \******************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int rsecond;
int rminute = 61;  // Переменная для отслеживания изменения минут
int rhour;         // переменная для хранения часов
int rday;
int rdayOfWeek;
int rmonth;
int ryear;
String rdayofYear;
String temperatureDS3231; // переменная для хранения температуры
void timeToDisplay();
void playMelodyToIndex(byte _index);
void FmasMelodiaClear();
void FmasMelodiaPlay();
void playMelodyToIndex(byte _index);
void menuDraw();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ТЕХНИЧЕСКИЙ РАЗДЕЛ SDBT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// функции SDBT
#define TESTDELAY 0

#define DEFMaxMasSize 100
#define DEFRecordStop DEFMaxMasSize - 2
unsigned int masMelodiaMas [2][DEFMaxMasSize];

int recordCounter = 0;
int recordCounter2 = 0;

// 0 - flag
unsigned int masComboMasForPlay[9] = {0,0,0,0,0,0,0,0,0};
unsigned int masComboMas[9] = {0,0,0,0,0,0,0,0,0};
byte counterComboMas = 1;

bool flagBT = 0;
bool flagBTonof = 0;
bool flagRecord = 0;

bool flagPlayForMemory = 0;

unsigned long BTstartMill = 0UL;
unsigned long BTstopMill = 0UL;
unsigned long BTresMill = 0UL;

byte flagMenu = 1;
byte flagMenu2 = 1;

char b_d; // bluetooth data. входные данные с блютуз. переменная для хранения считывания первого управляющего байта
int bt_not = 0; // входные данные с блютуз. переменная для считывания хранения данных. формат: 1 - 24
int delayFor_d = 0;
int popravkaDelay = 15;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String indexToNameFileSD(int _index){
	byte index = _index;
	String name = "";
	name = "m";
	name += String(index);
	name += ".txt";
	return name;
}

void FmasComboMasClear(){
	for(int i=0; i <9; i++){
		masComboMas[i] = 0;
	}
}
void masComboMasForPlayClear(){
	for(int i=0; i <9; i++){
		masComboMasForPlay[i] = 0;
	}
}

void FmasMelodiaClear(){
	for(int i=0; i < DEFMaxMasSize; i++){
		masMelodiaMas[0][i] = 0;
		masMelodiaMas[1][i] = 0;
	}
}

void FmasMelodiaSetToFile(int _indexM){
	int indexM = _indexM;
	if(indexM < 1 || indexM > 40){
		return;
	}
	String dataString = "";
	for(int i=1; i < DEFMaxMasSize; i++){
		if(masMelodiaMas[0][i] > 0){
			dataString += "_";
			dataString += String(masMelodiaMas[0][i]);
			if(masMelodiaMas[1][i] > 0){
				dataString += "*";
				dataString += String(masMelodiaMas[1][i]);
				dataString += ".";
				dataString += "\n";
			}
		}else{
			dataString += "!";
			break;
		}
	}

	if (SD.exists(indexToNameFileSD(indexM))){
		SD.remove(indexToNameFileSD(indexM));
	}

	dataFile = SD.open(indexToNameFileSD(indexM), FILE_WRITE);
 	if (dataFile){

 	 	dataFile.println(dataString);
 	 	dataFile.close();
 	}else{

 	 	Serial.print("error opening file for write ");
 	 	Serial.println(indexToNameFileSD(indexM));
 	}

 	// dataFile = SD.open(indexToNameFileSD(indexM));
  // 	if (dataFile) {

  // 		Serial.println(indexToNameFileSD(indexM));
		// Serial.println("");

  //   	while (dataFile.available()) {
  //     		Serial.write(dataFile.read());
  //   	}
  //  		dataFile.close();
  // 	}else{
  //   	Serial.println("error opening file for read");
  // 	}
}

void FmasMelodiaGetForFile(int _indexM){
	int indexM = _indexM;
	FmasMelodiaClear();
	Serial. println(indexM);  ///////////////////////////////////////////////>>>>>>>>>

	if (SD.exists(indexToNameFileSD(indexM))){
			dataFile = SD.open(indexToNameFileSD(indexM));
  		if (dataFile) {
	
  			Serial.println(indexToNameFileSD(indexM));
			Serial.println("");
	
    		while (dataFile.available()) {
    	  		Serial.write(dataFile.read());
    		}
   			dataFile.close();
  		}else{
    		Serial.println("error opening file for read");
  		}
	}

	
}

void FmasMelodiaSetLoop(){
	bool cikl1 = 1;
	int mCounter = 0;
	Serial1.print("*l"); // отправка признака индикатора
    Serial1.println("R255G255B255*"); // отправка цвета индикатора
	Serial1.println("*t select the cell to save U or D *");
	while(cikl1){
		if(Serial1.available());
		b_d = Serial1.read();

		if(b_d == 'S'){
			break;
		}else if(b_d == 'U'){
			Serial1.print("*p"); // отправка звукового сигнала
    		mCounter --;
    		if(mCounter < 0){
    			mCounter = 40;
    		}
    		Serial1.print("*t");
    		if(mCounter != 0){
    			Serial1.print(indexToNameFileSD(mCounter));
    		}else{
    			Serial1.println("cancel");
    		}
    		Serial1.println("*");
		}else if(b_d == 'D'){
			Serial1.print("*p"); // отправка звукового сигнала
    		mCounter ++;
    		if(mCounter > 40){
    			mCounter = 0;
    		}
    		Serial1.print("*t");
    		if(mCounter != 0){
    			Serial1.print(indexToNameFileSD(mCounter));
    		}else{
    			Serial1.println("cancel");
    		}
    		Serial1.println("*");
		}
	}

	if(mCounter != 0){

		FmasMelodiaSetToFile(mCounter);
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R255G130B0*"); // отправка цвета индикатора
		Serial1.print("*t");
		Serial1.print(indexToNameFileSD(mCounter));
		Serial1.println(" SAVED OK*");
		Serial1.println("MELODY SAVED OK");
	}else{
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R255G130B0*"); // отправка цвета индикатора
		Serial1.println("*t CANCEL SAVE *");
	}
}

void sheduleSetLoop(){

}

void playMelodyForMemoryLoop(){
	bool cikl1 = 1;
	int mCounter = 0;
	Serial1.print("*l"); // отправка признака индикатора
    Serial1.println("R0G255B0*"); // отправка цвета индикатора
    Serial1.println("*t PLAY FOR MEMORY MODE *"); // отправка строки меню
    Serial1.println("*s PLAY *");
    while(cikl1){
    	if(Serial1.available());
		b_d = Serial1.read();

		if(b_d == 'S'){
			break;
		}else if(b_d == 'U'){
			Serial1.print("*p"); // отправка звукового сигнала
    		mCounter --;
    		if(mCounter < 0){
    			mCounter = 70;
    		}
    		Serial1.print("*t");
    		if(mCounter != 0){
    			Serial1.print(indexToNameFileSD(mCounter));
    			Serial1.print(" PLAY");
    		}else{
    			Serial1.print("cancel");
    		}
    		Serial1.println("*");
		}else if(b_d == 'D'){
			Serial1.print("*p"); // отправка звукового сигнала
    		mCounter ++;
    		if(mCounter > 70){
    			mCounter = 0;
    		}
    		Serial1.print("*t");
    		if(mCounter != 0){
    			Serial1.print(indexToNameFileSD(mCounter));
    			Serial1.print(" PLAY");
    		}else{
    			Serial1.print("cancel");
    		}
    		Serial1.println("*");
		}
    }

    if(mCounter != 0){

		Serial1.print("*t");
		Serial1.print(indexToNameFileSD(mCounter));
		Serial1.println(" PLAYED*");
		playMelodyToIndex(mCounter);
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R0G150B150*"); // отправка цвета индикатора
		Serial1.println("MELODY PLAY OK");
	}else{
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R0G150B150*"); // отправка цвета индикатора
		Serial1.println("*t CANCEL PLAY *");
	}
	menuDraw();
}

void FmasMelodiaPlay(){
	for(int i=1; i < DEFMaxMasSize; i++){
		if(masMelodiaMas[0][i] == 0){
			break;
		}
		if(masMelodiaMas[1][i] > 0){
			if(masComboMasForPlay[0] == 0){
				nota(masMelodiaMas[0][i], masMelodiaMas[1][i]);
			}else{
				masComboMasForPlay[counterComboMas] = masMelodiaMas[0][i];
				if(counterComboMas == 2){
					combo2(masComboMasForPlay[1], masComboMasForPlay[2], masMelodiaMas[1][i]);
				}else if(counterComboMas == 3){
					combo3(masComboMasForPlay[1], masComboMasForPlay[2] ,masComboMasForPlay[3], masMelodiaMas[1][i]);
				}else if(counterComboMas == 4){
					combo4(masComboMasForPlay[1], masComboMasForPlay[2], masComboMasForPlay[3], masComboMasForPlay[4], masMelodiaMas[1][i]);
				}else if(counterComboMas == 5){
					combo5(masComboMasForPlay[1], masComboMasForPlay[2], masComboMasForPlay[3], masComboMasForPlay[4], masComboMasForPlay[5], masMelodiaMas[1][i]);
				}else if(counterComboMas == 6){
					combo6(masComboMasForPlay[1], masComboMasForPlay[2], masComboMasForPlay[3], masComboMasForPlay[4], masComboMasForPlay[5], masComboMasForPlay[6], masMelodiaMas[1][i]);
				}else if(counterComboMas == 7){
					combo7(masComboMasForPlay[1], masComboMasForPlay[2], masComboMasForPlay[3], masComboMasForPlay[4], masComboMasForPlay[5], masComboMasForPlay[6], masComboMasForPlay[7], masMelodiaMas[1][i]);
				}else if(counterComboMas == 8){
					combo8(masComboMasForPlay[1], masComboMasForPlay[2], masComboMasForPlay[3], masComboMasForPlay[4], masComboMasForPlay[5], masComboMasForPlay[6], masComboMasForPlay[7], masComboMasForPlay[8], masMelodiaMas[1][i]);
				}
				counterComboMas = 1;
				masComboMasForPlay[0] = 0;
				masComboMasForPlayClear();
			}
		}else{
			if(masComboMasForPlay[0] == 0){masComboMasForPlay[0] = 1;}
			masComboMasForPlay[counterComboMas] = masMelodiaMas[0][i];
			counterComboMas ++;
			if(counterComboMas > 8){counterComboMas = 8;}
		}
	}

	rminute = 61;
	timeToDisplay();
}

void FmasMelodiaPlayForFile(byte _indexM){
	byte indexM = _indexM;

	FmasMelodiaGetForFile(indexM);
	FmasMelodiaPlay();
	FmasMelodiaClear();
}


void menuDraw(){
	if(flagMenu == 1){
		Serial1.println("*s MEM *");
    	Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R0G150B150*"); // отправка цвета индикатора
    	Serial1.println("*t PEREZVON MODE *"); // отправка строки меню
    	Serial1.print("PRESS COLOR BUTTON TO PLAY. "); // отправка справочной информации
    	Serial1.print("SEND m AND NUMBER 1-70 FOR PLAY MELODY ON MEMORY. "); // отправка справочной информации
    	Serial1.print("SEND m1 TO PLAY MELODY m1. m2 TO PLAY m2... "); // отправка справочной информации
    	Serial1.println("PRESS M TO PLAY MELODY FOR MEMORY MODE"); // отправка справочной информации
	}else if(flagMenu == 2){
		Serial1.println("*s STOP *");
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R0G100B200*"); // отправка цвета индикатора
		Serial1.println("*t SERIAL PRINT MODE 1 *"); // отправка строки меню
		Serial1.println("PRESS COLOR BUTTON TO PLAY AND PRINT MELODY CODE FOR SERIAL MONITOR MODE 1. PRESS STOP TO STOP PRINT"); // отправка справочной информации
		Serial1.println("PLEASE CONNECT TO PC"); // отправка справочной информации
	}else if(flagMenu == 3){
		Serial1.println("*s STOP *");
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R0G50B250*"); // отправка цвета индикатора
		Serial1.println("*t SERIAL PRINT MODE 2 *"); // отправка строки меню
		Serial1.println("PRESS COLOR BUTTON TO PLAY AND PRINT MELODY CODE FOR SERIAL MONITOR 	MODE 2. PRESS STOP TO STOP PRINT"); // отправка справочной информации
		Serial1.println("PLEASE CONNECT TO PC"); // отправка справочной информации
	}else if(flagMenu == 4){
		Serial1.println("*s REC *");
    	Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R255G0B0*"); // отправка цвета индикатора
		Serial1.println("*t RECORD NEW MELODY. PRESS REC *"); // отправка строки меню
    	Serial1.println("PRESS REC TO START AND STOP TO STOP RECORDING"); // отправка справочной информации
    	Serial1.println("PRESS COLOR BUTTON TO PLAY AND RECORD NEW MELODY"); // отправка справочной информации
	}else if(flagMenu == 5){
		Serial1.println("*s PLAY *");
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R0G255B0*"); // отправка цвета индикатора
		Serial1.println("*t PLAY RECORDED MELODY. PRESS PLAY *"); // отправка строки меню
		Serial1.println("PRESS PLAY TO PLAY RECORDED MELODY"); // отправка справочной информации
	}else if(flagMenu == 6){
		Serial1.println("*s SAVE *");
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R255G130B0*"); // отправка цвета индикатора
		Serial1.println("*t SAVE RECORDED MELODY. PRESS SAVE *"); // отправка строки меню
		Serial1.println("PRESS SAVE TO SAVE RECORDED MELODY"); // отправка справочной информации
	}else if(flagMenu == 7){
		Serial1.println("*s OK *");
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R100G0B200*"); // отправка цвета индикатора
		Serial1.println("*t SHEDULE CONFIGURATION *"); // отправка строки меню
		Serial1.println("PRESS OK TO SETTING CONFIG SHEDULE"); // отправка справочной информации
		Serial1.println("NASTROYKA RASPISANIYA"); // отправка справочной информации
	}else if(flagMenu == 8){
		Serial1.println("*s EXIT *");
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R150G150B150*"); // отправка цвета индикатора
		Serial1.println("*t EXIT *"); // отправка строки меню
		Serial1.println("PRESS EXIT TO EXIT"); // отправка справочной информации
	}
}


void BTloop(){
	Serial1.print("*l"); // отправка признака индикатора
    Serial1.println("R255G255B255*"); // отправка цвета индикатора
    flagMenu = 1;
    menuDraw();

	while(1){

		if (Serial1.available()){
    		b_d = Serial1.read();  // считывает первый управляющий байт (символ'x') определяющий дальнейшие действия в переменную b_d
    
    		if (b_d == ' '){       // если k то нажата кнопка колокола
    	  		bt_not = Serial1.parseInt(); //  считывает число int в переменную bt_not до первого символа
    	  		counterComboMas = 1;
    	  		masComboMas[counterComboMas] = bt_not;
    	  		masComboMas[0] = bt_not;
    	  		while(1){
    	  			if (Serial1.available()){
    	  				b_d = Serial1.read();
    	  				if(b_d == ' '){
    	  					counterComboMas ++;
    	  					masComboMas[counterComboMas] = Serial1.parseInt();
    	  				}
    	  				else if(b_d == '.'){




    	  					// 1
    	  					if(flagMenu == 1){  // здесь отслеживание флага меню
    	  						if(counterComboMas == 1){
    	  							nota(masComboMas[1], TESTDELAY);
    	  						}
    	  						else if(counterComboMas == 2){
    	  							combo2(masComboMas[1], masComboMas[2], TESTDELAY);
    	  						}
    	  						else if(counterComboMas == 3){
    	  							combo3(masComboMas[1], masComboMas[2], masComboMas[3], TESTDELAY);
    	  						}
    	  						else if(counterComboMas == 4){
    	  							combo4(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], TESTDELAY);
    	  						}
    	  						else if(counterComboMas == 5){
    	  							combo5(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], TESTDELAY);
    	  						}
    	  						else if(counterComboMas == 6){
    	  							combo6(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], TESTDELAY);
    	  						}
    	  						else if(counterComboMas == 7){
    	  							combo7(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], TESTDELAY);
    	  						}
    	  						else if(counterComboMas == 8){
    	  							combo8(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], masComboMas[8], TESTDELAY);
    	  						}




    	  						// 2
    	  					}else if(flagMenu == 2){
    	  						if(counterComboMas == 1){
    	  							BTstopMill = millis();
    	  							nota(masComboMas[1], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("nota(");
    	  							Serial.print(bt_not);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 2){
    	  							BTstopMill = millis();
    	  							combo2(masComboMas[1], masComboMas[2], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 3){
    	  							BTstopMill = millis();
    	  							combo3(masComboMas[1], masComboMas[2], masComboMas[3], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 4){
    	  							BTstopMill = millis();
    	  							combo4(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 5){
    	  							BTstopMill = millis();
    	  							combo5(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[5]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 6){
    	  							BTstopMill = millis();
    	  							combo6(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[5]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[6]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 7){
    	  							BTstopMill = millis();
    	  							combo7(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[5]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[6]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[7]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 8){
    	  							BTstopMill = millis();
    	  							combo8(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], masComboMas[8], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[5]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[6]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[7]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[8]);
    	  							Serial.print(", ");
    	  						}




    	  						// 3
    	  					}else if(flagMenu == 3){
    	  						if(counterComboMas == 1){
    	  							BTstopMill = millis();
    	  							nota(masComboMas[1], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("nota(");
    	  							Serial.print(bt_not);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 2){
    	  							BTstopMill = millis();
    	  							combo2(masComboMas[1], masComboMas[2], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 3){
    	  							BTstopMill = millis();
    	  							combo3(masComboMas[1], masComboMas[2], masComboMas[3], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 4){
    	  							BTstopMill = millis();
    	  							combo4(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 5){
    	  							BTstopMill = millis();
    	  							combo5(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[5]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 6){
    	  							BTstopMill = millis();
    	  							combo6(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[5]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[6]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 7){
    	  							BTstopMill = millis();
    	  							combo7(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[5]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[6]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[7]);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 8){
    	  							BTstopMill = millis();
    	  							combo8(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], masComboMas[8], TESTDELAY);
    	  							BTresMill = BTstopMill - BTstartMill;
    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(");");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print("combo");
    	  							Serial.print(counterComboMas);
    	  							Serial.print("(");
    	  							Serial.print(masComboMas[1]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[2]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[3]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[4]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[5]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[6]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[7]);
    	  							Serial.print(",");
    	  							Serial.print(masComboMas[8]);
    	  							Serial.print(", ");
    	  						}




    	  						// 4
    	  					}else if(flagMenu == 4){

    	  						if(flagRecord == 1){

    	  							if(counterComboMas == 1){
    	  								BTstopMill = millis();
    	  								nota(masComboMas[1], TESTDELAY);

    	  								masMelodiaMas[0][recordCounter] = masComboMas[1];

    	  								BTresMill = BTstopMill - BTstartMill;
    	  								if(BTresMill != BTstopMill){
    	  									BTresMill -= popravkaDelay;
    	  									recordCounter2 = recordCounter - counterComboMas;
    	  									if(recordCounter2 > 0){
    	  										masMelodiaMas[1][recordCounter2] = BTresMill;
    	  									}
    	  								}
    	  								BTstartMill = millis();

    	  								recordCounter ++;
    	  							}
    	  							else if(counterComboMas == 2){
    	  								BTstopMill = millis();
    	  								combo2(masComboMas[1], masComboMas[2], TESTDELAY);

    	  								masMelodiaMas[0][recordCounter] = masComboMas[1];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[2];

    	  								BTresMill = BTstopMill - BTstartMill;
    	  								if(BTresMill != BTstopMill){
    	  									BTresMill -= popravkaDelay;
    	  									recordCounter2 = recordCounter - counterComboMas;
    	  									masMelodiaMas[1][recordCounter2] = BTresMill;
    	  								}
    	  								BTstartMill = millis();
    	  								
    	  								recordCounter ++;
    	  							}
    	  							else if(counterComboMas == 3){
    	  								BTstopMill = millis();
    	  								combo3(masComboMas[1], masComboMas[2], masComboMas[3], TESTDELAY);

    	  								masMelodiaMas[0][recordCounter] = masComboMas[1];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[2];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[3];

    	  								BTresMill = BTstopMill - BTstartMill;
    	  								if(BTresMill != BTstopMill){
    	  									BTresMill -= popravkaDelay;
    	  									recordCounter2 = recordCounter - counterComboMas;
    	  									masMelodiaMas[1][recordCounter2] = BTresMill;
    	  								}
    	  								BTstartMill = millis();
    	  								
    	  								recordCounter ++;
    	  							}
    	  							else if(counterComboMas == 4){
    	  								BTstopMill = millis();
    	  								combo4(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], TESTDELAY);

    	  								masMelodiaMas[0][recordCounter] = masComboMas[1];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[2];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[3];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[4];

    	  								BTresMill = BTstopMill - BTstartMill;
    	  								if(BTresMill != BTstopMill){
    	  									BTresMill -= popravkaDelay;
    	  									recordCounter2 = recordCounter - counterComboMas;
    	  									masMelodiaMas[1][recordCounter2] = BTresMill;
    	  								}
    	  								BTstartMill = millis();
    	  								
    	  								recordCounter ++;
    	  							}
    	  							else if(counterComboMas == 5){
    	  								BTstopMill = millis();
    	  								combo5(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], TESTDELAY);

    	  								masMelodiaMas[0][recordCounter] = masComboMas[1];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[2];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[3];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[4];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[5];

    	  								BTresMill = BTstopMill - BTstartMill;
    	  								if(BTresMill != BTstopMill){
    	  									BTresMill -= popravkaDelay;
    	  									recordCounter2 = recordCounter - counterComboMas;
    	  									masMelodiaMas[1][recordCounter2] = BTresMill;
    	  								}
    	  								BTstartMill = millis();
    	  								
    	  								recordCounter ++;
    	  							}
    	  							else if(counterComboMas == 6){
    	  								BTstopMill = millis();
    	  								combo6(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], TESTDELAY);
    	  								
    	  								masMelodiaMas[0][recordCounter] = masComboMas[1];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[2];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[3];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[4];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[5];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[6];

    	  								BTresMill = BTstopMill - BTstartMill;
    	  								if(BTresMill != BTstopMill){
    	  									BTresMill -= popravkaDelay;
    	  									recordCounter2 = recordCounter - counterComboMas;
    	  									masMelodiaMas[1][recordCounter2] = BTresMill;
    	  								}
    	  								BTstartMill = millis();
    	  								
    	  								recordCounter ++;
    	  							}
    	  							else if(counterComboMas == 7){
    	  								BTstopMill = millis();
    	  								combo7(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], TESTDELAY);

    	  								masMelodiaMas[0][recordCounter] = masComboMas[1];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[2];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[3];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[4];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[5];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[6];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[7];
    	  								
    	  								BTresMill = BTstopMill - BTstartMill;
    	  								if(BTresMill != BTstopMill){
    	  									BTresMill -= popravkaDelay;
    	  									recordCounter2 = recordCounter - counterComboMas;
    	  									masMelodiaMas[1][recordCounter2] = BTresMill;
    	  								}
    	  								BTstartMill = millis();

    	  								recordCounter ++;
    	  							}
    	  							else if(counterComboMas == 8){
    	  								BTstopMill = millis();
    	  								combo8(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], masComboMas[8], TESTDELAY);

    	  								masMelodiaMas[0][recordCounter] = masComboMas[1];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[2];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[3];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[4];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[5];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[6];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[7];
    	  								recordCounter ++;
    	  								masMelodiaMas[0][recordCounter] = masComboMas[8];

    	  								BTresMill = BTstopMill - BTstartMill;
    	  								if(BTresMill != BTstopMill){
    	  									BTresMill -= popravkaDelay;
    	  									recordCounter2 = recordCounter - counterComboMas;
    	  									masMelodiaMas[1][recordCounter2] = BTresMill;
    	  								}
    	  								BTstartMill = millis();

    	  								recordCounter ++;
    	  							}

    	  							if(recordCounter >= DEFRecordStop){
    	  								flagRecord = 0;
    	  								Serial1.println("*s REC *");
    									recordCounter2 = recordCounter - 1;
    									masMelodiaMas[1][recordCounter2] = 1000;
    									masMelodiaMas[0][recordCounter] = 0;
    	  								recordCounter = 0;
    									Serial1.print("*l"); // отправка признака индикатора
    									Serial1.println("R255G0B0*"); // отправка цвета индикатора
    	  							}
    	  						}
    	  						else if(flagRecord == 0){
    	  							
    	  						}





    	  					}else if(flagMenu == 5){

    	  					}else if(flagMenu == 6){

    	  					}else if(flagMenu == 7){

    	  					}
    	  					
    	  					counterComboMas = 1;
    	  					break;
    	  				}
    	  			}
    	  		}

    	  		rminute = 61;
				timeToDisplay();
    		}


    		else if (b_d == 'S'){  // селект
    			if(flagMenu == 1){
    				Serial1.print("*p"); // отправка звукового сигнала
    				flagPlayForMemory = 1;
    				if(flagPlayForMemory == 1){
    					playMelodyForMemoryLoop();
    					flagPlayForMemory = 0;
    				}
    			}else if(flagMenu == 2){
    				Serial1.print("*p"); // отправка звукового сигнала
    				Serial.println("1000);");
    				Serial.println("");
    				BTstartMill = 0;
    			}else if(flagMenu == 3){
    				Serial1.print("*p"); // отправка звукового сигнала
    			}else if(flagMenu == 4){
    				Serial1.print("*p"); // отправка звукового сигнала
    				flagRecord = !flagRecord;
    				if(flagRecord == 1){
    					Serial1.println("*s STOP *");
    					FmasMelodiaClear();
    					recordCounter = 1;
    					Serial1.print("*l"); // отправка признака строки меню
    					Serial1.println("R255G200B0*"); // отправка строки меню
    				}else if(flagRecord == 0){
    					Serial1.println("*s REC *");
    					recordCounter2 = recordCounter - 1;
    					masMelodiaMas[1][recordCounter2] = 1000;
    					masMelodiaMas[0][recordCounter] = 0;
    	  				recordCounter = 0;
    					Serial1.print("*l"); // отправка признака индикатора
    					Serial1.println("R255G0B0*"); // отправка цвета индикатора
    				}
    				BTstartMill = 0;
    			}else if(flagMenu == 5){
    				Serial1.print("*p"); // отправка звукового сигнала
    				FmasMelodiaPlay();
    			}else if (flagMenu == 6){
    				Serial1.print("*p"); // отправка звукового сигнала
    				FmasMelodiaSetLoop();
    			}else if(flagMenu == 7){
    				Serial1.print("*p"); // отправка звукового сигнала
    				sheduleSetLoop();
    			}else if(flagMenu == 8){
    				Serial1.print("*p"); // отправка звукового сигнала
    				flagBT = 0;
    				Serial1.println("*t EXIT OK. MEGAFON SHEDULE ACTIVE *");
    				Serial.println("x");
    				rminute = 61;
					timeToDisplay();
    				break;
    			}
    		}


    		else if (b_d == 'U'){
    			Serial1.print("*p"); // отправка звукового сигнала
    			flagMenu --;
    			if(flagMenu < 1){
    				flagMenu = 8;
    			}
    			menuDraw();
    		}


    		else if (b_d == 'D'){
    			Serial1.print("*p"); // отправка звукового сигнала
    			flagMenu ++;
    			if(flagMenu > 8){
    				flagMenu = 1;
    			}
    			menuDraw();
    		}


    		else if (b_d == 'm'){
    			playMelodyToIndex(Serial1.parseInt());  // усли в сериал отправить m1 то будет проиграна мелодия с индексом 1
    			rminute = 61;
				timeToDisplay();
    		}


    		else if(b_d == 'd'){
    			delayFor_d = Serial1.parseInt();
    			delay(delayFor_d);
    		}
  		}
	}
	Serial1.print("*l"); // отправка признака строки меню
    Serial1.println("R0G0B0*"); // отправка строки меню
    Serial1.println("EXIT OK"); // отправка строки меню
    Serial1.println("MEGAZVON ACTIVE"); // отправка строки меню
    Serial1.println("RASPISANIE RABOTAET"); // отправка строки меню
}
