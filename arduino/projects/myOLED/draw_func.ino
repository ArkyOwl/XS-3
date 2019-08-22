// the most basic function, set a single pixel
void drawPixel(int16_t x, int16_t y, uint16_t color) {
  if ((x < 0) || (x >= 128) || (y < 0) || (y >= 64))
    return;

  // x is which column
  if (color == 1) 
    buffer[x+ (y/8)*LCDWIDTH] |= _BV((y%8));  
  else
    buffer[x+ (y/8)*LCDWIDTH] &= ~_BV((y%8)); 
}
/*

// Draw a character
void drawChar(int16_t x, int16_t y, unsigned char c,
          uint16_t color, uint16_t bg, uint8_t size) {

  if((x >= 128)            || // Clip right
     (y >= 64)           || // Clip bottom
     ((x + 6 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
    return;

  for (int8_t i=0; i<6; i++ ) {
    uint8_t line;
    if (i == 5) 
      line = 0x0;
    else 
      line = pgm_read_byte(font+(c*5)+i);
    for (int8_t j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          drawPixel(x+i, y+j, color);
        else {  // big size
          fillRect(x+(i*size), y+(j*size), size, size, color);
        } 
      } else if (bg != color) {
        if (size == 1) // default size
          drawPixel(x+i, y+j, bg);
        else {  // big size
          fillRect(x+i*size, y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
          uint16_t color) {
  // Update in subclasses if desired!
  for (int16_t i=x; i<x+w; i++) {
    drawFastVLine(i, y, h, color);
  }
}

void drawFastVLine(int16_t x, int16_t y,
         int16_t h, uint16_t color) {
  // Update in subclasses if desired!
  drawLine(x, y, x, y+h-1, color);
}

// Bresenham's algorithm - thx wikpedia
void drawLine(int16_t x0, int16_t y0,
          int16_t x1, int16_t y1,
          uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
*/
