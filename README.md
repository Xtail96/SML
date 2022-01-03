# README #

## Описание ##

![SML_logo](./readme_files/sml_logo_mini.png)

SML - программно-аппаратная платформа для управления станками ЧПУ.

Тестирование системы производится на станках с ЧПУ "КАМЕЯ" и "РОБОР" производства [НПФ "СЕМИЛ"](https://semil.ru/).

Актуальная версия системы: SML 0.0.1.

## Контакты ##

* Электронный адрес разработчика: xtail1996@yandex.ru;
* Telegram: +7(911)209-75-27;

## Сборка релизов ##

### Для Linux ###

#### Зависимости ####

* Qt 5.10.1 <=
* opengl
* g++ and gcc
* [linuxdeployqt](https://github.com/probonopd/linuxdeployqt) или [linuxdeployqt fork](https://github.com/ApplicationsForge/linuxdeployqt)

#### Последовательность действий ####

* Простейшим вариантом сборки релиза под Linux является запуск команды`./linuxdeployqt-5-x86_64.AppImage /home/xtail/Projects/sml-qt/app/build-SML-Desktop_Qt_5_12_3_GCC_64bit-Release/SML -qmake=/home/xtail/Qt/5.12.3/gcc_64/bin/qmake -appimage` из терминала. На выходе будет сформирован файл `SML.AppImage`, который можно переносить на целевую машину для запуска программы.

* С использованием файла \*.desktop

Перед запуском `linuxdeployqt-5-x86_64.AppImage`, нужно обеспечить наличие в файловой системе директории со следующей структурой. После чего передать в утилиту `linuxdeployqt-5-x86_64.AppImage` путь до файла `\*.desktop` из этой директории.

```
releases/linux
└── usr
    ├── bin
    │   └── sml_bianry
    ├── lib
    └── share
        ├── applications
        │   └── sml.desktop
        └── icons
            └── hicolor
                └── 256x256
                    └── apps
                        └── sml_logo.png
```

Для этого, необходимо выполнить в папке репоизитория следующие действия:
1. Добавить пустую директорию `lib` в директории `releases/linux/usr/`
2. Добавить директорию `bin` в директории `releases/linux/usr`
3. Положить актуальный исполняемый файл `SML` в директорию `releases/linux/usr/bin`
4. При необходимости, обновить изображения значка приложения и файл \*.desktop.
5. Запустить команду `./linuxdeployqt-continuous-x86_64.AppImage /home/xtail/Projects/SML/sml-qt/releases/linux/usr/share/applications/sml.desktop -qmake=/home/xtail/Qt/5.9.2/gcc_64/bin/qmake -appimage` из терминала

### Для MacOS ###

Для сборки релиза для MacOS, необходимо запустить команду `./macdeployqt <RepositoryPath>/app/build-SML-Desktop_Qt_5_9_2_clang_64bit-Release/SML.app/ -dmg` из терминала. На выходе будет сформирован файл `SML.dmg`, который является одним из стандартных способов поставки программ для MacOS.
