#define LOGO_H

const unsigned char splash[] PROGMEM = { //screen image
0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xff, 
	0x40, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0xff, 
	0x40, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 
	0xa0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x07, 0xff, 
	0x90, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x07, 0xff, 
	0xc8, 0x1f, 0x81, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xfe, 0x07, 0xff, 
	0xe4, 0xc0, 0x18, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x03, 0xfc, 0x0f, 0xff, 
	0xf3, 0x87, 0xe3, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x30, 0x0f, 0xff, 
	0xf9, 0x86, 0x18, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xfe, 0x80, 0x00, 0x0f, 0xff, 
	0xfc, 0xc3, 0x8c, 0x60, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0x1f, 0xff, 
	0xff, 0x60, 0x78, 0x22, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xec, 0x40, 0x1f, 0xff, 
	0xff, 0x9c, 0x00, 0x60, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xe6, 0x00, 0x3f, 0xff, 
	0xff, 0xcf, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7c, 0x3f, 0xe0, 0x00, 0x03, 0xff, 
	0xff, 0xe3, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xc0, 0x00, 0x1c, 0x00, 0x7f, 
	0xff, 0xf9, 0xa0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xe7, 0x1b, 0xe3, 0xc0, 0x00, 0x03, 0x00, 0x1f, 
	0xff, 0xfc, 0xf8, 0x00, 0x10, 0x0f, 0xff, 0xff, 0x8f, 0x58, 0x04, 0x20, 0x00, 0x07, 0x60, 0x07, 
	0xff, 0xfe, 0x34, 0x00, 0x80, 0x03, 0xff, 0xfe, 0xe7, 0xc0, 0x04, 0x10, 0x00, 0x1f, 0xe6, 0x01, 
	0xff, 0xff, 0x1d, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x48, 0x00, 0x09, 0xd0, 0x00, 0xc7, 0xff, 0x1c, 
	0xff, 0xff, 0xc6, 0xc0, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x0b, 0x40, 0x03, 0xc7, 0xff, 0xff, 
	0xff, 0xff, 0xe3, 0xa0, 0x00, 0x00, 0x11, 0xf8, 0x04, 0x00, 0x0a, 0x50, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf1, 0xc8, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x09, 0x90, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xd8, 0x76, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x08, 0x23, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xfc, 0x1e, 0x3d, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x04, 0xcf, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x08, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc1, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xe7, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfd, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf4, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xe8, 0x00, 0x0a, 0x80, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x07, 0x80, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x19, 0xe0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x78, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x9e, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x67, 0x80, 0x00, 0x1e, 0x01, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x1c, 0xe0, 0x00, 0x20, 0x00, 0x7f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x38, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xee, 0x00, 0x00, 0x00, 0x87, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x19, 0xc0, 0x00, 0x00, 0x21, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x43, 0x70, 0x00, 0x00, 0x08, 0x7f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0x70, 0xfc, 0x00, 0x3f, 0xc2, 0x1f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xfc, 0x1f, 0x01, 0xc0, 0x1e, 0x87, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0x83, 0xc1, 0x00, 0x81, 0xc1, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xf3, 0x07, 0xfc, 0x70, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1d, 0x07, 0x07, 0x18, 0x3f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0x83, 0x83, 0x8c, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xc0, 0xff, 0x06, 0x07, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x70, 0x00, 0x06, 0x01, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x00, 0x0c, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xf8, 0x00, 0x7f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x38, 0x00, 0x00, 0x3f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0x00, 0x00, 0x0f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xc0, 0x00, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x38, 0x00, 0x07, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x80, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x70, 0x03, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x01, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x23
};

const byte PROGMEM frames[][288] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,16,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,16,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,16,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,16,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,16,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,16,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,16,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,16,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,124,25,147,16,0,0,60,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,124,25,147,16,0,0,120,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,124,25,147,16,0,0,60,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,124,25,147,16,0,0,120,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,124,25,147,0,0,0,60,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,12,25,147,0,0,0,124,25,147,0,0,0,120,25,147,0,0,0,96,25,147,0,0,0,96,25,147,0,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,124,25,147,16,0,0,60,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,124,25,147,16,0,0,120,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,124,25,147,16,0,0,60,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,12,25,147,16,0,0,124,25,147,16,0,0,120,25,147,16,0,0,96,25,147,16,0,0,96,25,147,16,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,0,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,0,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,16,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,16,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,16,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,16,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,255,255,128,14,0,0,0,1,192,24,0,0,0,0,96,25,17,16,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,124,25,147,48,0,0,60,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,12,25,147,48,0,0,124,25,147,48,0,0,120,25,147,48,0,0,96,25,147,48,0,0,96,25,147,48,0,0,96,25,17,16,0,0,96,24,0,0,0,0,96,14,0,0,0,0,192,7,255,255,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

