# README #


## Описание ##

![SML_logo](./readme_files/sml_logo_mini.png)

SML - это система управления фрезерными и токарно-фрезерными станками ЧПУ. Система не привязана к определенному железу. Вместо этого коммуникации с контроллерами (управляющими ШД, сервоприводами, датчиками, шпинделями, прочими устройствами) реализована с помощью механизма адаптеров.

Адаптер - это специальная программа, работающая в фоне и обеспечивающая конвертацию команд, поступающих от системы SML в интерфейс управляющего контроллера и наоборот. Таким образом, имея навыки программирования, можно написать такой адаптер для интересующего Вас контроллера и использовать систему SML для управления им. Адаптеры можно релизовывать на любом языке программирования, в библиотеках к которому есть поддержка технологии Web-Socket и коммуникаций с внешними устройствами по требуемому интерфейсу подключения (USB, SerialPort, Ethernet, Bluetooth, Wifi и т.д.).

Тестирование системы производится на станках с ЧПУ "КАМЕЯ" и "РОБОР" производства [НПФ "СЕМИЛ"](https://semil.ru/).

Актуальная версия системы: SML 0.0.1:Acacia.

## Контакты ##

* EMail: xtail1996@yandex.ru;
* Skype: xtail1996;
* Phone number/Telegram: +7(911)209-75-27;
* [Project website](https://bitbucket.org/account/user/applications-forge/projects/SML).

## Release Building Instructions ##

### Linux ###

#### Requrements ####

* Qt 5.10.1 <=
* opengl
* g++ and gcc
* [linuxdeployqt](https://github.com/probonopd/linuxdeployqt) или [linuxdeployqt fork](https://github.com/ApplicationsForge/linuxdeployqt)

#### Intructions ####

* Simple example `./linuxdeployqt-5-x86_64.AppImage /home/xtail/Projects/sml-qt/app/build-SML-Desktop_Qt_5_12_3_GCC_64bit-Release/SML -qmake=/home/xtail/Qt/5.12.3/gcc_64/bin/qmake -appimage`

* With .desktop file

provide this directory structure

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

1. Add empty `lib` folder to `releases/linux/usr/`
2. Add `bin` folder to `releases/linux/usr`
3. Add new `SML` binary file to `releases/linux/usr/bin`
4. Update icons and desktop file if it neccessary.
5. Run `./linuxdeployqt-continuous-x86_64.AppImage /home/xtail/Projects/SML/sml-qt/releases/linux/usr/share/applications/sml.desktop -qmake=/home/xtail/Qt/5.9.2/gcc_64/bin/qmake -appimage`

### MacOS ###
`./macdeployqt /Users/xtail/Projects/SML/sml-qt/app/build-SML-Desktop_Qt_5_9_2_clang_64bit-Release/SML.app/ -dmg`
