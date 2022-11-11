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
    

    //fontes
    Font fonts[MAX_FONTS] = { 0 };
    fonts[0] = LoadFontEx("src/Fonts/titulo.ttf", 50, 0, 250);
    fonts[1] = LoadFontEx("src/Fonts/letras.ttf", 50, 0, 250);

    //variaveis auxiliares
    int escolha = 0;
    int escolhatexto = 0;
    int pagina = 0;
    int tamanhoarq = 0;
    int quantingrediente = 0;

    //variaveis de texto
    struct Receita r = {0};
    r.tipo = '0';

    char* ingrediente = new char[13];
    strcpy(ingrediente, "\0");

    char* buscarnome = new char[25];
    strcpy(buscarnome, "\0");


    SetTargetFPS(10);        //deixar o programa rodando a 10 fps
    //---------------------------------------------------------

    while (!WindowShouldClose()){
        //---------------------------------------------------------
        //a escolha 0 é a tela inicial, a escolha 1 é a tela de cadastro, 
        //a escolha 2 é a tela de abrir livro, a escolha 3 é a tela de buscar receita
        //a variavel escolha recebe o valor da tela que o usuario escolheu de acordo 
        //com o clique do mouse no botao
        escolha = EscolhaBotao(r, escolha, abrirlivro, buscarreceita, novareceita, sair, botaovoltar, botaocadastro, botaoaddingredientes, botaoproximo, botaoanterior, escolhatexto);
        //---------------------------------------------------------
        //---------------------------------------------------------
        //a variavel escolhatexto recebe o valor da caixa de texto que o usuario 
        //escolheu de acordo com o clique do mouse na caixa do texto
        escolhatexto = EscolhaTexto(escolhatexto, textonome, textoingredientes, textomodopreparo, textotempopreparo, textorendimento, textobuscar, botaoaddingredientes);
        //---------------------------------------------------------
        //---------------------------------------------------------
        //a variavel contarbusca recebe a quantidade de resultados da busca
        contarbusca = ContarBusca(buscarnome);
        //---------------------------------------------------------
        //---------------------------------------------------------
        //a variavel r.tipo recebe o tipo de receita que o usuario escolheu de 
        //acordo com o clique do mouse no botao
        r.tipo = TipoReceita(r, botaotipo);
        //---------------------------------------------------------
        //---------------------------------------------------------
        //checar o tamanho do arquivo
        tamanhoarq = TamanhoArquivo(caminhodat);
        //---------------------------------------------------------
        //---------------------------------------------------------
        //checa a escolha do usuario e executa a acao correspondente
        ChecarEscolha(escolha, r, ingrediente, pagina, tamanhoarq, contarbusca, buscarnome, quantingrediente);
        //---------------------------------------------------------
        //---------------------------------------------------------
        //checa a escolha do texto e armazena o texto digitado pelo usuario 
        //na variavel correspondente
        ChecarEscolhaTexto(escolhatexto, r, ingrediente, buscarnome);
        //---------------------------------------------------------

        BeginDrawing();//comeca a desenhar as coisas na tela

            if(escolha == 0){

                //apagar retangulos
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

                //criar retangulos
                //x, y, largura, altura
                abrirlivro = { screenWidth/2.0f - 120, 110, 225, 50 };
                buscarreceita = { screenWidth/2.0f - 120, 185, 225, 50 };
                novareceita = { screenWidth/2.0f - 120, 260, 230, 50 };
                sair = { screenWidth - 145, screenHeight - 45, 135, 38 };
                botaovoltar = { 10, -1, 105, 40 };

                //funcao que desenha o menu inicial
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
                textotempopreparo.width = -1;
                textorendimento.width = -1;
                botaocadastro.width = -1;
                botaoaddingredientes.width = -1;
                textobuscar.width = -1;

                //criar retangulos
                //x, y, largura, altura
                botaovoltar = { 10, 10, 107, 40 };
                botaoanterior = { 10, screenHeight - 55, 140, 44 };
                botaoproximo = { screenWidth - 135, screenHeight - 55, 120, 44 };
                textomodopreparo = { 20, 615, screenWidth - 40, 470};

                //funcao que desenha a tela de listar receitas
                TelaAbreLivro(fonts, botaovoltar, botaoproximo, botaoanterior, pagina, tamanhoarq, textomodopreparo);

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
                textotempopreparo.width = -1;
                textorendimento.width = -1;
                botaocadastro.width = -1;
                botaoaddingredientes.width = -1;

                //criar retangulos
                //x, y, largura, altura
                botaovoltar = { 10, 10, 107, 40 };
                textobuscar = { screenWidth - 330, 10, 320, 40 };                
                botaoanterior = { 10, screenHeight - 55, 140, 44 };
                botaoproximo = { screenWidth - 135, screenHeight - 55, 120, 44 };                
                textomodopreparo = { 20, 615, screenWidth - 40, 470};

                //funcao que desenha a tela de buscar receitas
                TelaBuscaReceita(fonts, botaovoltar, textobuscar, buscarnome, tamanhoarq, pagina, contarbusca, botaoproximo, botaoanterior, textomodopreparo);

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

                //criar Retangulos
                //x, y, largura, altura
                botaovoltar = { 10, 10, 107, 40 };
                textonome = { 10, 90, 675, 70 };
                botaotipo = { 475, 10, 210, 50 };
                textoingredientes = { 10, 200, 510, 50 };
                botaoaddingredientes = { textoingredientes.x + textoingredientes.width + 5, textoingredientes.y, 160, 50 };
                textotempopreparo = { 10, 295, 290, 50 };
                textorendimento = { 380, 295, 225, 50 };
                textomodopreparo = { 10, 390, 675, 540 };
                botaocadastro = { screenWidth - 175, screenHeight - 55, 160, 44 };

                //funcao que desenha a tela de cadastro de receitas
                TelaCadastroReceita(escolha, escolhatexto, ingrediente, r, fonts, botaovoltar, textonome, botaotipo, textoingredientes, botaoaddingredientes, textomodopreparo, textotempopreparo, textorendimento, botaocadastro, quantingrediente);

            }else if (escolha == 4){//sair do programa
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
