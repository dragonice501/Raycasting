#pragma once

#include "defs.h"
#include "graphics.h"
#include "map.h"

typedef struct
{
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float width;
    float height;
    int turnDirection; // -1 for left, +1 for right
    int walkDirection; // -1 for back, +1 for front
    int strafeDirection;
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} player_t;

extern player_t player;

#define MOUSE_SENSITIVITY 2

void movePlayer(float deltaTime);
void renderPlayer(void);