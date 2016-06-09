#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <iostream>

struct Comando {
    int id;
    bool enable;
    /*
    * Senha
    */
    int cout = 0;
    char pass [4]; //Senha
    const byte ROWS = 4; //Quatro linhas
    const byte COLS = 3; //Três colunas
};

#define PORTNUM 4325

//Mapeamento de teclas
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

void loop(){
  char key = keypad.getKey();                         //Obtém tecla pressionada
  if (key != NO_KEY){                                  //Se foi pressionada uma tecla:
    if (key == '#') {                                          //Se a tecla é '#'
      code_entry_init();                                    //Então espera que seja inserida uma senha
      int entrada = 0;
      while (count < 4 ){                                  //Conta 4 entradas/teclas
        char key = keypad.getKey();                //Obtém tecla pressionada
        if (key != NO_KEY){                          //Se foi pressionada uma tecla:
          entrada += 1;                                     //Faz entrada = entrada + 1
          /* tone(audioPin, 1080, 100);                 //Para cada dígito emite um som de indicação
          delay(duration);                                 //Duração do som
          noTone(audioPin); */                            //Para de emitir som
          if (key == pass[count])count += 1;       //Se a tecla pressionada corresponde ao dígito
                                                                      //da senha correspondente, soma 1 no contador
          if ( count == 4 ) unlocked();                 //Se contador chegou a 4 e com dígitos corretos,
                                                                     //desbloqueia sistema
          if ((key == '#') || (entrada == 4)){        //Se foi pressionada a tecla "#' ou foram feitas
                                                                     //4 entradas,
             key_init();                                         //Inicializa o sistema
            break;                                               //Para o sistema e espera por uma tecla
          }
        }
      }
    }
  }
}
int main(int argc, char *argv[])
{

    bool controle = true;
    char com;
    struct sockaddr_in endereco;
    int socketId;

    Comando comando;
    comando.id = 0; // ID padrão: 0
    comando.enable = true; //Enabled padrão

    int bytesenviados;
    /*
     * Configurações do endereço
    */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons((short int)(PORTNUM));
    endereco.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(controle){
        std::cout << "----------------\n";
        std::cout << "Comandos atuais: ID: " << comando.id << ".\n";
        std::cout << "Enabled: " << comando.enable << ".\n";
        std::cout << "----------------\n";
        std::cout << "Lista de comandos:\n";
        std::cout << "i: Setar ID do comando.\n";
        std::cout << "e: Setar enabled/disabled.\n";
        std::cout << "s: Enviar comando.\n";
        std::cout << "x: Sair do programa de controle.\n";
        std::cin >> com;
        switch(com){
            case 'I':
            case 'i':
                std::cout << "Sete o ID de 0 até 1 (0 para todos).\n";
                std::cin >> comando.id;
                break;
            case 'e':
            case 'E':
                comando.enable = !comando.enable;
                std::cout << "Você inverteu o enabled.\n";
                break;
            case 'S':
            case 's':
                /*
                 * Criando o Socket
                 *
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

                //Enviar uma msg para o cliente que se conectou
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
