#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <ctype.h>
#include <iomanip>
#include <fstream> //arquivo

using namespace std;

void Cadastro (char* caminhodat, char* caminhotxt);
void Listar (char* caminhodat, char* caminhotxt);
void Buscar (char* caminhodat, char* caminhotxt);
void Imprimir (Receita r);

void Cadastro (char* caminhodat, char* caminhotxt){
    
    //Declaração de variáveis
    struct Receita r;
    //declarando o arquivo
    fstream arquivodat;
    /*
    //Abrindo o arquivo
    arquivodat.open(caminhodat, ios::in);
        //Verificando se o arquivo existe
        if(!arquivodat){
            r.codigo = 1;
        }

        //Se o arquivo existir, o código da receita será o último código + 1
        //---------------------Ta errado esse negocio ak---------------------
        else{
            arquivodat.seekg(-sizeof(r), ios::end);
            arquivodat.read((char*)&r, sizeof(r));
            r.codigo = r.codigo + 1;
        }

    //Fechando o arquivo
    arquivodat.close();
    */

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

    //Abrindo o arquivo como app

    arquivodat.open(caminhodat, ios::app);

        //Escrevendo os dados no arquivo
        arquivodat.write((char*)&r, sizeof(r));

    //Fechando o arquivo
    arquivodat.close();

    //Abrindo o arquivo como app
    arquivodat.open(caminhotxt, ios::app);

        //Escrevendo os dados no arquivo txt
        arquivodat << "----------------------------------------" << endl;
        arquivodat << "Nome: " << r.nome << endl;
        arquivodat << "Ingredientes: \n" << r.ingredientes << endl;
        arquivodat << "Modo de preparo: \n" << r.modoPreparo << endl;
        arquivodat << "Tempo de preparo: " << r.tempoPreparo << endl;
        arquivodat << "Rendimento: " << r.rendimento << endl;
    
    //Fechando o arquivo
    arquivodat.close();

}

void Listar (char* caminhodat, char* caminhotxt){
    
    //Declaração de variáveis
    struct Receita r;

    //Abrindo o arquivo como in

    fstream arquivodat;    
    arquivodat.open(caminhodat, ios::in);

        //chechando se o arquivo existe
        if(!arquivodat){
            cout << "Nao ha receitas cadastradas!" << endl;
        }
        else{
            //Lendo os dados do arquivo
            arquivodat.read((char*)&r, sizeof(r));
            while(!arquivodat.eof()){
                Imprimir(r);
                arquivodat.read((char*)&r, sizeof(r));
            }
            
        cout << "----------------------------------------" << endl;
        }

    //Fechando o arquivo
    arquivodat.close();

}

void Buscar (char* caminhodat, char* caminhotxt){

    //Declaração de variáveis
    struct Receita r;
    char nome[35];
    int achou = 0;

    //Lendo o nome da receita
    cout << "Digite o nome da receita: ";
    cin.getline(nome, 35);

    //Abrindo o arquivo como in

    fstream arquivodat;    
    arquivodat.open(caminhodat, ios::in);

        //Lendo os dados do arquivo
        do{
            arquivodat.read((char*)&r, sizeof(r));
            if(arquivodat.eof()){
                break;
            }
            if(strcmp(r.nome, nome) == 0){
                Imprimir(r);
                achou = 1;
            }
        
        }while (!arquivodat.eof());
        
        cout << "----------------------------------------" << endl;

    //Fechando o arquivo
    arquivodat.close();

    if(achou == 0){
        cout << "Receita nao encontrada!" << endl;
    }

}

void Imprimir (Receita r){
        cout << "----------------------------------------" << endl;
        cout << "Nome: " << r.nome << endl;
        cout << "Ingredientes: \n" << r.ingredientes << endl;
        cout << "Modo de preparo: \n" << r.modoPreparo << endl;
        cout << "Tempo de preparo: " << r.tempoPreparo << endl;
        cout << "Rendimento: " << r.rendimento << endl;
}