int average = 0, cont = 0, state = 0, value, limit, contt = 0, contl = 0, i = 0;
unsigned long tval = 0;

unsigned long timee;
unsigned long timeinit;
unsigned long timend;
unsigned long ttotal;

int vec[600];

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
  timee = millis();
  
  if (contl == 0)
  {
    limit = value + 50; 
    contl++;
  }
  
  switch(state)
  {
    case 0:
      average = 0; 
      cont = 0; 
      contt = 0;
      tval = 0;
      i = 0;
      state++;
      
      break; 
    case 1:
        if (value >= limit)
        {
          if(contt == 0)
          {
            timeinit = timee;
            contt++; 
          }
          if (cont % 3 == 0)
          {
            tval = tval + value;
            vec[i] = value;
            i++;
          }
          cont++;
        }
  
        if(contt != 0)
        { 
          timend = timee;
          ttotal = timend - timeinit;
  
          if(ttotal >= 300)
          {
            state++;
            break;
          }
        }
        break;
    case 2:
      average = tval/cont;
  
      if(cont > 315 && average > 690)
      {
        Serial.println("Semente de arroz vermelho");
        Serial.println((String)"average: "+average);
        
        Serial.println((String)"cont: "+cont);

        for (int i = 0; i < 599; i++)
        {
          Serial.println(vec[i]);
        }
        
        state = 0;
        break;
      }
      
      if(cont > 150 && average < 690)
      {
        Serial.println("Semente de arroz branco");
        Serial.println((String)"average: "+average);
        Serial.println((String)"cont: "+cont);

        for (int i = 0; i < 599; i++)
        {
          Serial.println(vec[i]);
        }

        state = 0;
        break;
      }
    break;
  }
}
