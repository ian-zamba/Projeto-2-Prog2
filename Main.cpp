#include "structs.h"
#include "funcoes.h"


int main(void) {

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
        switch (opcao){
            case '1':
                Cadastro(caminhodat, caminhotxt);
                break;
            case '2':
                Listar(caminhodat, caminhotxt);
                break;
            case '3':
                Buscar(caminhodat, caminhotxt);
                break;
            case '4':
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "\nOpcao invalida!\n" << endl;
                break;
        }
    } while (opcao != '4');


    return 0;
}