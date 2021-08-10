#define LED_PIN 7

int estado_led = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);   
  
  // Configuração do timer1 //Liga interrupção
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 1;                        // 0000 0001b // configura prescaler para dividir por 1
  TCNT1 = 49536;                    // 65536 - 16000 =  49536 (valor a ser carregado no registrador de 16 bits) //Tem que mudar esse valor                                       
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1
} 

ISR(TIMER1_OVF_vect)//interrupção do TIMER1 com frequencia de 1Hz //Função da biblioteca arduino
{
  TCNT1 += 49536; //Renicia TIMER //65536 - 16000 = 49536 (valor a ser carregado no registrador de 16 bits)

  if (estado_led >= 1000)
  {
    estado_led = 0;
  }
  
  estado_led++;

  if (estado_led >= 500)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }

  /*if(tx_fsm >= TX_START)
  {
    if(tx_fsm == TX_START)
    {
       tx_tick_count = 3; // na próxima interrupção, inicie o start bit.
       tx_fsm++;
       tx_shift_frame = ((unsigned int)tx_byte<<1)|0xFE00; // 7 bits em 1 seguido do byte a ser transmitido seguido de zero (frame completo em uma palavra)
    }
    else // vamos transmitir o frame de dados (start byte stop)
    {
      tx_tick_count++;
      
      if((tx_tick_count & 3)== 0) // forma eficiente de testar se passou 4 unidades
      { 
        digitalWrite(TX_PIN, tx_shift_frame & 1);
        tx_shift_frame >>=1;
        tx_fsm++;
        
        if(tx_fsm>TX_STOP_BIT)
        {
          tx_fsm=TX_IDLE; // transmitiu todo o frame, não precisa fazer mais nada.        
        }
      }  
    }
  }

  if(rx_fsm == RX_IDLE)
  {
    if(digitalRead(RX_PIN) == 0) // start bit detectado
    {
      rx_tick_count=3;
      rx_fsm++;      
    }
  }
  else // tem byte sendo recebido
  {
    rx_tick_count++;
    
    if((rx_tick_count & 3)== 0) // forma eficiente de testar se passou 4 unidades
    {
      rx_fsm++;
      
      if(rx_fsm <= RX_STOP_BIT)
      {
        rx_shift>>=1;   
        
        if(digitalRead(RX_PIN))rx_shift+=0x80; //0x80 = 0000 0001 0000 0000
      }
      else
      {
        rx_fsm=RX_IDLE;
        rx_byte=rx_shift;
        rx_new_byte=1; // notifica que há um novo byte recebido.
      }
    }
  }*/
}
