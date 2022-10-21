#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <fstream> //arquivo
#include "structs.h"

using namespace std;

void Cadastro(char* caminhodat, char* caminhotxt);
void Listar(char* caminhodat);
void Buscar(char* caminhodat);
void Imprimir(Receita r, ostream &saida);
void Saindo();

void Cadastro (char* caminhodat, char* caminhotxt){
    
    //Declaração de variáveis

    struct Receita r;

    //declarando o arquivo

    fstream arquivodat;
    fstream arquivotxt;

    //perguntar tipo doce ou salgado

    cout << "1 - Doce" << endl 
    <<  "2 - Salgado" << endl;
    do{
        r.tipo = getch();
        if (r.tipo != '1' && r.tipo != '2'){
            cout << "Tipo invalido! Digite novamente: " << endl;
        }
    }while(r.tipo != '1' && r.tipo != '2');

    //limpa a tela
    system("cls");

    //Lendo os dados da receita

    cout << "Digite o nome da receita: ";
    cin.getline(r.nome, 35);
    cout << "Digite os ingredientes da receita: ";
    fgets(r.ingredientes, 150, stdin);
    char aux[30];
    do{
        fgets(aux, 30, stdin);
        if(strcmp(aux, "\n") != 0){
            strcat(r.ingredientes, aux);
        }        
    }while (strcmp(aux, "\n") != 0);
    
    cout << "Digite o modo de preparo da receita: ";
    cin.getline(r.modoPreparo, 100);
    cout << "Digite o tempo de preparo da receita: ";
    cin.getline(r.tempoPreparo, 10);
    cout << "Digite o rendimento da receita: ";
    cin.getline(r.rendimento, 10);

    //limpa a tela
    system("cls");

    //Abrindo o arquivo como app

    arquivodat.open(caminhodat, ios::app);

        //Escrevendo os dados no arquivo

        arquivodat.write((char*)&r, sizeof(r));

    //Fechando o arquivo
    arquivodat.close();

    //Abrindo o arquivo como app

    arquivotxt.open(caminhotxt, ios::app);

        //Escrevendo os dados no arquivo txt

        Imprimir(r, arquivotxt);
    
    //Fechando o arquivo
    arquivotxt.close();

}

void Listar (char* caminhodat){
    
    //Declaração de variáveis

    struct Receita r;
    char tipo;
    int achou = 0;
    fstream arquivodat;    

    //Abrindo o arquivo como in

    arquivodat.open(caminhodat, ios::in);

        //chechando se o arquivo existe

        if(!arquivodat){
            cout << "Nao ha receitas cadastradas!" << endl;
            cout << "----------------------------------------" << endl;
        }
        else{
            //perguntar o tipo

            cout << "1 - Doce" << endl;
            cout << "2 - Salgado" << endl;
            cout << "3 - Todos" << endl;
            cout << "4 - Voltar" << endl;
            do{
                tipo = getch();
                if (tipo != '1' && tipo != '2' && tipo != '3' && tipo != '4'){
                    cout << "Tipo invalido! Digite novamente: " << endl;
                }
            }while(tipo != '1' && tipo != '2' && tipo != '3' && tipo != '4');

            //limpa a tela
            system("cls");

            if(tipo != '4'){

                //Lendo os dados do arquivo

                while(arquivodat.read((char*)&r, sizeof(r))){
                    if(tipo == '1' && r.tipo == '1'){
                        Imprimir(r, cout);
                        achou = 1;
                    }
                    else if(tipo == '2' && r.tipo == '2'){
                        Imprimir(r, cout);
                        achou = 1;
                    }
                    else if(tipo == '3'){
                        Imprimir(r, cout);
                        achou = 1;
                    }
                }
                if(achou == 0){
                    cout << "----------------------------------------" << endl;
                    cout << "Nenhuma receita encontrada!" << endl;
                }
            
                cout << "----------------------------------------" << endl;
                Listar(caminhodat);
            }

            //limpa a tela
            system("cls");


        }

    //Fechando o arquivo
    arquivodat.close();

}

void Buscar (char* caminhodat){

    //Declaração de variáveis
    
    struct Receita r;
    char pesquisa[35];    
    char aux[35];
    int achou = 0;
    fstream arquivodat;    

    //Abrindo o arquivo como in

    arquivodat.open(caminhodat, ios::in);

        //chechando se o arquivo existe

        if(!arquivodat){
            cout << "Nao ha receitas cadastradas!" << endl;
        }else{
            //Lendo o nome da receita
            cout << "Digite o nome da receita: ";
            fgets(pesquisa, 35, stdin);
            //tirar o \n do final da string
            pesquisa[strlen(pesquisa)-1] = '\0';

            //Lendo os dados do arquivo

            do{
                arquivodat.read((char*)&r, sizeof(r));
                if(arquivodat.eof()){
                    break;
                }
                //deixar tudo em minusculo
                for(int i = 0; i < strlen(r.nome); i++){
                    r.nome[i] = tolower(r.nome[i]);
                }
                for(int i = 0; i < strlen(pesquisa); i++){
                    pesquisa[i] = tolower(pesquisa[i]);
                }

                int i = 0;

                while(i < strlen(r.nome)){
                    if(r.nome[i] == pesquisa[0]){
                        int j = 0;
                        while(j < strlen(pesquisa)){
                            aux[j] = r.nome[i];
                            i++;
                            j++;
                        }
                        aux[j] = '\0';
                        if(strcmp(aux, pesquisa) == 0){
                            Imprimir(r, cout);
                            achou = 1;
                        }
                    }
                    i++;
                }
            
            }while (!arquivodat.eof());

            if(achou == 0){
                cout << "----------------------------------------" << endl;
                cout << "Nenhuma receita encontrada!" << endl;
            }
        }
        
        cout << "----------------------------------------" << endl;

    //Fechando o arquivo
    arquivodat.close();

}

void Imprimir (Receita r , ostream &saida){
        saida << "----------------------------------------" << endl;
        saida << "Nome: " << r.nome << endl;
        if(r.tipo == '1'){
            saida << "Tipo: Doce" << endl;
        }
        else{
            saida << "Tipo: Salgado" << endl;
        }
        saida << "Ingredientes: \n" << r.ingredientes;
        saida << "Modo de preparo: \n" << r.modoPreparo << endl;
        saida << "Tempo de preparo: " << r.tempoPreparo << endl;
        saida << "Rendimento: " << r.rendimento << endl;
}

void Saindo(){
    //limpa a tela
    system("cls");
    cout << "Saindo";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".";
    Sleep(500);
    cout << ".\n\n";
}