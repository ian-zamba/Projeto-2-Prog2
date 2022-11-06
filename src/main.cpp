#include "funcoes.h"

#define SCREEN_TITLE  "Livro de receitas da vovó"

int main(void){

    //inicializando a tela
    InitWindow(screenWidth, screenHeight, SCREEN_TITLE);

    //botoes da tela inicial
    Rectangle abrirlivro;
    Rectangle buscarreceita;
    Rectangle novareceita;
    Rectangle sair;

    //botoes das telas abri livro e buscar receita
    Rectangle botaovoltar;
    Rectangle botaoproximo;
    Rectangle botaoanterior;

    //retaangulos dos textos cadastros
    Rectangle textonome;
    Rectangle textoingredientes;
    Rectangle botaoaddingredientes;
    Rectangle textomodopreparo;
    Rectangle textotempopreparo;
    Rectangle textorendimento;
    Rectangle botaotipo;
    Rectangle botaocadastro;

    //variaveis buscar
    Rectangle textobuscar;
    int contarbusca = 0;
    char* buscarnome = new char[25];
    strcpy(buscarnome, "\0");

    //variaveis cadastro
    char* ingrediente = new char[13];
    strcpy(ingrediente, "\0");

    //fontes
    Font fonts[MAX_FONTS] = { 0 };
    fonts[0] = LoadFontEx("src/Fonts/titulo.ttf", 50, 0, 250);
    fonts[1] = LoadFontEx("src/Fonts/letras.ttf", 50, 0, 250);

    //variaveis auxiliares
    int escolha = 0;
    int escolhatexto = 0;
    int posisaoler = 0;
    int tamanhoarq = 0;

    //variaveis de texto
    struct Receita r = {0};
    r.tipo = '0';


    SetTargetFPS(10);        // Set our game to run at 10 frames-per-second
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose()){

        escolha = EscolhaBotao(r, escolha, abrirlivro, buscarreceita, novareceita, sair, botaovoltar, botaocadastro, botaoaddingredientes, botaoproximo, botaoanterior);

        escolhatexto = EscolhaTexto(escolhatexto, textonome, textoingredientes, textomodopreparo, textotempopreparo, textorendimento, textobuscar);

        contarbusca = ContarBusca(buscarnome);

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
        }else if(escolhatexto == 6){
            ReceberEscrita(buscarnome, 24);
        }

        if(escolha == 5){
            CadastroReceita(r, escolha);
        }

        else if(escolha == 6){
            escolha = AdiconarIngrediente(ingrediente, r);
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

        else if(escolha == 9){
            if(posisaoler < contarbusca - 1){
                posisaoler++;
            }
            escolha = 2;
        }

        else if(escolha == 10){            
            if(posisaoler > 0){
                posisaoler--;
            }
            escolha = 2;
        }

        else if(escolha == 0){
            posisaoler = 0;
            buscarnome[0] = '\0';
            r = {0};
            r.tipo = '0';
        }

        BeginDrawing();

            if(escolha == 0){

                //criar retangulos
                //x, y, largura, altura
                textonome.width = -1;
                botaotipo.width = -1;
                textoingredientes.width = -1;
                textomodopreparo.width = -1;
                textotempopreparo.width = -1;
                textorendimento.width = -1;
                botaocadastro.width = -1;
                botaoaddingredientes.width = -1;
                botaoproximo.width = -1;
                botaoanterior.width = -1;
                textobuscar.width = -1;
                //botaobuscar.width = -1;

                //apagar retangulos
                //x, y, largura, altura
                abrirlivro = { screenWidth/2.0f - 120, 110, 225, 50 };
                buscarreceita = { screenWidth/2.0f - 120, 185, 225, 50 };
                novareceita = { screenWidth/2.0f - 120, 260, 230, 50 };
                sair = { screenWidth - 85, screenHeight - 45, 75, 38 };
                botaovoltar = { 10, -1, 105, 40 };

                DesenhaMenuPrincipal(fonts, abrirlivro, buscarreceita, novareceita, sair, botaovoltar);

            }else if (escolha == 1){

                //apagar retangulos
                //x, y, largura, altura
                abrirlivro.width = -1;
                buscarreceita.width = -1;
                novareceita.width = -1;
                sair.width = -1;
                textonome.width = -1;
                botaotipo.width = -1;
                textoingredientes.width = -1;
                textomodopreparo.width = -1;
                textotempopreparo.width = -1;
                textorendimento.width = -1;
                botaocadastro.width = -1;
                botaoaddingredientes.width = -1;
                textobuscar.width = -1;
                //botaobuscar.width = -1;

                //criar retangulos
                //x, y, largura, altura
                botaovoltar = { 10, 10, 107, 40 };
                botaoanterior = { 10, screenHeight - 55, 140, 44 };
                botaoproximo = { screenWidth - 135, screenHeight - 55, 120, 44 };

                TelaAbreLivro(fonts, botaovoltar, botaoproximo, botaoanterior, posisaoler, tamanhoarq);

            }else if (escolha == 2){

                //apagar retangulos
                //x, y, largura, altura
                abrirlivro.width = -1;
                buscarreceita.width = -1;
                novareceita.width = -1;
                sair.width = -1;
                textonome.width = -1;
                botaotipo.width = -1;
                textoingredientes.width = -1;
                textomodopreparo.width = -1;
                textotempopreparo.width = -1;
                textorendimento.width = -1;
                botaocadastro.width = -1;
                botaoaddingredientes.width = -1;

                //criar retangulos
                //x, y, largura, altura
                botaovoltar = { 10, 10, 107, 40 };
                textobuscar = { screenWidth - 400, 10, 320, 40 };                
                botaoanterior = { 10, screenHeight - 55, 140, 44 };
                botaoproximo = { screenWidth - 135, screenHeight - 55, 120, 44 };
                //botaobuscar = { textobuscar.x + textobuscar.width + 5, textobuscar.y, 225, 40};

                TelaBuscaReceita(fonts, botaovoltar, textobuscar, buscarnome, tamanhoarq, posisaoler, contarbusca, botaoproximo, botaoanterior);

            }else if (escolha == 3){


                //apagar Retangulos
                //x, y, largura, altura
                abrirlivro.width = -1;
                buscarreceita.width = -1;
                novareceita.width = -1;
                sair.width = -1;
                botaoproximo.width = -1;
                botaoanterior.width = -1;
                textobuscar.width = -1;
                //botaobuscar.width = -1;

                //criar Retangulos
                //x, y, largura, altura
                botaovoltar = { 10, 10, 107, 40 };
                textonome = { 10, 90, 675, 70 };
                botaotipo = { 475, 200, 210, 50 };
                textoingredientes = { 10, 200, 280, 50 };
                botaoaddingredientes = { textoingredientes.x + textoingredientes.width + 5, textoingredientes.y, 160, 50 };
                textotempopreparo = { 10, 295, 290, 50 };
                textorendimento = { 380, 295, 225, 50 };
                textomodopreparo = { 10, 390, 675, 540 };
                botaocadastro = { screenWidth - 175, screenHeight - 55, 160, 44 };

                TelaCadastroReceita(escolha, escolhatexto, ingrediente, r, fonts, botaovoltar, textonome, botaotipo, textoingredientes, botaoaddingredientes, textomodopreparo, textotempopreparo, textorendimento, botaocadastro);

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
