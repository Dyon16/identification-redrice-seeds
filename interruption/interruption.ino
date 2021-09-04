#define LED_PIN 7
#define SENSOR_PIN A0
#define pinSensor

int valueSave[500];
int valueMonitor, limit, countl = 0, tval = 0, average, activator = 0;
int cont = 0;
int estado_led = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);   
  
  // Configuração do timer1 //Liga interrupção
  TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 1;                        // 0000 0001b // configura prescaler para dividir por 1
  TCNT1 = 49536;                    // 65536 - 16000 =  49536 (valor a ser carregado no registrador de 16 bits) //Tem que mudar esse valor                                       
  TIMSK1 |= (1 << TOIE1);           // habilita a interrupção do TIMER1
} 

void loop()
{
  if (cont < 500)
  {
    for (int i = 0; i < 499; i ++)
    {
      tval = tval + valueSave[i];
      
      Serial.print("Value: ");
      Serial.println(valueSave[i]);
    }
  }

  if ((cont = 500) && (activator = 1))
  {
    average = tval/cont;
    Serial.print("Average: ");
    Serial.println(average);

    Serial.println("Encheu o vetor");

    cont = 0;
    tval = 0;
    activator = 0;
  }
}

ISR(TIMER1_OVF_vect)//interrupção do TIMER1 com frequencia de 1Hz //Função da biblioteca arduino
{
  TCNT1 += 49536; //Renicia TIMER //65536 - 16000 = 49536 (valor a ser carregado no registrador de 16 bits)

  if (countl == 0)
  {
    limit = valueMonitor + 50; 
    countl++;
  }

  if(cont < 500)
  {
    valueMonitor = analogRead(SENSOR_PIN);
    
      if (valueMonitor > limit)
      {
        valueSave[cont] = analogRead(SENSOR_PIN);
        activator = 1;
        cont++;
      }
  }

  /*if (cont >= 1000)
  {
    cont = 0;
  }
  
  cont++;

  if (cont >= 500)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }*/
}
