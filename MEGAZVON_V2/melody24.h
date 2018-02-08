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

// МЕЛОДИИ ДЛЯ ЗВОНА КОЛОКОЛОВ
// СПИСОК И СОСТАВ МЕЛОДИЙ

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ПОЛЬЗОВАТЕЛЬСКИЙ РАЗДЕЛ:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// В ЭТОМ РАЗДЕЛЕ СОЗДАВАТЬ МЕЛОДИИ:

// функция мелодия состоит из последовательных вызовов функции нота. по сути является определенной мелодией

// мелодия EX1 пример мелодии с 1 набором нот
void melodiaEX1(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodiaEX1");
	delay(1000);

	// здесь писать ноты
	enota(1, 95, 1000);    // 1 нота, реле 22 (время включения реле 95мс, задержка до следующей ноты 1000мс)
	enota(2, 105, 1000);   // 2 нота, реле 23 (время включения реле 105мс, задержка до следующей ноты 1000мс)
	enota(3, 100, 500);    // 3 нота, реле 24 (время включения реле 100мс, задержка до следующей ноты 500мс)
	enota(4, 100, 2000);   // 4 нота, реле 25 (время включения реле 100мс, задержка до следующей ноты 2000мс)
	enota(5, 100, 1000);   // 5 нота, реле 26 (время включения реле 100мс, задержка до следующей ноты 1000мс)
	enota(6, 100, 1000);   // 6 нота, реле 27 (время включения реле 100мс, задержка до следующей ноты 1000мс)
	enota(7, 100, 1000);   // 7 нота, реле 28 (время включения реле 100мс, задержка до следующей ноты 1000мс)
	enota(8, 100, 1000);   // 8 нота, реле 29 (время включения реле 100мс, задержка до следующей ноты 1000мс)
}

// мелодия EX2 пример мелодии со 2 набором нот
// для написания мелодий лучше использовать 2 или 3 набор нот. 1 для настройки колоколов и создания уникальных нот
void melodiaEX2(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodiaEX2");
	delay(1000);

	// здесь писать ноты
	nota(1, 500);   // 1 нота, реле 22 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota(2, 500);   // 2 нота, реле 23 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota(3, 500);   // 3 нота, реле 24 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota(4, 500);   // 4 нота, реле 25 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota(5, 500);   // 5 нота, реле 26 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota(6, 500);   // 6 нота, реле 27 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota(7, 500);   // 7 нота, реле 28 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota(8, 500);   // 8 нота, реле 29 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)

	// пример комбо нот. удар в несколько колоколов одновременно
	combo2(1, 2, 500);   // комбо нота 2 колокола
	combo3(1, 2, 3, 500);   // комбо нота 3 колокола
	combo4(1, 2, 3, 4, 500);   // комбо нота 4 колокола
	combo5(1, 2, 3, 4, 5, 500);   // комбо нота 5 колоколов
	combo6(1, 2, 3, 4, 5, 6, 500);   // комбо нота 6 колоколов
	combo7(1, 2, 3, 4, 5, 6, 7, 500);   // комбо нота 7 колоколов
	combo8(1, 2, 3, 4, 5, 6, 7, 8, 500);   // комбо нота 8 колоколов
}

// мелодия EX3 пример мелодии с 3 набором нот
// для написания мелодий лучше использовать 2 или 3 набор нот. 1 для настройки колоколов и создания уникальных нот
void melodiaEX3(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodiaEX3");
	delay(1000);

	// здесь писать ноты
	nota1(500);   // 1 нота, реле 22 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota2(500);   // 2 нота, реле 23 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota3(500);   // 3 нота, реле 24 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota4(500);   // 4 нота, реле 25 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota5(500);   // 5 нота, реле 26 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota6(500);   // 6 нота, реле 27 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota7(500);   // 7 нота, реле 28 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota8(500);   // 8 нота, реле 29 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
}

// ДОПОЛНИТЕЛЬНЫЕ МЕЛОДИИ:

// мелодияRes1
void melodiaRes1(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodiaRes1");
	delay(1000);

	float tempMelody = 1.0;  // это переменная темпа мелодии. если нужно ускорить 0.9 - 0.1.  ` замедлить 1.1 - 10.0

 	enota(4, 100, 350);   // 4 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(5, 100, 350);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(6, 100, 350);   // 6 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(7, 100, 350);   // 7 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(6, 100, 350);   // 6 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(5, 100, 350);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(4, 100, 600);   // 4 нота, (время включения реле 100мс, задержка до следующей ноты 600мс)
  	enota(5, 100, 250);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 250мс)
  	
  	enota(5, 100, 250);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 250мс)
  	enota(5, 100, 400);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 400мс)
  	enota(6, 100, 300);   // 6 нота, (время включения реле 100мс, задержка до следующей ноты 300мс)
  	enota(5, 100, 300);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 300мс)
  	enota(4, 100, 600);   // 4 нота, (время включения реле 100мс, задержка до следующей ноты 600мс)
    
 	enota(4, 100, 350);   // 4 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(5, 100, 350);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(6, 100, 350);   // 6 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(7, 100, 350);   // 7 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(6, 100, 350);   // 6 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(5, 100, 350);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 350мс)
  	enota(4, 100, 600);   // 4 нота, (время включения реле 100мс, задержка до следующей ноты 600мс)
  	enota(5, 100, 250);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 250мс)
  	
  	enota(5, 100, 250);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 250мс)
  	enota(5, 100, 400);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 400мс)
  	enota(6, 100, 300);   // 6 нота, (время включения реле 100мс, задержка до следующей ноты 300мс)
  	enota(5, 100, 300);   // 5 нота, (время включения реле 100мс, задержка до следующей ноты 300мс)
  	combo2(4, 5);        // комбо нота 2 колокола
}
// мелодияRes2
void melodiaRes2(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodiaRes2");
	delay(1000);

	float tempMelody = 1.0;  // это переменная темпа мелодии. если нужно ускорить 0.9 - 0.1.  ` замедлить 1.1 - 10.0

	combo2(16,17,500*tempMelody);
	combo2(16,17,300*tempMelody);
	combo2(5,17,500*tempMelody);
	combo2(5,17,200*tempMelody);
	combo2(16,17,200*tempMelody);

	nota15(200*tempMelody);
	combo2(16,17,200*tempMelody);
	combo2(16,17,200*tempMelody);
	nota5(200*tempMelody);

	combo2(15,17,500*tempMelody);
	nota11(200*tempMelody);
	nota16(200*tempMelody);
	nota7(200*tempMelody);
	nota11(400*tempMelody);

	nota14(200*tempMelody);
	nota13(200*tempMelody);
	nota12(300*tempMelody);
	nota16(400*tempMelody);
	nota12(500*tempMelody);
	nota16(200*tempMelody);

	nota12(500*tempMelody);
	nota12(200*tempMelody);
	nota5(200*tempMelody);
	nota16(200*tempMelody);
	nota12(500*tempMelody);

	nota15(200*tempMelody);
	nota13(500*tempMelody);
	nota7(200*tempMelody);
	nota7(200*tempMelody);
	nota16(500*tempMelody);

	combo2(5,13,200*tempMelody);
	combo2(13,3,300*tempMelody);
	combo2(5,3,200*tempMelody);
	combo2(18,3,300*tempMelody);

	nota3(200*tempMelody);
	combo2(11,16,300*tempMelody);
	combo2(5,15,200*tempMelody);
	combo2(5,15,200*tempMelody);

	combo2(13,3,500*tempMelody);
	combo2(14,7,300*tempMelody);
	combo2(16,19,200*tempMelody);
	nota5(200*tempMelody);

	combo2(14,13,200*tempMelody);
	combo2(15,13,200*tempMelody);
	combo2(18,13,0);
}
// мелодияRes3
void melodiaRes3(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodiaRes3");
	delay(1000);

	float tempMelody = 1.0;  // это переменная темпа мелодии. если нужно ускорить 0.9 - 0.1.  ` замедлить 1.1 - 10.0

	combo2(11,14,500*tempMelody);
	combo2(11,14,300*tempMelody);
	nota11(300*tempMelody);
	nota11(300*tempMelody);
	combo2(11,14,500*tempMelody);
	combo2(11,14,200*tempMelody);
	nota11(300*tempMelody);
	nota11(300*tempMelody);
	nota6(300*tempMelody);
	nota7(300*tempMelody);
	nota11(300*tempMelody);
	nota11(100*tempMelody);
	nota7(300*tempMelody);
	nota6(300*tempMelody);
	nota6(300*tempMelody);
	nota7(300*tempMelody);
	nota7(300*tempMelody);
	nota6(300*tempMelody);
	nota7(300*tempMelody);
	nota11(300*tempMelody);
	nota7(100*tempMelody);
	nota7(100*tempMelody);
	nota6(300*tempMelody);
	nota11(300*tempMelody);

	combo2(11,14,200*tempMelody);
	nota11(200*tempMelody);
	combo2(11,14,200*tempMelody);

	nota11(200*tempMelody);
	combo2(14,16,500*tempMelody);
	nota15(100*tempMelody);
	combo2(11,14,200*tempMelody);
	nota15(300*tempMelody);

	combo2(11,14,300*tempMelody);
	nota11(200*tempMelody);
	combo2(11,14,300*tempMelody);

}
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

// ОСНОВНЫЕ МЕЛОДИИ:
// МЕЛОДИЯ КАЖДЫЙ ЧАС:

// мелодия1
void melodia1(){
	// здесь писать ноты или мелодии
}

// мелодия2
void melodia2(){
	
}

// мелодия3
void melodia3(){
	
}

// мелодия4
void melodia4(){
	
}

// мелодия5
void melodia5(){
	
}

void melodia6(){
	
}

// мелодия7
void melodia7(){
	
}

// мелодия8
void melodia8(){
	
}

// мелодия9
void melodia9(){
	
}

// мелодия10
void melodia10(){
	
}

// мелодия11
void melodia11(){
	
}

// мелодия12
void melodia12(){
	
}

// МЕЛОДИИ КАЖДЫЕ 15 минут:

// мелодия15
void melodia15(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodia15");
	delay(1000);

	delay(1000);
	nota7(600);   // 7 нота, (время включения реле задано в настройках нот, задержка до следующей ноты 600мс)
  	nota5(600);   // 5 нота, (время включения реле задано в настройках нот, задержка до следующей ноты 600мс)
  	nota6(600);   // 6 нота, (время включения реле задано в настройках нот, задержка до следующей ноты 600мс)
  	nota4(0);     // 4 нота, (время включения реле задано в настройках нот, задержка до следующей ноты 0мс)
}

// мелодия30
void melodia30(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodia30");
	delay(1000);

	combo3(10, 18, 11,500);   // комбо нота 3 колокола
  	combo3(10, 18, 7, 500);   // комбо нота 3 колокола
  	combo3(10, 18, 6, 500);   // комбо нота 3 колокола
  	combo3(10, 18, 11, 500);  // комбо нота 3 колокола
  	combo3(10, 18, 5, 500);   // комбо нота 3 колокола
  	combo3(17,18,6,800);      // комбо нота 3 колокола
  	nota4(0);                 // 4 нота, (время включения реле задано в настройках нот, задержка до следующей ноты 0мс)
}

// мелодия45
void melodia45(){

	lcd.clear();
	lcd.setCursor(6,1);
	lcd.write(byte(1));
	lcd.setCursor(8,1);
	lcd.print("melodia45");
	delay(1000);

	nota13(300);     // 19 нота, (время включения реле задано в настройках нот, задержка до следующей ноты 300мс)
  	nota7(300);      // 10 нота, (время включения реле задано в настройках нот, задержка до следующей ноты 300мс)
  	nota11(300);     // 6 нота,  (время включения реле задано в настройках нот, задержка до следующей ноты 300мс)
  	nota6(500);      // 5 нота,  (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
  	combo2(5,11,0);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
