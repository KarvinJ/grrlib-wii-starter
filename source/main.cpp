
#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "BMfont2_png.h"
// #include "alien_1_png.h"
#include "test_jpg_jpg.h"

#define BLACK 0x000000FF
#define WHITE 0xFFFFFFFF

typedef struct
{
    float x;
    float y;
    float w;
    float h;
    unsigned int color;
} Rectangle;

int main(int argc, char **argv)
{
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    Rectangle bounds = {0, 0, 64, 64, WHITE};

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SPEED = 10;

    // loading images png
    // GRRLIB_texImg *tex_test_jpg = GRRLIB_LoadTexture(test_jpg_jpg);

    // loading fonts
    GRRLIB_texImg *tex_BMfont2 = GRRLIB_LoadTexture(BMfont2_png);
    // To indicate the font region to load.
    GRRLIB_InitTileSet(tex_BMfont2, 16, 16, 32);

    // Initialise the Wiimotes
    WPAD_Init();

    // Loop forever
    while (true)
    {
        WPAD_SetVRes(0, SCREEN_WIDTH, SCREEN_HEIGHT);
        WPAD_ScanPads(); // Scan the Wiimotes

        const u32 padDown = WPAD_ButtonsDown(0);
        const u32 padHeld = WPAD_ButtonsHeld(0);

        GRRLIB_FillScreen(BLACK); // Clear the screen

        // displaying text with the loaded fonts.
        GRRLIB_Printf(300, 25, tex_BMfont2, WHITE, 1, "DEMO");

        // Draw img
        //  GRRLIB_DrawImg(10, 50, tex_test_jpg, 0, 1, 1, WHITE);

        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (padDown & WPAD_BUTTON_HOME)
        {
            break;
        }
        if (padHeld & WPAD_BUTTON_LEFT && bounds.x > 0)
        {
            bounds.x -= SPEED;
        }
        if (padHeld & WPAD_BUTTON_RIGHT && bounds.x < SCREEN_WIDTH - bounds.w)
        {
            bounds.x += SPEED;
        }
        if (padHeld & WPAD_BUTTON_UP && bounds.y > 0)
        {
            bounds.y -= SPEED;
        }
        if (padHeld & WPAD_BUTTON_DOWN && bounds.y < SCREEN_HEIGHT - bounds.h)
        {
            bounds.y += SPEED;
        }

        // ---------------------------------------------------------------------
        // Place your drawing code here
        // ---------------------------------------------------------------------

        GRRLIB_Rectangle(bounds.x, bounds.y, bounds.w, bounds.h, bounds.color, 1);

        GRRLIB_Render(); // Render the frame buffer to the TV
    }

    GRRLIB_FreeTexture(tex_BMfont2); // Be a good boy, clear the memory allocated by GRRLIB

    GRRLIB_Exit();
    exit(0); // Use exit() to exit a program, do not use 'return' from main()
}
