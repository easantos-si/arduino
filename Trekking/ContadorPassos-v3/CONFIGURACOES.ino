void configuracoes()
{
  int opcao = 0;
  criarPergunta("Conf. relogio?", "Sim", "Nao");
  opcao = 2;
  if (esperarRespostaPergunta(&opcao))
  {
    ajustarRelogio();
  }
  criarPergunta("Conf. largada P?", "Sim", "Nao");
  opcao = 2;
  if (esperarRespostaPergunta(&opcao))
  {
    ajustarLargadaProva();
  }
  criarPergunta("Conf. largada N?", "Sim", "Nao");
  opcao = 2;
  if (esperarRespostaPergunta(&opcao))
  {
    ajustarLargadaNeutro();
  }
}
