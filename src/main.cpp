#include "funcoes.h"

#define SCREEN_TITLE  "Livro de receitas da vovó"

int main(void){

    //inicializando a tela
    InitWindow(screenWidth, screenHeight, SCREEN_TITLE);

    //retangulos dos botoes
    Rectangle abrirlivro;
    Rectangle buscarreceita;
    Rectangle novareceita;
    Rectangle sair;

    Rectangle botaovoltar;
    Rectangle botaoproximo;
    Rectangle botaoanterior;

    //retaangulos dos textos
    Rectangle botaonome;
    Rectangle botaoingredientes;
    Rectangle botaoaddingredientes;
    Rectangle botaomodoPreparo;
    Rectangle botaotempoPreparo;
    Rectangle botaorendimento;
    Rectangle botaotipo;
    Rectangle botaocadastro;

    //fontes
    Font fonts[MAX_FONTS] = { 0 };
    fonts[0] = LoadFontEx("src/Fonts/titulo.ttf", 50, 0, 250);
    fonts[1] = LoadFontEx("src/Fonts/letras.ttf", 50, 0, 250);

    //criando as variaveis
    int escolha = 0;
    int escolhatexto = 0;
    struct Receita r = {0};
    r.tipo = '0';

    int emcimatipo = 0;
    int auxtipo = 0;
    int posisaoler = 0;
    int tamanhoarq = 0;
    int tamanhosalgado = 0;

    char* ingrediente = new char[13];
    strcpy(ingrediente, "\0");


    SetTargetFPS(10);        // Set our game to run at 10 frames-per-second
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose()){

        escolha = EscolhaBotao(r, escolha, abrirlivro, buscarreceita, novareceita, sair, botaovoltar, botaocadastro, botaoaddingredientes, botaoproximo, botaoanterior);

        escolhatexto = EscolhaTexto(escolhatexto,  botaonome, botaoingredientes, botaomodoPreparo, botaotempoPreparo, botaorendimento);

        r.tipo = TipoReceita(r, botaotipo);

        //checar o tamanho do arquivo
        tamanhoarq = TamanhoArquivo(caminhodat);

        if(escolhatexto == 1){
            char *p = r.nome;
            ReceberEscrita(p, 24);
        }else if(escolhatexto == 2){
            char *p = ingrediente;
            ReceberEscrita(p, 13);
        }else if(escolhatexto == 3){
            char *p = r.modoPreparo;
            ReceberEscrita(p, 300);
        }else if(escolhatexto == 4){
            char *p = r.tempoPreparo;
            ReceberEscrita(p, 11);
        }else if(escolhatexto == 5){
            char *p = r.rendimento;
            ReceberEscrita(p, 10);
        }

        if(escolha == 5){
            CadastroReceita(r, escolha);
        }

        else if(escolha == 6){
            escolha = AdiconarReceita(ingrediente, r);
        }

        else if(escolha == 7){
            if(posisaoler < tamanhoarq - 1){
                posisaoler++;
            }
            escolha = 1;
        }

        else if(escolha == 8){
            if(posisaoler > 0){
                posisaoler--;
            }
            escolha = 1;
        }

        else if(escolha == 0){
            posisaoler = 0;
        }

        BeginDrawing();

            if(escolha == 0){

                //retangulos dos botoes
                //x, y, largura, altura
                abrirlivro = { screenWidth/2.0f - 120, 110, 225, 50 };
                buscarreceita = { screenWidth/2.0f - 120, 185, 225, 50 };
                novareceita = { screenWidth/2.0f - 120, 260, 230, 50 };
                sair = { screenWidth - 85, screenHeight - 45, 75, 38 };
                botaovoltar = { 10, -1000, 105, 40 };

                //retaangulos dos textos
                //x, y, largura, altura
                botaonome.width = -1000;
                botaotipo.width = -1000;
                botaoingredientes.width = -1000;
                botaomodoPreparo.width = -1000;
                botaotempoPreparo.width = -1000;
                botaorendimento.width = -1000;
                botaocadastro.width = -1000;
                botaoaddingredientes.width = -1000;
                botaoproximo.width = -1000;
                botaoanterior.width = -1000;


                DesenhaMenuPrincipal(fonts, abrirlivro, buscarreceita, novareceita, sair, botaovoltar);

            }else if (escolha == 1){

                //retangulos dos botoes
                //x, y, largura, altura
                abrirlivro.width = -1000;
                buscarreceita.width = -1000;
                novareceita.width = -1000;
                sair.width = -1000;
                botaovoltar = { 10, 10, 107, 40 };
                botaoproximo = { screenWidth - 135, screenHeight - 55, 120, 44 };
                botaoanterior = { 10, screenHeight - 55, 140, 44 };

                //retaangulos dos textos
                //x, y, largura, altura
                botaonome.width = -1000;
                botaotipo.width = -1000;
                botaoingredientes.width = -1000;
                botaomodoPreparo.width = -1000;
                botaotempoPreparo.width = -1000;
                botaorendimento.width = -1000;
                botaocadastro.width = -1000;
                botaoaddingredientes.width = -1000;

                TelaAbreLivro(fonts, botaovoltar, botaoproximo, botaoanterior, posisaoler, tamanhoarq);

            }else if (escolha == 2){

                //retangulos dos botoes
                //x, y, largura, altura
                abrirlivro.width = -1000;
                buscarreceita.width = -1000;
                novareceita.width = -1000;
                sair.width = -1000;
                botaovoltar = { 10, 10, 107, 40 };
                botaoproximo.width = -1000;
                botaoanterior.width = -1000;

                //retaangulos dos textos
                //x, y, largura, altura
                botaonome.width = -1000;
                botaotipo.width = -1000;
                botaoingredientes.width = -1000;
                botaomodoPreparo.width = -1000;
                botaotempoPreparo.width = -1000;
                botaorendimento.width = -1000;
                botaocadastro.width = -1000;
                botaoaddingredientes.width = -1000;

                TelaBuscaReceita(fonts, botaovoltar);

            }else if (escolha == 3){


                //retangulos dos botoes^
                //x, y, largura, altura
                abrirlivro.width = -1000;
                buscarreceita.width = -1000;
                novareceita.width = -1000;
                sair.width = -1000;
                botaoproximo.width = -1000;
                botaoanterior.width = -1000;
                botaovoltar = { 10, 10, 107, 40 };

                //retaangulos dos textos
                //x, y, largura, altura
                botaonome = { 10, 90, 675, 70 };
                botaotipo = { 475, 200, 210, 50 };
                botaoingredientes = { 10, 200, 225, 50 };
                botaoaddingredientes = { 260, 200, 160, 50 };
                botaotempoPreparo = { 10, 295, 290, 50 };
                botaorendimento = { 380, 295, 225, 50 };
                botaomodoPreparo = { 10, 390, 675, 540 };
                botaocadastro = { screenWidth - 175, screenHeight - 55, 160, 44 };

                TelaCadastroReceita(escolha, escolhatexto, ingrediente, r, fonts, botaovoltar, botaonome, botaotipo, botaoingredientes, botaoaddingredientes, botaomodoPreparo, botaotempoPreparo, botaorendimento, botaocadastro);

            }else if (escolha == 4){
                return 0;
            }

        EndDrawing();


    }

    CloseWindow();

    // InitWindow(screenWidth, screenHeight, SCREEN_TITLE);

    // while (!WindowShouldClose()){
    //     BeginDrawing();
    //         ClearBackground(RAYWHITE);
    //         DrawText("Obrigado por usar o programa!", 10, 10, 20, BLACK);
    //     EndDrawing();
    // }

    // CloseWindow();


    return 0;
}
