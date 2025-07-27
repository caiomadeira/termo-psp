#ifndef menu_h
#define menu_h

#include "common.h"

typedef struct MenuData {
    //Music background_music;
    int current_option;
    const char* options[4];
} MenuData;

MenuData* init_menu(void);
void menu_update(MenuData* data, SceCtrlData* pad);
void menu_draw(MenuData* data, Font menu_font);
void free_menu(MenuData* data);

#endif