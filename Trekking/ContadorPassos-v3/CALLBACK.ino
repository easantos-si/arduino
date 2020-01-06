void passos_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    if (_memoria.ModoSistema == modoSistemaProva)
    {
      _memoria.Metros += _memoria.TamanhoPasso;
      if (_memoria.AlertaMetragem)
      {
        if (_memoria.Metros >= _memoria.AlertaMetragemMetros)
        {
          som3();
          _memoria.AlertaMetragemMetros = 0;
          _memoria.AlertaMetragem = false;
          _memoria.AlertaMetragemNivelProximidade = 0;
          escreverLCD(formatarDireita("Alerta", 16, ' ') + formatarDireita("Metragem:" + FloatToString(_memoria.AlertaMetragemMetros, 0), 16, ' '));
          delay(2000);
        }
        else if (_memoria.AlertaMetragemNivelProximidade > 0 && _memoria.Metros >= (_memoria.AlertaMetragemMetros - _memoria.AlertaMetragemNivelProximidade))
        {
          _memoria.AlertaMetragemNivelProximidade--;
          som4();
        }
      }
      else
      {
        som1();
      }
    }
    else if (_memoria.ModoSistema == modoSistemaCalibragem)
    {
      _quantidadePassos++;
      som1();
    }
  }
}
void teclaCima_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaCima;
  }
}
void teclaBaixo_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaBaixo;
  }
}
void teclaEsquerda_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaEsquerda;
  }
}
void teclaDireita_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaDireita;
  }
}
void teclaOK_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaOK;
  }
}
void teclaNumero1_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero1;
  }
}
void teclaNumero2_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero2;
  }
}
void teclaNumero3_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero3;
  }
}
void teclaNumero4_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero4;
  }
}
void teclaNumero5_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero5;
  }
}
void teclaNumero6_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero6;
  }
}
void teclaNumero7_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero7;
  }
}
void teclaNumero8_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero8;
  }
}
void teclaNumero9_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero9;
  }
}
void teclaNumero0_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaNumero0;
  }
}
void teclaAsterisco_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaAsterisco;
  }
}
void teclaCharp_callback()
{
  _interrupcao = millis();
  if (_interrupcao - _interrupcaoAnterior > 250)
  {
    _interrupcaoAnterior = millis();
    _teclaPressionada = teclaCharp;
  }
}
