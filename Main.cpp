#include "funcoes.h"


int main(void){

    //deixar em portugues
    setlocale(LC_ALL, "Portuguese");

    //limpa a tela
    system("cls");

    //Declarando o caminho do arquivo
    char* caminhodat = "receitas.dat";
    char* caminhotxt = "receitas.txt";
    //Declarando a variável de opção
    char opcao;

    //Menu
    do{

        cout << "1 - Cadastrar receita" << endl;
        cout << "2 - Listar receitas" << endl;
        cout << "3 - Buscar receita" << endl;
        cout << "4 - Sair" << endl;
        opcao = getch();
        //limpa a tela
        system("cls");
        
        switch (opcao){
            case '1':
                Cadastro(caminhodat, caminhotxt);
                break;
            case '2':
                Listar(caminhodat);
                break;
            case '3':
                Buscar(caminhodat);
                break;
            case '4':
                Saindo();
                break;
            default:
                cout << "Opcao invalida!\n" << endl;
                break;
        }

    } while (opcao != '4');

    return 0;
}