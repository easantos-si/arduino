void calibarTamanhoPasso()
{

  _quantidadePassos = 0;
  float tamanhoPassoGeral = 0;
  String tecla;
  int _modoSistemaAux = _memoria.ModoSistema;
  _memoria.ModoSistema = modoSistemaCalibragem;

  criarPergunta("Conf. metragem?", "Sim", "Nao");
  int opcao = 2;
  if (esperarRespostaPergunta(&opcao))
  {
    ajustarMetros(false);
  }
  boolean continuar = true;
  int contador = 1;

  _memoria.ModoSistema = modoSistemaCalibragem;
  while (continuar)
  {
    escreverLCD(formatarDireita("Calibragem:" + IntToString(contador) + "/6", 16, ' ') + formatarDireita("Passos:" + IntToString(_quantidadePassos), 16, ' '));
    tecla = teclaPressionada(false);
    if (_quantidadePassos > 0)
    {
      if (tecla == teclaOK)
      {
        tamanhoPassoGeral += _memoria.MetragemBase / _quantidadePassos;
        _quantidadePassos = 0;
        contador++;

        if (contador > 6)
        {
          _memoria.TamanhoPasso = tamanhoPassoGeral / 6;
          continuar = false;
        }
      }
      else if (tecla == teclaCharp)
      {
        _quantidadePassos = 0;
      }
    }
    else if (tecla == teclaCharp)
    {
      continuar = false;
    }
  }
  _memoria.ModoSistema = _modoSistemaAux;

}
