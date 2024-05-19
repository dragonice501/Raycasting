#include "player.h"
#include "utils.h"

player_t player = {
    .x = WINDOW_WIDTH * 0.85f,
    .y = WINDOW_HEIGHT * 0.9f,
    .width = 1,
    .height = 1,
    .turnDirection = 0,
    .walkDirection = 0,
    .strafeDirection = 0,
    .rotationAngle = (3 * PI) / 2,
    .walkSpeed = 75,
    .turnSpeed = 90 * (PI / 180)
};

void movePlayer(float deltaTime)
{
    player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;
    normalizeAngle(&player.rotationAngle);

    float moveStep = player.walkDirection * player.walkSpeed * deltaTime;
    float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
    float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;

    if (!mapHasWallAt(newPlayerX, newPlayerY))
    {
        player.x = newPlayerX;
        player.y = newPlayerY;
    }

    float strafeAngle = player.rotationAngle - (M_PI * 0.5f);
    normalizeAngle(&player.strafeDirection);

    float strafeStep = player.strafeDirection * player.walkSpeed * deltaTime;
    float newPlayerStrafeRightX = player.x + cos(strafeAngle) * strafeStep;
    float newPlayerStrafeRightY = player.y + sin(strafeAngle) * strafeStep;

    if (!mapHasWallAt(newPlayerStrafeRightX, newPlayerStrafeRightY))
    {
        player.x = newPlayerStrafeRightX;
        player.y = newPlayerStrafeRightY;
    }
}

void renderPlayer(void)
{
    drawRect(
        player.x * MINIMAP_SCALE_FACTOR,
        player.y * MINIMAP_SCALE_FACTOR,
        player.width * MINIMAP_SCALE_FACTOR,
        player.height * MINIMAP_SCALE_FACTOR,
        0xFFFFFFFF
    );
}
