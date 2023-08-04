#ifndef Monit_h
#define Monit_h
#include <string.h>
#include <inttypes.h>
#include <stdio.h> // for size_t

#define DEC 10
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSOROFF 0x00
#define LCD_BLINKOFF 0x00

// flags for function set
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08


void rightToLeft(void);
void leftToRight(void);
void MyCrystal(int rs, int enable, int d4, int d5, int d6, int d7);
void MyInit(int fourbitmode, int rs, int rw, int enable, int d4, int d5, int d6, int d7);
void clear();
void setCursor(int, int); 
void command(int);

size_t PrintChar(char);
size_t write(int);
size_t PrintStr(const char str[]);
size_t PrintInt(int);
size_t checkMinus(long n, int base);
size_t printNumber(unsigned long n, uint8_t base);
size_t checkPointNull(const char *str);
size_t PrintDouble(double n);

#endif
