#ifndef Monit_h
#define Monit_h
#include <string.h>
#include <inttypes.h>
#include <stdio.h> // for size_t
//#include "WString.h"
//#include "Printable.h"

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
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00
// flags for function set

#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


void rightToLeft(void);
void leftToRight(void);
void MyCrystal(int rs, int enable, int d4, int d5, int d6, int d7);
void MyInit(int fourbitmode, int rs, int rw, int enable, int d4, int d5, int d6, int d7);
void begin(int cols, int rows, int charsize);
void clear();
void setRowOffsets(int row1, int row2, int row3, int row4);
void setCursor(int, int); 
void command(int);


//char
int as();
size_t MyPrintChar(char);
size_t Mywrite(int);



//sring
// size_t MyPrintStr(char str[]);
// size_t write1(const char *str);
// size_t write2(const uint8_t *buffer, size_t size);



//int
size_t MyPrintInt(int);
size_t print2(long n, int base);
size_t printNumber(unsigned long n, uint8_t base);
size_t write(uint8_t);
size_t write5(const uint8_t *buffer, size_t size);
size_t write4(const char *str);

//size_t print3(const __FlashStringHelper *ifsh);

#endif
