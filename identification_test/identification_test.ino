int value, average, cont = 0;
unsigned long tval = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(7, HIGH);
}

void loop() 
{
  digitalWrite(7, HIGH);

  value = analogRead(A0); 
  
  Serial.println(value);
}
