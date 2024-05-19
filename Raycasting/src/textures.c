#include "textures.h"

static const char* textureFileNames[NUM_TEXTURES] = {
    "./images/redbrick.png",    // [1]
    "./images/purplestone.png", // [2]
    "./images/mossystone.png",  // [3]
    "./images/graystone.png",   // [4]
    "./images/colorstone.png",  // [5]
    "./images/bluestone.png",   // [6]
    "./images/wood.png",        // [7]
    "./images/eagle.png",       // [8]
    "./images/pikuma.png",      // [9]
    "./images/barrel.png",      // [10]
    "./images/light.png",       // [11]
    "./images/table.png",       // [12]
    "./images/guard.png",       // [13]
    "./images/armor.png",        // [14]
    "./images/gold.png"        // [15]
};

void loadTextures(void)
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        upng_t* upng = upng_new_from_file(textureFileNames[i]);
        if (upng != NULL)
        {
            upng_decode(upng);
            if (upng_get_error(upng) == UPNG_EOK)
            {
                textures[i] = upng;
            }
        }
    }
}

void freeTextures(void)
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        upng_free(textures[i]);
    }
}
