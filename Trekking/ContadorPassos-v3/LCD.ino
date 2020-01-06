void escreverLCD(String valor)
{
  //_lcd.setCursor(0, 0);
  //  _lcd.print(tamanho);
  //  delay(1000);
  int tamanho = valor.length();

  if (tamanho > 0)
  {
    int col = 0;
    for (int marcador = 0; marcador < 16; marcador++)
    {
      if (marcador < tamanho && _telaLCD[0][col] != valor[marcador])
      {
        _telaLCD[0][col] = valor[marcador];
        _telaMapaTL++;
        _telaMapa[_telaMapaTL - 1] = col;
        _lcd.setCursor(0, 0);
      }
      col++;
    }

    col = 0;
    for (int marcador = 16; marcador < 32; marcador++)
    {
      if (marcador < tamanho && _telaLCD[1][col] != valor[marcador])
      {
        _telaLCD[1][col] = valor[marcador];
        _telaMapaTL++;
        _telaMapa[_telaMapaTL - 1] = col + 16;
      }
      col++;
    }
    atualizarLCD();
  }
}
void atualizarLCD()
{
  if (_telaMapaTL > 0)
  {
    for (int marcador = 0; marcador < _telaMapaTL; marcador++)
    {
      if (_telaMapa[marcador] < 16)
      {
        _lcd.setCursor(_telaMapa[marcador], 0);
        _lcd.print(_telaLCD[0][_telaMapa[marcador]]);
      }
      else
      {
        _lcd.setCursor(_telaMapa[marcador] - 16, 1);
        _lcd.print(_telaLCD[1][_telaMapa[marcador] - 16]);
      }
    }
    _telaMapaTL = 0;
  }
}
void escreverLCD(int posicao, int caracter)
{
  if (posicao < 16)
  {
    _lcd.setCursor(posicao, 0);
  }
  else
  {
    _lcd.setCursor(posicao - 16, 1);
  }
  _lcd.write(caracter);
}
void limparLCD()
{
  _telaMapaTL = 0;
  for (int m = 0; m < 32; m++)
  {
    if (m < 16)
    {
      _telaLCD[0][m] = ' ';
    }
    else
    {
      _telaLCD[1][m - 16] = ' ';
    }
  }
  _lcd.clear();
}
