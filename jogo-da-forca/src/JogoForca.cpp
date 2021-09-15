#include "../include/JogoForca.h"
#include "../include/util.h"

#include <iostream>
#include <fstream>
#include <string>

#include <chrono>//sleep
#include <thread>//sleep

#include <random>//random number

using namespace std;

JogoForca::JogoForca(int argc, string nomeArquivo){
    letra = '\0';
    pontos = 0;
    iteracoes = 0;
    initialize_game(argc,nomeArquivo); 
}

JogoForca::~JogoForca(){}

void JogoForca::initialize_game(int argc, string nomeArquivo){
    //Carrega as palavras
    if(argc==1){
        cout << "ERROR000: Nenhum arquivo foi indicado" << endl;
        state = GAME_OVER;
        return;
    }
    
    ifstream levelFile("data/" + nomeArquivo);//carrega o arquivo
    lineCount = 0;
    string line;
    
    if(levelFile.is_open()){
        while (getline(levelFile,line)){ //pega cada linha do arquivo
            if(lineCount > 50){
                cout << "ERROR0001: Quantidade de palavras excedidas" << endl;
                state = GAME_OVER;
                return;
            }
            if(line == "\0"){
                cout << "ERROR002: Há ao menos uma linha vazia" << endl;
                state = GAME_OVER;
                return;
            }
            palavras.push_back(line);
            lineCount++;
        }
    }
    else{
        cout << "ERROR0003: Falha ao abrir o arquivo" << endl;
        state = GAME_OVER;
        return;
    }
    state = RUNNING;    
}

void JogoForca::process_actions(){
    if(state == RUNNING || state == FIRST_TIME){
        if (state == FIRST_TIME){
            palavra = sortWord(); //sorteia a palavra
            tamanhoPalavra = palavra.length();
            //Underlines
            for(int i = 0 ; i < tamanhoPalavra ; i++){
                palavraForca.push_back('_');
            }
        }
        geraTela();
    }
}

void JogoForca::loop(){
    
    while(state != GAME_OVER){
        if (iteracoes == 0){state=FIRST_TIME;}
        else if(iteracoes == -1){state=GAME_OVER;}
        else{state=RUNNING;}
        process_actions();
    }

    //Salva no arquivo de saida 

}

void JogoForca::geraTela(){
    if(iteracoes == 0){//Primeira interação
        cout << "Pontos: " << pontos << endl;
        
        printaForca(erros);
        
        //Printa underlines
        for(int i = 0 ; i < tamanhoPalavra ; i++){
            if(i == 0){cout << palavraForca[0];}
            else{
                cout << " " << palavraForca[i];     
            }
           
        }
        cout << endl;
        iteracoes++;
    }
    
    else{

        //Entrada do usuário
        cout << "Digite uma letra: ";
        cin >> letra;
        cin.ignore();

        bool acerto = 0;

        //Busca letra na string
        for(int i = 0 ; i < tamanhoPalavra ; i++){
            if(letra == palavra[i]){
                acerto = 1;
                palavraForca[i] = letra; //Muda o caractere da posição em que a letra foi acertada
                pontos++;
            }
        }

        if(acerto == 0){
            erros++;//Resgistra o erro para não ganhar pontuação extra
            pontos--; //se não acertou perde ponto
        }

        system("clear");
        cout << "Pontos: " << pontos << endl;

        printaForca(erros);

        printaPalavraForca();

        if(acerto == 0){
            cout << "ESSA LETRA NÂO ESTÀ NA PALAVRA :D" << endl;
        }

        iteracoes++;

        resolveWINORLOSE();
    }
}

string JogoForca::sortWord(){
    int random = rand() % lineCount;
    return palavras[random];
}

void JogoForca::printaPalavraForca(){
    for(int i = 0 ; i < tamanhoPalavra ; i++){
        if(i == 0){cout << palavraForca[0];}
        else{
            cout << " " << palavraForca[i];
        }
    }
    cout << endl;
}

void JogoForca::resolveWINORLOSE(){      
        if(erros ==  6){
            cout << "GAMEOVER :C, a palavra era " << palavra << endl;
            cout << "Informe o seu nome: ";
            cin >> nomeJogador;
            iteracoes = -1;
        }

        if(palavraForca == palavra){
            palavrasAcertadas.push_back(palavra);
            if (erros == 0){
                cout << "Parabéns, você acertou a palavra inteira sem erros, isso te dá 2 pontos adicionais !!" << endl;
                pontos+=2;
                cout << "Pontos: " << pontos << endl;
            }
            else{
                cout << "Parabéns, você acertou a palavra e ganhará 1 ponto adicional" << endl;
                pontos++;
                cout << "Pontos: " << pontos << endl;

            }
            cout << "Você deseja continuar jogando ? (1/0)(Sim/Não): ";
            
            int resposta;
            cin >> resposta;

            wait(1000);
            system("clear");
            if(resposta == 1){
                iteracoes = 0;
                erros = 0;
                palavraForca = "\0";           
            }
            else{
                iteracoes = -1;
                cout << "Informe o seu nome: ";
                cin >> nomeJogador;
                
                ofstream f_out;
                f_out.open("data/scores.txt",ios::app);
                
                if(f_out.is_open()){
                    f_out << nomeJogador << "; ";
                    for(vector<string>::iterator it = palavrasAcertadas.begin(); it != palavrasAcertadas.end() ; it++){
                        f_out << *it << ", ";
                    }
                    f_out << pontos << ";" << endl;
                }
                else{
                    cout << "Erro ao abrir o arquivo scores.txt" << endl;
                }
            }
        }    
}
