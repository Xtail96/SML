# README #

## Описание ##

![SML_logo](./readme_files/sml_logo_mini.png)

SML - это система управления фрезерными и токарно-фрезерными станками ЧПУ. Система не привязана к определенному железу. Вместо этого коммуникации с контроллерами (управляющими ШД, сервоприводами, датчиками, шпинделями, прочими устройствами) реализована с помощью механизма адаптеров.

Адаптер - это специальная программа, работающая в фоне и обеспечивающая конвертацию команд, поступающих от системы SML в интерфейс управляющего контроллера и наоборот. Таким образом, имея навыки программирования, можно написать такой адаптер для интересующего Вас контроллера и использовать систему SML для управления им. Адаптеры можно релизовывать на любом языке программирования, в библиотеках к которому есть поддержка технологии Web-Socket и коммуникаций с внешними устройствами по требуемому интерфейсу подключения (USB, SerialPort, Ethernet, Bluetooth, Wifi и т.д.).

В рамках проекта реализуются адаптеры для слеующих контроллеров управления (U1 - управление датчиками и внешними устройствами. U2 - управление ШД или сервоприводами):

1. Arduino (U1) - в разработке. [Код скетча](https://bitbucket.org/applications-forge/arduinou1/src/master/). [Код адаптера](https://bitbucket.org/applications-forge/u1serialadapter/src/master/).
2. SiLabs (U1) - в разработке. [Код адаптера](https://bitbucket.org/applications-forge/usbxpressadapter/src/master/).
3. KFLOP (U2) - в разработке. Разработка еще не началась.
4. Mach3 (U1 + U2) - в разработке. Разработка еще не началась.

Этот репозиторий содержит только ядро системы управления - клиентское приложение для управления станком. Примеры реализации адаптеров приведены в [другом репозитории](https://bitbucket.org/account/user/applications-forge/projects/SML).
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
* [linuxdeployqt](https://github.com/probonopd/linuxdeployqt) или [linuxdeployqt fork](https://github.com/ApplicationsForge/linuxdeployqt)

#### Intructions ####

* Simple example `./linuxdeployqt-continuous-x86_64.AppImage /home/xtail/Projects/SML/sml-qt/app/build-SML-Desktop_Qt_5_10_1_GCC_64bit2-Release/SML -qmake=/home/xtail/Qt/5.10.1/gcc_64/bin/qmake -appimage`

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
1. Add `bin` folder to `releases/linux/usr`
1. Add new `SML` binary file to `releases/linux/usr/bin`
1. Update icons and desktop file if it neccessary.
1. Run `./linuxdeployqt-continuous-x86_64.AppImage /home/xtail/Projects/SML/sml-qt/releases/linux/usr/share/applications/sml.desktop -qmake=/home/xtail/Qt/5.9.2/gcc_64/bin/qmake -appimage`

### MacOS ###
`./macdeployqt /Users/xtail/Projects/SML/sml-qt/app/build-SML-Desktop_Qt_5_9_2_clang_64bit-Release/SML.app/ -dmg`
