# README #

## Описание ##

* SML - это систему управления для станков с ЧПУ. Запуск и тестирование системы производится на станках с ЧПУ "КАМЕЯ" и "РОБОР" производства [НПФ "СЕМИЛ"](https://semil.ru/).
* SML 1.0.0:Acacia;
* [Сайт проекта](https://appsforgeinc.bitbucket.io/);

## Контакты ##

* EMail: xtail1996@yandex.ru;
* Skype: xtail1996;
* Phone number/Telegram: +7(911)209-75-27;

## Releases ##

### Linux ###

* Simple `./linuxdeployqt-continuous-x86_64.AppImage /home/xtail/Projects/SML/sml-qt/app/build-SML-Desktop_Qt_5_9_2_GCC_64bit-Release/SML -qmake=/home/xtail/Qt/5.9.2/gcc_64/bin/qmake -appimage`

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
