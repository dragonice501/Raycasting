#ifndef SPRITE_H
#define SPRITE_H

#include "defs.h"
#include "graphics.h"
#include "player.h"
#include "textures.h"
#include "utils.h"
#include "ray.h"

typedef struct {
    float x;
    float y;
    bool visible;
    float distance;
    float angle;
    int texture;
} sprite_t;

void renderSpriteProjection(void);
void renderMapSprites(void);

#endif
