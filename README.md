STM32 C playground from 2015
========================================
This document is written on 171228

# Description
This was a working playground for my learning of C programming language, microcontrollers in general and STM32 and contains various drivers for various cheap eBay modules and uC internal components, such as:
- Buses:
  - SPI
  - I2C - there is a bug (erm, feature): returns 88 (or some other uint) as error message (which is also valid as a return value)
  - GPIO
  - UART (RX part is probably sub par)
- EEPROM
- Wireless modules:
  - nRF24
  - WiFi UART
  - BT UART
- GLCD ILI9341 (SPI, 240x320)
- OLED SSD1306 (I2C)
- ADC
- PWM
- barometer (BMP180) - this little fucker had a nasty bug in official datasheet
- compass (maybe in PMS branch - Primjena mikroupravljačkih sustava - college project)
- RTC
- WS28xx LED array (src/led_array.{c,h}) - proof of concept, probably stolen from somewhere
- Wii nunchuck

It is abandoned somewhere in 2015. but it still contains some useful stuff, for example EEPROM driver which should work with SPI and I2C drivers (C function pointers).
There are untranslated comments, commit messages and stuff like that but it can be used as an example.
Also, there is some sort of layerisation (AVR ATmega{8,328,32} and STM32{F1,F4}).
In 2016 I had plans to rewrite this in C++ (or better C) but I was (and still am) lazy piece of shiet.
In 2017 I have started learning embedded Rust, so, in some time in near future (ha!) Rust STM32 repo should contain better examples.

Also, non C parts which can be used as examples:
- Makefile
  - skriptica.sh (en: little script): This script will parse main.c and return all dependencies which need to be built
    It will return something like "src/spi.x" and Makefile then will take over and search for 'src/spi.h' and 'src/spi.c' and cook that into 'obj/spi.o'
    Probably needs update for clang newer than 3.6 or GCC 4.8 (aww, memories, GCC when we all were young and World seems like a less shitty place™)
- Linker script
- OpenOCD upload scripts

# Branches
- diplomski (college master thesis): IIRC, this should contains unfinished prototype for "lazy house"
- master2: Well, something thas I have used as master "back in the day"
- master: This description

# Licence
- Beerware - my stuff
- ST libs (src/lib) are BSDL or something like that

# Disclaimer
- Untranslated comments and commit messages
- Curse words (in English and Balkanian) are probable.
- I don't know if this can still be compilated, but, again, it should be used as an example.
- I was far from git expert back in the day.
- I am not very well organized person.

# OT
Evo ga Filka, ogledni primjerak mojih sranja, valjda ce nesta posluzit.
