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
#define inRele 50

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
    Serial.begin(9600); //Inicia a porta serial
    pinMode(inRele, INPUT); // define o pino 13 como entrada (recebe)
    //fechadoOk(true);
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
                  digitalWrite(inRele, HIGH);
                  delayMicroseconds(10);
                  //fechadoOk(false);                     //desbloqueia sistema

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
    int count = 0; //Variável count é zero na inicialização

    cout << "Acesso ao Sistema: \n";

    void code_entry_init();

    cout << "Entre com a senha: \n";
    count = 0;  //Variável count é zero na entrada da senha

    /*
    digitalWrite(redPin, LOW);                            //Apaga LED Vermelho
    digitalWrite(yellowPin, HIGH);                      //Acende LED Amarelo
    digitalWrite(greenPin, LOW);                        //Apaga LED Verde
    */
}

/*
* Subrotina para Acesso Liberado
*/
void fechadoOk(){                                           //unlocked

    cout << "Acesso Liberado!";                       //Emite mensagem

    digitalWrite(redPin, LOW);                           //Apaga LED Vermelho
    digitalWrite(yellowPin, LOW);                      //Apaga LED Amarelo

    //Executa 20 vezes +- 5 segundos, emite som e pisca LED verde
    for (int x = 0; x < 20; x++){

    digitalWrite(greenPin, HIGH);
    tone(audioPin, 2000, 100);
    delay(duration);
    noTone(audioPin);
    digitalWrite(greenPin, LOW);
    tone(audioPin, 2000, 100);
    delay(duration);
    noTone(audioPin);
    delay(250);
    }
  }

int main(int argc, char *argv[])
{
    bool controle = true;
    char com;

    struct sockaddr_in endereco;
    int socketId;

    int bytesenviados;

    Comando comando;
    comando.id = 0;
    comando.enable = true;

    /*
     * Configurações do endereço
    */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons((short int)(PORTNUM));
    endereco.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* while(controle){
        cout << "Digite sua senha: \n";
        cout << "Digite # para confirmar \n";

        switch(com){
        case :
            key_init();
            break;
        case #:
            fechadoOk();
            break;*/

    /*
    * Criando o Socket
    */
        socketId = socket(AF_INET, SOCK_STREAM, 0);

        //Verificar erros
        if (socketId == -1)
        {
        printf("Falha ao executar socket()\n");
        exit(EXIT_FAILURE);
        }

        //Conectando o socket cliente ao socket servidor
        if ( connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
        {
        printf("Falha ao executar connect()\n");
        exit(EXIT_FAILURE);
        }
        printf ("Cliente conectado ao servidor\n");

        //Enviar uma mensagem para o cliente que se conectou
        printf("Cliente vai enviar um comando\n");
        bytesenviados = send(socketId, &comando,sizeof(comando),0);

        if (bytesenviados == -1)
        {
            printf("Falha ao executar send()");
            exit(EXIT_FAILURE);
            }
            //printf("Cliente enviou a seguinte msg (%d bytes) para o servidor: %d \n",bytesenviados, mensagem.id);

            close(socketId);
            break;
            case 'X':
                case 'x':
                    controle = !controle;
                break;
                default:
                break;
            }
            std::system("clear");
        }
        return 0;
    }

    //QCoreApplication a(argc, argv);
    //return a.exec();
}
