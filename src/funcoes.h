#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "structs.h"

int EscolhaBotao(Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle botaovoltar);
void DesenhaMenuPrincipal(Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle sair, Rectangle botaovoltar);
void TelaAbreLivro(const char* caminhodat, Rectangle botaovoltar);
void TelaTelaBuscaReceita(const char* caminhodat, Rectangle botaovoltar);
void DesenhaBotao(Rectangle botao, const char* texto, int tamanho);
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

void DesenhaMenuPrincipal(Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle sair, Rectangle botaovoltar){
    
    ClearBackground(ORANGE);

    //titulo
    DrawText("Livro de receitas da vovó", 74, 17 , 50, BLUE);
    
    //botao abrir livro
    DesenhaBotao(abrirlivro, "Abrir livro", 40);
    //botao buscar receita
    DesenhaBotao(buscarreceita, "Buscar receita", 29);
    //botao cadastrar receita
    DesenhaBotao(novareceita, "Cadastrar receita", 23);
    //botao sair
    DesenhaBotao(sair, "Sair", 29);


}

void TelaAbreLivro(const char* caminhodat, Rectangle botaovoltar){
    
    ClearBackground(ORANGE);
    DrawText("Livro Aberto", 300, 100, 20, GRAY);
    DesenhaBotao(botaovoltar, "Voltar", 8);
}

void TelaBuscaReceita(const char* caminhodat, Rectangle botaovoltar){
    
    ClearBackground(ORANGE);
    DrawText("Pesquisar receita", 300, 100, 20, GRAY);
    DesenhaBotao(botaovoltar, "Voltar", 8);

}

void TelaCadastroReceita(const char* caminhodat, const char* caminhotxt, Rectangle botaovoltar){
    
    ClearBackground(ORANGE);
    DrawText("Cadastrar receita", 300, 100, 20, GRAY);
    DesenhaBotao(botaovoltar, "Voltar", 8);

}

void DesenhaBotao(Rectangle botao, const char* texto, int tamanho){
    DrawRectangleRec(botao, WHITE);
    DrawText(texto, (int)botao.x + 7, (int)botao.y + 8, tamanho, BLUE);
    if (CheckCollisionPointRec(GetMousePosition(), botao)){
        for(int i = 0; i < 4; i++){
            DrawRectangleLines((int)botao.x - i, (int)botao.y - i, (int)botao.width + i*2, (int)botao.height + i*2, RED);
        }
    }else DrawRectangleLines((int)botao.x, (int)botao.y, (int)botao.width, (int)botao.height, DARKGRAY);
}



