#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "structs.h"

#define COR_FUNDO ORANGE
#define COR_LETRA BLUE
#define COR_BOTAO LIGHTGRAY
#define COR_LETRA_BOTAO BLUE
#define COR_BOTAO_SELECIONADO RED
#define COR_CAIXATEXTO WHITE
#define MAX_FONTS 2

const int screenWidth = 700;
const int screenHeight = 1000;

int EscolhaBotao(Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle botaovoltar);
void DesenhaMenuPrincipal(Font fonts[], Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle sair, Rectangle botaovoltar);
void TelaAbreLivro(Font fonts[], const char* caminhodat, Rectangle botaovoltar);
void TelaTelaBuscaReceita(Font fonts[], const char* caminhodat, Rectangle botaovoltar);
void TelaCadastroReceita(int escolhatexto, Receita r, Font fonts[], const char* caminhodat, const char* caminhotxt, Rectangle botaovoltar, Rectangle botaotipo, Rectangle botaonome, Rectangle botaoingredientes, Rectangle botaomodoPreparo, Rectangle botaotempoPreparo, Rectangle botaorendimento, Rectangle botaocadastrar);
char TipoReceita(Receita r, Rectangle botaotipo, int mouseOnText, int aux);
int EscolhaTexto(int mousenoquadrado,  int aux, Rectangle botaonome, Rectangle botaoingredientes, Rectangle botaomodoPreparo, Rectangle botaotempoPreparo, Rectangle botaorendimento);
void ReceberEscrita(char* dado, int max);
void RetangulosTexto(Font fonts[], Rectangle botao, char* dado, int tamanho, char* titulo, int tipo);
static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);
void DesenhaBotao(Font fonts[], Rectangle botao, const char* texto, int tamanho);

int EscolhaBotao(int aux, Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle sair, Rectangle botaovoltar){
    
    //checar se esté em cima de abrir livro
    if (CheckCollisionPointRec(GetMousePosition(), abrirlivro) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 1;
    //checar se esté em cima de buscar receita
    }else if (CheckCollisionPointRec(GetMousePosition(), buscarreceita) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 2;
    //checar se esté em cima de cadastrar receita
    }else if (CheckCollisionPointRec(GetMousePosition(), novareceita) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 3;
    //checar se esté em cima de voltar
    }else if (CheckCollisionPointRec(GetMousePosition(), sair) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 4;
    }else if (CheckCollisionPointRec(GetMousePosition(), botaovoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 0;
    }

    return aux;
}

void DesenhaMenuPrincipal(Font fonts[], Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle sair, Rectangle botaovoltar){
    
    Vector2 positions[MAX_FONTS] = { 0 };
    positions[0] = (Vector2){ 74, 17 };
    ClearBackground(COR_FUNDO);

    //titulo
    //DrawText("Livro de receitas da vovó", 74, 17 , 50, COR_LETRA);
    DrawTextEx(fonts[0], "Livro de receitas da vovó", positions[0], 50, 2, COR_LETRA);
    
    //botao abrir livro
    DesenhaBotao(fonts, abrirlivro, "Abrir livro", 40);
    //botao buscar receita
    DesenhaBotao(fonts, buscarreceita, "Buscar receita", 29);
    //botao cadastrar receita
    DesenhaBotao(fonts, novareceita, "Cadastrar receita", 23);
    //botao sair
    DesenhaBotao(fonts, sair, "Sair", 29);

}

void TelaAbreLivro(Font fonts[], const char* caminhodat, Rectangle botaovoltar){
    
    ClearBackground(COR_FUNDO);
    Vector2 positions[MAX_FONTS] = { 0 };
    positions[0] = (Vector2){ 300, 100 };
    
    //DrawText("Livro Aberto", 300, 100, 20, COR_LETRA);
    DrawTextEx(fonts[1], "Livro Aberto", positions[0], 40, 2, COR_LETRA_BOTAO);

    DesenhaBotao(fonts, botaovoltar, "Voltar", 29);
    
}

void TelaBuscaReceita(Font fonts[], const char* caminhodat, Rectangle botaovoltar){
    
    ClearBackground(COR_FUNDO);

    Vector2 positions[MAX_FONTS] = { 0 };
    positions[0] = (Vector2){ 300, 100 };

    //DrawText("Pesquisar receita", 300, 100, 20, COR_LETRA);
    DrawTextEx(fonts[1], "Pesquisar receita", positions[0], 40, 2, COR_LETRA_BOTAO);

    DesenhaBotao(fonts, botaovoltar, "Voltar", 29);

}

void TelaCadastroReceita(int escolhatexto, Receita r, Font fonts[], const char* caminhodat, const char* caminhotxt, Rectangle botaovoltar, Rectangle botaonome, Rectangle botaotipo, Rectangle botaoingredientes, Rectangle botaomodoPreparo, Rectangle botaotempoPreparo, Rectangle botaorendimento, Rectangle botaocadastrar){
    
    ClearBackground(COR_FUNDO);

    //DrawText("Cadastrar receita", 300, 100, 20, COR_LETRA);
    //DrawTextEx(fonts[1], TextFormat("escolatexto: %d", escolhatexto), (Vector2){ 300, 500 }, 40, 2, COR_LETRA_BOTAO);
    
    DesenhaBotao(fonts, botaovoltar, "Voltar", 29);
    DesenhaBotao(fonts, botaocadastrar, "Cadastrar", 29);

    

    
    RetangulosTexto(fonts, botaonome,r.nome, 50, "Nome", 1);
    RetangulosTexto(fonts, botaoingredientes, r.ingredientes, 29, "Ingredientes", 1);
    RetangulosTexto(fonts, botaomodoPreparo, r.modoPreparo, 40, "Modo de preparo", 2);
    RetangulosTexto(fonts, botaotempoPreparo, r.tempoPreparo, 29, "Tempo de preparo", 1);
    RetangulosTexto(fonts, botaorendimento, r.rendimento, 29, "Rendimento", 1);

    //isso ak n ta funcionando
    if(r.tipo == '0'){
        DesenhaBotao(fonts, botaotipo, "Tipo: Doce", 29);
    }else if(r.tipo == '1'){
        DesenhaBotao(fonts, botaotipo, "Tipo: Salgado", 29);
    }


}

char TipoReceita(Receita r, Rectangle botaotipo, int mouseOnText, int aux){

    if (CheckCollisionPointRec(GetMousePosition(), botaotipo)) mouseOnText = 1;
        else mouseOnText = 0;

        if (mouseOnText && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && r.tipo == '0'){
            aux = 1;
        }else if(mouseOnText && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && r.tipo == '1'){
            aux = 0;
        }

        if(aux == 1){
            r.tipo = '1';
        }else if(aux == 0){
            r.tipo = '0';
        }

        return r.tipo;


    // if (CheckCollisionPointRec(GetMousePosition(), botaotipo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && r.tipo == '0'){
    //     r.tipo = '1';
    // }else if (CheckCollisionPointRec(GetMousePosition(), botaotipo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && r.tipo == '1'){
    //     r.tipo = '0';
    // }  
    // return r.tipo;


}

int EscolhaTexto(int mousenoquadrado, int aux, Rectangle botaonome, Rectangle botaoingredientes, Rectangle botaomodoPreparo, Rectangle botaotempoPreparo, Rectangle botaorendimento){

    if(CheckCollisionPointRec(GetMousePosition(), botaonome)){
        aux = 1;
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        //mousenoquadrado = 1;
    }else if(CheckCollisionPointRec(GetMousePosition(), botaoingredientes)){
        aux = 2;
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        //mousenoquadrado = 2;
    }else if(CheckCollisionPointRec(GetMousePosition(), botaomodoPreparo)){
        aux = 3;
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        //mousenoquadrado = 3;
    }else if(CheckCollisionPointRec(GetMousePosition(), botaotempoPreparo)){
        aux = 4;
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        //mousenoquadrado = 4;
    }else if(CheckCollisionPointRec(GetMousePosition(), botaorendimento)){
        aux = 5;
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        //mousenoquadrado = 5;
    }else {
        aux = 0;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        //mousenoquadrado = 0;
    }

    if(aux == 1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        mousenoquadrado = 1;
        return mousenoquadrado;
    }else if(aux == 2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        mousenoquadrado = 2;
        return mousenoquadrado;
    }else if(aux == 3 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        mousenoquadrado = 3;
        return mousenoquadrado;
    }else if(aux == 4 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        mousenoquadrado = 4;
        return mousenoquadrado;
    }else if(aux == 5 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        mousenoquadrado = 5;
        return mousenoquadrado;
    }else if(aux == 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        mousenoquadrado = 0;
        return mousenoquadrado;
    }
    
    
}

void ReceberEscrita(char* dado, int max){

    int key = GetCharPressed();
    int pos;

        // Check if more characters have been pressed on the same frame
        while (key > 0){
            pos = strlen(dado);
            // NOTE: Only allow keys in range [32..125]
            if ((strlen(dado) < max)){
                dado[pos] = (char)key;
                dado[pos+1] = '\0'; 
            }
            if (IsKeyPressed(KEY_ENTER)){
                dado[pos] = '\n';
                dado[pos+1] = '\0';
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)){
            pos = strlen(dado) - 1;
            if (pos < 0){
                pos = 0;
            }
            dado[pos] = '\0';
        }
}

void RetangulosTexto(Font fonts[], Rectangle botao, char* dado, int tamanho, char* titulo, int tipo){
   
    DrawTextEx(fonts[0], titulo, (Vector2){ botao.x +13, botao.y - 32 }, 30, 2, COR_LETRA_BOTAO);
    DrawRectangleRec(botao, COR_CAIXATEXTO);
    if(tipo == 1){
        DrawTextEx(fonts[1], dado, (Vector2){ botao.x + 13, botao.y + 7 }, tamanho, 2, COR_LETRA_BOTAO);
    }else if(tipo == 2){
        DrawTextBoxed(fonts[1], dado, (Rectangle){ botao.x + 4, botao.y + 4, botao.width - 4, botao.height - 4 }, (float)tamanho, 2.0f, true, COR_LETRA_BOTAO);
    }
    // if (CheckCollisionPointRec(GetMousePosition(), botao)){
    //     SetMouseCursor(MOUSE_CURSOR_IBEAM);
    // }else{
    //     SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    // }
    
    
}

static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint){
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}

static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint){
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}


void DesenhaBotao(Font fonts[], Rectangle botao, const char* texto, int tamanho){
   
    DrawRectangleRec(botao, COR_BOTAO);
    
    Vector2 positions[MAX_FONTS] = { 0 };
    positions[0] = (Vector2){ botao.x + 13, botao.y + 7 };

    //DrawText(texto, (int)botao.x + 7, (int)botao.y + 8, tamanho, COR_LETRA_BOTAO);
    DrawTextEx(fonts[0], texto, positions[0], tamanho, 2, COR_LETRA_BOTAO);
    
    if (CheckCollisionPointRec(GetMousePosition(), botao)){
        for(int i = 0; i < 4; i++){
            DrawRectangleLines((int)botao.x - i, (int)botao.y - i, (int)botao.width + i*2, (int)botao.height + i*2, COR_BOTAO_SELECIONADO);
            //DrawRectangleRec(botao, COR_BOTAO_SELECIONADO);
            //DrawText(texto, (int)botao.x + 7, (int)botao.y + 8, tamanho, COR_LETRA_BOTAO);
        }
    }else DrawRectangleLines((int)botao.x, (int)botao.y, (int)botao.width, (int)botao.height, BLACK);
}



