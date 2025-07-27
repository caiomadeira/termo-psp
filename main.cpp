#include "src/common.h"
#include "src/entry.h"
#include "src/menu.h"

PSP_MODULE_INFO("Termo", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

typedef enum GameScreen {
    ENTRY = 0,
    MENU,
    GAMEPLAY,
    TROPHIES,
    OPTIONS,
    EXIT
} GameScreen;

SceCtrlData pad;

int main() {
    pspDebugScreenInit();
    //InitAudioDevice();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    Font vogueFont = LoadFontEx("resources/font/Vogue.ttf", 32, 0, 250);
    Font menu_font = LoadFont("resources/font/pixelplay.png");

    if (vogueFont.texture.id == 0 || menu_font.texture.id == 0 ) {
        print("Erro ao carregar a fonte.");
    }

    GameScreen currentScreen = ENTRY;

    // Habilita o controle analógico
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    SetTargetFPS(60);

    Logo* logo = init_logo();
    MenuData* menu_data = init_menu();
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
                menu_update(menu_data, &pad);
                if ((pad.Buttons & PSP_CTRL_CROSS)) {
                    if (menu_data->current_option == 0) currentScreen = GAMEPLAY;
                    else if (menu_data->current_option == 1) currentScreen = TROPHIES;
                    else if (menu_data->current_option == 2) currentScreen = OPTIONS;
                    else if (menu_data->current_option == 3) currentScreen = EXIT;
                }
            } break;
            case GAMEPLAY:
            {
                
            } break;
            case TROPHIES:
            {

            } break;
            case OPTIONS:
            {

            } break;
            case EXIT:
            {
                goto exit_loop;
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
                    menu_draw(menu_data, menu_font);
                } break;
                case GAMEPLAY:
                {
                    DrawText("TELA EM CONSTRUCAO", 50, 120, 20, LIGHTGRAY);

                } break;
                case TROPHIES:
                {
                    DrawText("TELA EM CONSTRUCAO", 50, 120, 20, LIGHTGRAY);

                } break;
                case OPTIONS:
                {
                    DrawText("TELA EM CONSTRUCAO", 50, 120, 20, LIGHTGRAY);

                } break;
                case EXIT:
                {

                } break;
            }

        EndDrawing();
    }

exit_loop:
    if (logo != NULL) free_logo(logo);
    if (menu_data != NULL) free_menu(menu_data);
    UnloadFont(vogueFont);
    UnloadFont(menu_font);

    CloseWindow();

    sceKernelExitGame();
    return 0;
}