void som1()
{
  for (int contador = 700; contador < 1000; contador += 50) //x 6
  {
    tone(buzzerPin, contador, 50);
  }
  /*
    tone(buzzerPin, 700, 50);
    tone(buzzerPin, 750, 50);
    tone(buzzerPin, 800, 50);
    tone(buzzerPin, 850, 50);
    tone(buzzerPin, 1000, 50);
    tone(buzzerPin, 1050, 50);
  */
}
void som2()
{
  for (int contador = 400; contador < 700; contador += 50) //x 6
  {
    tone(buzzerPin, contador, 25);
  }
  /*
    tone(buzzerPin, 400, 25);
    tone(buzzerPin, 450, 25);
    tone(buzzerPin, 500, 25);
    tone(buzzerPin, 550, 25);
    tone(buzzerPin, 700, 25);
    tone(buzzerPin, 750, 25);
  */
}
void som3()
{
  for (int contador = 400; contador < 1400; contador += 50) //x 20
  {
    tone(buzzerPin, contador, 50);
  }
}
void som4()
{
  for (int contador = 1500; contador < 1800; contador += 50) //x 6
  {
    tone(buzzerPin, contador, 25);
  }
}
