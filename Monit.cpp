#include "Monit.h"
#include <Arduino.h>

#include <string.h>
#include <math.h>

void send(int, int);
void write4bits(int);
 
void pulseEnable();

int _rs_pin; // LOW: command.  HIGH: character.
int _rw_pin; // LOW: write to LCD.  HIGH: read from LCD.
int _enable_pin; // activated by a HIGH pulse.
int _data_pins[4];
int _displayfunction;
int _displaycontrol;
int _displaymode;
int _initialized;
int _numlines;
int _row_offsets[4];

void MyCrystal(int rs, int enable,int d4, int d5, int d6, int d7)
{
  MyInit(4, rs, 255, enable, d4, d5, d6, d7);
}


void MyInit(int fourbitmode, int rs, int rw, int enable, int d4, int d5, int d6, int d7)
{
  _rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;
   
  _data_pins[0] = d4;
  _data_pins[1] = d5;
  _data_pins[2] = d6;
  _data_pins[3] = d7; 
  
  _displayfunction = LCD_4BITMODE;

  int cols=20;
  _displayfunction |= LCD_2LINE;
  _numlines = 4;

//set rows
  _row_offsets[0] = 0x00;
  _row_offsets[1] = 0x40;
  _row_offsets[2] = 0x00 + cols;
  _row_offsets[3] = 0x40 + cols;

  pinMode(_rs_pin, OUTPUT);
  // we can save 1 pin by not using RW. Indicate by passing 255 instead of pin#
  if (_rw_pin != 255) { 
    pinMode(_rw_pin, OUTPUT);
  }
  pinMode(_enable_pin, OUTPUT);
  
  // Do these once, instead of every time a character is drawn for speed reasons.
  for (int i=0; i< 4; ++i)
  {
    pinMode(_data_pins[i], OUTPUT);
   } 

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
  delayMicroseconds(50000); 
  // Now we pull both RS and R/W low to begin commands
  digitalWrite(_rs_pin, LOW);
  digitalWrite(_enable_pin, LOW);
  if (_rw_pin != 255) { 
    digitalWrite(_rw_pin, LOW);
  }

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1ms

    // second try
    write4bits(0x03);
    delayMicroseconds(4500); // wait min 4.1ms
    
    // third go!
    write4bits(0x03); 
    delayMicroseconds(150);

    // finally, set to 4-bit interface
    write4bits(0x02); 
  

  // finally, set # lines, font size, etc.
  command(LCD_FUNCTIONSET | _displayfunction);  

  // turn the display on with no cursor or blinking default
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  

    _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);

  // clear it off
  clear();
  leftToRight();

  // set the entry mode
  command(LCD_ENTRYMODESET | _displaymode);

}


/********** high level commands, for the user! */
void clear()
{
  command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  delayMicroseconds(2000);  // this command takes a long time!
}

void setCursor(int col, int row)
{
  const int max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting w/0
  }
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting w/0
  }
  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

/*********** mid level commands, for sending data/cmds */

 void command(int value) {
  send(value, LOW);
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
void send(int value, int mode) {
  digitalWrite(_rs_pin, mode);

  // if there is a RW pin indicated, set it low to Write
  if (_rw_pin != 255) { 
    digitalWrite(_rw_pin, HIGH);
  }
    write4bits(value>>4);
    write4bits(value);
  
}

void pulseEnable(void) {
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(1);    
  digitalWrite(_enable_pin, HIGH);
  delayMicroseconds(1);    // enable pulse must be >450ns
  digitalWrite(_enable_pin, LOW);
  delayMicroseconds(100);   // commands need > 37us to settle
}

void write4bits(int value) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(_data_pins[i], (value >> i) & 0x01);
  }
  pulseEnable();
}


 size_t write(int value) {
  send(value, HIGH);
  return value; // assume sucess
}

size_t PrintChar(char c)
{
  write(c);
}


// This is for text that flows Left to Right
void leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

size_t PrintInt(int n)
{
  return checkMinus((long) n, DEC);
}

size_t checkMinus(long n, int base)//проверка на отрицательное число
{

     if (base == 10) {
    if (n < 0) {
      int t = write('-');
      n = -n;
      
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

size_t writePrint(const char *str) {
  if (str == NULL) return 0;  //проверка на пустой указатель
  else{
    const uint8_t *buffer=(const uint8_t *)str;//берёт указатель, размер. Отправляет на печать по символьно пока размер не = 0
        size_t size=strlen(str);
        while (size--) {
          if (write(*buffer++));
          else break;
        }
      }
}


size_t printNumber(unsigned long n, uint8_t base)
{
  
  char buf[4 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];
  *str = '\0';
  do {
    char c = n % base;
    n /= base;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);
  return writePrint(str);
}

size_t PrintDouble(double number )
{
  uint8_t digits= 3;//3 это колиество знаков после запятой
  size_t n = 0;
  
  if (isnan(number)) return writePrint("nan");
  if (isinf(number)) return writePrint("inf");
  if (number > 4294967040.0) return writePrint ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return writePrint ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     n += write('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += checkMinus(int_part,10);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += write('.'); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    n += checkMinus(toPrint,10);
    remainder -= toPrint; 
  } 
  return n;
}

size_t PrintStr(const char str[])
{
   writePrint(str);
}