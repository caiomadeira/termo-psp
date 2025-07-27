#include "entry.h"

Logo* init_logo(void) {
    Logo* data = (Logo*)malloc(sizeof(Logo));
    if (data == NULL) { return NULL; }
    data->x = CENTRALIZED_X;
    data->y = CENTRALIZED_Y;
    data->fps = 0;
    data->letters_count = 0;
    data->top_width = 16;
    data->left_height = 16;
    data->bottom_width = 16;
    data->right_height = 16;
    data->state = 0;
    data->alpha = 1.0f;
    return data;
}

void free_logo(Logo* logo) {
    //UnloadFont(logo->font_ttf);
    if (logo != NULL) {
        free(logo);
    }
}

bool init_logo_logic(Logo* logo) {
    if (logo == NULL) return false;

    switch(logo->state) {
        case 0: // Espera inicial
            logo->fps++;
            if (logo->fps >= 120) {
                logo->state = 1;
                logo->fps = 0;
            }
            break;
        
        case 1: // Animação de expansão 1
            logo->top_width += 4;
            logo->left_height += 4;
            if (logo->top_width >= LOGO_SQUARE_SIZE) logo->state = 2;
            break;
            
        case 2: // Animação de expansão 2
            logo->bottom_width += 4;
            logo->right_height += 4;
            if (logo->bottom_width >= LOGO_SQUARE_SIZE) logo->state = 3;
            break;
            
        case 3: // Escrevendo o texto
            logo->fps++;
            // CORRIGIDO: usa >= em vez de / para evitar bugs
            if (logo->fps >= 8 && logo->letters_count < (int)strlen(AUTHOR_NAME)) {
                logo->letters_count++;
                logo->fps = 0;
            }
            if (logo->letters_count >= (int)strlen(AUTHOR_NAME)) {
                logo->state = 4;
                logo->fps = 0;
            }
            break;
            
        case 4: // Espera com o texto na tela
            logo->fps++;
            if (logo->fps >= 90) { // Espera 1.5 segundos
                logo->state = 5;
            }
            break;
            
        case 5: // Fade out
            logo->alpha -= 0.02f;
            if (logo->alpha <= 0.0f) {
                logo->alpha = 0.0f;
                // ** CORREÇÃO DO LOOP INFINITO: VAI PARA O ESTADO 6 **
                logo->state = 6;
            }
            break;
            
        case 6: // Fim da animação
            return true; // Retorna true para mudar de tela
    }
    
    return false; // Retorna false enquanto a animação não termina
}

void init_logo_draw(Logo* logo, Font customFont) {
    if (logo == NULL) return;
    ClearBackground(BLACK);

    if (logo->state == 0) {
        // Usa a nova espessura
        if ((logo->fps/15)%2) DrawRectangle(logo->x, logo->y, LOGO_LINE_THICKNESS, LOGO_LINE_THICKNESS, RAYWHITE);
    }
    else if (logo->state < 3) {
        // Usa a nova espessura
        DrawRectangle(logo->x, logo->y, logo->top_width, LOGO_LINE_THICKNESS, RAYWHITE);
        DrawRectangle(logo->x, logo->y, LOGO_LINE_THICKNESS, logo->left_height, RAYWHITE);
        if (logo->state == 2) {
            // Usa o novo tamanho e espessura para posicionar as outras linhas
            DrawRectangle(logo->x + LOGO_SQUARE_SIZE - LOGO_LINE_THICKNESS, logo->y, LOGO_LINE_THICKNESS, logo->right_height, RAYWHITE);
            DrawRectangle(logo->x, logo->y + LOGO_SQUARE_SIZE - LOGO_LINE_THICKNESS, logo->bottom_width, LOGO_LINE_THICKNESS, RAYWHITE);   
        }
    }
    else if (logo->state >= 3 && logo->state <=5) {
        // Desenha as 4 linhas com a nova espessura e tamanho
        DrawRectangle(logo->x, logo->y, logo->top_width, LOGO_LINE_THICKNESS, Fade(RAYWHITE, logo->alpha));
        DrawRectangle(logo->x, logo->y + LOGO_LINE_THICKNESS, LOGO_LINE_THICKNESS, logo->left_height - (2*LOGO_LINE_THICKNESS), Fade(RAYWHITE, logo->alpha));
        DrawRectangle(logo->x + LOGO_SQUARE_SIZE - LOGO_LINE_THICKNESS, logo->y + LOGO_LINE_THICKNESS, LOGO_LINE_THICKNESS, logo->right_height - (2*LOGO_LINE_THICKNESS), Fade(RAYWHITE, logo->alpha));
        DrawRectangle(logo->x, logo->y + LOGO_SQUARE_SIZE - LOGO_LINE_THICKNESS, logo->bottom_width, LOGO_LINE_THICKNESS, Fade(RAYWHITE, logo->alpha));

        // Desenha o retângulo interno para o texto, ajustado ao novo tamanho
        int innerPadding = LOGO_LINE_THICKNESS + 4; // Um pequeno preenchimento
        int innerSize = LOGO_SQUARE_SIZE - (innerPadding * 2);
        DrawRectangle(logo->x + innerPadding, logo->y + innerPadding, innerSize, innerSize, Fade(BLACK, logo->alpha));

        // Centraliza o texto dentro da nova área
        Vector2 textSize = MeasureTextEx(customFont, AUTHOR_NAME, (float)customFont.baseSize, 2.0f);
        // Vector2 textPosition = {
        //     (float)logo->x + (LOGO_SQUARE_SIZE - textSize.x) / 2,
        //     (float)logo->y + (LOGO_SQUARE_SIZE - textSize.y) / 2
        // };
        Vector2 textPosition = { (float)logo->x, textSize.y };

        DrawTextEx(customFont, 
                   TextSubtext(AUTHOR_NAME, 0, logo->letters_count), 
                   textPosition, 
                   (float)16, 
                   2.0f, 
                   Fade(RAYWHITE, logo->alpha));
    }
}
