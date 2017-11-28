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
#define HHH 0  // HIGH
#define LLL 1  // LOW
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// НАСТРОЙКИ:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SET_CLOK_FOR_PROG 0           // если 1 то установка часов будет при записи программы. если 0 то нет
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUDNICNIY_ENABLE 0            // если 1 то будничный будет отбиваться. если 0 то нет
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUDNICNIY_DELAY_DEF 4000      //  задержка между ударами в будничный колокол
#define HOUR_OF_BLOW_DELAY 5000       // задержка между ударами колокола, при отбивании колоколом количества часов. 5с
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEF_YARKOST_DISPLEYA_DEF 256  // яркость экрана MIN 0 - MAX 256, если 0 подсветка отключена
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ТЕРМОРЕГУЛЯТОР БОКСА С УСРОЙСТВОМ:
#define DEF_TEMP_ENABLE 1             // 1 функция подогрева включена. 0 функция подогрева выключена
#define DEF_TEMP_ON 5                 // температура включения подогрева
#define DEF_TEMP_OFF 10               // температура выключения подогрева
#define DEF_TEMP_RELE_PIN 46          // пин Arduino к которому подключено реле обогревателя

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// РАСПИНОВКА КОЛОКОЛОВ: для настройки изменять цифры, те что в конце, перед коментарием
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// для настройки изменять последнюю цифру(номер пина Arduino к которому подключен ударный механизм(язычек))
// значение идущее за #define является именем колокола. к которому нужно обращатся в программе для создания мелодий.
#define RELE_K1 22                    // 1 колокол (реле 1)
#define RELE_K2 23                    // 2 колокол (реле 2)
#define RELE_K3 24                    // 3 колокол (реле 3)
#define RELE_K4 25                    // 4 колокол (реле 4)
#define RELE_K5 26                    // 5 колокол (реле 5)
#define RELE_K6 27                    // 6 колокол (реле 6)
#define RELE_K7 28                    // 7 колокол (реле 7)
#define RELE_K8 29                    // 8 колокол (реле 8)
#define RELE_K9 30                    // 9 колокол (реле 9)
#define RELE_K10 31                   // 10 колокол (реле 10)
#define RELE_K11 32                   // 11 колокол (реле 11)
#define RELE_K12 33                   // 12 колокол (реле 12)
#define RELE_K13 34                   // 13 колокол (реле 13)
#define RELE_K14 35                   // 14 колокол (реле 14)
#define RELE_K15 36                   // 15 колокол (реле 15)
#define RELE_K16 37                   // 16 колокол (реле 16)
#define RELE_K17 38                   // 17 колокол (реле 17)
#define RELE_K18 39                   // 18 колокол (реле 18)
#define RELE_K19 40                   // 19 колокол (реле 19)
#define RELE_K20 41                   // 20 колокол (реле 20)
#define RELE_K21 42                   // 21 колокол (реле 21)
#define RELE_K22 43                   // 22 колокол (реле 22)
#define RELE_K23 44                   // 23 колокол (реле 23)
#define RELE_K24 45                   // 24 колокол (реле 24)

// колокол который отбивает время, по умолчанию 24 колокол
#define RELE_HOUR_BLOW RELE_K22       // это настройка, изменять последнюю цифру что после К
// будничный колокол
#define RELE_BUDNICNIY RELE_K22       // это настройка, изменять последнюю цифру что после К
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// РАСПИНОВКА КОМПЛЕКТУЮЩИХ:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ДИСПЛЕЙ:
#define DEF_LCD_INIT_PIN 8, 9, 4, 5, 6, 7  // настройка распиновки дисплея
#define DEF_LCD_LIGHT_PIN 10               // подсветка дисплея
#define DEF_LCD_KEY_PIN 0                  // вход кнопок, аналоговый вход A0
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\\
// \\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// НАСТРОЙКИ ВРЕМЕННЫХ ЗАДЕРЖЕК  ДЛЯ НОТ ПО УМОЛЧАНИЮ: (длительность включения реле)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// НАСТРОЙКА ТИПА ПАМЯТИ ДЛЯ ДЛИТЕЛЬНОСТИ НОТ. ЧТОБ РАБОТАЛА ЗАПИСЬ ИЗ МЕНЮ ПОСТАВИТЬ 0. ДЛЯ ПЕРВОГО ЗАПУСКА EEPROM 1.
#define DEF_TIME_OF_BLOW_UNIC_NOTA_ENABLE 0  // если 1 то будет запись длит. из конфига. если 0 то из настроек меню
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// для всех нот, 1 набор нот
#define DEF_TIME_OF_BLOW_TO_THE_BELL 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_DEL_UNT_NEXT_NOTA 1500              // ВРЕМЯ ДО ВЫЗОВА СЛЕДУЮЩЕЙ НОТЫ (ТАЙМАУТ МЕЖДУ НОТАМИ)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// для каждой ноты в отдельности, 2 набор нот
//здесь калибруется длительность сработки язычка для каждой ноты в мс по умолчанию 300
#define DEF_TIME_OF_BLOW_UNIC_NOTA_1 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В 1 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_2 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА ВО 2 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_3 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В 3 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_4 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В 4 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_5 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В 5 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_6 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В 6 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_7 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В 7 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_8 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В 8 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_9 100UL      // ВРЕМЯ УДАРА ЯЗЫЧКА В 9 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_10 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 10 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_11 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 11 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_12 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 12 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_13 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 13 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_14 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 14 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_15 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 15 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_16 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 16 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_17 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 17 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_18 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 18 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_19 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 19 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_20 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 20 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_21 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 21 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_22 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 22 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_23 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 23 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
#define DEF_TIME_OF_BLOW_UNIC_NOTA_24 100UL     // ВРЕМЯ УДАРА ЯЗЫЧКА В 24 КОЛОКОЛ В МИЛЛИСЕКУНДАХ (ВРЕМЯ НОТЫ)
