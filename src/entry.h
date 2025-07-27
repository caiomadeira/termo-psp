#ifndef entry_h
#define entry_h

#include "common.h"

#define LOGO_SQUARE_SIZE 160 // antigo era 256
#define LOGO_LINE_THICKNESS 8 // antes era 16

#define CENTRALIZED_X SCREEN_WIDTH / 2 - LOGO_SQUARE_SIZE / 2
#define CENTRALIZED_Y SCREEN_HEIGHT / 2 - LOGO_SQUARE_SIZE / 2
#define DURATION_3S 180
#define DURATION_5S 300
#define AUTHOR_NAME "By Caio Madeira"

typedef struct Logo {
    int x;
    int y;
    int fps;
    int letters_count;
    int top_width;
    int left_height;
    int bottom_width;
    int right_height;
    int state;
    float alpha;
} Logo;

Logo* init_logo(void);
bool init_logo_logic(Logo* logo);
void init_logo_draw(Logo* logo, Font customFont); 
void free_logo(Logo* logo);

#endif