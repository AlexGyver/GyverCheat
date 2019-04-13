/*
  Скетч к проекту "Электронная супер-шпора"
  Страница проекта (схемы, описания): https://alexgyver.ru/GyverCheat/
  Исходники на GitHub: https://github.com/AlexGyver/GyverCheat/
  Нравится, как написан код? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор: AlexGyver Technologies, 2018
  https://AlexGyver.ru/
*/

/*
   Накликиваем нужный билет/вариант - получаем подтверждение в виде количества импульсов вибрации
   Долгий клик - выбор билета/варианта, подтверждение - одиночный короткий импульс вибрации
   Клик - вывод вибрацией ответа на следующий вопрос
   Долгий клик - возврат в меню, подтверждение - долгая вибрация
   Долгая вибрация также будет при ошибках (нет такого билета, закончились вопросы в выбранном билете)
*/

// ----------------- НАСТРОЙКИ -----------------
#define BUF_SIZE 1000	  // размер буфера (0-1021)
#define MODE 1            // 0 - карта памяти, 1 - EEPROM
#define MOTOR_SPEED 250   // скорость мотора (0-255)
#define BTN 3             // пин кнопки
#define MOTOR 9           // пин мотора

// настройки времени вибрации
#define PAUSE 500             // пауза между вибрациями, мс (когда выводит цифру)
#define LONG_VIBR 1500        // длинная вибрация, мс (при ошибках и любом выходе в корень)
#define ANSWER_VIBR 300       // длина импульса при выводе цифры, мс
#define MANY_ANSW_PAUSE 1000  // пауза между ответами, когда в вопросе их несколько, мс

// ----------------- ДЛЯ РАЗРАБОТЧИКОВ -----------------
#define SIZE_POS 1022     // позиция ячейки с размером буфера
#include "GyverButton.h"
GButton butt(BTN);

#if (MODE == 0)
#include <SPI.h>
#include <SD.h>
File myFile;
const char *filename;
#define logName "exam.txt"
#else
#include "EEPROMex.h"
#endif

char buf[BUF_SIZE];
uint16_t bufSize;
uint16_t bufPos;
uint16_t bufCounter;

void setup() {
  Serial.begin(9600);
  butt.setTimeout(800);
#if (MODE == 0)
  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(10)) {
    Serial.println(F(" failed!"));
  }
  Serial.println(F(" done"));

  if (SD.exists(logName)) {
    Serial.print(logName); Serial.println(F(" found"));
  } else {
    Serial.print(logName); Serial.println(F(" not found"));
  }

  myFile = SD.open(logName, FILE_READ);

  int fileSize = myFile.size();
  bufPos = 0;
  bufCounter = 0;
  myFile.seek(0);
  for (int i = 0; i < fileSize; i++) {
    char sdBuf = (char)myFile.read();
    if (sdBuf > 38 && sdBuf < 122) {
      buf[bufCounter] = sdBuf;
      bufCounter++;
    }
  }
  bufSize = bufCounter;
#else
  if (EEPROM.read(SIZE_POS) != 255 && EEPROM.read(SIZE_POS + 1) != 255) {
    bufSize = EEPROM.readInt(SIZE_POS);
    for (int i = 0; i < bufSize; i++) {
      buf[i] = (char)EEPROM.readByte(i);
    }
    Serial.println(F("EEPROM read OK"));
  }
#endif
  Serial.println(F("System start"));
  pinMode(MOTOR, OUTPUT);  
}

byte ticket = 1;
byte question = 0;
byte answer;
byte mode = 0;
uint16_t ticketPos;

char bufRead() {
#if (MODE == 0)
  char retChar = myFile.read();
#else
  char retChar = buf[bufPos];
#endif
  bufPos++;
  return retChar;
}

void loop() {
  if (Serial.available() > 0) {
    bufCounter = 0;
#if (MODE == 0)
    myFile.seek(0);   // в начало файла
#endif
    while (Serial.available() > 0) {
      char serialBuf = Serial.read();
      if (serialBuf > 38 && serialBuf < 122) {
#if (MODE == 1)
        buf[bufCounter] = serialBuf;
        bufCounter++;
        if (bufCounter > BUF_SIZE) {
          Serial.println(F("Buffer overflow"));
          break;
        }
#else
        bufCounter++;
        myFile.print(serialBuf);
#endif
      }
      delay(10);
    }
    Serial.println(F("Serial read success"));
    bufSize = bufCounter;
#if (MODE == 1)
    for (int i = 0; i < bufSize; i++) {
      EEPROM.updateByte(i, (byte)buf[i]);
    }
    EEPROM.updateInt(SIZE_POS, bufSize);
    Serial.println(F("EEPROM write success"));
#else
    myFile.flush();
    Serial.println(F("SD write success"));
#endif
  }

  butt.tick();    // опрос кнопки

  if (butt.isHolded()) {
    if (mode == 0) {
      mode = 1;
      Serial.println(F("Ticket chosen"));
      bufPos = 0;
#if (MODE == 0)
      myFile.seek(0);   // в начало файла
#endif
      while (true) {
        if (bufRead() == 'B') {     // ищем префикс B
          char buf1 = bufRead();
          char buf2 = bufRead();
          byte tickNum;
          if (buf2 == ';') {        // если номер билета <10 (сразу встретили разделитель)
            tickNum = buf1 - '0';
            ticketPos = bufPos;
          } else {                  // если номер билета >10 (не встретили разделитель)
            tickNum = (buf1 - '0') * 10 + (buf2 - '0');
            bufPos++;
            ticketPos = bufPos;
          }
          if (tickNum == ticket) {
            Serial.println(F("Ticket found"));
            vibrate(1, ANSWER_VIBR);
            question = 0;
            break;
          }
        }
        if (bufPos >= bufSize) {
          Serial.println(F("Error: not found"));
          vibrate(1, LONG_VIBR);
          butt.getClicks(); // чистим буфер
          mode = 0;
          break;
        }
      }
    } else {
      mode = 0;
      Serial.println(F("Back to root"));
      vibrate(1, LONG_VIBR);
      butt.getClicks(); // чистим буфер
    }
  }

  if (butt.isClick() && mode == 1) {                // кликаем в режиме вывода ответов
    char bufChar;
    while (true) {
      if (bufPos >= bufSize) {                      // проверка на конец файла
        Serial.println(F("Error: end of file"));
        vibrate(1, LONG_VIBR);
        mode = 0;
        break;
      }
      bufChar = bufRead();
      if (bufChar == 'B') {                         // проверка на следующий билет
        mode = 0;
        Serial.println(F("The End. Back to root"));
        vibrate(1, LONG_VIBR);
        break;
      }
      if (buf[bufPos] == ',') {                     // если запятая
        char bufMany[10];                           // массив хранения нескольких ответов
        byte bufManyCounter = 0;                    // счетчик массива bufMany
        byte counter = 0;
        while (true) {
          bufMany[bufManyCounter] = buf[bufPos + counter - 1];  // пишем в массив
          counter++;                                            // счётчик
          if (buf[bufPos + counter - 1] == ',') {               // проверяем есть ли ещё запятая
            bufManyCounter++;       // в этом случае ++ количество ответов
            counter++;              // и счётчик
          } else break;
        }
        bufPos += (counter - 1);    // запоминаем позицию в файле с учётом ответа с запятыми
        question++;                 // ++ номер вопроса
        Serial.print("Question " + String(question) + ", answer: ");
        for (byte i = 0; i < bufManyCounter + 1; i++) {
          answer = bufMany[i] - '0';
          Serial.print(answer);
          vibrate(answer, ANSWER_VIBR);
          delay(MANY_ANSW_PAUSE);
          Serial.print(", ");
        }
        Serial.println();
        break;
      } else {                                      // если не запятая, а просто цифра
        answer = bufChar - '0';
        question++;
        Serial.println("Question " + String(question) + ", answer: " + String(answer));
        vibrate(answer, ANSWER_VIBR);
        break;
      }

    }
  }

  if (butt.hasClicks()) {
    if (mode == 0) {
      ticket = butt.getClicks();
      Serial.println("Ticket " + String(ticket));
      vibrate(ticket, ANSWER_VIBR);
    }
    /*  // выбор ответа кликами. Не работает одновременно с переключением
      else if (mode == 1) {
      question = butt.getClicks();
      myFile.seek(ticketPos - 1 + question * 3);
      answer = myFile.read() - '0';
      Serial.println("Fast question " + String(question) + ", answer: " + String(answer));
      }*/
  }
}

void vibrate(byte amount, int duration) {
  for (byte i = 0; i < amount; i++) {
    analogWrite(MOTOR, MOTOR_SPEED);
    delay(duration);
    analogWrite(MOTOR, 0);
    delay(PAUSE);
  }
}
