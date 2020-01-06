unsigned long TempoConverter(int  horas,  int  minutos,  int  segundos)
{
  /*
    unsigned long millessegundos = 0;

    millessegundos += horas * Tempo_h;
    millessegundos += minutos * Tempo_m;
    millessegundos += segundos * Tempo_s;

    return millessegundos;*/
  return ((long)horas * (long)Tempo_h) + ((long)minutos * (long)Tempo_m) + ((long)segundos * (long)Tempo_s);
}
String TempoConverter(unsigned long milessegundos)
{
  /*
    int segundos = 0;
    int minutos = 0;
    int horas = 0;

    horas = (milessegundos % Tempo_d) / Tempo_h;
    minutos = ((milessegundos % Tempo_d) % Tempo_h) / Tempo_m;
    segundos = (((milessegundos % Tempo_d) % Tempo_h) % Tempo_m) / Tempo_s;
  */
  int  horas = TempoHoras(milessegundos);
  int  minutos = TempoMinutos(milessegundos);
  int  segundos = TempoSegundos(milessegundos);

  String tempo = "";

  if (horas < 10)
  {
    tempo += "0";
  }
  tempo += String(horas, DEC);
  tempo += ":";

  if (minutos < 10)
  {
    tempo += "0";
  }
  tempo += String(minutos, DEC);
  tempo += ':';

  if (segundos < 10)
  {
    tempo += "0";
  }
  tempo += String(segundos, DEC);

  return tempo;
}
int TempoHoras(unsigned long milessegundos)
{
  // return (milessegundos % Tempo_d) / Tempo_h;
  return milessegundos / Tempo_h;
}
int TempoMinutos(unsigned long milessegundos)
{
  // return ((milessegundos % Tempo_d) % Tempo_h) / Tempo_m;
  return (milessegundos % Tempo_h) / Tempo_m;
}
int TempoSegundos(unsigned long milessegundos)
{
  //return (((milessegundos % Tempo_d) % Tempo_h) % Tempo_m) / Tempo_s;
  return ((milessegundos % Tempo_h) % Tempo_m) / Tempo_s;
}
void Alertas(unsigned long milessegundos)
{
  if (milessegundos > 930 && milessegundos <= 1000)
  {
    for (int contador = 0; contador < 3; contador++)
    {
      som4();
      delay(33);
    }
  }
  else if (milessegundos == 2000 || milessegundos == 3000 || milessegundos == 4000 || milessegundos == 5000 || milessegundos == 6000 || milessegundos == 7000 || milessegundos == 8000 || milessegundos == 9000 || milessegundos == 10000)
  {
    som4();
    delay(1000);
  }
  else if (milessegundos == 60000)
  {
    som4();
    delay(2000);
  }
  else if (milessegundos == 120000)
  {
    som4();
    delay(2000);
    som4();
    delay(2000);
  }
  else if (milessegundos == 180000)
  {
    som4();
    delay(2000);
    som4();
    delay(2000);
    som4();
    delay(2000);
  }
  else if (milessegundos == 240000)
  {
    som4();
    delay(2000);
    som4();
    delay(2000);
    som4();
    delay(2000);
    som4();
    delay(2000);
  }
  else if (milessegundos == 300000)
  {
    som4();
    delay(2000);
    som4();
    delay(2000);
    som4();
    delay(2000);
    som4();
    delay(2000);
    som4();
    delay(2000);
  }
}

