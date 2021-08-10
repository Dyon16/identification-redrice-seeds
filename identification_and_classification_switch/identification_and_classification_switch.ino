lar int average = 0, cont = 0, state = 0, value, limit, contt = 0, contl = 0, i = 0, liberou = 0;
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
  while(timee == millis()); // barreira de tempo: espera até timee ser diferente do valor lido por millis(). Na pratica, aguarda até que se inicie o proximo milissegundo, se ainda não estiever ocorrido.
  timee = millis(); //atualiza o valor de timee para o milissegundo atual.
  value = analogRead(A0); // le a analógica (1000amostras/s) com a barreira acima
  
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
          liberou++;
          if(contt == 0)
          {
            timeinit = timee;
            contt++; 
          }
        }

        cont++;

        if (liberou > 0)
        {
          if (cont % 1 == 0)
            {
              tval = tval + value;
              vec[i] = value;
              
              if(i < 599)
              {
                i++; // ultimo indice possível, não incrementa mais para não sobrescrever fora da área do array
              }
            }
        }
  
        if(contt != 0)
        { 
          timend = timee;
          ttotal = timend - timeinit;
  
          if(ttotal >= 600)
          {
            state++;
            break;
          }
        }
        break;
    case 2:
      average = tval/cont;
  
      if(average > 690)
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
      
      if(average < 690)
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
