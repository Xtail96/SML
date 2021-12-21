# README #

## Описание ##

![SML_logo](./readme_files/sml_logo_mini.png)

SML - программно-аппаратная платформа для управления станками ЧПУ.

Тестирование системы производится на станках с ЧПУ "КАМЕЯ" и "РОБОР" производства [НПФ "СЕМИЛ"](https://semil.ru/).

Актуальная версия системы: SML 0.0.1.

## Контакты ##

* EMail: xtail1996@yandex.ru;
* Phone number/Telegram: +7(911)209-75-27;

## Release Building Instructions ##

### Linux ###

#### Requirements ####

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
