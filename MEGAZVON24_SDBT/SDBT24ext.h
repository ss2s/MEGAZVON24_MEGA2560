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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ТЕХНИЧЕСКИЙ РАЗДЕЛ SDBT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// функции SDBT
#define TESTDELAY 0

#define DEFMaxMasSize 100
unsigned int masMelodiaMas [2][DEFMaxMasSize];

int recordCounter = 0;

// 0 - flag
unsigned int masComboMas[9] = {0,0,0,0,0,0,0,0,0};
byte counterComboMas = 1;

bool flagBT = 0;
bool flagBTonof = 0;
bool flagRecord = 0;

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

void menuDraw(){
	if(flagMenu == 1){
    	Serial1.println("*t PEREZVON MODE *"); // отправка строки меню
    	Serial1.println("PRESS BUTTON TO PLAY"); // отправка справочной информации
	}else if(flagMenu == 2){
		Serial1.println("*t SERIAL PRINT MODE 1 *"); // отправка строки меню
		Serial1.println("PRESS BUTTON TO PLAY AND PRINT MELODY CODE FOR SERIAL MONITOR MODE 1. PRESS OK TO STOP PRINT"); // отправка справочной информации
	}else if(flagMenu == 3){
		Serial1.println("*t SERIAL PRINT MODE 2 *"); // отправка строки меню
		Serial1.println("PRESS BUTTON TO PLAY AND PRINT MELODY CODE FOR SERIAL MONITOR 	MODE 2. PRESS OK TO STOP PRINT"); // отправка справочной информации
	}else if(flagMenu == 4){
		Serial1.println("*t RECORD NEW MELODY *"); // отправка строки меню
    	Serial1.println("PRESS OK TO START RECORDING"); // отправка справочной информации
	}else if(flagMenu == 5){
		Serial1.println("*t PLAY RECORDED MELODY *"); // отправка строки меню
		Serial1.println("PRESS OK TO PLAY RECORDED MELODY"); // отправка справочной информации
	}else if(flagMenu == 6){
		Serial1.println("*t SAVE RECORDED MELODY *"); // отправка строки меню
		Serial1.println("PRESS OK TO SAVE RECORDED MELODY"); // отправка справочной информации
	}else if(flagMenu == 7){
		Serial1.println("*t SETING *"); // отправка строки меню
		Serial1.println("PRESS BUTTON TO PLAY AND PRINT MELODY CODE FOR SERIAL MONITOR. PRESS OK TO STOP PRINT"); // отправка справочной информации
	}
}

void BTloop(){
	Serial1.print("*l"); // отправка признака индикатора
    Serial1.println("R147G255B0*"); // отправка цвета индикатора
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
    	  						}
    	  						else if(flagRecord == 0){}





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
    			if(flagMenu == 2){
    				Serial.println("0);");
    				Serial.println("");
    				BTstartMill = 0;
    			}else if(flagMenu == 4){
    				flagRecord = !flagRecord;
    				if(flagRecord == 1){
    					Serial1.print("*l"); // отправка признака строки меню
    					Serial1.println("R255G0B0*"); // отправка строки меню
    				}else if(flagRecord == 0){
    					Serial1.print("*l"); // отправка признака индикатора
    					Serial1.println("R147G255B0*"); // отправка цвета индикатора
    					Serial.println("0);");
    					Serial.println("");
    					BTstartMill = 0;
    				}
    			}
    		}


    		else if (b_d == 'U'){
    			flagMenu --;
    			if(flagMenu < 1){
    				flagMenu = 7;
    			}
    			menuDraw();
    		}


    		else if (b_d == 'D'){
    			flagMenu ++;
    			if(flagMenu > 7){
    				flagMenu = 1;
    			}
    			menuDraw();
    		}


    		else if (b_d == 'X'){
    			flagBT = 0;
    			Serial.println("x");
    			rminute = 61;
				timeToDisplay();
    			break;
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
}

void BTchek(){
	if(flagBTonof == 1){
		BTloop();
	}
}

void FmasComboMasClear(){
	for(int i=0; i <9; i++){
		masComboMas[i] = 0;
	}
}

void FmasMelodiaClear(){
	for(int i=0; i < DEFMaxMasSize; i++){
		masMelodiaMas[0][i] = 0;
		masMelodiaMas[1][i] = 0;
	}
}

void FmasMelodiaGetForBT(){}

void FmasMelodiaSetToFile(byte _indexM){}

void FmasMelodiaGetForFile(byte _indexM){
	if(masMelodiaMas[0][0] != 0){
		FmasMelodiaClear();
	}
}

void FmasMelodiaPlay(){
	masMelodiaMas[1][0] = 0;
	masMelodiaMas[0][0] = 0;
	for(int i=1; i < DEFMaxMasSize; i++){
		if(masMelodiaMas[0][i] == 0){
			break;
		}
		if(masMelodiaMas[1][i] > 0){
			if(masComboMas[0] == 0){
				nota(masMelodiaMas[0][i], masMelodiaMas[1][i]);
				masMelodiaMas[1][0] = masMelodiaMas[1][0] + masMelodiaMas[1][i];
				masMelodiaMas[0][0]++;
			}else{
				masComboMas[counterComboMas] = masMelodiaMas[0][i];
				if(counterComboMas == 2){
					combo2(masComboMas[1], masComboMas[2], masMelodiaMas[1][i]);
					masMelodiaMas[1][0] = masMelodiaMas[1][0] + masMelodiaMas[1][i];
					masMelodiaMas[0][0]++;
				}else if(counterComboMas == 3){
					combo3(masComboMas[1], masComboMas[2] ,masComboMas[3], masMelodiaMas[1][i]);
					masMelodiaMas[1][0] = masMelodiaMas[1][0] + masMelodiaMas[1][i];
					masMelodiaMas[0][0]++;
				}else if(counterComboMas == 4){
					combo4(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masMelodiaMas[1][i]);
					masMelodiaMas[1][0] = masMelodiaMas[1][0] + masMelodiaMas[1][i];
					masMelodiaMas[0][0]++;
				}else if(counterComboMas == 5){
					combo5(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masMelodiaMas[1][i]);
					masMelodiaMas[1][0] = masMelodiaMas[1][0] + masMelodiaMas[1][i];
					masMelodiaMas[0][0]++;
				}else if(counterComboMas == 6){
					combo6(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masMelodiaMas[1][i]);
					masMelodiaMas[1][0] = masMelodiaMas[1][0] + masMelodiaMas[1][i];
					masMelodiaMas[0][0]++;
				}else if(counterComboMas == 7){
					combo7(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], masMelodiaMas[1][i]);
					masMelodiaMas[1][0] = masMelodiaMas[1][0] + masMelodiaMas[1][i];
					masMelodiaMas[0][0]++;
				}else if(counterComboMas == 8){
					combo8(masComboMas[1], masComboMas[2], masComboMas[3], masComboMas[4], masComboMas[5], masComboMas[6], masComboMas[7], masComboMas[8], masMelodiaMas[1][i]);
					masMelodiaMas[1][0] = masMelodiaMas[1][0] + masMelodiaMas[1][i];
					masMelodiaMas[0][0]++;
				}
				counterComboMas = 1;
				masComboMas[0] = 0;
				FmasComboMasClear();
			}
		}else{
			if(masComboMas[0] == 0){masComboMas[0] = 1;}
			masComboMas[counterComboMas] = masMelodiaMas[0][i];
			counterComboMas ++;
			masMelodiaMas[0][0]++;
			if(counterComboMas > 8){counterComboMas = 8;}
		}
	}
}

void FmasMelodiaPlayForFile(byte _indexM){
	byte indexM = _indexM;
	if(masMelodiaMas[0][0] != 0){
		FmasMelodiaClear();
	}

	FmasMelodiaGetForFile(indexM);
	FmasMelodiaPlay();
	FmasMelodiaClear();
}