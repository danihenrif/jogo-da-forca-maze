#include "../include/JogoForca.h"
#include "../include/util.h"

#include <iostream>
#include <fstream>
#include <string>

#include <chrono>//sleep
#include <thread>//sleep

#include <random>//random number
#include <ctime>//random number

using namespace std;

JogoForca::JogoForca(int argc, string nomeArquivo){
    letra = '\0';
    pontos = 0;
    erros = 0;
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
    state = FIRST_TIME;    
}


void JogoForca::loop(){
    if(state==GAME_OVER){return;}//Finaliza antes de mostrar a tela em caso de erro no arquivo
    
    //Iniciar o jogo ou listar
    cout << "Você deseja jogar ou listar os scores anteriores (1/0)? ";
    int op;
    cin >> op;
    cin.ignore();
    
    if(op == 0){//Lista os scores anteriores
        ifstream arq("data/scores.txt");//abre o arquivo scpres.txt
        if(arq.is_open()){
            cout << arq.rdbuf();//printa o conteudo do arquivo scores.txt
        }
    }
    else{//Loop para o jogo
        while(state != GAME_OVER){ //Loop de realização do jogo
            process_actions();
        }
    }
}

void JogoForca::process_actions(){  
    if(state == RUNNING || state == FIRST_TIME){
        if (state == FIRST_TIME){
            palavra = sortWord(); //sorteia a palavra
            tamanhoPalavra = palavra.length();
            
            //Acrescenta os underlines na palavra da forca
            for(int i = 0 ; i < tamanhoPalavra ; i++){
                palavraForca.push_back('_');
            }
        }
        geraTela();
    }
}


void JogoForca::geraTela(){
    if(state == FIRST_TIME){//Primeira interação
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
        state = RUNNING;
    }
    
    else{
        //Entrada do usuário
        cout << "Digite uma letra: ";
        cin >> letra;
        cin.ignore();

        bool acerto = 0;

        //Busca letra na string e muda caso acerte
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

        clearScreen();
        cout << "Pontos: " << pontos << endl;

        printaForca(erros);

        printaPalavraForca();

        if(acerto == 0){
            cout << "ESSA LETRA NÂO ESTÀ NA PALAVRA :D" << endl;
        }

        resolveWINORLOSE();
    }
}

string JogoForca::sortWord(){
    srand(time(NULL));
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
        arquivo();//Grava no arquivo
        return;
    }

    if(palavraForca == palavra){
        palavrasAcertadas.push_back(palavra);//Adiciona a palavra na lista de palavras acertadas
            
        /*Checa se venceu sem errar*/
        if (erros == 0){
            cout << "Parabéns, você acertou a palavra inteira sem erros, isso te dá 1 ponto adicional !!" << endl;
            pontos++;
            cout << "Pontos: " << pontos << endl;
        }
        else{
            cout << "Parabéns, você acertou a palavra e ganhará mais 2 pontos" << endl;
            pontos+=2;
            cout << "Pontos: " << pontos << endl;

        }
        /*                         */
            
        cout << "Você deseja continuar jogando ? (1/0)(Sim/Não): ";
            
        int resposta;
        cin >> resposta;

        wait(1000);
        clearScreen();
            
        // Se quer continuar, zera as variáveis de controle para a próxima rodada
        if(resposta == 1){
            state=FIRST_TIME;
            erros = 0;
            palavraForca = "\0";       
        }
        else{//Se não grava no arquivo
            arquivo();
        }
    }    
}

void JogoForca::arquivo(){
    state=GAME_OVER;
    cout << "Informe o seu nome: ";
    cin >> nomeJogador;
                
    //Adiciona os dados da rodada no arquivo
    ofstream f_out;
    f_out.open("data/scores.txt",ios::app);//Abre o arquivo
                
    if(f_out.is_open()){
        f_out << nomeJogador << "; "; //Adiciona o nome do jogador no arquivo
        
        for(vector<string>::iterator it = palavrasAcertadas.begin(); it != palavrasAcertadas.end() ; it++){//Palavras acertadas
            f_out << *it << ", ";
        }
        
        f_out << pontos << ";" << endl; //Adiciona a pontuação no arquivo
        cout << "Seus dados foram gravados em data/scores.txt" << endl;
    }
    else{
        cout << "Erro ao abrir o arquivo scores.txt" << endl;
    }    
}
