/*
 * (C) 2014 Kimmo Lindholm <kimmo.lindholm@gmail.com> Kimmoli
 *
 */

#define TCA_ADDR 0x3b

int tca8424_readInputReport(int file, char* report);
int tca8424_initComms(unsigned char addr);
int tca8424_closeComms(int file);
int tca8424_reset(int file);
int tca8424_leds(int file, unsigned char leds);
int tca8424_readMemory(int file, int start, int len, char* data);
const char* tca8424_processKeyMap(char *map, int *code, int *isShift, int *isAlt, int *isCtrl);
