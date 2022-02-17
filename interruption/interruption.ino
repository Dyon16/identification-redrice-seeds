#define LED_PIN 7
#define SENSOR_PIN A0

int valueSaver[500];
int valueSensor, limit, counterLimit = 0, totalValue = 0, average, activator = 0, counterWait = 0, counterInterruption = 0, stateSeed = 0;

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

  int counter;

  Serial.println(counterInterruption);

  if (counterInterruption > 100)
  {
    for (counter = 0; counter < 499; counter ++)
      {
        if (counter == 0)
        {
          Serial.println("inicio");
          Serial.println("");
        }
        
        totalValue = totalValue + valueSaver[counter];
        
        if (valueSaver[counter] != 0)
        {
          Serial.println(valueSaver[counter]);
        }
      }
    
      if (counter == 498)
      {
        stateSeed = 1;
        Serial.println("Fim");
        Serial.println("");
      }
    }
    
    if ((counterInterruption == 500) && (activator == 1))
    {
      average = totalValue/counterInterruption;
      Serial.print("Average: ");
      Serial.println(average);
    
      Serial.println("Encheu o vetor");
    
      counterInterruption = 0;
      totalValue = 0;
      activator = 0;
    }
}

ISR(TIMER1_OVF_vect)//interrupção do TMER1 com frequencia de 1Hz //Função da biblioteca arduino
{
  TCNT1 += 49536; //Renicia TIMER //65536 - 16000 = 49536 (valor a ser carregado no registrador de 16 bits)

  /*if (counterLimit == 0)
  {
    if (counterWait == 10)
    {
      limit = valueSensor + 150; 
      counterLimit++;
    }
    counterWait++;
  }*/

  limit = 10;
  
  valueSensor = analogRead(SENSOR_PIN);
  
  if(valueSensor > limit)
  {
    for(counterInterruption = 0; counterInterruption < 499; counterInterruption++)
    {
      valueSaver[counterInterruption] = analogRead(SENSOR_PIN);
    }
  }
}
