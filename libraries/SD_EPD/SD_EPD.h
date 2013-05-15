#ifndef SP_EPD_H
#define SP_EPD_H
#include <inttypes.h>
#include "EPD.h"
#include "SD.h"

// Arduino IO layout
const int EPD_TEMPERATURE = A4;
const int EPD_PANEL_ON = 2;
const int EPD_BORDER = 3;
const int EPD_DISCHARGE = 4;
const int EPD_PWM = 5;
const int EPD_RESET = 6;
const int EPD_BUSY = 7;
const int EPD_EPD_CS = 8;
const int EPD_FLASH_CS = 9;
const uint8_t UNIFONT_RECLEN = 33;

class SD_EPD{
 private:
  bool pingpong;
  // clear screen
  void _erase();
  void _draw();

 public:
  EPD_Class EPD;
  File display_file;
  File unifont_file;
  uint16_t epd_height;
  uint16_t epd_width;
  uint16_t epd_bytes;
  uint8_t unifont_data[UNIFONT_RECLEN - 1];

  // constructor
  SD_EPD();

  // call in arduino setup function
  void setup(EPD_size size);

  // clear the display
  void clear();

  // display a WIF image at x, y
  bool display_wif(char *path, int16_t x, int16_t y);

  // used for EPD calls
  void reader(void *buffer, uint32_t address, uint16_t length);
  
  // toggle a pixel at x, y
  void togglepix(uint16_t x, uint16_t y);

  // set a pixel to a value
  void setpix(uint16_t x, uint16_t y, bool val);
  
  // display a line from start to stop. toggle each pix on line
  void toggle_line(int16_t startx, int16_t starty, int16_t stopx, int16_t stopy);

  // display a line from start to stop in specified color: true=black, false=white
  void draw_line(int16_t startx, int16_t starty, int16_t stopx, int16_t stopy, bool color);
  
  // draw an ellipse centered at cx, cy with horizontal radius rx and vertical radius ry
  // toggle each pix on ellipse
  void toggle_ellipse(uint16_t cx, uint16_t cy, uint16_t rx, uint16_t ry);

  // draw an ellipse centered at cx, cy with horizontal radius rx and vertical radius ry
  // in specified color: true=black, false=white
  void draw_ellipse(uint16_t cx, uint16_t cy, uint16_t rx, uint16_t ry, bool color);

  // display a unifont char at position x, y.  true = black, false = white
  void draw_char(uint16_t x, uint16_t y, uint16_t unic, bool color);
						
  // display many ascii chars
  void draw_ascii_string(uint16_t x, uint16_t y, char *ascii, bool color);

  // display many unicode chars
  void draw_unicode_string(uint16_t x, uint16_t y, uint16_t *unicode, bool color);

  // display new image.  Call when image is complete
  void show();

  // power off and delay
  void sleep(uint32_t delay_ms);
  
  // set spi params for epd
  void set_spi_for_epd();
  
  uint16_t put_char(uint16_t x, uint16_t y, uint16_t unic, bool color);
  uint16_t put_ascii(uint16_t x, uint16_t y, char * ascii, bool color);
  uint16_t put_unicode(uint16_t x, uint16_t y, uint16_t * unic, bool color);
  // used to pass to EPD 
  void SD_image_dims(File imgFile, unsigned short *h, unsigned short *w);
  void SD_image_reader(File imgFile, void *buffer, uint32_t address, 
		       uint16_t length);

  uint8_t unifont_read_char(File unifont_file, uint32_t i, uint8_t *dest);
  bool char_is_blank(uint32_t unic);

};

// define the E-Ink display
extern SD_EPD sdepd;

void reader_wrap(void *buffer, uint32_t address, uint16_t length);
#endif