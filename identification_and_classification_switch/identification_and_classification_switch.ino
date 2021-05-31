int tval = 0, average = 0, cont = 0, state = 0, value, limit, contt = 0, i = 0;

unsigned long timee;
unsigned long timeinit;
unsigned long timend;
unsigned long ttotal;

int vec[500];

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
      state++;
      break; 
    case 1:
      while(state == 1)
      {
        value = analogRead(A0);
        timee = millis();

        //Serial.println(value);
        
        if (value >= limit)
        {
          //Serial.println("Open limit if");
          
          if(contt == 0)
          {
            timeinit = timee;
            tval = 0;
            contt++; 
          }

          vec[i] = value;

          tval = tval + value;
          cont++;
          i++;
          
          /*Serial.print("Tval: ");
          Serial.println(tval);*/
        }
  
        if(contt != 0)
        { 
          timend = timee;
          ttotal = timend - timeinit;

          /*Serial.print("Inicial time: ");
          Serial.println(timeinit);

          Serial.print("Final time: ");
          Serial.println(timend);

          Serial.print("Ttotal: ");
          Serial.println(ttotal);

          Serial.print("ttaol: ");
          Serial.println(ttotal);*/
  
          if(ttotal >= 200)
          {
            state++;
            break;
          }
        }
      }
    case 2:
      average = tval/cont;

      /*Serial.print("State: ");
      Serial.println(state);*/
  
      if (state == 2 && value < limit)
      {
        if(average > 300)
        {
          Serial.println("Semente de arroz vermelho");
          Serial.print("average: ");
          Serial.println(average);

          Serial.print("Tval: ");
          Serial.println(tval);

          Serial.print("Inicial time: ");
          Serial.println(timeinit);

          Serial.print("Final time: ");
          Serial.println(timend);

          Serial.print("Ttotal: ");
          Serial.println(ttotal);

          Serial.print("cont: ");
          Serial.println(cont);

          for (int i = 0; i < cont; i++)
          {
            Serial.print(vec[i]);
            Serial.print(" "); 
          }
          
          break;
        }
        else
        {
          Serial.println("Semente de arroz branco");
          Serial.print("average: ");
          Serial.println(average);

          Serial.print("Tval: ");
          Serial.println(tval);

          Serial.print("Inicial time: ");
          Serial.println(timeinit);

          Serial.print("Final time: ");
          Serial.println(timend);

          Serial.print("Ttotal: ");
          Serial.println(ttotal);

          Serial.print("cont: ");
          Serial.println(cont);

          for (int i = 0; i < cont; i++)
          {
            Serial.print(vec[i]);
            Serial.print(" "); 
          }
          
          break;
        }
      }
  }
}
