#include "display.h"

int cout = 0;
char pass [4]; //Senha
const byte ROWS = 4; //Quatro linhas
const byte COLS = 3; //Três colunas

display::display()
{
}

void setup()
{
}

//Mapeamento de teclas
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

//Loop Principal do Programa
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
          tone(audioPin, 1080, 100);                 //Para cada dígito emite um som de indicação
          delay(duration);                                 //Duração do som
          noTone(audioPin);                            //Para de emitir som
          if (key == pass[count])count += 1;       //Se a tecla pressionada corresponde ao dígito
                                                                      //da senha correspondente, soma 1 no contador
          if ( count == 4 ) unlocked();                 //Se contador chegou a 4 e com dígitos corretos,
                                                                     //desbloqueia siatema
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

//Inicializar o Sistema
void key_init (){
  lcd.clear();                                                //Limpa o LCD
  lcd.print("Aguardando...");                        //Emite mensagem
  lcd.setCursor(0,1);                                   //Muda de linha
  lcd.print("Tecle #");                                  //Emite mensagem

  count = 0;                                                //Variável count é zero na inicialização

  //Subrotina de Entrada da Senha
  void code_entry_init(){
    lcd.clear();                                                //Limpa LCD
    lcd.print("Entre a Senha:");                        //Emite mensagem

    count = 0;                                                //Variável count é zero na entrada de senha

    //Emite som e acende LEDs
    tone(audioPin, 1500, 100);
    delay(duration);
    noTone(audioPin);
    tone(audioPin, 1500, 100);
    delay(duration);
    noTone(audioPin);
    tone(audioPin, 1500, 100);
    delay(duration);
    noTone(audioPin);
    digitalWrite(redPin, LOW);                            //Apaga LED Vermelho
    digitalWrite(yellowPin, HIGH);                      //Acende LED Amarelo
    digitalWrite(greenPin, LOW);                        //Apaga LED Verde
  }


  //Subrotina para Acesso Liberado
  void unlocked(){
    lcd.clear();                                                    //Limpa LCD
    lcd.print("Acesso Liberado!");                       //Emite mensagem

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
