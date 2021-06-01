int average = 0, cont = 0, state = 0, value, limit, contt = 0;
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
    pinMode(7, HIGH);
}
 
void loop()
{
  value = analogRead(A0);
  timee = millis();
  
  switch(state)
  {
    case 0:
      digitalWrite(7, HIGH);
      
      limit = analogRead(A0) + 50;
      average = 0; 
      cont = 0; 
      contt = 0;
      tval = 0;
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
          tval = tval + value;
          cont++;
        }
  
        if(contt != 0)
        { 
          timend = timee;
          ttotal = timend - timeinit;
  
          if(ttotal >= 200)
          {
            state++;
            break;
          }
        }
        break;
    case 2:
      average = tval/cont;
  
      /*if (value < limit)
      {*/
        if(average > 690)
        {
          Serial.println("Semente de arroz vermelho");
          Serial.println((String)"average: "+average);
          
          state = 0;
          break;
        }
        else
        {
          Serial.println("Semente de arroz branco");
          Serial.println((String)"average: "+average);

          state = 0;
          break;
        }
      //}
      break;
  }
}
