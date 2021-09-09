![PROJECT_PHOTO](https://github.com/AlexGyver/GyverCheat/blob/master/proj_img.jpg)
# Электронная шпаргалка на Arduino
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
Электронная шпаргалка, позволяющая незаметно списать тест  
Страница проекта на сайте: https://alexgyver.ru/GyverCheat/  
   
#### Особенности:
- Хранение ответов в EEPROM памяти микроконтроллера (до 1020 цифр)
- Хранение ответов на SD карте (неограниченное количество)
- Управление одной кнопкой
- Вывод ответов количеством вибраций

<a id="chapter-1"></a>
## Папки
**ВНИМАНИЕ! Если это твой первый опыт работы с Arduino, читай [инструкцию](#chapter-4)**
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **firmware** - прошивки для Arduino
- **schemes** - схемы подключения компонентов

<a id="chapter-2"></a>
## Схемы
![SCHEME](https://github.com/AlexGyver/GyverCheat/blob/master/schemes/scheme1.jpg)
![SCHEME](https://github.com/AlexGyver/GyverCheat/blob/master/schemes/scheme3.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
### Ссылки оставлены на магазины, с которых я закупаюсь уже не один год
- Arduino NANO https://ali.ski/kxfdF6  https://ali.ski/9TfYf
- Вибромотор https://ali.ski/Md6bhN  https://ali.ski/OegAt3
- Пачка транзисторов 2N7000 https://ali.ski/rGU5R  https://ali.ski/WzLZWn
- Пачка диодов (нужен 1N4001) https://ali.ski/BNyEJK
- Пачка резисторов (нужны 100R и 10K) https://ali.ski/FR_pwe
- Пачка выключателей https://ali.ski/OkMiw0  https://ali.ski/akNIHs
- Зарядка-защита лития https://ali.ski/12jni  https://ali.ski/ifvSLQ
- Акум на 100 mah https://ali.ski/2gYr8r  https://ali.ski/lgEjS
- MicroSD модуль https://ali.ski/X06PX  https://ali.ski/B6P04-  

Кнопки
- Тактовая кнопка https://ali.ski/Zn0KAd
- Бесшумная кнопка https://ali.ski/CLa-F
- Сенсорный модуль https://ali.ski/60yXE  https://ali.ski/Vuy7Rd

ЧипДип:
- Вибромотор https://www.chipdip.ru/product/vibrating-motor
- 100 Ом https://www.chipdip.ru/product0/47324
- 10 кОм https://www.chipdip.ru/product0/41486
- Кнопка https://www.chipdip.ru/product/kls7-ts6601-11.0-180-it-1102k
- Транзистор https://www.chipdip.ru/product/2n7000ta

## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить библиотеки в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
* **Подключить внешнее питание 5 Вольт**
* Подключить Ардуино к компьютеру
* Запустить файл прошивки (который имеет расширение .ino)
* Настроить IDE (COM порт, модель Arduino, как в статье выше)
* Настроить что нужно по проекту
* Нажать загрузить
* Пользоваться  

## Настройки в коде
    BUF_SIZE 1000	  // размер буфера (0-1021)
    MODE 1            // 0 - карта памяти, 1 - EEPROM
    MOTOR_SPEED 250   // скорость мотора (0-255)
    BTN 3             // пин кнопки
    MOTOR 9           // пин мотора

    // настройки времени вибрации
    PAUSE 500             // пауза между вибрациями, мс (когда выводит цифру)
    LONG_VIBR 1500        // длинная вибрация, мс (при ошибках и любом выходе в корень)
    ANSWER_VIBR 300       // длина импульса при выводе цифры, мс
    MANY_ANSW_PAUSE 1000  // пауза между ответами, когда в вопросе их несколько, мс
	
<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Вылетает ошибка загрузки / компиляции!
О: Читай тут: https://alexgyver.ru/arduino-first/#step-5

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)