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

using namespace std;

/*
*Senha
*/
struct Senha{
    int entrada = 0;
    int count = 0;
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
void loop(){
    char key = keypad.getKey();                         //Obtém tecla pressionada
        if (key != NO_KEY){                             //Se foi pressionada uma tecla:
            if (key == '#') {                           //Se a tecla é '#'
            code_entry_init();                          //Então espera que seja inserida uma senha

            while (entrada < 4 ){                       //Conta 4 entradas/teclas
            char key = keypad.getKey();                //Obtém tecla pressionada
                if (key != NO_KEY){                    //Se foi pressionada uma tecla:
                entrada += 1;                          //Faz entrada = entrada + 1

                /* tone(audioPin, 1080, 100);          //Para cada dígito emite um som de indicação
                delay(duration);                       //Duração do som
                noTone(audioPin); */                   //Para de emitir som

              if (key == senha[posicao])                //Se a tecla pressionada corresponde ao dígito
                  posicao++;                           //da senha correspondente, soma 1 no contador

              if (posicao == 4 )                        //Se contador chegou a 4 e com dígitos corretos,
                  fechadoOk(false);                     //desbloqueia sistema

              if ((key == '#') || (entrada == 4)){     //Se foi pressionada a tecla "#' ou foram feitas
                                                       //4 entradas,
              key_init();                              //Inicializa o sistema
              break;                                   //Para o sistema e espera por uma tecla
              //delay(100);
              }
            }
          }
        }
      }
}

/*void fechadoOk(int fechado){
  if (fechado){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  else{
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }*/
}

/*
* Inicializando o sistema
*/

void key_init(){
    std::cout << "";
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    return a.exec();
}
