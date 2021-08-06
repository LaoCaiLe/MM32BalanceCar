#ifndef _KEY_H
#define _KEY_H

#include "headfile.h"

#define Key1_PIN C8
#define Key2_PIN G7
#define Key3_PIN G5
#define Key4_PIN G3

#define Key1 1
#define Key2 2
#define Key3 3
#define Key4 4

void Key_Init(void);

uint8 Key_Scan(uint8 mode);

#endif
