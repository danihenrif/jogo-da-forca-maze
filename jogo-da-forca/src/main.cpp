#include <iostream>
#include "../include/JogoForca.h"

int main(int argc, char *argv[]){
    std::string nomeArquivo = argv[1];
    JogoForca jogo(argc,nomeArquivo);
    jogo.loop(); //bloqueia aqui e só sai quando o jogo termina
    return 0;
}