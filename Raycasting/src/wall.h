#pragma once

#include "defs.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "textures.h"

#include <stdint.h>

void changeColorIntensity(color_t* color, float factor);
void renderWallProjection(void);