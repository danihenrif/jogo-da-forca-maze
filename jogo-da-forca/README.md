# Jogo da forca
<h2>Bem vindo ao clássico jogo da forca :D</h2>

<h3> by Daniel Henriques</h3>
<br>

## Compilar
<br>
Para compilar, dentro da pasta jogo-da-forca, digite no terminal os comandos:


```console
$ g++ src/*.cpp -o main -I../include -std=c++11
```

Para executar com o arquivo .txt, digite no terminal :
```console
$ ./main "nome-do-arquivo.txt"
  ex: ./main words.txt
```
## Atenção

* <span style="color:red">Os arquivos.txt devem estar na pasta data</span>
<br>
* <span style="color:red">Os arquivos.txt não devem conter mais do que 50 palavras ou espaços vazios entre palavras, caso contrário uma mensagem de ERRO será informada e o programa encerrará</span>
<br>

## Limitações
* O jogo não barra letras repetidas