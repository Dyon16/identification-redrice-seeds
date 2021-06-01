int average = 0, cont = 0, state = 0, value, limit, contt = 0, contl = 0;
unsigned long tval = 0;

unsigned long timee;
unsigned long timeinit;
unsigned long timend;
unsigned long ttotal;

/*
states:
0 - Configuração;
1 - Antes da passagem;
2 - Durante a passagem;
3 - Pós passagem.
*/

void setup()
{
    Serial.begin(9600);
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
}
 
void loop()
{
  value = analogRead(A0);

  if (contl == 0)
  {
    limit = value + 50; 
    contl++;
  }
  
  timee = millis();
  
  if(state == 0)
  {
    average = 0; 
    cont = 0; 
    contt = 0;
    tval = 0;
    state++;
  }
  
  if(state == 1)
  {
    Serial.println(value);
    Serial.println(limit);
    Serial.println(" ");
        
    if (value >= limit)
    {
      if(contt == 0)
      {
        timeinit = timee;
        contt++; 
      }
      tval = tval + value;
      cont++;
    }

    if(contt != 0)
    { 
      timend = timee;
      ttotal = timend - timeinit;

      if(ttotal >= 500)
      {
        state++;
      }
     }
  }
    if(contt == 2)
    {
      average = tval/cont;
  
      if(average > 690)
      {
        Serial.println("Semente de arroz vermelho");
        Serial.println((String)"average: "+average);
        
        state = 0;
      }
      else
      {
        Serial.println("Semente de arroz branco");
        Serial.println((String)"average: "+average);

        state = 0;
      }
  }
}
