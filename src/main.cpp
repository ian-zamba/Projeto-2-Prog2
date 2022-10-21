#include "funcoes.h"

#define SCREEN_TITLE  "Livro de receitas da vovó"

int main(void){
    //criando as variaveis fixas
    const int screenWidth = 800;
    const int screenHeight = 450;
    const char* caminhodat = "Arquivos/receitas.dat";
    const char* caminhotxt = "Arquivos/receitas.txt";

    //inicializando a tela
    InitWindow(screenWidth, screenHeight, SCREEN_TITLE);

    //char name[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;

    Rectangle abrirlivro = { screenWidth/2.0f - 120, 110, 225, 50 };
    Rectangle buscarreceita = { screenWidth/2.0f - 120, 185, 225, 50 };
    Rectangle novareceita = { screenWidth/2.0f - 120, 260, 225, 50 };
    Rectangle sair = { screenWidth - 85, 400, 70, 38 };
    Rectangle botaovoltar = { 10, 10, 50, 25 };

    int framesCounter = 0;
    int escolha = 0;


    SetTargetFPS(10);               // Set our game to run at 10 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()){

        escolha = EscolhaBotao(escolha, abrirlivro, buscarreceita, novareceita, sair, botaovoltar);

        /*
        if (escolha == 1){
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        */
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            if(escolha == 0){
                DesenhaMenuPrincipal(abrirlivro, buscarreceita, novareceita, sair, botaovoltar);
            }else if (escolha == 1){
                TelaAbreLivro(caminhodat, botaovoltar);
            }else if (escolha == 2){
                TelaBuscaReceita(caminhodat, botaovoltar);
            }else if (escolha == 3){
                TelaCadastroReceita(caminhodat, caminhotxt, botaovoltar);
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
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}
