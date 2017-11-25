////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

          https://github.com/ss2s/MEGAZVON24_MEGA2560
        \******************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "Arduino.h"
//#include "config24.h"
//#include "nota24.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// МЕЛОДИИ ДЛЯ ЗВОНА КОЛОКОЛОВ
// СПИСОК И СОСТАВ МЕЛОДИЙ

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ПОЛЬЗОВАТЕЛЬСКИЙ РАЗДЕЛ:

// В ЭТОМ РАЗДЕЛЕ СОЗДАВАТЬ МЕЛОДИИ:

// функция мелодия состоит из последовательных вызовов функции нота. по сути является определенной мелодией

// мелодия EX1 пример мелодии с 1 набором нот
void melodiaEX1(){
	// здесь писать ноты
	nota(1, 250, 2000);   // 1 нота, реле 22 (время включения реле 250мс, задержка до следующей ноты 2000мс)
	nota(2, 280, 2000);   // 2 нота, реле 23 (время включения реле 280мс, задержка до следующей ноты 2000мс)
	nota(3, 250, 3000);   // 3 нота, реле 24 (время включения реле 250мс, задержка до следующей ноты 3000мс)
	nota(4, 300, 5000);   // 4 нота, реле 25 (время включения реле 300мс, задержка до следующей ноты 5000мс)
	nota(5, 300, 2000);   // 5 нота, реле 26 (время включения реле 300мс, задержка до следующей ноты 2000мс)
	nota(6, 300, 2000);   // 6 нота, реле 27 (время включения реле 300мс, задержка до следующей ноты 2000мс)
	nota(7, 300, 2000);   // 7 нота, реле 28 (время включения реле 300мс, задержка до следующей ноты 2000мс)
	nota(8, 300, 2000);   // 8 нота, реле 29 (время включения реле 300мс, задержка до следующей ноты 2000мс)
	combo2(1, 2, 2000);
	combo3(1, 2, 3, 2000);
	combo4(1, 2, 3, 4, 2000);
	combo5(1, 2, 3, 4, 5, 2000);
	combo6(1, 2, 3, 4, 5, 6, 2000);
	combo7(1, 2, 3, 4, 5, 6, 7, 2000);
	combo8(1, 2, 3, 4, 5, 6, 7, 8, 2000);
}

// мелодия EX2 пример мелодии со 2 набором нот
// для написания мелодий лучше использовать второй набор нот. первый для настройки колоколов и создания уникальных нот
void melodiaEX2(){
	// здесь писать ноты
	nota1(500);   // 1 нота, реле 22 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota2(500);   // 2 нота, реле 23 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota3(500);   // 3 нота, реле 24 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota4(500);   // 4 нота, реле 25 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota5(500);   // 5 нота, реле 26 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota6(500);   // 6 нота, реле 27 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota7(500);   // 7 нота, реле 28 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	nota8(500);   // 8 нота, реле 29 (время включения реле задано в настройках нот, задержка до следующей ноты 500мс)
	combo2(1, 2, 1000);
	combo3(1, 2, 3, 1000);
	combo4(1, 2, 3, 4, 1000);
	combo5(1, 2, 3, 4, 5, 1000);
	combo6(1, 2, 3, 4, 5, 6, 1000);
	combo7(1, 2, 3, 4, 5, 6, 7, 1000);
	combo8(1, 2, 3, 4, 5, 6, 7, 8, 1000);
}

// мелодия EX3
void melodiaEX3(){

	float tempMelody = 0.1;  // это переменная темпа мелодии. если нужно ускорить 0.9 - 0.1.  ` замедлить 1.1 - 10.0

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
