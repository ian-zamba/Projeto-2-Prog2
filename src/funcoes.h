#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "structs.h"

#define COR_FUNDO ORANGE
#define COR_LETRA BLUE
#define COR_BOTAO LIGHTGRAY
#define COR_LETRA_BOTAO BLUE
#define COR_BOTAO_SELECIONADO RED
#define MAX_FONTS 2

int EscolhaBotao(Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle botaovoltar);
void DesenhaMenuPrincipal(Font fonts[], Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle sair, Rectangle botaovoltar);
void TelaAbreLivro(Font fonts[], const char* caminhodat, Rectangle botaovoltar);
void TelaTelaBuscaReceita(Font fonts[], const char* caminhodat, Rectangle botaovoltar);
void DesenhaBotao(Font fonts[], Rectangle botao, const char* texto, int tamanho);
void TelaCadastroReceita(const char* caminhodat, const char* caminhotxt, Rectangle botaovoltar);

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

void TelaCadastroReceita(Font fonts[], const char* caminhodat, const char* caminhotxt, Rectangle botaovoltar){
    
    ClearBackground(COR_FUNDO);

    Vector2 positions[MAX_FONTS] = { 0 };
    positions[0] = (Vector2){ 300, 100 };

    //DrawText("Cadastrar receita", 300, 100, 20, COR_LETRA);
    DrawTextEx(fonts[1], "Cadastrar receita", positions[0], 40, 2, COR_LETRA_BOTAO);
    
    DesenhaBotao(fonts, botaovoltar, "Voltar", 29);

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



