void menuAcoes()
{
  String tecla = "";
  int idMenuAcoes = 1;

  int _modoSistemaAux = _memoria.ModoSistema;

  _memoria.ModoSistema = modoSistemaFuncoes;
  boolean continuar = true;
  while (continuar)
  {
    int quantidadeMenu = 15;
    switch (idMenuAcoes)
    {
      case 1: {
          escreverLCD(formatarDireita("Calibar tamanho do passo", 32, ' '));
          break;
        }
      case 2: {
          escreverLCD(formatarDireita("Modo largada", 32, ' '));
          break;
        }
      case 3: {
          escreverLCD(formatarDireita("Modo neutro", 32, ' '));
          break;
        }
      case 4: {
          escreverLCD(formatarDireita("Modo prova", 32, ' '));
          break;
        }
      case 5: {
          escreverLCD(formatarDireita("Configuracoes", 32, ' '));
          break;
        }
      case 6: {
          if (_memoria.TempoModoRelogio)
            escreverLCD(formatarDireita("Tempo cronometro", 32, ' '));
          else
            escreverLCD(formatarDireita("Tempo relogio", 32, ' '));

          break;
        }
      case 7: {
          escreverLCD(formatarDireita("Gravar", 32, ' '));
          break;
        }
      case 8: {
          escreverLCD(formatarDireita("Restaurar", 32, ' '));
          break;
        }
      case 9: {
          escreverLCD(formatarDireita("Ver metragem    base", 32, ' '));
          break;
        }
      case 10: {
          escreverLCD(formatarDireita("Ver tamanho do  passo", 32, ' '));
          break;
        }
      case 11: {
          escreverLCD(formatarDireita("Ver horario lar. prova", 32, ' '));
          break;
        }
      case 12: {
          escreverLCD(formatarDireita("Ver horario lar. neutro", 32, ' '));
          break;
        }
      case 13: {
          escreverLCD(formatarDireita("Ver contador de gravacoes", 32, ' '));
          break;
        }
      case 14: {
          escreverLCD(formatarDireita("Desligar", 32, ' '));
          break;
        }
      case 15: {
          escreverLCD(formatarDireita("Redefinir", 32, ' '));
          break;
        }
    }

    tecla = teclaPressionada(true);

    if (tecla == teclaCima)
    {
      if (idMenuAcoes > 1)
      {
        idMenuAcoes--;
      }
    }
    else if (tecla == teclaBaixo)
    {
      if (idMenuAcoes < quantidadeMenu)
      {
        idMenuAcoes++;
      }
    }
    else if (tecla == teclaEsquerda)
    {
      idMenuAcoes = 1;
    }
    else if (tecla == teclaDireita)
    {
      idMenuAcoes = quantidadeMenu;
    }
    else if (tecla == teclaCharp)
    {
      continuar = false;
    }
    else if (tecla == teclaOK)
    {
      switch (idMenuAcoes)
      {
        case 1: {
            calibarTamanhoPasso();
            escreverLCD(formatarDireita("Tam. passo:", 16, ' ') + formatarDireita(FloatToString(_memoria.TamanhoPasso, 4), 16, ' '));
            break;
          }
        case 2: {
            _modoSistemaAux = modoSistemaLargada;
            continuar = false;
            break;
          }
        case 3: {
            _modoSistemaAux = modoSistemaNeutro;
            continuar = false;
            break;
          }
        case 4: {
            _modoSistemaAux = modoSistemaProva;
            continuar = false;
            break;
          }
        case 5: {
            configuracoes();
            break;
          }
        case 6: {
            _memoria.TempoModoRelogio = !_memoria.TempoModoRelogio;
            continuar = false;
            break;
          }
        case 7: {
            _memoria.ModoSistema = _modoSistemaAux;
            memoriaGravar();
            _memoria.ModoSistema = modoSistemaFuncoes;
            escreverLCD(formatarDireita("Memoria gravada!", 32, ' '));
            break;
          }
        case 8: {
            memoriaCarregar();
            escreverLCD(formatarDireita("Memoria restaurada!", 32, ' '));
            break;
          }
        case 9: {
            escreverLCD(formatarDireita("Metragem base:", 16, ' ') + formatarDireita(FloatToString(_memoria.MetragemBase, 4), 16, ' '));
            break;
          }
        case 10: {
            escreverLCD(formatarDireita("Tam. passo:", 16, ' ') + formatarDireita(FloatToString(_memoria.TamanhoPasso, 4), 16, ' '));
            break;
          }
        case 11: {
            escreverLCD(formatarDireita("Largada em:", 16, ' ') + formatarDireita(TempoConverter(_memoria.LargadaProva), 16, ' '));
            break;
          }
        case 12: {
            escreverLCD(formatarDireita("Larg. neutro em:", 16, ' ') + formatarDireita(TempoConverter(_memoria.LargadaNeutro), 16, ' '));
            break;
          }
        case 13: {
            escreverLCD(formatarDireita("Cont. gavacoes:", 16, ' ') + formatarDireita(IntToString(_memoria.QuantidadeGravacao), 16, ' '));
            break;
          }
        case 14: {
            int opcao = 0;
            criarPergunta("Desligar agora?", "Sim", "Nao");
            opcao = 2;
            if (esperarRespostaPergunta(&opcao))
            {
              criarPergunta("Salvar memoria?", "Sim", "Nao");
              opcao = 1;
              if (esperarRespostaPergunta(&opcao))
              {
                _memoria.ModoSistema = _modoSistemaAux;
                memoriaGravar();
                _memoria.ModoSistema = modoSistemaFuncoes;
              }
              digitalWrite(releAlimentacao, LOW);
            }
            break;
          }
        case 15: {
            memoriaRedefinir(_modoSistemaAux);
            break;
          }
      }
      if (continuar)
      {
        tecla = teclaPressionada(true);
        if (tecla == teclaCharp)
        {
          continuar = false;
        }
      }
    }
  }
  _memoria.ModoSistema = _modoSistemaAux;
}
