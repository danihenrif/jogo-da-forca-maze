#ifndef JogoForca_h
#define JogoForca_h

#include <iostream>
#include <vector>

using namespace std;

class JogoForca{
    public:
        enum GameStates{
            RUNNING,
            FIRST_TIME,
            GAME_OVER,
            WAITING_USER
        };
    private:
        vector<string> palavras; //Vector para armazenas as palavras do jogo da forca vindas do arquivo txt
        vector<string> palavrasAcertadas;
        char letra; //Letra de entrada do usuário
        string palavra; //Palavra sorteada
        string palavraForca;
        string nomeJogador;
        int tamanhoPalavra;
        GameStates state; //Armazena o estado do jogo
        int lineCount;
        int pontos; 
        int erros;
        int iteracoes;
    public:
        JogoForca(int argc, string nomeArquivo); //Construtor
        ~JogoForca(); //Destrutor
        
        void initialize_game(int argc, string nomeArquivo);
        void process_actions();
        void geraTela();
        void loop();
        string sortWord();
        void printaPalavraForca();
        void resolveWINORLOSE();

};

#endif