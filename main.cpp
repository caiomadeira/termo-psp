#include "src/common.h"
#include "src/entry.h"

PSP_MODULE_INFO("Termo", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

typedef enum GameScreen {
    ENTRY = 0,
    MENU,
    GAMEPLAY
} GameScreen;

int main() {
    pspDebugScreenInit();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    Font vogueFont = LoadFontEx("resources/font/Vogue.ttf", 32, 0, 250);
    if (vogueFont.texture.id == 0) {
        print("Erro");
    }

    GameScreen currentScreen = ENTRY;

    // Habilita o controle analógico
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    SceCtrlData pad;

    SetTargetFPS(60);

    Logo* logo = init_logo();
    // Loop principal do aplicativo
    while (!WindowShouldClose()) {
        // --- Lógica de Atualização ---
        sceCtrlReadBufferPositive(&pad, 1);
        switch (currentScreen) 
        {
            case ENTRY:
            {
                if (init_logo_logic(logo) == true) {
                    currentScreen = MENU;
                    free_logo(logo);
                    logo = NULL;
                }
                
            } break;
            case MENU:
            {
                if (pad.Buttons & PSP_CTRL_CROSS) {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
            
                
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            switch(currentScreen) 
            {
                case ENTRY:
                {
                    init_logo_draw(logo, vogueFont);
                } break;
                case MENU:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS X to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    

                } break;
            }

        EndDrawing();
    }

    if (logo != NULL) {
        free_logo(logo);
    }
    UnloadFont(vogueFont);
    CloseWindow();

    sceKernelExitGame();
    return 0;
}