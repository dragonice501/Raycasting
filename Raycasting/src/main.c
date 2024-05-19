#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "defs.h"
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "textures.h"
#include "wall.h"
#include "sprite.h"

bool isGameRunning = false;
int ticksLastFrame;

void setup(void)
{
    loadTextures();
}

void processInput(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
        {
            isGameRunning = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                isGameRunning = false;
            if (event.key.keysym.sym == SDLK_w)
                player.walkDirection = +1;
            if (event.key.keysym.sym == SDLK_s)
                player.walkDirection = -1;
            if (event.key.keysym.sym == SDLK_d)
                player.strafeDirection = -1;
            if (event.key.keysym.sym == SDLK_a)
                player.strafeDirection = 1;
            if (event.key.keysym.sym == SDLK_e)
                player.turnDirection = 1;
            if (event.key.keysym.sym == SDLK_q)
                player.turnDirection = -1;
            break;
        }
        case SDL_KEYUP:
        {
            if (event.key.keysym.sym == SDLK_w)
                player.walkDirection = 0;
            if (event.key.keysym.sym == SDLK_s)
                player.walkDirection = 0;
            if (event.key.keysym.sym == SDLK_d)
                player.strafeDirection = 0;
            if (event.key.keysym.sym == SDLK_a)
                player.strafeDirection = 0;
            if (event.key.keysym.sym == SDLK_e)
                player.turnDirection = 0;
            if (event.key.keysym.sym == SDLK_q)
                player.turnDirection = 0;
            break;
        }
    }
}

void update(void)
{
    int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);
    if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
    {
        SDL_Delay(timeToWait);
    }
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    ticksLastFrame = SDL_GetTicks();

    movePlayer(deltaTime);
    castAllRays();
}

void render(void)
{
    clearColorBuffer(0xFF000000);

    renderWallProjection();
    renderSpriteProjection();

    // Render mini map
    renderMap();
    renderMapSprites();
    renderRays();
    renderPlayer();

    renderColorBuffer();
}

void releaseResources(void)
{
    freeTextures();
    destroyWindow();
}

int main(int argc, char* argv[])
{
    isGameRunning = initializeWindow();

    setup();

    while (isGameRunning)
    {
        processInput();
        update();
        render();
    }

    releaseResources();

    return 0;
}
