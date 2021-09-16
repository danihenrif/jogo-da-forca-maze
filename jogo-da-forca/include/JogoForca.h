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
        vector<string> palavrasAcertadas;//Palavras já acertadas pelo usuário
        char letra; //Letra de entrada do usuário
        string palavra; //Palavra sorteada
        string palavraForca;//Palavra que aparece na forca, inicialmente underlines
        string nomeJogador;//Nome do jogador
        int tamanhoPalavra;//tamanho da palavra
        GameStates state; //Armazena o estado do jogo
        int lineCount;//Quantidade de linhas do arquivo
        int pontos; //Pontos do usuário
        int erros;//Quantidade de erros
        int iteracoes;//Quantidad de iterações 
    public:
        JogoForca(int argc, string nomeArquivo); //Construtor
        ~JogoForca(); //Destrutor
        
        void initialize_game(int argc, string nomeArquivo);
        void process_actions();//Processa as ações do jogo
        void geraTela();//Printa toda a tela do jogo
        void loop();//Loop principal do jogo
        string sortWord();//Sorteia a palavra da forca
        void printaPalavraForca();//aparece na forca, inicialmente underlines
        void resolveWINORLOSE();//Checa se o usuário ganha ou perde o jogo
        void arquivo();//Salva os dados no arquivo, pós GAMEOVER

};

#endif