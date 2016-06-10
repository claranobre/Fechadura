#include "socket.h"

using namespace std;

socket::socket(int pornum = 4325, char* ip = "127.0.0.1")
{
    this->portnum = portnum; //número da porta de conexão
    this->ip = ip;  //ip de conexão
    this->ligado = false; //status da fechadura
    this->pass = false; //verificação de autenticação

    this->comando.id = 0;   //comando do cliente
    this->comando.enable = 1; //liberação de sinal do comando dado
}
socket::~socket(){
    connect.join();
}

void socket::setIp(char* ip){
    this->ip = ip;
}

void socket::setPort(int port){
    this->portnum = port;
}

void socket::changeStat(bool set){
    this->ligado = set;
}

void socket::socketHandler(int socketDescriptor, Comando comando){
    int byteslidos;
    /*
     * Verificando erros
     */
    if ( socketDescriptor == -1)
    {
        printf("Falha ao executar accept()");
        exit(EXIT_FAILURE);
    }

    /*
     * Receber uma mensagem do cliente
     */
    byteslidos = recv(socketDescriptor,&comando,sizeof(comando),0);
    if (byteslidos == -1)
    {
        printf("Falha ao executar recv()");
        exit(EXIT_FAILURE);
    }
    else if (byteslidos == 0)
    {
        printf("Cliente finalizou a conexão\n");
        exit(EXIT_SUCCESS);
    }

    cout<< "Servidor recebeu os seguintes dados do cliente: " << endl;
    cout << comando.id << endl;
    cout << comando.enable << endl;

    this->comando.id = comando.id;
    this->comando.enable = comando.enable;
    emit update();
    close(socketDescriptor);
}
void socket::start(){
    connect = std::thread(&socket::run,this);
}

void socket::run(){

    struct sockaddr_in endereco;
    int socketId;

    //variáveis relacionadas com as conexões clientes
    struct sockaddr_in enderecoCliente;
    socklen_t tamanhoEnderecoCliente = sizeof(struct sockaddr);
    int conexaoClienteId;

    /*
     * Mensagem enviada pelo cliente
     */
    Comando *comando;

    /*
     * Configurações do endereço
    */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(this->portnum);
    //endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_addr.s_addr = inet_addr(this->ip);

    /*
     * Criando o socket
     *
     * PARAM1: AF_INET ou AF_INET6 (IPV4 ou IPV6)
     * PARAM2: SOCK_STREAM ou SOCK_DGRAM
     * PARAM3: protocolo (IP, UDP, TCP, etc). Valor 0 escolhe automaticamente
    */
    socketId = socket(AF_INET, SOCK_STREAM, 0);

    /*
     * Verificar erros
     */
    if (socketId == -1)
    {
        printf("Falha ao executar socket()\n");
        //exit(EXIT_FAILURE);
        return;
    }

    /*
     * Conectando o socket a uma porta. Executado apenas no lado servidor
     */
    if ( bind (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
    {
        printf("Falha ao executar bind()\n");
        //exit(EXIT_FAILURE);
        return;
    }

    /*
     * Habilitando o servidor a receber conexoes do cliente
     */
    if ( listen( socketId, 10 ) == -1)
    {
        printf("Falha ao executar listen()\n");
        //exit(EXIT_FAILURE);
        return;
    }
    this->ligado = true;
    cout << "Abrindo conexão em" << this->ip << " na porta " << this->portnum << ".";
    while(this->ligado)
    {

        cout << "Servidor: esperando conexões clientes\n";
        /*
         * Servidor fica bloqueado esperando uma conexão do cliente
         */
        conexaoClienteId = accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );

        printf("Servidor: recebeu conexão de %s\n", inet_ntoa(enderecoCliente.sin_addr));

        /*
         * Disparar a thread
         */
        std::thread t(&socket::socketHandler, this, conexaoClienteId, *comando);
        t.detach();
    }
}


