String formatarEsquerda(int valor, int tamanho, char caracter)
{
  String tmp = String(valor, DEC);

  return formatarEsquerda(tmp, tamanho, caracter);
}
String formatarDireita(int valor, int tamanho, char caracter)
{
  String tmp = String(valor, DEC);

  return formatarDireita(tmp, tamanho, caracter);
}
String formatarEsquerda(String valor, int tamanho, char caracter)
{
  String retorno = "";
  if (valor.length() / sizeof(String) < tamanho)
  {
    for (int contador = 0; contador < tamanho - valor.length(); contador++)
    {
      retorno += caracter;
    }
  }
  else if (valor.length() / sizeof(String) > tamanho)
  {
    retorno = valor.substring(0, tamanho);
  }
  return retorno += valor;
}
String formatarDireita(String valor, int tamanho, char caracter)
{
  String retorno = valor;
  if (valor.length() / sizeof(String) < tamanho)
  {
    for (int contador = 0; contador < tamanho - valor.length(); contador++)
    {
      retorno += caracter;
    }
  }
  else if (valor.length() / sizeof(String) > tamanho)
  {
    retorno = valor.substring(valor.length() - tamanho, tamanho);
  }
  return retorno;
}
void criarPergunta(String mensagem, String opcao1, String opcao2)
{
  escreverLCD(formatarDireita(mensagem, 16, ' ') + formatarDireita("   " + formatarDireita(opcao1, 3, ' ') + "   " + formatarDireita(opcao2, 3, ' '), 16, ' '));
}
boolean esperarRespostaPergunta(int *opcao)
{
  boolean retorno = false;
  moverCursorOpcao(opcao);
  boolean aguardandoResposta = true;
  String tecla = "";

  boolean som = true;
  while (aguardandoResposta)
  {
    tecla = teclaPressionada(true);

    if (tecla == teclaEsquerda)
    {
      *opcao = 1;
    }
    else if (tecla == teclaDireita)
    {
      *opcao = 2;
    }
    else if (tecla == teclaOK)
    {
      aguardandoResposta = false;
    }
    moverCursorOpcao(opcao);
  }
  if (*opcao == 1)
  {
    retorno = true;//(opcao == 1);
  }

  delay(300);

  return retorno;
}
void moverCursorOpcao(int *opcao)
{
  if (*opcao == 1)
  {
    escreverLCD(17, 2);
    escreverLCD(23, 0);
  }
  else if (*opcao == 2)
  {
    escreverLCD(17, 0);
    escreverLCD(23, 2);
  }
  else
  {
    escreverLCD(17, 0);
    escreverLCD(23, 0);
  }
}
void processar(String* teclsPressionada)
{
  if (*teclsPressionada == teclaAsterisco)
  {
    menuAcoes();
  }
  else if (*teclsPressionada == teclaOK)
  {
    ajustarMetros(false);
  }
  else
  {
    ajustarMetros(true);
  }
}
void ajustarMetros(boolean metragemAlerta)
{
  char valor[] = "_000";

  String tecla;

  int posicao = 0;

  char caracterAtual = '0';

  boolean continuar = true;
  boolean numeroPressionado = false;

  if (metragemAlerta)
  {
    escreverLCD(formatarDireita("Ajuste alerta M:", 16, ' ') + formatarDireita(CharsToString(valor), 16, ' '));
  }
  else if (_memoria.ModoSistema == modoSistemaCalibragem)
  {
    escreverLCD(formatarDireita("Ajuste metragem:", 16, ' ') + formatarDireita(CharsToString(valor), 16, ' '));
  }
  else if (_memoria.ModoSistema == modoSistemaProva)
  {
    escreverLCD(formatarDireita("Ajuste metros:", 16, ' ') + formatarDireita(CharsToString(valor), 16, ' '));
  }

  while (continuar)
  {
    tecla = teclaPressionada(true);

    numeroPressionado = false;

    if (setarValor(&tecla, valor, &posicao))
    {
      numeroPressionado = true;
    }
    else if (tecla == teclaEsquerda)
    {
      if (posicao > 0)
      {
        if (valor[posicao] == '_')
        {
          valor[posicao] = caracterAtual;
        }
        posicao--;
      }
    }
    else if (tecla == teclaDireita)
    {
      if (posicao < 3)
      {
        if (valor[posicao] == '_')
        {
          valor[posicao] = caracterAtual;
        }
        posicao++;
      }
    }
    else if ((tecla == teclaCharp) || (tecla == teclaOK))
    {
      continuar = false;
    }

    if (numeroPressionado && posicao < 3)
    {
      posicao++;
    }

    if (valor[posicao] != '_')
    {
      caracterAtual = valor[posicao];
      valor[posicao] = '_';
      if (posicao == 3 && numeroPressionado)
      {
        valor[posicao] = caracterAtual;
      }
    }

    if (metragemAlerta)
    {
      escreverLCD(formatarDireita("Ajuste alerta M:", 16, ' ') + formatarDireita(CharsToString(valor), 16, ' '));
    }
    else if (_memoria.ModoSistema == modoSistemaCalibragem)
    {
      escreverLCD(formatarDireita("Ajuste metragem:", 16, ' ') + formatarDireita(CharsToString(valor), 16, ' '));
    }
    else if (_memoria.ModoSistema == modoSistemaProva)
    {
      escreverLCD(formatarDireita("Ajuste metros:", 16, ' ') + formatarDireita(CharsToString(valor), 16, ' '));
    }
  }

  if (valor[posicao] == '_')
  {
    valor[posicao] = caracterAtual;
  }
  if (tecla == teclaOK)
  {
    if (metragemAlerta)
    {
      _memoria.AlertaMetragemMetros = 0;
      _memoria.AlertaMetragem = false;
      _memoria.AlertaMetragemNivelProximidade = 10;
      _memoria.AlertaMetragemMetros = CharsToString(valor).toFloat();

      if (_memoria.AlertaMetragemMetros > 0)
      {
        _memoria.AlertaMetragem = true;
      }
    }
    else
    {
      if (_memoria.ModoSistema == modoSistemaCalibragem)
      {
        _memoria.MetragemBase = CharsToString(valor).toFloat();
      }
      else if (_memoria.ModoSistema == modoSistemaProva)
      {
        _memoria.Metros = CharsToString(valor).toFloat();
      }
    }
  }
}
void ajustarRelogio()
{
  char dia[] = "00";
  char mes[] = "00";
  char ano[] = "0000";

  char horas[] = "00";
  char minutos[] = "00";
  char segundos[] = "00";
  _tempo = _relogio.getTime();
  StringToChars(formatarEsquerda(_tempo.date, 2, '0'), dia);
  StringToChars(formatarEsquerda(_tempo.mon, 2, '0'), mes);
  StringToChars(formatarEsquerda(_tempo.year, 4, '0'), ano);

  _tempo = _relogio.getTime();
  StringToChars(formatarEsquerda(_tempo.hour, 2, '0'), horas);
  StringToChars(formatarEsquerda(_tempo.min, 2, '0'), minutos);
  StringToChars(formatarEsquerda(_tempo.sec, 2, '0'), segundos);

  boolean continuar = true;
  boolean numeroPressionado = false;

  String tecla;

  int posicao = 0;
  int posicaoReal = 0;

  char* valor = dia;
  char caracterAtual = '0';

  caracterAtual = valor[posicaoReal];
  valor[posicaoReal] = '_';

  escreverLCD(formatarDireita("Data:" + CharsToString(dia) + "/" + CharsToString(mes) + "/" + CharsToString(ano), 16, ' ') + formatarDireita("Hora:" + CharsToString(horas) + ":" + CharsToString(minutos) + ":" + CharsToString(segundos), 16, ' '));

  while (continuar)
  {
    numeroPressionado = false;
    tecla = teclaPressionada(true);

    if (setarValor(&tecla, valor, &posicaoReal))
    {
      numeroPressionado = true;
    }
    else if ((tecla == teclaCharp) || (tecla == teclaOK))
    {
      continuar = false;
    }
    else if (tecla == teclaEsquerda)
    {
      if (posicao > 0)
      {
        if (valor[posicaoReal] == '_')
        {
          valor[posicaoReal] = caracterAtual;
        }
        posicao--;
      }
    }
    else if (tecla == teclaDireita)
    {
      if (posicao < 13)
      {
        if (valor[posicaoReal] == '_')
        {
          valor[posicaoReal] = caracterAtual;
        }
        posicao++;
      }
    }
    else if (tecla == teclaCima)
    {
      if (posicao > 7)
      {
        posicao = 0;
        valor[posicaoReal] = caracterAtual;
      }
    }
    else if (tecla == teclaBaixo)
    {
      if (posicao < 8)
      {
        posicao = 8;
        valor[posicaoReal] = caracterAtual;
      }
    }

    if (numeroPressionado && posicao < 13)
    {
      posicao++;
    }


    if (posicao >= 0 && posicao <= 1)
    {
      if (posicao == 0)
      {
        posicaoReal = 0;
      }
      else
      {
        posicaoReal = 1;
      }
      valor = dia;
    }
    else  if (posicao >= 2 && posicao <= 3)
    {
      if (posicao == 2)
      {
        posicaoReal = 0;
      }
      else
      {
        posicaoReal = 1;
      }

      valor = mes;
    }
    else  if (posicao >= 4 && posicao <= 7)
    {
      if (posicao == 4)
      {
        posicaoReal = 0;
      }
      else if (posicao == 5)
      {
        posicaoReal = 1;
      }
      else if (posicao == 6)
      {
        posicaoReal = 2;
      }
      else if (posicao == 7)
      {
        posicaoReal = 3;
      }
      valor = ano;
    }
    else  if (posicao >= 8 && posicao <= 9)
    {
      if (posicao == 8)
      {
        posicaoReal = 0;
      }
      else
      {
        posicaoReal = 1;
      }
      valor = horas;
    }
    else  if (posicao >= 10 && posicao <= 11)
    {
      if (posicao == 10)
      {
        posicaoReal = 0;
      }
      else
      {
        posicaoReal = 1;
      }
      valor = minutos;
    }
    else  if (posicao >= 12 && posicao <= 13)
    {
      if (posicao == 12)
      {
        posicaoReal = 0;
      }
      else
      {
        posicaoReal = 1;
      }
      valor = segundos;
    }

    if (valor[posicaoReal] != '_')
    {
      caracterAtual = valor[posicaoReal];
      valor[posicaoReal] = '_';

      if (posicao == 13 && numeroPressionado)
      {
        valor[posicaoReal] = caracterAtual;
      }
    }

    escreverLCD(formatarDireita("Data:" + CharsToString(dia) + "/" + CharsToString(mes) + "/" + CharsToString(ano), 16, ' ') + formatarDireita("Hora:" + CharsToString(horas) + ":" + CharsToString(minutos) + ":" + CharsToString(segundos), 16, ' '));
  }

  if (valor[posicaoReal] == '_')
  {
    valor[posicaoReal] = caracterAtual;
  }
  if (tecla == teclaOK)
  {
    _relogio.setDate(CharsToString(dia).toInt(), CharsToString(mes).toInt(), CharsToString(ano).toInt());
    _relogio.setTime(CharsToString(horas).toInt(), CharsToString(minutos).toInt(), CharsToString(segundos).toInt());
  }
}
boolean setarValor(String* teclaPressionada, char valor[], int *posicao)
{
  boolean retorno = false;

  if (*teclaPressionada == teclaNumero1)
  {
    valor[*posicao] = '1';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero2)
  {
    valor[*posicao] = '2';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero3)
  {
    valor[*posicao] = '3';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero4)
  {
    valor[*posicao] = '4';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero5)
  {
    valor[*posicao] = '5';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero6)
  {
    valor[*posicao] = '6';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero7)
  {
    valor[*posicao] = '7';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero8)
  {
    valor[*posicao] = '8';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero9)
  {
    valor[*posicao] = '9';
    retorno = true;
  }
  else if (*teclaPressionada == teclaNumero0)
  {
    valor[*posicao] = '0';
    retorno = true;
  }

  return retorno;
}
long ajustarValoresDataHora(String legenda, long milessegundos)
{
  char horas[] = "00";
  char minutos[] = "00";
  char segundos[] = "00";

  StringToChars(formatarEsquerda(IntToString(TempoHoras(milessegundos)), 2, '0'), horas);
  StringToChars(formatarEsquerda(IntToString(TempoMinutos(milessegundos)), 2, '0'), minutos);
  StringToChars(formatarEsquerda(IntToString(TempoSegundos(milessegundos)), 2, '0'), segundos);

  boolean continuar = true;
  boolean numeroPressionado = false;

  String tecla;

  int posicao = 0;
  int posicaoReal = 0;

  char* valor = horas;
  char caracterAtual = '0';

  caracterAtual = valor[posicaoReal];
  valor[posicaoReal] = '_';

  escreverLCD(formatarDireita(legenda, 16, ' ') + formatarDireita("Hora:" + CharsToString(horas) + ":" + CharsToString(minutos) + ":" + CharsToString(segundos), 16, ' '));

  while (continuar)
  {
    numeroPressionado = false;
    tecla = teclaPressionada(true);

    if (setarValor(&tecla, valor, &posicaoReal))
    {
      numeroPressionado = true;
    }
    else if ((tecla == teclaCharp) || (tecla == teclaOK))
    {
      continuar = false;
    }
    else if (tecla == teclaEsquerda)
    {
      if (posicao > 0)
      {
        if (valor[posicaoReal] == '_')
        {
          valor[posicaoReal] = caracterAtual;
        }
        posicao--;
      }
    }
    else if (tecla == teclaDireita)
    {
      if (posicao < 5)
      {
        if (valor[posicaoReal] == '_')
        {
          valor[posicaoReal] = caracterAtual;
        }
        posicao++;
      }
    }

    if (numeroPressionado && posicao < 5)
    {
      posicao++;
    }

    if (posicao >= 0 && posicao <= 1)
    {
      if (posicao == 0)
      {
        posicaoReal = 0;
      }
      else
      {
        posicaoReal = 1;
      }
      valor = horas;
    }
    else  if (posicao >= 2 && posicao <= 3)
    {
      if (posicao == 2)
      {
        posicaoReal = 0;
      }
      else
      {
        posicaoReal = 1;
      }
      valor = minutos;
    }
    else  if (posicao >= 4 && posicao <= 5)
    {
      if (posicao == 4)
      {
        posicaoReal = 0;
      }
      else
      {
        posicaoReal = 1;
      }
      valor = segundos;
    }

    if (valor[posicaoReal] != '_')
    {
      caracterAtual = valor[posicaoReal];
      valor[posicaoReal] = '_';

      if (posicao == 5 && numeroPressionado)
      {
        valor[posicaoReal] = caracterAtual;
      }
    }

    escreverLCD(formatarDireita(legenda, 16, ' ') + formatarDireita("Hora:" + CharsToString(horas) + ":" + CharsToString(minutos) + ":" + CharsToString(segundos), 16, ' '));
  }

  if (valor[posicaoReal] == '_')
  {
    valor[posicaoReal] = caracterAtual;
  }

  return TempoConverter(CharsToString(horas).toInt(), CharsToString(minutos).toInt(), CharsToString(segundos).toInt());
}
void ajustarLargadaProva()
{
  _memoria.LargadaProva = ajustarValoresDataHora("Largada prova:", _memoria.LargadaProva);
}
void ajustarLargadaNeutro()
{
  if (_memoria.LargadaNeutro > 0)
    _memoria.LargadaNeutro = _memoria.LargadaProva + ajustarValoresDataHora("Largada neutro:", (_memoria.LargadaNeutro - _memoria.LargadaProva));
  else
    _memoria.LargadaNeutro = _memoria.LargadaProva + ajustarValoresDataHora("Largada neutro:", _memoria.LargadaNeutro);
}
String CharsToString(char valores[])
{
  return String(valores);
}
String FloatToString(float valor, int casasDecimais)
{
  String retorno = String(valor, casasDecimais);
  retorno.trim();
  return retorno;
}
String IntToString(int valor)
{
  return String(valor, DEC);
}
void StringToChars(String valor, char valores[])
{
  valor.toCharArray(valores, sizeof(valor));
}
