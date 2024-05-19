#include "sprite.h"

#define NUM_SPRITES 25

static sprite_t sprites[NUM_SPRITES] = {
    { .x = 738, .y = 164, .texture = 9 }, // barrel
    { .x = 738, .y = 292, .texture = 9 }, // barrel
    { .x = 738, .y = 420, .texture = 9 }, // barrel
    { .x = 738, .y = 548, .texture = 9 }, // barrel
    { .x = 866, .y = 228, .texture = 9 }, // barrel
    { .x = 866, .y = 356, .texture = 9 }, // barrel
    { .x = 866, .y = 484, .texture = 9 }, // barrel
    { .x = 866, .y = 572, .texture = 9 }, // barrel
    { .x = 410, .y = 572, .texture = 13 }, // armour
    { .x = 410, .y = 484, .texture = 13 }, // armour
    { .x = 410, .y = 356, .texture = 13 }, // armour
    { .x = 410, .y = 228, .texture = 13 }, // armour
    { .x = 550, .y = 164, .texture = 13 }, // armour
    { .x = 550, .y = 292, .texture = 13 }, // armour
    { .x = 550, .y = 420, .texture = 13 }, // armour
    { .x = 550, .y = 548, .texture = 13 }, // armour
    { .x = 100, .y = 164, .texture = 14 }, // gold
    { .x = 100, .y = 292, .texture = 14 }, // gold
    { .x = 100, .y = 420, .texture = 14 }, // gold
    { .x = 100, .y = 548, .texture = 14 }, // gold
    { .x = 220, .y = 228, .texture = 14 }, // gold
    { .x = 220, .y = 356, .texture = 14 }, // gold
    { .x = 220, .y = 484, .texture = 14 }, // gold
    { .x = 220, .y = 572, .texture = 14 }, // gold
    { .x = 170, .y = 620, .texture = 14 }, // gold
};

void renderMapSprites(void) {
    for (int i = 0; i < NUM_SPRITES; i++)
    {
        drawRect(
            sprites[i].x * MINIMAP_SCALE_FACTOR,
            sprites[i].y * MINIMAP_SCALE_FACTOR,
            2,
            2,
            sprites[i].visible ? 0xFF00FFFF : 0xFF44444);
    }
}

void renderSpriteProjection(void) {
    sprite_t visibleSprites[NUM_SPRITES];
    int numVisibleSprites = 0;
    for (int i = 0; i < NUM_SPRITES; i++)
    {
        float angleSpritePlayer = player.rotationAngle - atan2(sprites[i].y - player.y, sprites[i].x - player.x);

        if (angleSpritePlayer > PI)
        {
            angleSpritePlayer -= TWO_PI;
        }
        if (angleSpritePlayer < -PI)
        {
            angleSpritePlayer += TWO_PI;
        }

        angleSpritePlayer = fabs(angleSpritePlayer);

        const float EPSILON = 0.2f;
        if (angleSpritePlayer < FOV_ANGLE / 2 + EPSILON)
        {
            sprites[i].visible = true;
            sprites[i].angle = angleSpritePlayer;
            sprites[i].distance = distanceBetweenPoints(player.x, player.y, sprites[i].x, sprites[i].y);
            visibleSprites[numVisibleSprites] = sprites[i];
            numVisibleSprites++;
        }
        else
        {
            sprites[i].visible = false;
        }
    }

    for (int i = 0; i < numVisibleSprites - 1; i++)
    {
        for (int j = i + 1; j < numVisibleSprites; j++)
        {
            if (visibleSprites[i].distance < visibleSprites[j].distance)
            {
                sprite_t temp = visibleSprites[i];
                visibleSprites[i] = visibleSprites[j];
                visibleSprites[j] = temp;
            }
        }
    }

    for (int i = 0; i < numVisibleSprites; i++)
    {
        sprite_t sprite = visibleSprites[i];

        float perpDistance = sprite.distance * cos(sprite.angle);

        float spriteHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;
        float spriteWidth = spriteHeight;

        float spriteTopY = WINDOW_HEIGHT / 2 - spriteHeight / 2;
        spriteTopY = spriteTopY < 0 ? 0 : spriteTopY;

        float spriteBottomY = WINDOW_HEIGHT / 2 + spriteHeight / 2;
        spriteBottomY = spriteBottomY > WINDOW_HEIGHT ? WINDOW_HEIGHT : spriteBottomY;

        float spriteAngle = atan2(sprite.y - player.y, sprite.x - player.x) - player.rotationAngle;
        float spriteScreenPositionX = tan(spriteAngle) * DIST_PROJ_PLANE;

        float spriteLeftX = (WINDOW_WIDTH / 2) + spriteScreenPositionX - spriteWidth / 2;
        float spriteRightX = spriteLeftX + spriteWidth;

        int textureWidth = upng_get_width(textures[sprite.texture]);
        int textureHeight = upng_get_height(textures[sprite.texture]);

        for (int x = spriteLeftX; x < spriteRightX; x++)
        {
            float texelWidth = (textureWidth / spriteWidth);
            int textureOffsetX = (x - spriteLeftX) * texelWidth;

            for (int y = spriteTopY; y < spriteBottomY; y++)
            {
                int distanceFromTop = y + spriteHeight / 2 - WINDOW_HEIGHT / 2;
                int textureOffsetY = distanceFromTop * (textureHeight / spriteHeight);

                if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
                {
                    color_t* spriteTextureBuffer = (color_t*)upng_get_buffer(textures[sprite.texture]);
                    color_t texelColor = spriteTextureBuffer[textureOffsetX + textureOffsetY * textureWidth];

                    if(sprite.distance < rays[x].distance && texelColor != 0xFFFF00FF)
                        drawPixel(x, y, texelColor);
                }
            }
        }
    }
}
