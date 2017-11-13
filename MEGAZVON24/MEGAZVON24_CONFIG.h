////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /******************************************************************************************************\
          MEGAZVON24  Arduino MEGA2560 программа для автоматического перезвона колоколов по заданному времени.

          https://github.com/ss2s/MEGAZVON24_MEGA2560
        \******************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ФАЙЛ КОНФИГУРАЦИИ здесь настраиваются:
// настройки
// пины к которым подключены колокола
// прочие настройки распиновок
// НАСТРОЙКА ДЛИТЕЛЬНОСТИ НОТ

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// НАСТРОЙКА РЕЛЕ: если реле включается нолем поменять местами 1 и 0
#define HHH 1  // HIGH
#define LLL 0  // LOW

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// НАСТРОЙКИ:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HOUR_OF_BLOW_DELAY 5000  // задержка между ударами колокола, при отбивании колоколом количества часов. 5с

#define TOB_ZIMA  // ZIMA, LETO  для включения летнего набора нот, изменить #define TOB_ZIMA на #define TOB_LETO

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// РАСПИНОВКА: для настройки изменять цифры, те что в конце, перед коментарием

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// РАСПИНОВКА КОЛОКОЛОВ:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// для настройки изменять последнюю цифру(номер пина Arduino к которому подключен ударный механизм(язычек))
// значение идущее за #define является именем колокола. к которому нужно обращатся в программе для создания мелодий.
#define RELE_K1 21                   // 1 колокол (реле 1)
#define RELE_K2 22                   // 2 колокол (реле 2)
#define RELE_K3 23                   // 3 колокол (реле 3)
#define RELE_K4 24                   // 4 колокол (реле 4)
#define RELE_K5 25                   // 5 колокол (реле 5)
#define RELE_K6 26                   // 6 колокол (реле 6)
#define RELE_K7 27                   // 7 колокол (реле 7)
#define RELE_K8 28                   // 8 колокол (реле 8)
#define RELE_K9 29                   // 9 колокол (реле 9)
#define RELE_K10 30                  // 10 колокол (реле 10)
#define RELE_K11 31                  // 11 колокол (реле 11)
#define RELE_K12 32                  // 12 колокол (реле 12)
#define RELE_K13 33                  // 13 колокол (реле 13)
#define RELE_K14 34                  // 14 колокол (реле 14)
#define RELE_K15 35                  // 15 колокол (реле 15)
#define RELE_K16 36                  // 16 колокол (реле 16)
#define RELE_K17 37                  // 17 колокол (реле 17)
#define RELE_K18 38                  // 18 колокол (реле 18)
#define RELE_K19 39                  // 19 колокол (реле 19)
#define RELE_K20 40                  // 20 колокол (реле 20)
#define RELE_K21 41                  // 21 колокол (реле 21)
#define RELE_K22 42                  // 22 колокол (реле 22)
#define RELE_K23 43                  // 23 колокол (реле 23)
#define RELE_K24 44                  // 24 колокол (реле 24)

// колокол который отбивает время, по умолчанию 24 колокол
#define RELE_HOUR_BLOW RELE_K24      // это настройка, изменять последнюю цифру что после К

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// РАСПИНОВКА КОМПЛЕКТУЮЩИХ:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ДИСПЛЕЙ:
#define DEF_LCD_INIT_PIN 8, 9, 4, 5, 6, 7  // настройка распиновки дисплея
#define DEF_LCD_LIGHT_PIN 10               // подсветка дисплея
#define DEF_LCD_KEY_PIN 0                  // вход кнопок, аналоговый вход A0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ДВА НАБОРА НАСТРОЕК ДЛИТЕЛЬНОСТИ НОТ (ЗИМА, ЛЕТО) по умолчанию #define TOB_ZIMA
// для включения летнего набора нот, изменить #define TOB_ZIMA на #define TOB_LETO

// нстройка режима #define TOB_ZIMA находится вверху ↑

// настройка длительности нот для режимов внизу ↓

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ЗИМА:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ПЕРВЫЙ БЛОК ЗИМА ОСНОВНОЙ ПО УМОЛЧАНИЮ, ДЛЯ ЗИМЫ.

#ifndef TOB_LETO  // эту строку не трогать
// НАСТРОЙКИ ВРЕМЕННЫХ ЗАДЕРЖЕК  ДЛЯ НОТ ПО УМОЛЧАНИЮ: (длительность включения реле)

// для всех нот, 1 набор нот
#define DEF_TIME_OF_BLOW_TO_THE_BELL 300      // ВРЕМЯ УДАРА ЯЗЫЧКА В КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_DEL_UNT_NEXT_NOTA 3000      // ВРЕМЯ ДО ВЫЗОВА СЛЕДУЮЩЕЙ НОТЫ (ТАЙМАУТ МЕЖДУ НОТАМИ)

// для каждой ноты в отдельности, 2 набор нот
//здесь калибруется длительность сработки язычка для каждой ноты в мс по умолчанию 300
#define DEF_TIME_OF_BLOW_UNIC_NOTA_1 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 1 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_2 300   // ВРЕМЯ УДАРА ЯЗЫЧКА ВО 2 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_3 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 3 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_4 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 4 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_5 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 5 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_6 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 6 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_7 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 7 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_8 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 8 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_9 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 9 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_10 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 10 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_11 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 11 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_12 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 12 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_13 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 13 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_14 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 14 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_15 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 15 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_16 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 16 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_17 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 17 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_18 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 18 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_19 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 19 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_20 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 20 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_21 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 21 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_22 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 22 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_23 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 23 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_24 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 24 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)

// колокол который отбивает время, по умолчанию 24 колокол
#define DEF_TIME_OF_BLOW_UNIC_NOTA_HOUR_OF_BLOW DEF_TIME_OF_BLOW_UNIC_NOTA_24 // это настройка, изменять последнюю цифру

#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ЛЕТО:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ВТОРОЙ БЛОК ЛЕТО РЕЗЕРВНЫЙ, ДЛЯ ЛЕТА.

#ifdef TOB_LETO  // эту строку не трогать
// НАСТРОЙКИ ВРЕМЕННЫХ ЗАДЕРЖЕК  ДЛЯ НОТ ПО УМОЛЧАНИЮ: (длительность включения реле)

// для всех нот, 1 набор нот
#define DEF_TIME_OF_BLOW_TO_THE_BELL 300      // ВРЕМЯ УДАРА ЯЗЫЧКА В КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_DEL_UNT_NEXT_NOTA 3000      // ВРЕМЯ ДО ВЫЗОВА СЛЕДУЮЩЕЙ НОТЫ (ТАЙМАУТ МЕЖДУ НОТАМИ)

// для каждой ноты в отдельности, 2 набор нот
//здесь калибруется длительность сработки язычка для каждой ноты в мс по умолчанию 300
#define DEF_TIME_OF_BLOW_UNIC_NOTA_1 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 1 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_2 300   // ВРЕМЯ УДАРА ЯЗЫЧКА ВО 2 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_3 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 3 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_4 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 4 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_5 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 5 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_6 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 6 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_7 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 7 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_8 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 8 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_9 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 9 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_10 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 10 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_11 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 11 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_12 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 12 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_13 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 13 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_14 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 14 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_15 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 15 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_16 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 16 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_17 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 17 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_18 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 18 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_19 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 19 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_20 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 20 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_21 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 21 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_22 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 22 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_23 300   // ВРЕМЯ УДАРА ЯЗЫЧКА В 23 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)

// колокол который отбивает время, по умолчанию 24 колокол
#define DEF_TIME_OF_BLOW_UNIC_NOTA_HOUR_OF_BLOW DEF_TIME_OF_BLOW_UNIC_NOTA_24 // это настройка, изменять последнюю цифру

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
