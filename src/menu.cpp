#include "menu.h"

MenuData* init_menu(void) {
    MenuData* data = (MenuData*)malloc(sizeof(MenuData));
    if (data == NULL) { return NULL; }
    data->current_option = 0;
    data->options[0] = "Play";
    data->options[1] = "Trophies";
    data->options[2] = "Options";
    data->options[3] = "Exit";

    //data->menu_font = LoadFont("resources/font/pixelplay.png");
    return data;
}

// logic where
void menu_update(MenuData* data, SceCtrlData* pad) {
    if (data == NULL) return;
    //PlayMusicStream(data->background_music);

    if (data->current_option >= 0 && data->current_option <= 3) {
        if ((pad->Buttons & PSP_CTRL_UP)) {
            data->current_option--;
            if (data->current_option < 0) {
                data->current_option = 3;
            }
        }

        if ((pad->Buttons & PSP_CTRL_DOWN)) {
            data->current_option++;
            if (data->current_option > 3) {
                data->current_option = 0;
            }
        }
    }
}
void menu_draw(MenuData* data, Font menu_font) {
    if (data == NULL) return;
    DrawRectangleGradientH(0, 0, GetScreenWidth(), GetScreenHeight(), MAROON, GOLD);

    float text_size = 24;
    float initial_y = GetScreenHeight()/2.0f - 50;

    for (int i = 0; i < 4; i++) {
        Vector2 position = { 40, initial_y + (i * 35.0f) };
        Color color = RAYWHITE;

        if (i == data->current_option) {
            color = YELLOW;
            DrawTextEx(menu_font, ">", (Vector2){position.x - 20, position.y}, text_size, 2.0f, color);
        }
        
        DrawTextEx(menu_font, data->options[i], position, text_size, 2.0f, color);
    }
}

void free_menu(MenuData* data) {
    if (data != NULL) {
        free(data);
    }
}