#pragma once

#include <stdio.h>
#include <stdint.h>
#include "defs.h"
#include "upng.h"

#define NUM_TEXTURES 15

upng_t* textures[NUM_TEXTURES];

void loadTextures(void);
void freeTextures(void);