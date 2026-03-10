#include <stdio.h>

#include "sa.h"




void MyEventHandler(nova_Window* window, const nova_Event* e)
{
    // switch (e->type)
    // {
    //     case NOVA_EVENT_KEY_DOWN:
    //         printf("User callback: Key DOWN %d\n", e->key.key);
    //         break;

    //     case NOVA_EVENT_MOUSE_BUTTON_DOWN:
    //         if (e->mouseButton.button == NOVA_MOUSE_BUTTON_LEFT)
    //             printf("User callback: LEFT CLICK!\n");
    //         break;

    //     case NOVA_EVENT_MOUSE_SCROLL:
    //         printf("User callback: Scroll %.1f\n", e->scroll.offset);
    //         break;

    //     // add whatever you want
    // }
}




int main(int argc, char **argv)
{
    nova_Start(NOVA_RESIZABLE);

    nova_OpenWindow(800, 600, "title");

    nova_Texture* tex = nova_LoadTexture("test.PNG");


    nova_Entity player = nova_SpawnEntity();
    nova_Vec2 pos = {50.0f, 100.0f};
    nova_Sizei PlayerSize = {200, 200};

    nova_EntitySetPosition(player, pos.x, pos.y);
    nova_EntitySetVelocity(player, 0.0f, 0.0f);

    nova_EntityGiveSprite(
        player, tex, NOVA_RECT(pos.x, pos.y, PlayerSize.width, PlayerSize.height)
    );

    float speed = 180.0f;

    nova_SetEventTo(MyEventHandler);

    // nova_Event event;
    while (nova_Play())
    {
        // needed for run any type of event handling, can be NULL but important to call for event handling

        float DeltaTime = nova_GetDeltaTime();

        /* Use only when neeed countinous movement */
        // if (nova_IsKeyPressed(NOVA_KEY_A))      // pressed this exact frame
        //     nova_EntitySetVelocity(player, -speed, 0.0f);

        // if (nova_IsKeyPressed(NOVA_KEY_W))      // pressed this exact frame
        //     nova_EntitySetVelocity(player, 0.0f, -speed);

        // if (nova_IsKeyPressed(NOVA_KEY_D))      // pressed this exact frame
        //     nova_EntitySetVelocity(player, speed, 0.0f);

        // if (nova_IsKeyPressed(NOVA_KEY_S))      // pressed this exact frame
        //     nova_EntitySetVelocity(player, 0.0f, speed);

        // Horizontal
        float vx = 0.0f;
        float vy = 0.0f;
        if (nova_IsKeyDown(NOVA_KEY_A) || nova_IsKeyDown(NOVA_KEY_LEFT)) {
            vx = -speed;
        }
        if (nova_IsKeyDown(NOVA_KEY_D) || nova_IsKeyDown(NOVA_KEY_RIGHT)) {
            vx = +speed;
        }

        // Vertical
        if (nova_IsKeyDown(NOVA_KEY_W) || nova_IsKeyDown(NOVA_KEY_UP)) {
            vy = -speed;
        }
        if (nova_IsKeyDown(NOVA_KEY_S) || nova_IsKeyDown(NOVA_KEY_DOWN)) {
            vy = +speed;
        }


        if (nova_IsKeyPressed(NOVA_KEY_F))      // pressed this exact frame
            nova_EnableFullScreen();


        nova_EntitySetVelocity(player, vx, vy);


        nova_BeginDrawing();


        nova_DrawAllSprites();



        nova_EndDrawing();

        nova_EntitiesUpdate(DeltaTime);
    }

    nova_UnloadTexture(tex);
    nova_CloseWindow();
}