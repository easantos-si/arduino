String teclaPressionada(boolean esperar)
{
  String retorno = "";
  boolean continuar = esperar;
  boolean precionamentoDetectado = false;
  _teclaPressionada = "";

  do {

    precionamentoDetectado = false;

    if (_controle.decode(&_results))
    {
      _controleInterrupcaoAnterior = millis();
      _controle.resume();
      retorno = String(_results.value, HEX);
      retorno.toUpperCase();

      precionamentoDetectado = true;
    }
    else if (_teclaPressionada.length() > 0)
    {
      precionamentoDetectado = true;
      
      retorno = _teclaPressionada;
      
      _teclaPressionada = "";
    }

    if (precionamentoDetectado)
    {
      if (esperar)
      {
        continuar = !validarTecla(&retorno);
      }
      else
      {
        continuar = false;
        if (!validarTecla(&retorno))
        {
          retorno = "";
        }
      }
    }
  }
  while (continuar);
  if (retorno.length() > 0)
  {
    som2();
  }
  return retorno;
}
boolean validarTecla(String* tecla)
{
  boolean retorno = false;
  if ((*tecla == "511DBB") || (*tecla == "A3C8EDDB") || (*tecla == "52A3D41F") || (*tecla == "20FE4DBB") || (*tecla == "D7E84B1B")
      || (*tecla == "C101E57B") || (*tecla == "97483BFB") || (*tecla == "F0C41643") || (*tecla == "9716BE3F") || (*tecla == "3D9AE3F7")
      || (*tecla == "6182021B") || (*tecla == "8C22657B") || (*tecla == "488F3CBB") || (*tecla == "449E79F") || (*tecla == "1BC0157B")
      || (*tecla == "32C6FDF7") || (*tecla == "3EC3FC1B"))
  {
    retorno = true;
  }

  return retorno;
}
