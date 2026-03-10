#include "sa.h"




#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
#define WINDOW_TITLE    "basic example"




int main(int argc, char** argv) 
{
    /*
        nova_Start also recieves window flags, and it is only way to set window flags at starting
        so don't expect something as nova_SetWindowFlag as that doesn't exists.
    */
    nova_Start(0);

    nova_OpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);


    /*
        SageAura provides more than 50 inbuilt colors,
        if you want to create your own just use this macro -
            NOVA_RGB(r, g, b) 
        
        SageAura also provide hex option so you can use like 
        nova_SetBackgroundColor(nova_ColorFromHex("#00FFFFFF"));
    */
    nova_SetBackgroundColor(NOVA_BABY_BLUE); // default dark greyish type

    // nova_SetTargetFPS(60); // but don't worry to write this, 60 FPS was by default

    while (nova_Play())
    {
        nova_BeginDrawing();

        

        nova_EndDrawing();
    }


    /*
        nova_CloseWindow call is very important as it not only destroy window but also
        clear the many internal flags and many other type of type destruction. Like
        Default Font auto destruction, So developer wont bother to unload fonts that are set
        for default.
    */

    nova_CloseWindow();
    return 0;
}