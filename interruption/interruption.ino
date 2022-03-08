#define LED_PIN 7
#define SENSOR_PIN A0

//state = 0, configuration
//state = 1, before
//state = 2, during
//state = 3, later

int valueSaver[500];
int valueSensor, limit, counterLimit = 0, totalValue = 0, average, activator = 0, counterWait = 0, counterInterruption = 0, stateSeed = 0, state = 0, gcounter = 0, seedCounter = 0, brokenSeed = 0;

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

  analogRead(SENSOR_PIN);
  delay(10);

  valueSensor = analogRead(SENSOR_PIN);
  limit = valueSensor + 50;
  
  Serial.print("Limit: ");
  Serial.println(limit);
  
  state = 1;
} 

void loop()
{
  int counter;

  //Serial.print("gcounter: ");
  //Serial.println(gcounter);
  
  if (state == 3)
  {
    seedCounter++;
    
    Serial.print("seedCounter: ");
    Serial.println(seedCounter);

    /*if(gcounter <= 6)
    {
      brokenSeed++;

      Serial.print("brokenSeed: ");
      Serial.println(brokenSeed);

      state = 1;
    }*/
    
    for (counter = 0; counter <= gcounter; counter ++)
      {
        totalValue = totalValue + valueSaver[counter];
        Serial.println(valueSaver[counter]);
      }

    state = 1;
  }
}

ISR(TIMER1_OVF_vect)//interrupção do TMER1 com frequencia de 1Hz //Função da biblioteca arduino
{
  TCNT1 += 49536; //Renicia TIMER //65536 - 16000 = 49536 (valor a ser carregado no registrador de 16 bits)
  
  valueSensor = analogRead(SENSOR_PIN);

  if (state == 1)
  {
    if(valueSensor > limit)
    {
      state = 2;
      gcounter = 0;
    }
  }
  
  if (state == 2)
  {
    valueSaver[gcounter] = valueSensor;

    if(gcounter > 498)
    {
      state = 3;
    }

    if(valueSensor < limit)
    {
      state = 3;
    }

    gcounter++;
  }
}
