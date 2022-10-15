#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <ctype.h>
#include <iomanip>
#include <windows.h>
#include <fstream> //arquivo
#include "structs.h"

using namespace std;

void Cadastro(char* caminhodat, char* caminhotxt);
void Listar(char* caminhodat);
void Buscar(char* caminhodat);
void Imprimir(Receita r);
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
        arquivotxt << "----------------------------------------" << endl;
        arquivotxt << "Nome: " << r.nome << endl;
        if(r.tipo == '1'){
            arquivotxt << "Tipo: Doce" << endl;
        }
        else{
            arquivotxt << "Tipo: Salgado" << endl;
        }

        arquivotxt << "Ingredientes: \n" << r.ingredientes << endl;
        arquivotxt << "Modo de preparo: \n" << r.modoPreparo << endl;
        arquivotxt << "Tempo de preparo: " << r.tempoPreparo << endl;
        arquivotxt << "Rendimento: " << r.rendimento << endl;
    
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
                        Imprimir(r);
                        achou = 1;
                    }
                    else if(tipo == '2' && r.tipo == '2'){
                        Imprimir(r);
                        achou = 1;
                    }
                    else if(tipo == '3'){
                        Imprimir(r);
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
    char nome[35];
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
            cin.getline(nome, 35);

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
                for(int i = 0; i < strlen(nome); i++){
                    nome[i] = tolower(nome[i]);
                }
                if(strcmp(r.nome, nome) == 0){
                    Imprimir(r);
                    achou = 1;
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

void Imprimir (Receita r){
        cout << "----------------------------------------" << endl;
        cout << "Nome: " << r.nome << endl;
        if(r.tipo == '1'){
            cout << "Tipo: Doce" << endl;
        }
        else{
            cout << "Tipo: Salgado" << endl;
        }
        cout << "Ingredientes: \n" << r.ingredientes << endl;
        cout << "Modo de preparo: \n" << r.modoPreparo << endl;
        cout << "Tempo de preparo: " << r.tempoPreparo << endl;
        cout << "Rendimento: " << r.rendimento << endl;
}

void Saindo(){
    cout << "Saindo";
    Sleep(500);
    //limpa a tela
    system("cls");
    cout << "Saindo.";
    Sleep(500);
    //limpa a tela
    system("cls");
    cout << "Saindo..";
    Sleep(500);
    //limpa a tela
    system("cls");
    cout << "Saindo...\n" << endl;
}