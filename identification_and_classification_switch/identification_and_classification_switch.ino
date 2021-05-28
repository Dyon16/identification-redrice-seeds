int tval = 0, average = 0, cont = 0, state = 0, value, limit, contt = 0;

unsigned long time;
unsigned long timeinit;
unsigned long timend;

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
  time = millis();
  
  switch(state)
  {
    case 0:
      limit = analogRead(A0) + 20;
      state++;
      break; 
    case 1:
      if (value >= limit)
      {
        if(contt == 0)
        {
          timeinit = millis();
          contt++; 
        }
        tval = tval + value;
        cont++;
      }

      timend = millis();
      time = timend - timeinit;

      if(time >= 1000)
      {
        state++;
        break;
      }
    case 2:
      average = tval/cont;
  
      if (state == 2 && value < limit)
      {
        if(average > 300)
        {
          Serial.println("Semente de arroz vermelho");
          Serial.print("average: ");
          Serial.println(average);
          break;
        }
        else
        {
          Serial.print("Semente de arroz branco");
          Serial.print("average: ");
          Serial.println(average);
          break;
        }
      }
  }
}
