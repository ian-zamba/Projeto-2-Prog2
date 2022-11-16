#include <stdio.h>
#include <string.h>
#include <cctype>
#include "raylib.h"
#include "structs.h"

#define COR_FUNDO ORANGE
#define COR_LETRA BLACK
#define COR_BOTAO LIGHTGRAY
#define COR_LETRA_BOTAO BLACK
#define COR_BOTAO_SELECIONADO RED
#define COR_CAIXATEXTO WHITE
#define MAX_FONTS 2

//variaveis fixas
const int screenWidth = 700;
const int screenHeight = 1000;
const char* caminhodat = "src/Arquivos/receitad.dat";
const char* caminhotxt = "src/Arquivos/receitad.txt";

//declarando as funcoes
//---------------------------------------------------------
int EscolhaBotao(Receita r, Rectangle abrirlivro, Rectangle buscarreceita,
Rectangle novareceita, Rectangle botaovoltar, Rectangle botaocadastro,
Rectangle botaoaddingredientes, Rectangle botaoproximo, Rectangle botaoanterior, int escolhatexto);
//---------------------------------------------------------
void ChecarEscolha(int &escolha, Receita &r, char* ingrediente, int &pagina,
int tamanhoarq, int contarbusca, char* buscarnome, int &quantingrediente);
//---------------------------------------------------------
void DesenhaMenuPrincipal(Font fonts[], Rectangle abrirlivro, Rectangle buscarreceita,
Rectangle novareceita, Rectangle sair, Rectangle botaovoltar);
//---------------------------------------------------------
void TelaAbreLivro(Font fonts[], Rectangle botaovoltar, Rectangle botaoproximo,
Rectangle botaoanterior, int &proximo, int &pagina, int &tamanhoarq, Rectangle textomodopreparo);
//---------------------------------------------------------
void TelaBuscaReceita(Font fonts[], Rectangle botaovoltar, Rectangle textobuscar,
char* buscarnome, int tamanhoarq, int pagina, int contarbusca, Rectangle botaoproximo,
Rectangle botaoanterior, Rectangle textomodopreparo);
//---------------------------------------------------------
void TelaCadastroReceita(int &escolha, int escolhatexto, char* ingrediente, Receita &r,
Font fonts[], Rectangle botaovoltar, Rectangle botaotipo, Rectangle textonome,
Rectangle textoingredientes, Rectangle botaoaddingredientes, Rectangle textomodopreparo,
Rectangle textotempopreparo, Rectangle textorendimento, Rectangle botaocadastrar, int quantidade);
//---------------------------------------------------------
char TipoReceita(Receita r, Rectangle botaotipo);
//---------------------------------------------------------
int EscolhaTexto(int mousenoquadrado, Rectangle textonome, Rectangle textoingredientes,
Rectangle textomodopreparo, Rectangle textotempopreparo, Rectangle textorendimento,
Rectangle textobuscar, Rectangle botaoaddingredientes);
//---------------------------------------------------------
void ReceberEscrita(char* dado, int max);
//---------------------------------------------------------
void CaixadeTexto(Font fonts[], Rectangle botao, char* dado, int tamanho
, const char* titulo, int tipo, Color fundo);
//---------------------------------------------------------
void CadastroReceita(Receita &r, int &aux);
//---------------------------------------------------------
void DesenhaBotao(Font fonts[], Rectangle botao, const char* texto, int tamanho, int aux);
//---------------------------------------------------------
void DesenhaBotao(Font fonts[], Rectangle botao, const char* texto, int tamanho);
//---------------------------------------------------------
int AdiconarIngrediente(char* ingredientes, Receita &r, int &quantidade);
//---------------------------------------------------------
void Imprimirdados(Font fonts[], int pagina, int tamanhoarq, Rectangle textomodopreparo);
//---------------------------------------------------------
void Imprimirdados(Font fonts[], int pagina, int tamanhoarq, char* textobuscar, Rectangle textomodopreparo);
//---------------------------------------------------------
int ContarBusca(char* textobuscar);
//---------------------------------------------------------
void BotoesProximoAnterior(Font fonts[], Rectangle botaoproximo, Rectangle botaoanterior,
int a, int b);
//---------------------------------------------------------
static void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize,
float spacing, bool wordWrap, Color tint);
//---------------------------------------------------------
static void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec,
float fontSize, float spacing, bool wordWrap, Color tint, int selectStart,
int selectLength, Color selectTint, Color selectBackTint);
//---------------------------------------------------------

//funcoes
//---------------------------------------------------------
//essa funcao checa se o mouse está em cima e da um clique em algum botão
int EscolhaBotao(Receita r, int aux, Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle sair, Rectangle botaovoltar, Rectangle botaocadastro, Rectangle botaoaddingredientes, Rectangle botaoproximo, Rectangle botaoanterior, int escolhatexto){

    //checa se esta em cima e clica no botao abrir livro
    if (CheckCollisionPointRec(GetMousePosition(), abrirlivro) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 1;

    //checa se esta em cima e clica no botao buscar receita
    }else if (CheckCollisionPointRec(GetMousePosition(), buscarreceita) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 2;

    //checa se esta em cima e clica no botao cadastrar receita
    }else if (CheckCollisionPointRec(GetMousePosition(), novareceita) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 3;

    //checa se esta em cima e clica no botao sair
    }else if (CheckCollisionPointRec(GetMousePosition(), sair) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 4;

    //checa se esta em cima e clica no botao cadastrar receita
    }else if (CheckCollisionPointRec(GetMousePosition(), botaocadastro) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        //checa se nao tem nenhum campo vazio
        if(!strlen(r.nome) == 0 && !strlen(r.ingredientes) == 0 && !strlen(r.modoPreparo) == 0 && !strlen(r.tempoPreparo) == 0 && !strlen(r.rendimento) == 0){
            aux = 5;
        }
    //checa se esta em cima e clica no botao de adicionar ingredientes
    }else if (CheckCollisionPointRec(GetMousePosition(), botaoaddingredientes) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || escolhatexto == 2 && IsKeyPressed(KEY_ENTER)){
        aux = 6;

    //checa se esta em cima e clica no botao de proximo e esta na tela de abrir livro
    }else if (CheckCollisionPointRec(GetMousePosition(), botaoproximo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && aux == 1 || IsKeyPressed(KEY_RIGHT) && aux == 1){
        aux = 7;

    //checa se esta em cima e clica no botao de anterior e esta na tela de abrir livro
    }else if(CheckCollisionPointRec(GetMousePosition(), botaoanterior) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && aux == 1 || IsKeyPressed(KEY_LEFT) && aux == 1){
        aux = 8;

    //checa se esta em cima e clica no botao de proximo e esta na tela de buscar receita
    }else if (CheckCollisionPointRec(GetMousePosition(), botaoproximo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && aux == 2 || IsKeyPressed(KEY_RIGHT) && aux == 2){
        aux = 9;

    //checa se esta em cima e clica no botao de anterior e esta na tela de buscar receita
    }else if(CheckCollisionPointRec(GetMousePosition(), botaoanterior) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && aux == 2 || IsKeyPressed(KEY_LEFT) && aux == 2){
        aux = 10;
    }

    //checa se nao esta em cima de nenhum botao e clica com o mouse
    else if (CheckCollisionPointRec(GetMousePosition(), botaovoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        aux = 0;
    }

    return aux;
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao checa a escolha e faz a ação correspondente
void ChecarEscolha(int &escolha, Receita &r, char* ingrediente, int &pagina, int tamanhoarq, int contarbusca, char* buscarnome, int &quantingrediente){

    if(escolha == 5){//adiciona a receita nos arquivos
            CadastroReceita(r, escolha);
        }

        else if(escolha == 6){//adiciona os ingredientes na variavel r.ingredientes
            escolha = AdiconarIngrediente(ingrediente, r, quantingrediente);
        }

        else if(escolha == 7){//(botao proximo) checa se a posicao do ler for menor que o tamanho do arquivo e aumenta a posicao do ler
            if(pagina < tamanhoarq - 1){
                pagina++;
            }
            escolha = 1;
        }

        else if(escolha == 8){//(botao anterior) checa se a posicao do ler for maior que 0 e diminui a posicao do ler
            if(pagina > 0){
                pagina--;
            }
            escolha = 1;
        }

        else if(escolha == 9){//(botao proximo) checa se a posicao do ler for menor que a quantidade da busca e aumenta a posicao do ler
            if(pagina < contarbusca - 1){
                pagina++;
            }
            escolha = 2;
        }

        else if(escolha == 10){//(botao anterior) checa se a posicao do ler for maior que 0 e diminui a posicao do ler
            if(pagina > 0){
                pagina--;
            }
            escolha = 2;
        }

        else if(escolha == 0){//zera as variaveis
            pagina = 0;
            buscarnome[0] = '\0';
            r = {0};
            r.tipo = '0';
            quantingrediente = 0;
            ingrediente[0] = '\0';
        }

}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao checa se o mouse está em cima e da um clique em alguma caixa de texto
int EscolhaTexto(int mousenoquadrado, Rectangle textonome, Rectangle textoingredientes, Rectangle textomodopreparo, Rectangle textotempopreparo, Rectangle textorendimento, Rectangle textobuscar, Rectangle botaoaddingredientes){

    //checa se esta em cima e clica na caixa de texto nome
    if(CheckCollisionPointRec(GetMousePosition(), textonome) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return 1;

    //checa se esta em cima e clica na caixa de texto ingredientes
    }else if(CheckCollisionPointRec(GetMousePosition(), textoingredientes) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || CheckCollisionPointRec(GetMousePosition(), botaoaddingredientes) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return 2;

    //checa se esta em cima e clica na caixa de texto tempo de preparo
    }else if(CheckCollisionPointRec(GetMousePosition(), textotempopreparo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return 3;

    //checa se esta em cima e clica na caixa de texto rendimento
    }else if(CheckCollisionPointRec(GetMousePosition(), textorendimento) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return 4;

    //checa se esta em cima e clica na caixa de texto modo de preparo
    }else if(CheckCollisionPointRec(GetMousePosition(), textomodopreparo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return 5;

    //checa se esta em cima e clica na caixa de texto buscar
    }else if(CheckCollisionPointRec(GetMousePosition(), textobuscar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return 6;

    //checa se nao esta em cima de nenhuma caixa de texto e clica com o mouse
    }else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        return 0;
    }
    if(mousenoquadrado != 0 && mousenoquadrado != 6 && IsKeyPressed(KEY_TAB)){
        mousenoquadrado++;
    }

    return mousenoquadrado;
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao checa a escolha do texto e armazena o texto digitado pelo usuario na variavel correspondente
void ChecarEscolhaTexto(int escolhatexto, Receita &r, char* ingrediente, char* buscarnome){

    if(escolhatexto == 1){//se o usuario clicar na caixa de texto nome e chama a funcao que recebe a escrita do usuario
            char *p = r.nome;//ponteiro para a variavel nome
            ReceberEscrita(p, 24);
        }else if(escolhatexto == 2){//se o usuario clicar na caixa de texto ingredientes e chama a funcao que recebe a escrita do usuario
            char *p = ingrediente;//ponteiro para a variavel ingrediente
            ReceberEscrita(p, 35);//
        }else if(escolhatexto == 3){//se o usuario clicar na caixa de texto tempo de preparo e chama a funcao que recebe a escrita do usuario
            char *p = r.tempoPreparo;//ponteiro para a variavel tempoPreparo
            ReceberEscrita(p, 11);
        }else if(escolhatexto == 4){//se o usuario clicar na caixa de texto rendimento e chama a funcao que recebe a escrita do usuario
            char *p = r.rendimento;//ponteiro para a variavel rendimento
            ReceberEscrita(p, 10);
        }else if(escolhatexto == 5){//se o usuario clicar na caixa de texto modo de preparo e chama a funcao que recebe a escrita do usuario
            char *p = r.modoPreparo;//ponteiro para a variavel modoPreparo
            ReceberEscrita(p, 550);
        }else if(escolhatexto == 6){//se o usuario clicar na caixa de texto buscar e chama a funcao que recebe a escrita do usuario
            ReceberEscrita(buscarnome, 24);
        }

}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao conta quantas receitas tem no arquivo
int TamanhoArquivo(const char* caminho){

    FILE *arquivo;
    Receita r;
    int tamanho = 0;

    arquivo = fopen(caminho, "r");

        while(fread(&r, sizeof(Receita), 1, arquivo) == 1){//enquanto conseguir ler um registro do arquivo
            tamanho++;//aumenta o tamanho
        }

    fclose(arquivo);

    return tamanho;
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao desenha o menu principal
void DesenhaMenuPrincipal(Font fonts[], Rectangle abrirlivro, Rectangle buscarreceita, Rectangle novareceita, Rectangle sair, Rectangle botaovoltar){

    Vector2 positions[MAX_FONTS] = { 0 };
    positions[0] = (Vector2){ 74, 17 };
    ClearBackground(COR_FUNDO);

    //titulo
    DrawTextEx(fonts[0], "Livro de receitas da vovó", positions[0], 50, 2, COR_LETRA);

    //botao abrir livro
    DesenhaBotao(fonts, abrirlivro, "Abrir livro", 40);
    //botao buscar receita
    DesenhaBotao(fonts, buscarreceita, "Buscar receita", 29);
    //botao cadastrar receita
    DesenhaBotao(fonts, novareceita, "Cadastrar receita", 23);
    //botao sair
    DesenhaBotao(fonts, sair, "Guardar", 29);

}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao desenha a tela de abrir livro(listagem de receitas)
void TelaAbreLivro(Font fonts[], Rectangle botaovoltar, Rectangle botaoproximo, Rectangle botaoanterior, int &pagina, int &tamanhoarq, Rectangle textomodopreparo){

    ClearBackground(COR_FUNDO);

    //imprime os dados da receita na sua posicao do arquivo
    Imprimirdados(fonts, pagina, tamanhoarq, textomodopreparo);

    //botao voltar para a tela inicial
    DesenhaBotao(fonts, botaovoltar, "voltar", 29);

    //botao proximo e anterior
    BotoesProximoAnterior(fonts, botaoproximo, botaoanterior, tamanhoarq, pagina);
    //numero da receita e total de receitas
    if(tamanhoarq > 0){
        DrawTextEx(fonts[0], TextFormat("%d/%d", pagina + 1, tamanhoarq), (Vector2){screenWidth /2 - 5, 950}, 30, 2, COR_LETRA);
    }else{
        DrawTextEx(fonts[0], TextFormat("%d/%d", 0, 0), (Vector2){screenWidth /2 - 5, 950}, 30, 2, COR_LETRA);
    }
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao desenha a tela de busca de receita
void TelaBuscaReceita(Font fonts[], Rectangle botaovoltar, Rectangle textobuscar, char* buscarnome, int tamanhoarq, int pagina, int contarbusca, Rectangle botaoproximo, Rectangle botaoanterior, Rectangle textomodopreparo){

    ClearBackground(COR_FUNDO);

    //botao voltar para a tela inicial
    DesenhaBotao(fonts, botaovoltar, "voltar", 29);

    if(strlen(buscarnome) == 0){//se o usuario nao digitou nada imprimir "buscar"
        CaixadeTexto(fonts, textobuscar, "buscar", 29, "", 1, WHITE);
    }else{//se o usuario digitou algo imprimir o que ele digitou
        CaixadeTexto(fonts, textobuscar, buscarnome, 29, "", 1, WHITE);
    }

    //imprime os dados da receita na sua posicao do arquivo
    Imprimirdados(fonts, pagina, tamanhoarq, buscarnome, textomodopreparo);

    if(contarbusca > 0){//se o usuario digitou algo e encontrou alguma receita
        DrawTextEx(fonts[0], TextFormat("%d/%d", pagina + 1, contarbusca), (Vector2){screenWidth /2 - 5, 950}, 30, 2, COR_LETRA);
    }else{//se o usuario digitou algo e nao encontrou nenhuma receita
        DrawTextEx(fonts[0], TextFormat("%d/%d", 0, 0), (Vector2){screenWidth /2 - 5, 950}, 30, 2, COR_LETRA);
    }

    if (CheckCollisionPointRec(GetMousePosition(), textobuscar)){//se o usuario estiver com o mouse sobre a caixa de texto buscar
        SetMouseCursor(MOUSE_CURSOR_IBEAM);//deixa o cursor do mouse "I"
    }else{
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);//deixa o cursor do mouse normal
    }

    //botao proximo e anterior
    BotoesProximoAnterior(fonts, botaoproximo, botaoanterior,contarbusca, pagina);

}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao desenha a tela de cadastro de receita
void TelaCadastroReceita(int &escolha, int escolhatexto, char* ingrediente, Receita &r, Font fonts[], Rectangle botaovoltar, Rectangle textonome, Rectangle botaotipo, Rectangle textoingredientes, Rectangle botaoaddingredientes, Rectangle textomodopreparo, Rectangle textotempopreparo, Rectangle textorendimento, Rectangle botaocadastrar, int quantidade){

    ClearBackground(COR_FUNDO);

    //botao voltar para a tela inicial
    DesenhaBotao(fonts, botaovoltar, "voltar", 29);

    //caixa de texto para o nome da receita
    CaixadeTexto(fonts, textonome,r.nome, 50, "Nome", 1, WHITE);
    //caiixa de texto para os ingredientes
    if(quantidade < 15){
        CaixadeTexto(fonts, textoingredientes, ingrediente, 32, TextFormat("Ingredientes  %d/15", quantidade), 1, WHITE);
    }else{
        CaixadeTexto(fonts, textoingredientes, "cheio", 32, "Ingredientes  15/15", 1, WHITE);
    }
    //botao para adicionar ingredientes
    DesenhaBotao(fonts, botaoaddingredientes, "adicionar", 29, escolha);
    //botao para escolher o tipo da receita
    if(r.tipo == '0'){//se for do tipo 0 entao imprimir "doce"
        DesenhaBotao(fonts, botaotipo, "Tipo: Doce", 29, escolha);
    }else if(r.tipo == '1'){//se for do tipo 1 entao imprimir "salgado"
        DesenhaBotao(fonts, botaotipo, "Tipo: Salgado", 29, escolha);
    }
    CaixadeTexto(fonts, textotempopreparo, r.tempoPreparo, 40, "Tempo de preparo", 1, WHITE);
    //caixa de texto para o rendimento
    CaixadeTexto(fonts, textorendimento, r.rendimento, 29, "Rendimento", 1, WHITE);
    //caixa de texto para o modo de preparo
    CaixadeTexto(fonts, textomodopreparo, r.modoPreparo, 26, "Modo de preparo", 2, WHITE);
    //caixa de texto para o tempo de preparo

    //botao cadastrar
    DesenhaBotao(fonts, botaocadastrar, "Cadastrar", 29, escolha);

    //checa se o usuario esta com o mouse sobre alguma caixa de texto
    if (CheckCollisionPointRec(GetMousePosition(), textonome) || CheckCollisionPointRec(GetMousePosition(), textoingredientes) || CheckCollisionPointRec(GetMousePosition(), textomodopreparo) || CheckCollisionPointRec(GetMousePosition(), textotempopreparo) || CheckCollisionPointRec(GetMousePosition(), textorendimento)){
        SetMouseCursor(MOUSE_CURSOR_IBEAM);//deixa o cursor do mouse "I"
    }else{
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);//deixa o cursor do mouse normal
    }


}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao alterna o tipo de receita ao clicar no botão
char TipoReceita(Receita r, Rectangle botaotipo){
    //se o usuario clicar no botao tipo
    if (CheckCollisionPointRec(GetMousePosition(), botaotipo) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return r.tipo == '0' ? '1' : '0';//alterna entre doce e salgado
    }
    return r.tipo;

}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao recebe a escrita do teclado e coloca na caixa de texto selecionada
void ReceberEscrita(char* dado, int max){

    int key = GetCharPressed();//recebe a tecla pressionada
    key = tolower((char)key);//transforma a letra em minuscula

    int pos;

        // Check if more characters have been pressed on the same frame
        while (key > 0){

            pos = strlen(dado);//pega a posicao do ultimo caracter da string

            if ((strlen(dado) < max)){//checa se a string nao esta cheia
                dado[pos] = (char)key;//coloca o caractere na string
                dado[pos+1] = '\0';//coloca o caractere "\0" na proxima posicao(fim da string)
            }

            key = GetCharPressed();//recebe a proxima tecla pressionada
            key = tolower((char)key);//transforma a letra em minuscula



        }

        //key igual a enter

        if (IsKeyDown(KEY_BACKSPACE)){//checa se o usuario apertou a tecla backspace
            pos = strlen(dado) - 1;//pega a posicao do ultimo caracter da string menos 1
            if (pos < 0){//se a posicao for menor que 0
                pos = 0;//deixa a posicao como 0
            }
            dado[pos] = '\0';//coloca o caractere "\0" na posicao(fim da string)
        }

        if (IsKeyDown(KEY_BACKSPACE) && IsKeyDown(KEY_LEFT_CONTROL)){//checa se o usuario apertou a tecla backspace e ctrl

            //deleta a ultima palavra da string
            while(dado[strlen(dado)-1] != ' '){
                pos = strlen(dado) - 1;
                if (pos < 0){
                    dado[0] = '\0';
                    break;
                }
                dado[pos] = '\0';
            }

        }
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao desenha as caixas de texto
void CaixadeTexto(Font fonts[], Rectangle botao, char* dado, int tamanho, const char* titulo, int tipo, Color fundo){

    //desenha a caixa de texto
    DrawRectangleRec(botao, fundo);
    //escrita do titulo da caixa de texto
    DrawTextEx(fonts[0], titulo, (Vector2){ botao.x + 13, botao.y - 32 }, 30, 2, COR_LETRA_BOTAO);

    if(tipo == 1){//tipo 1 = caixa de texto para uma linha
        DrawTextEx(fonts[1], dado, (Vector2){ botao.x + 13, botao.y + 7 }, tamanho, 2, COR_LETRA_BOTAO);
    }else if(tipo == 2){//tipo 2 = caixa de texto para mais de uma linha
        DrawTextBoxed(fonts[0], dado, (Rectangle){ botao.x + 4, botao.y + 4, botao.width - 4, botao.height - 4 }, (float)tamanho, 2.0f, true, COR_LETRA_BOTAO);
    }


}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao cadastra a receita no arquivo binario e no arquivo texto
void CadastroReceita(Receita &r, int &aux){

    if(strlen(r.nome) == 0 || strlen(r.ingredientes) == 0 || strlen(r.modoPreparo) == 0 || strlen(r.tempoPreparo) == 0 || strlen(r.rendimento) == 0){
        aux = 1;
    }else{
        aux = 0;
    }

    FILE* arq;
    FILE* arq2;
    //abrir arquivos como app
    /*(se o arquivo nao existir, ele sera criado, se o arquivo existir,
       os dados serao adicionados ao final do arquivo)*/
    arq = fopen(caminhodat, "a+");
    arq2 = fopen(caminhotxt, "a+");

        //Imprimir no arquivo binario
        fwrite(&r, sizeof(Receita), 1, arq);

        //Imprimir no arquivo texto
        fprintf(arq2, "----------------------------------------\n");
        fprintf(arq2, "Nome: %s\n", r.nome);
        if(r.tipo == '1'){
            fprintf(arq2, "Tipo: Salgado\n");
        }
        else{
            fprintf(arq2, "Tipo: Doce\n");
        }
        fprintf(arq2, "Ingredientes: \n%s", r.ingredientes);
        fprintf(arq2, "Modo de Preparo: \n%s\n", r.modoPreparo);
        fprintf(arq2, "Tempo de Preparo: %s\n", r.tempoPreparo);
        fprintf(arq2, "Rendimento: %s\n", r.rendimento);

    //fechar arquivos
    fclose(arq);
    fclose(arq2);

    //limpar a struct
    r = {0};
    r.tipo = '0';
    aux = 0;

}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao desenha os botões da tela cadastro
void DesenhaBotao(Font fonts[], Rectangle botao, const char* texto, int tamanho, int aux){

    //desenha o botao
    DrawRectangleRec(botao, WHITE);

    //desenha o texto do botao
    DrawTextEx(fonts[0], texto, (Vector2){ botao.x + 13, botao.y + 10 }, tamanho, 2, COR_LETRA_BOTAO);

    if (CheckCollisionPointRec(GetMousePosition(), botao)){//checa se o mouse esta sobre o botao
        for(int i = 0; i < 4; i++){
            //desenha o botao com a borda diferente
            DrawRectangleLines((int)botao.x - i, (int)botao.y - i, (int)botao.width + i*2, (int)botao.height + i*2, COR_BOTAO_SELECIONADO);
        }
    }
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao desenha os botões
void DesenhaBotao(Font fonts[], Rectangle botao, const char* texto, int tamanho){

    //desenha o botao
    DrawRectangleRec(botao, COR_BOTAO);

    //desenha o texto do botao
    DrawTextEx(fonts[0], texto, (Vector2){ botao.x + 13, botao.y + 7 }, tamanho, 2, COR_LETRA_BOTAO);

    if (CheckCollisionPointRec(GetMousePosition(), botao)){//checa se o mouse esta sobre o botao
        for(int i = 0; i < 4; i++){
            //desenha o botao com a borda diferente mais grossa
            DrawRectangleLines((int)botao.x - i, (int)botao.y - i, (int)botao.width + i*2, (int)botao.height + i*2, COR_BOTAO_SELECIONADO);
        }
    }else {
        //desenha o botao com a borda normal
        DrawRectangleLines((int)botao.x, (int)botao.y, (int)botao.width, (int)botao.height, BLACK);
    }
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao adiciona o ingrediente da caixa de texto na variavel da receita
int AdiconarIngrediente(char* ingredientes, Receita &r, int &quantidade){

    if(quantidade < 15 && strlen(ingredientes) > 0){
        strcat(r.ingredientes, ingredientes);//adiciona o ingrediente na variavel da receita
        strcat(r.ingredientes, "\n");//adiciona uma quebra de linha no final da receita
        strcpy(ingredientes, "\0");//limpa a caixa de texto
        quantidade++;//aumenta a quantidade de ingredientes
    }

    return 3;
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao imprime os dados da receita selecionada
void Imprimirdados(Font fonts[], int pagina, int tamanhoarq, Rectangle textomodopreparo){

    if(tamanhoarq == 0){//checa se o arquivo estiver vazio
        DrawTextEx(fonts[0], "Nao ha receitas cadastradas", (Vector2){ screenWidth / 2 - strlen("Nao ha receitas cadastradas") * 10, 300 }, 40, 2, COR_LETRA);
    }else{

        FILE *arquivo;
        //abrindo arquivo como in
        arquivo = fopen(caminhodat, "r");
        char aux[25];

        //lendo o arquivo
        Receita r;
        int i = 0;
        while(fread(&r, sizeof(Receita), 1, arquivo) == 1){//enquanto nao chegar no final do arquivo
            strcpy(aux, r.nome);
            if(i == pagina){//checa se a posicao do arquivo e igual a posicao da pagina

                //posicoes dos textos
                Vector2 positions[7] = { 0 };
                positions[0] = (Vector2){ screenWidth /2 - strlen(aux) * 9 , 10 };//nome
                positions[1] = (Vector2){ 20, 70 };//ingredientes titulo
                positions[2] = (Vector2){ 20, 110 };//ingredientes
                positions[3] = (Vector2){ 420, 180 };//tempo de preparo titulo
                positions[4] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 6 - strlen(r.tempoPreparo) * 4, 220 };//tempo de preparo
                positions[5] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 5 - strlen("Rendimento:") * 4, 330};//rendimento titulo
                positions[6] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 6 - strlen(r.rendimento) * 4, 370 };//rendimento
                positions[7] = (Vector2){ 20, 575 };//modo de preparo titulo
                if(r.tipo == '0'){
                    positions[8] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 6 - strlen("doce") * 4, 70 };//tipo
                }else if(r.tipo == '1'){
                    positions[8] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 5 - strlen("salgado") * 4, 70 };//tipo
                }

                //imprime os dados da receita
                DrawTextEx(fonts[0], TextFormat("%s",aux), positions[0], 40, 2, COR_LETRA);
                DrawTextEx(fonts[0], "Ingredientes:", positions[1], 30, 2, COR_LETRA);
                DrawTextEx(fonts[0], TextFormat("%s",r.ingredientes), positions[2], 20, 2, COR_LETRA);
                DrawTextEx(fonts[0], "Tempo de Preparo:", positions[3], 30, 2, COR_LETRA);
                DrawTextEx(fonts[0], TextFormat("%s",r.tempoPreparo), positions[4], 30, 2, COR_LETRA);
                DrawTextEx(fonts[0], "Rendimento:", positions[5], 30, 2, COR_LETRA);
                DrawTextEx(fonts[0], TextFormat("%s",r.rendimento), positions[6], 20, 2, COR_LETRA);
                DrawTextEx(fonts[0], "Modo de Preparo:", positions[7], 30, 2, COR_LETRA);
                CaixadeTexto(fonts, textomodopreparo, r.modoPreparo, 20, "", 2, COR_FUNDO);
                if(r.tipo == '0'){
                    DrawTextEx(fonts[0], "Doce", positions[8], 30, 2, COR_LETRA);
                }else if(r.tipo == '1'){
                    DrawTextEx(fonts[0], "Salgado", positions[8], 30, 2, COR_LETRA);
                }
                break;
            }
            i++;
        }

        //fechando arquivo
        fclose(arquivo);
    }
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao imprime os dados da receita que foi buscada
void Imprimirdados(Font fonts[], int pagina, int tamanhoarq, char* textobuscar, Rectangle textomodopreparo){

    if(tamanhoarq == 0){//checa se o arquivo estiver vazio
        DrawTextEx(fonts[0], "Nao ha receitas cadastradas", (Vector2){ screenWidth / 2 - strlen("Nao ha receitas cadastradas") * 10, 300  }, 40, 2, COR_LETRA);
    }else{

        FILE *arquivo;
        //abrindo arquivo como in
        arquivo = fopen(caminhodat, "r");

        Receita r;
        int cont = 0;
        //cria um vetor dinamico para armazenar as receitas que contem o texto buscado
        Receita *aux = new Receita[tamanhoarq];


        while(fread(&r, sizeof(Receita), 1, arquivo) == 1){//enquanto nao chegar no final do arquivo
            if(strcmp(r.nome, textobuscar) == 0){//checa se o nome da receita e igual ao texto de busca
                aux[cont] = r;
                cont++;
            }
        }
        if(cont == 0){//checa se nao foi encontrado nenhuma receita com o texto de busca
            DrawTextEx(fonts[0], "Nenhuma receita encontrada", (Vector2){ screenWidth / 2 - strlen("Nenhuma receita encontrada") * 10, 300  }, 40, 2, COR_LETRA);
        }else{

            int i = 0;

            while(i < cont){//enquanto nao chegar no final do vetor

                //posicoes dos textos
                Vector2 positions[7] = { 0 };
                positions[0] = (Vector2){ 20, 70 };//ingredientes titulo
                positions[1] = (Vector2){ 20, 110 };//ingredientes
                positions[2] = (Vector2){ 420, 180 };//tempo de preparo titulo
                positions[3] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 6 - strlen(aux[i].tempoPreparo) * 4, 220 };//tempo de preparo
                positions[4] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 5 - strlen("Rendimento:") * 4, 330 };//rendimento titulo
                positions[5] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 6 - strlen(aux[i].rendimento) * 4, 370 };//rendimento
                positions[6] = (Vector2){ 20, 575 };//modo de preparo titulo
                if(r.tipo == '0'){
                    positions[7] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 6 - strlen("doce") * 4, 70 };//tipo
                }else if(r.tipo == '1'){
                    positions[7] = (Vector2){ 420 + strlen("Tempo de Preparo:") * 5 - strlen("salgado") * 4, 70 };//tipo
                }


                if(i == pagina){//checa se a posicao do vetor e igual a posicao da pagina
                    //imprime os dados da receita
                    DrawTextEx(fonts[0], "Ingredientes:", positions[0], 30, 2, COR_LETRA);
                    DrawTextEx(fonts[0], TextFormat("%s",aux[i].ingredientes), positions[1], 20, 2, COR_LETRA);
                    DrawTextEx(fonts[0], "Tempo de Preparo:", positions[2], 30, 2, COR_LETRA);
                    DrawTextEx(fonts[0], TextFormat("%s",aux[i].tempoPreparo), positions[3], 30, 2, COR_LETRA);
                    DrawTextEx(fonts[0], "Rendimento:", positions[4], 30, 2, COR_LETRA);
                    DrawTextEx(fonts[0], TextFormat("%s",aux[i].rendimento), positions[5], 20, 2, COR_LETRA);
                    DrawTextEx(fonts[0], "Modo de Preparo:", positions[6], 30, 2, COR_LETRA);
                    CaixadeTexto(fonts, textomodopreparo, aux[i].modoPreparo, 20, "", 2, COR_FUNDO);
                    if(r.tipo == '0'){
                        DrawTextEx(fonts[0], "Doce", positions[7], 30, 2, COR_LETRA);
                    }else if(r.tipo == '1'){
                        DrawTextEx(fonts[0], "Salgado", positions[7], 30, 2, COR_LETRA);
                    }



                    // DrawTextEx(fonts[0], TextFormat("Nome: %s",aux[i].nome), positions[0], 20, 2, COR_LETRA);
                    // DrawTextEx(fonts[0], TextFormat("Ingredientes: %s",aux[i].ingredientes), positions[1], 20, 2, COR_LETRA);
                    // DrawTextEx(fonts[0], TextFormat("Tempo de Preparo: %s",aux[i].tempoPreparo), positions[2], 20, 2, COR_LETRA);
                    // DrawTextEx(fonts[0], TextFormat("Rendimento: %s",aux[i].rendimento), positions[3], 20, 2, COR_LETRA);
                    // DrawTextEx(fonts[0], TextFormat("Modo de Preparo: %s",aux[i].modoPreparo), positions[4], 20, 2, COR_LETRA);
                    // if(aux[i].tipo == '0'){
                    //     DrawTextEx(fonts[0], "Tipo: Doce", positions[5], 20, 2, COR_LETRA);
                    // }else if(aux[i].tipo == '1'){
                    //     DrawTextEx(fonts[0], "Tipo: Salgado", positions[5], 20, 2, COR_LETRA);
                    // }

                    break;
                }
                i++;
            }
        }
        //fechando arquivo
        fclose(arquivo);
    }

}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao conta quantas receitas foram encontradas da busca
int ContarBusca(char* textobuscar){

    FILE *arquivo;
    Receita r;
    int cont = 0;

    //abrindo arquivo como in
    arquivo = fopen(caminhodat, "r");

        while(fread(&r, sizeof(Receita), 1, arquivo) == 1){//enquanto nao chegar no final do arquivo
            if(strcmp(r.nome, textobuscar) == 0){//checa se o nome da receita e igual ao texto de busca
                cont++;//incrementa o contador
            }
        }

    //fechando arquivo
    fclose(arquivo);

    return cont;
}
//---------------------------------------------------------
//---------------------------------------------------------
//essa funcao desenha os botões de proximo e anterior
void BotoesProximoAnterior(Font fonts[], Rectangle botaoproximo, Rectangle botaoanterior, int a, int b){

    if(a > 0 && b < a - 1){//checa se a pagina atual e menor que a quantidade de paginas
        DesenhaBotao(fonts, botaoproximo, "Proximo", 28);//desenha o botao proximo
    }
    if(b > 0){//checa se a pagina atual e maior que 0
        DesenhaBotao(fonts, botaoanterior, "Anterior", 28);//desenha o botao anterior
    }

}
//---------------------------------------------------------
//---------------------------------------------------------
//essas funções são para o escrever texto dentro da caixa de texto
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

    for (int i = 0, k = 0; i < length; i++, k++){
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
//---------------------------------------------------------




