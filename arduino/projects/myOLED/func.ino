//Command fram I2C
void sendCommand(uint8_t c)
{
  // I2C
    uint8_t control = 0x00;   // Co = 0, D/C = 0
    Wire.beginTransmission(I2CADDR);
    Wire.write(control);
    Wire.write(c);
    Wire.endTransmission();
}
//Data frame I2c
void ssd1306_data(uint8_t c)
{
  // I2C
  uint8_t control = 0x40;   // Co = 0, D/C = 1
  Wire.beginTransmission(I2CADDR);
  Wire.write(control);
  Wire.write(c);
  Wire.endTransmission();
}
void beginOLED()
{
  sendCommand(DISPLAYOFF);                    // 0xAE
  sendCommand(SETDISPLAYCLOCKDIV);            // 0xD5
  sendCommand(0x80);                                  // the suggested ratio 0x80
  sendCommand(SETMULTIPLEX);                  // 0xA8
  sendCommand(0x3F);
  sendCommand(SETDISPLAYOFFSET);              // 0xD3
  sendCommand(0x0);                                   // no offset
  sendCommand(SETSTARTLINE | 0x0);            // line #0
  sendCommand(CHARGEPUMP);                    // 0x8D
  if (SWITCHCAPVCC == EXTERNALVCC) 
    { sendCommand(0x10); }
  else 
    { sendCommand(0x14); }
  sendCommand(MEMORYMODE);                    // 0x20
  sendCommand(0x00);                                  // 0x0 act like ks0108
  sendCommand(SEGREMAP | 0x1);
  sendCommand(COMSCANDEC);
  sendCommand(SETCOMPINS);                    // 0xDA
  sendCommand(0x12);
  sendCommand(SETCONTRAST);                   // 0x81
  if (SWITCHCAPVCC == EXTERNALVCC) 
    { sendCommand(0x9F); }
  else 
    { sendCommand(0xCF); }
  sendCommand(SETPRECHARGE);                  // 0xd9
  if (SWITCHCAPVCC == EXTERNALVCC) 
    { sendCommand(0x22); }
  else 
    { sendCommand(0xF1); }
  sendCommand(SETVCOMDETECT);                 // 0xDB
  sendCommand(0x40);
  sendCommand(DISPLAYALLON_RESUME);           // 0xA4
  sendCommand(NORMALDISPLAY);                 // 0xA6
  
  sendCommand(0xb0);
  sendCommand(0x10);
  sendCommand(0x01);//Set original position to (0,0)
  sendCommand(DISPLAYON);
}

void displayFrame()
{
    // save I2C bitrate
    uint8_t twbrbackup = TWBR;
    TWBR = 12; // upgrade to 400KHz!
    // I2C
    for (uint16_t i=0; i<(LCDWIDTH*LCDHEIGHT/8); i++) {
      // send a bunch of data in one xmission
      Wire.beginTransmission(I2CADDR);
      Wire.write(0x40);
      for (uint8_t x=0; x<16; x++)
      {
          Wire.write(buffer[i]);
          i++;
      }
      i--;
      Wire.endTransmission();
    }
    TWBR = twbrbackup;
}
