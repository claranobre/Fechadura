#include <QCoreApplication>
#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <iostream>

#define port 4325
/*
*Senha
*/
struct Senha{
    int posicao = 0;
    char senha[4] = "2016"; /*Senha*/
    const byte linhas = 4; /*Quatro linhas*/
    const byte colunas = 3; /*Três colunas*/
}
/*
* Mapeamento das teclas
*/
char teclas[linhas][colunas] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pinoLinha[linhas] = {9,8,7,6};
byte pinoColuna[colunas] = {5,4,3,2};

Keypad keypad = Keypad(makeKeymap(teclas), pinoLinha, pinoColuna, linhas, colunas);

void setup(){
    fechadoOk(true);
}

/*
* Função para verificar a senha
*/


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    return a.exec();
}
