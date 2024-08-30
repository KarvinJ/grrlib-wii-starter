
#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "BMfont3_png.h"
#include "alien_png.h"
#include "test_jpg_jpg.h"

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF
#define GREEN 0x008000FF
#define YELLOW 0xFFFF00FF

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SPEED = 10;

bool isGamePaused = false;

typedef struct
{
    float x;
    float y;
    float w;
    float h;
    unsigned int color;
} Rectangle;

Rectangle bounds = {0, 0, 64, 64, WHITE};

void update()
{
    const u32 padHeld = WPAD_ButtonsHeld(0);

    if (padHeld & WPAD_BUTTON_LEFT && bounds.x > 0)
    {
        bounds.x -= SPEED;
    }

    else if (padHeld & WPAD_BUTTON_RIGHT && bounds.x < SCREEN_WIDTH - bounds.w)
    {
        bounds.x += SPEED;
    }

    else if (padHeld & WPAD_BUTTON_UP && bounds.y > 0)
    {
        bounds.y -= SPEED;
    }

    else if (padHeld & WPAD_BUTTON_DOWN && bounds.y < SCREEN_HEIGHT - bounds.h)
    {
        bounds.y += SPEED;
    }
}

int main(int argc, char **argv)
{
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // loading images png
    // It fails, but I don't know why
    GRRLIB_texImg *alien = GRRLIB_LoadTexturePNG(alien_png);

    // loading fonts
    GRRLIB_texImg *tex_BMfont3 = GRRLIB_LoadTexture(BMfont3_png);

    // To indicate the font region to load.
    GRRLIB_InitTileSet(tex_BMfont3, 32, 32, 32);

    // Initialise the Wiimotes
    WPAD_Init();

    // Loop forever
    while (true)
    {
        WPAD_SetVRes(0, SCREEN_WIDTH, SCREEN_HEIGHT);
        WPAD_ScanPads(); // Scan the Wiimotes

        const u32 padDown = WPAD_ButtonsDown(0);

        // If HOME was pressed on the first Wiimote, break out of the loop
        if (padDown & WPAD_BUTTON_HOME)
        {
            break;
        }

        if (padDown & WPAD_BUTTON_A)
        {
            isGamePaused = !isGamePaused;
        }

        if (!isGamePaused)
        {
            update();
        }

        GRRLIB_FillScreen(BLACK); // Clear the screen

        // ---------------------------------------------------------------------
        // Place your drawing code below
        // ---------------------------------------------------------------------

        // displaying text with the loaded fonts.
        if (isGamePaused)
        {
            GRRLIB_Printf(150, 20, tex_BMfont3, WHITE, 1, "GAME PAUSED");
        }

        // Draw a img
        GRRLIB_DrawImg(10, 50, alien, 0, 1, 1, WHITE);

        GRRLIB_Rectangle(bounds.x, bounds.y, bounds.w, bounds.h, bounds.color, 1);

        GRRLIB_Render(); // Render the frame buffer to the TV
    }

    GRRLIB_FreeTexture(tex_BMfont3); // Be a good boy, clear the memory allocated by GRRLIB

    GRRLIB_Exit();
    exit(0); // Use exit() to exit a program, do not use 'return' from main()
}
