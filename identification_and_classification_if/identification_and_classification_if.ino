int tval = 0, average = 0, cont = 0, state = 0, value, limit;

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
    digitalWrite(7, HIGH);
    value = analogRead(A0);

    if (state == 0)
    {
      limit = analogRead(A0) + 20;
      state++;
    }
    
    if (value >= limit)
    {
      tval = tval + value;
      cont++;
    }

    average = tval/cont;

    if (state == 2 && value < limit)
    {
      state = 3;

      if(average > 300)
      {
        Serial.println("Semente de arroz vermelho");
        Serial.print("average: ");
        Serial.println(average);
      }
      else
      {
        Serial.print("Semente de arroz branco");
        Serial.print("average: ");
        Serial.println(average);
      }
    }
}
