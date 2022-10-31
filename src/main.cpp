#include "funcoes.h"

#define SCREEN_TITLE  "Livro de receitas da vov�"

int main(void){
    //criando as variaveis fixas
    const char* caminhoddat = "src/Arquivos/receitasd.dat";
    const char* caminhodtxt = "src/Arquivos/receitasd.txt";    
    const char* caminhosdat = "src/Arquivos/receitass.dat";
    const char* caminhostxt = "src/Arquivos/receitass.txt";

    //inicializando a tela
    InitWindow(screenWidth, screenHeight, SCREEN_TITLE);

    //retangulos dos botoes
    Rectangle abrirlivro;
    Rectangle buscarreceita;
    Rectangle novareceita;
    Rectangle sair;
    Rectangle botaovoltar;

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


    SetTargetFPS(10);               // Set our game to run at 10 frames-per-second
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose()){

        escolha = EscolhaBotao(r, escolha, abrirlivro, buscarreceita, novareceita, sair, botaovoltar, botaocadastro);

        escolhatexto = EscolhaTexto(escolhatexto,  botaonome, botaoingredientes, botaomodoPreparo, botaotempoPreparo, botaorendimento);

        r.tipo = TipoReceita(r, botaotipo);

        if(escolhatexto == 1){
            char *p = r.nome;
            ReceberEscrita(p, 24);
        }else if(escolhatexto == 2){
            char *p = r.ingredientes;
            ReceberEscrita(p, 150);
        }else if(escolhatexto == 3){
            char *p = r.modoPreparo;
            ReceberEscrita(p, 100);
        }else if(escolhatexto == 4){
            char *p = r.tempoPreparo;
            ReceberEscrita(p, 10);
        }else if(escolhatexto == 5){
            char *p = r.rendimento;
            ReceberEscrita(p, 10);
        }

        if(escolha == 5){
            CadastroReceita(r, caminhoddat, caminhodtxt, caminhosdat, caminhostxt, escolha);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            if(escolha == 0){

                //retangulos dos botoes
                abrirlivro = { screenWidth/2.0f - 120, 110, 225, 50 };
                buscarreceita = { screenWidth/2.0f - 120, 185, 225, 50 };
                novareceita = { screenWidth/2.0f - 120, 260, 230, 50 };
                sair = { screenWidth - 85, screenHeight - 45, 75, 38 };
                botaovoltar = { 10, -1000, 105, 40 };

                //retaangulos dos textos
                botaonome.width = -1000;
                botaotipo.width = -1000;
                botaoingredientes.width = -1000;
                botaomodoPreparo.width = -1000;
                botaotempoPreparo.width = -1000;
                botaorendimento.width = -1000;
                botaocadastro.width = -1000;
                botaoaddingredientes.width = -1000;


                DesenhaMenuPrincipal(fonts, abrirlivro, buscarreceita, novareceita, sair, botaovoltar);

            }else if (escolha == 1){

                //retangulos dos botoes
                abrirlivro.width = -1000;
                buscarreceita.width = -1000;
                novareceita.width = -1000;
                sair.width = -1000;
                botaovoltar = { 10, 10, 107, 40 };

                //retaangulos dos textos
                botaonome.width = -1000;
                botaotipo.width = -1000;
                botaoingredientes.width = -1000;
                botaomodoPreparo.width = -1000;
                botaotempoPreparo.width = -1000;
                botaorendimento.width = -1000;
                botaocadastro.width = -1000;
                botaoaddingredientes.width = -1000;

                TelaAbreLivro(fonts, caminhoddat, botaovoltar);

            }else if (escolha == 2){

                //retangulos dos botoes
                abrirlivro.width = -1000;
                buscarreceita.width = -1000;
                novareceita.width = -1000;
                sair.width = -1000;
                botaovoltar = { 10, 10, 107, 40 };

                //retaangulos dos textos
                botaonome.width = -1000;
                botaotipo.width = -1000;
                botaoingredientes.width = -1000;
                botaomodoPreparo.width = -1000;
                botaotempoPreparo.width = -1000;
                botaorendimento.width = -1000;
                botaocadastro.width = -1000;
                botaoaddingredientes.width = -1000;

                TelaBuscaReceita(fonts, caminhoddat, botaovoltar);

            }else if (escolha == 3){


                //retangulos dos botoes
                abrirlivro.width = -1000;
                buscarreceita.width = -1000;
                novareceita.width = -1000;
                sair.width = -1000;
                botaovoltar = { 10, 10, 107, 40 };

                //retaangulos dos textos
                //x, y, largura, altura
                botaonome = { 10, 90, 500, 70 };
                botaotipo = { 435, 200, 210, 50 };
                botaoingredientes = { 10, 200, 225, 50 };
                botaoaddingredientes = { 260, 200, 160, 50 };
                botaotempoPreparo = { 10, 295, 290, 50 };
                botaorendimento = { 380, 295, 225, 50 };
                botaomodoPreparo = { 10, 390, 675, 540 };
                botaocadastro = { screenWidth - 175, screenHeight - 55, 160, 44 };

                TelaCadastroReceita(escolha, escolhatexto, r, fonts, botaovoltar, botaonome, botaotipo, botaoingredientes, botaoaddingredientes, botaomodoPreparo, botaotempoPreparo, botaorendimento, botaocadastro);

            }else if (escolha == 4){
                return 0;
            }

            /*
            DrawText(name, (int)abrirlivro.x + 5, (int)abrirlivro.y + 8, 40, BLUE);

            DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);
            if (aux == 1)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) DrawText("_", (int)abrirlivro.x + 8 + MeasureText(name, 40), (int)abrirlivro.y + 12, 40, MAROON);
                }
                else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
            }
            */
        EndDrawing();


    }

    CloseWindow();

    return 0;
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed(){

    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)){
        keyPressed = true;
    }

    return keyPressed;
}
