
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
void playMelodyByIndex(byte _index);
void FmasMelodiaClear();
void FmasMelodiaPlay();
void playMelodyByIndex(byte _index);
void menuDraw();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ТЕХНИЧЕСКИЙ РАЗДЕЛ SDBT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// функции SDBT
#define TESTDELAY 0

#define DEFMaxMasSize 333
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
unsigned long BTstopMill2 = 0UL;
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

void FmasMelodiaSetToFile(int _indexM){  // ФУНКЦИЯ ЗАПИСИ МЕЛОДИИ ИЗ ОПЕРАТИВНОЙ ПАМЯТИ В ФАЙЛ НА ФЛЭШКЕ

	int indexM = _indexM;

	if(indexM < 1 || indexM > 44){
		return;
	}

	String dataString = "";

	for(int i=1; i < DEFMaxMasSize; i++){

		if(masMelodiaMas[0][i] > 0){

			dataString += String(masMelodiaMas[0][i]);
			dataString += ",";

			if(masMelodiaMas[1][i] > 0){

				dataString += String(masMelodiaMas[1][i]);
				dataString += ".";
				dataString += "\n";
			}
		}else{

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

 	 	Serial1.print("error SD write ");
 	 	Serial1.println(indexToNameFileSD(indexM));
 	}




 	dataFile = SD.open(indexToNameFileSD(indexM));
  	if (dataFile) {

  		Serial.println(indexToNameFileSD(indexM));
		Serial.println("");

    	while (dataFile.available()) {
      		Serial.write(dataFile.read());
    	}
   		dataFile.close();
  	}else{
    	Serial1.println("error SD read");
  	}
}

void FmasMelodiaGetFromFile(int _indexM){  // ФУНКЦИЯ ЗАПИСИ МЕЛОДИИ ИЗ ФЛЭШКИ В ОПЕРАТИВНУЮ ПАМЯТЬ

	//FmasMelodiaClear();

	int indexM = _indexM;
	int simvolInt = 0;
	int GMcounter = 1;
	char simvol = 'y';


	Serial. println(indexM);  //--------------------------------------------------------------------------------->>
	Serial.println(indexToNameFileSD(indexM));
	Serial.println("");

	if (SD.exists(indexToNameFileSD(indexM))){

		dataFile = SD.open(indexToNameFileSD(indexM));

  		if(dataFile){

    		while(dataFile.available() && GMcounter < DEFRecordStop){


    	  		simvol = dataFile.read();

    	  		if (isDigit(simvol)){

    	  			simvolInt = (simvolInt * 10) + (simvol - '0');
    	  		}
    	  		else if(simvol == ','){

    	  			masMelodiaMas[0][GMcounter] = simvolInt;
    	  			simvolInt = 0;
    	  			GMcounter ++;
    	  		}
    	  		else if(simvol == '.'){
    	  			GMcounter --;
    	  			masMelodiaMas[1][GMcounter] = simvolInt;
    	  			simvolInt = 0;
    	  			GMcounter ++;
    	  		}
    		}
    		masMelodiaMas[0][GMcounter] = 0;

   			dataFile.close();
  		}else{

    		Serial.println("error SD read");
    		Serial1.println("error SD read");
    		lcd.clear();
    		lcd.print("error SD read");
    		delay(5000);
  		}
	}	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//byte raspisanie[32] = {1,0,0,0,0,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,1,67,68,69,1,0,70};
// ЗНАЧЕНИЕ ЯЧЕЕК МАСИВА
// 0 разрешить почасовое расписание 1, запретить 0
// 1  индекс мелодии для 01:00
// 2  индекс мелодии для 02:00
// 3  индекс мелодии для 03:00
// 4  индекс мелодии для 04:00
// 5  индекс мелодии для 05:00
// 6  индекс мелодии для 06:00
// 7  индекс мелодии для 07:00
// 8  индекс мелодии для 08:00
// 9  индекс мелодии для 09:00
// 10 индекс мелодии для 10:00
// 11 индекс мелодии для 11:00
// 12 индекс мелодии для 12:00
// 13 индекс мелодии для 13:00
// 14 индекс мелодии для 14:00
// 15 индекс мелодии для 15:00
// 16 индекс мелодии для 16:00
// 17 индекс мелодии для 17:00
// 18 индекс мелодии для 18:00
// 19 индекс мелодии для 19:00
// 20 индекс мелодии для 20:00
// 21 индекс мелодии для 21:00
// 22 индекс мелодии для 22:00
// 23 индекс мелодии для 23:00
// 24 индекс мелодии для 24:00
// 25 разрешить поминутное расписание 1, запретить 0
// 26 индекс мелодии для 15 минут
// 27 индекс мелодии для 30 минут
// 28 индекс мелодии для 45 минут
// 29 разрешить отбивать время колоколом 1, запретить 0
// 30 разрешить отбивать будничный
// 31 индекс мелодии для будничный
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sheduleSet(){  // ФУНКЦИЯ ЗАПИСИ РАСПИСАНИЯ ИЗ ОПЕРАТИВНОЙ ПАМЯТИ НА ФЛЭШКУ

	lcd.clear();
    lcd.print("shedule set");

  /////////////////////////////////////////////////////////////////////////////////////

    String sheduleString = "";

    sheduleString += "SHEDULE (RASPISANIE)";
	sheduleString += "\n";
	sheduleString += "\n";

	sheduleString += "[";
	sheduleString += String(raspisanie[0]);
	sheduleString += "] - ";
	sheduleString += "ENABLE HOURLY SHEDULE, 1-YES 0-NO";
	sheduleString += "\n";

	for(int i=1; i <= 24; i++){

		sheduleString += "[";
		sheduleString += String(raspisanie[i]);
		sheduleString += "] - ";
		sheduleString += "MELODY PER HOUR ";
		sheduleString += String(i);
		sheduleString += "  1-70 ";
		sheduleString += "\n";
	}

	sheduleString += "[";
	sheduleString += String(raspisanie[25]);
	sheduleString += "] - ";
	sheduleString += "ENABLE PER MINUTE SHEDULE, 1-YES 0-NO";
	sheduleString += "\n";

	sheduleString += "[";
	sheduleString += String(raspisanie[26]);
	sheduleString += "] - ";
	sheduleString += "MELODY PER MINUTE 15  1-70";
	sheduleString += "\n";

	sheduleString += "[";
	sheduleString += String(raspisanie[27]);
	sheduleString += "] - ";
	sheduleString += "MELODY PER MINUTE 30  1-70";
	sheduleString += "\n";

	sheduleString += "[";
	sheduleString += String(raspisanie[28]);
	sheduleString += "] - ";
	sheduleString += "MELODY PER MINUTE 45  1-70";
	sheduleString += "\n";

	sheduleString += "[";
	sheduleString += String(raspisanie[29]);
	sheduleString += "] - ";
	sheduleString += "ENABLE OTBIVANIE VREMENI, 1-YES 0-NO";
	sheduleString += "\n";

	sheduleString += "[";
	sheduleString += String(raspisanie[30]);
	sheduleString += "] - ";
	sheduleString += "ENABLE BUDNICHNIY, 1-YES 0-NO";
	sheduleString += "\n";

	sheduleString += "[";
	sheduleString += String(raspisanie[31]);
	sheduleString += "] - ";
	sheduleString += "MELODY FOR BUDNICHNIY";
	sheduleString += "\n";

  /////////////////////////////////////////////////////////////////////////////////////

	if (SD.exists("shedule.txt")){
		SD.remove("shedule.txt");
	}
	dataFile = SD.open("shedule.txt", FILE_WRITE);

 	if (dataFile){

 	 	dataFile.println(sheduleString);
 	 	dataFile.close();
 	}else{

 	 	Serial.print("error SD write ");
 	 	Serial.println("shedule.txt");

    	Serial1.print("error SD write ");
 	 	Serial1.println("shedule.txt");

    	lcd.clear();
    	lcd.print("error SD write");

    	delay(5000);
 	}
 	delay(500);
}

void sheduleGet(){  // ФУНКЦИЯ ЗАПИСИ РАСПИСАНИЯ ИЗ ФЛЭШКИ В ОПЕРАТИВНУЮ ПАМЯТЬ

	lcd.clear();
    lcd.print("shedule get");

    int simvolInt = 0;
	int Scounter = 0;
	char simvol = 'y';

    if (SD.exists("shedule.txt")){

		dataFile = SD.open("shedule.txt");

  		if(dataFile){

    		while(dataFile.available() && Scounter < 32){


    	  		simvol = dataFile.read();

    	  		if(simvol == '['){

    	  			while(1){

    	  				simvol = dataFile.read();

    	  				if (isDigit(simvol)){

    	  					simvolInt = (simvolInt * 10) + (simvol - '0');
    	  				}
    	  				else if(simvol == ']'){

    	  					raspisanie[Scounter] = simvolInt;
    	  					simvolInt = 0;
    	  					Scounter ++;

    	  					break;
    	  				}
    	  			}
    	  		}

    	  		if (isDigit(simvol)){

    	  			simvolInt = (simvolInt * 10) + (simvol - '0');
    	  		}
    	  		else if(simvol == ']'){

    	  			raspisanie[Scounter] = simvolInt;
    	  			simvolInt = 0;
    	  			Scounter ++;
    	  		}
    		}

   			dataFile.close();
  		}else{

    		Serial.println("error SD read");
    		Serial1.println("error SD read");
    		lcd.clear();
    		lcd.print("error SD read");
    		delay(5000);
  		}
	}	
}

void sheduleBegin(){  // ФУНКЦИЯ СЕТАП ДЛЯ РАСПИСАНИЯ

	if (SD.exists("shedule.txt")){

		sheduleGet();
		delay(300);
	}else{

		sheduleSet();
	}
}

void sheduleChangeFromB(){}

void sheduleSetLoop(){  // ЦИКЛ БЛЮТУЗ ПОДМЕНЮ НАСТРОЙКИ РАСПИСАНИЯ

	bool cikl1 = 1;
	int mCounter = 0;
	Serial1.print("*l"); // отправка признака индикатора
    Serial1.println("R255G255B255*"); // отправка цвета индикатора
	Serial1.println("*t select slot for save ↓↑ *");
	//while(cikl1){}
}

void FmasMelodiaSetLoop(){  // ЦИКЛ БЛЮТУЗ ПОДМЕНЮ СОХРАНЕНИЯ НОВОЙ ЗАПИСАНОЙ МЕЛОДИИ

	bool cikl1 = 1;
	int mCounter = 0;
	Serial1.print("*l"); // отправка признака индикатора
    Serial1.println("R255G255B255*"); // отправка цвета индикатора
	Serial1.println("*t select slot for save ↓↑ *");

	while(cikl1){

		if(Serial1.available());
		b_d = Serial1.read();

		if(b_d == 'S'){  // если нажат селект то закончить цикл выбора номера мелодии и перейти к следующему шагу
			break;
		}else if(b_d == 'U'){  // если нажата кнопка вверх то уменшить счетчик номера мелодии
			Serial1.print("*p"); // отправка звукового сигнала
    		mCounter --;
    		if(mCounter < 0){
    			mCounter = 44;
    		}
    		Serial1.print("*t");
    		if(mCounter != 0){
    			Serial1.print(indexToNameFileSD(mCounter));  // отправка имени файла в формате строки
    			if(SD.exists(indexToNameFileSD(mCounter))){
    				Serial1.print("[>]");                   // если файл существует то добавить [ ]
    			}
    		}else{
    			Serial1.println("cancel");
    		}
    		Serial1.println("*");
		}else if(b_d == 'D'){  // если нажата кнопка вниз то увеличить счетчик номера мелодии
			Serial1.print("*p"); // отправка звукового сигнала
    		mCounter ++;
    		if(mCounter > 44){
    			mCounter = 0;
    		}
    		Serial1.print("*t");
    		if(mCounter != 0){
    			Serial1.print(indexToNameFileSD(mCounter));  // отправка имени файла в формате строки
    			if(SD.exists(indexToNameFileSD(mCounter))){
    				Serial1.print("[>]");                   // если файл существует то добавить [ ]
    			}
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
		Serial1.print(indexToNameFileSD(mCounter));  // отправка имени файла в формате строки
		Serial1.println(" SAVED OK*");
		Serial1.println("MELODY SAVED OK");
	}else{
		Serial1.print("*l"); // отправка признака индикатора
    	Serial1.println("R255G130B0*"); // отправка цвета индикатора
		Serial1.println("*t CANCELED *");
	}
}



void playMelodyForMemoryLoop(){ // ЦИКЛ БЛЮТУЗ ПОДМЕНЮ ПРОИГРЫВАНИЯ ВЫБРАННОЙ МЕЛОДИИ ИЗ ПАМЯТИ ФЛЭШКИ
	bool cikl1 = 1;
	int mCounter = 0;
	Serial1.print("*l"); // отправка признака индикатора
    Serial1.println("R0G255B0*"); // отправка цвета индикатора
    Serial1.println("*t PLAY FROM MEMORY  *"); // отправка строки меню
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
    			Serial1.print(indexToNameFileSD(mCounter));  // отправка имени файла в формате строки
    			if(SD.exists(indexToNameFileSD(mCounter))){
    				Serial1.print("[>]");                   // если файл существует то добавить [ ]
    			}
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
    			Serial1.print(indexToNameFileSD(mCounter));  // отправка имени файла в формате строки
    			if(SD.exists(indexToNameFileSD(mCounter))){
    				Serial1.print("[>]");                   // если файл существует то добавить [ ]
    			}
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
		playMelodyByIndex(mCounter);
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

void FmasMelodiaPlay(){  // ФУНКЦИЯ ПРОИГРЫВАНИЯ МЕЛОДИИ ИЗ ОПЕРАТИВНОЙ ПАМЯТИ
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

void FmasMelodiaPlayFromFile(byte _indexM){  // ФУНКЦИЯ ПРОИГРЫВАНИЯ МЕЛОДИИ ИЗ ПАМЯТИ ФЛЭШКИ, ПО НОМЕРУ МЕЛОДИИ 1-44
	byte indexM = _indexM;

	FmasMelodiaGetFromFile(indexM);
	FmasMelodiaPlay();
	//FmasMelodiaClear();
}


void menuDraw(){  // ФУНКЦИЯ ОТРИСОВКИ БЛЮТУЗ МЕНЮ
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


void BTloop(){  // ОСНОВНОЙ БЛЮТУЗ ЦИКЛ.
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




    	  					// 1  ЕСЛИ РЕЖИМ ПЕРЕЗВОН
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




    	  						// 2  ЕСЛИ РЕЖИМ ПРИНТ 1
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




    	  						// 3  ЕСЛИ РЕЖИМ ПРИНТ 2
    	  					}else if(flagMenu == 3){
    	  						if(counterComboMas == 1){
    	  							
    	  							BTstopMill = millis();
    	  							
    	  							nota(masComboMas[1], TESTDELAY);
    	  							
    	  							BTresMill = BTstopMill - BTstartMill;

    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(".");
    	  							}
    	  							BTstartMill = millis();
    	  							Serial.print(bt_not);
    	  							Serial.print(", ");
    	  						}
    	  						else if(counterComboMas == 2){
    	  							
    	  							BTstopMill = millis();
    	  							
    	  							combo2(masComboMas[1], masComboMas[2], TESTDELAY);
    	  							
    	  							BTresMill = BTstopMill - BTstartMill;

    	  							if(BTresMill != BTstopMill){
    	  								Serial.print(BTresMill - popravkaDelay);
    	  								Serial.println(".");
    	  							}
    	  							BTstartMill = millis();

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
    	  								Serial.println(".");
    	  							}
    	  							BTstartMill = millis();

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
    	  								Serial.println(".");
    	  							}
    	  							BTstartMill = millis();
    	  							
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
    	  								Serial.println(".");
    	  							}
    	  							BTstartMill = millis();
    	  							
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
    	  								Serial.println(".");
    	  							}
    	  							BTstartMill = millis();
    	  							
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
    	  								Serial.println(".");
    	  							}
    	  							BTstartMill = millis();
    	  							
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
    	  								Serial.println(".");
    	  							}
    	  							BTstartMill = millis();
    	  							
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




    	  						// 4  ЕСЛИ РЕЖИМ ЗАПИСИ НОВОЙ МЕЛОДИИ
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





    	  					}else if(flagMenu == 5){  //  ЕСЛИ РЕЖИМ ВОСПРОИЗВЕДЕНИЯ НОВОЙ ЗАПИСАНОЙ МЕЛОДИИ

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


    		else if (b_d == 'S'){  // ЕСЛИ НАЖАТА КНОПККА СЕЛЕКТ В БЛЮТУЗ МЕНЮ:

    			if(flagMenu == 1){  // ЕСЛИ РЕЖИМ ПЕРЕЗВОН

    				Serial1.print("*p"); // отправка звукового сигнала
    				flagPlayForMemory = 1;
    				if(flagPlayForMemory == 1){
    					playMelodyForMemoryLoop();
    					flagPlayForMemory = 0;
    				}
    			}else if(flagMenu == 2){  // ЕСЛИ РЕЖИМ ПРИНТ 1

    				Serial1.print("*p"); // отправка звукового сигнала
    				Serial.println("1000);");
    				Serial.println("");
    				BTstartMill = 0;
    			}else if(flagMenu == 3){  // ЕСЛИ РЕЖИМ ПРИНТ 2

    				Serial1.print("*p"); // отправка звукового сигнала
    				Serial.println("1000.");
    				Serial.println("");
    				BTstartMill = 0;
    			}else if(flagMenu == 4){  // ЕСЛИ РЕЖИМ ЗАПИСИ НОВОЙ МЕЛОДИИ В ОПЕРАТИВНУЮ ПАМЯТЬ

    				Serial1.print("*p"); // отправка звукового сигнала
    				flagRecord = !flagRecord;
    				if(flagRecord == 1){
    					FmasMelodiaClear();
    					Serial1.println("*s STOP *");
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
    			}else if(flagMenu == 5){  // ЕСЛИ РЕЖИМ ПРОИГРЫВАНИЯ МЕЛОДИИ ИЗ ОПЕРАТИВНОЙ ПАМЯТИ

    				Serial1.print("*p"); // отправка звукового сигнала
    				FmasMelodiaPlay();
    			}else if (flagMenu == 6){  // ЕСЛИ РЕЖИМ СОХРАНЕНИЯ МЕЛОДИИ НА ФЛЭШКУ ИЗ ОПЕРАТИВНОЙ ПАМЯТИ
    				Serial1.print("*p"); // отправка звукового сигнала
    				FmasMelodiaSetLoop();
    			}else if(flagMenu == 7){  // ЕСЛИ РЕЖИМ НАСТРОЙКИ РАСПИСАНИЯ
    				Serial1.print("*p"); // отправка звукового сигнала
    				sheduleSetLoop();
    			}else if(flagMenu == 8){  // ЕСЛИ РЕЖИМ EXIT
    				Serial1.print("*p"); // отправка звукового сигнала
    				flagBT = 0;
    				Serial1.println("*t EXIT OK. MEGAFON ACTIVATED *");
    				Serial.println("x");
    				rminute = 61;
					timeToDisplay();
    				break;
    			}
    		}


    		else if (b_d == 'U'){  // ЕСЛИ НАЖАТА КНОПКА ВВЕРХ В БЛЮТУЗ МЕНЮ

    			//BTstartMill = 0;
    			Serial1.print("*p"); // отправка звукового сигнала
    			flagMenu --;
    			if(flagMenu < 1){
    				flagMenu = 8;
    			}
    			menuDraw();
    		}


    		else if (b_d == 'D'){  // ЕСЛИ НАЖАТА КНОПКА ВНИЗ В БЛЮТУЗ МЕНЮ

    			//BTstartMill = 0;
    			Serial1.print("*p"); // отправка звукового сигнала
    			flagMenu ++;
    			if(flagMenu > 8){
    				flagMenu = 1;
    			}
    			menuDraw();
    		}


    		else if (b_d == 'm'){  // ЕСЛИ ПРИШЛА БУКВА 'm' И ЧИСЛО ОТ 1 ДО 70 ТО ВОСПРОИЗВЕСТИ МЕЛОДИЮ СООТВЕТСТВУЮЩУЮ ЧИСЛУ

    			int mNindex = Serial1.parseInt();

    			if(mNindex > 0 && mNindex <= 70){

    				playMelodyByIndex(mNindex);  // усли в сериал отправить m1 то будет проиграна мелодия с индексом 1
    				rminute = 61;
					timeToDisplay();
    			}
    		}


    		else if(b_d == 'd'){  // ЕСЛИ ПРИШЛА БУКВА 'd' СДЕЛАТЬ ЗАДЕРЖКУ

    			delayFor_d = Serial1.parseInt();

    			delay(delayFor_d);
    		}


    		else if(b_d == 'B'){  // ЕСЛИ ПРИШЛА БУКВА BS=0,1,3,...31. АНГЛИЙСКАЯ ВКЛЮЧИТЬ РЕЖИМ ЗАПИСИ РАСПИСАНИЯ С ЧИСЛА

				// BS=1,0,0,0,0,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,1,67,68,69,1,0,70.
				// BH=0,0,0,0,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48.
				// BM=67,68,69.

    			sheduleChangeFromB();
    		}
  		}
	}

	Serial1.print("*l"); // отправка признака строки меню
    Serial1.println("R0G0B0*"); // отправка строки меню
    Serial1.println("EXIT OK"); // отправка строки меню
    Serial1.println("RASPISANIE RABOTAET"); // отправка строки меню
}
