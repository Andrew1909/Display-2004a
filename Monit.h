#ifndef Monit_h
#define Monit_h
#include <string.h>
 #include <inttypes.h>
 #include <stdio.h> // for size_t
#include "WString.h"
#include "Printable.h"




#define DEC 10
#define HEX 16
#define OCT 8
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
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

void MyCrystal(int rs, int enable, int d4, int d5, int d6, int d7);
void MyInit(int fourbitmode, int rs, int rw, int enable, int d4, int d5, int d6, int d7);
void begin(int cols, int rows, int charsize);
void clear();
void home();
void display();

//char
int write( int *buffer, int size);
int write1(const char *str);
size_t write2(const char *buffer, size_t size);
int MyPrintChar(char);

//int
size_t MyPrintInt(int, int = DEC);
size_t print2(long n, int base);
size_t printNumber(unsigned long n, uint8_t base);
size_t print3(const __FlashStringHelper *ifsh);

void setRowOffsets(int row1, int row2, int row3, int row4);
void createChar(int, int[]);
void setCursor(int, int); 
int Mywrite(int);
void command(int);
#endif
