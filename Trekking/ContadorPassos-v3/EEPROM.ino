void memoriaGravar()
{
  if(_memoria.QuantidadeGravacao < 0)
  {
    _memoria.QuantidadeGravacao = 0;
  }
  _memoria.QuantidadeGravacao++;
  EEPROM.put(_enderecoEEPROM, _memoria);

  //Serial.println("Escreveu na EEPROM!");
}
void memoriaCarregar()
{
  EEPROM.get(_enderecoEEPROM, _memoria);
  //Serial.println("Leu a EEPROM!");
}
boolean memoriaValidar()
{
  boolean retorno = false;
  if (EEPROM.read(_enderecoEEPROM) == 0)
  {
    retorno = true;
  }
  return retorno;
}
void memoriaRedefinir(int modoSistema)
{
  _memoria.Metros = 0;
  _memoria.MetragemBase = 0;
  _memoria.TamanhoPasso = 0;
  _memoria.LargadaProva = 0;
  _memoria.LargadaNeutro = 0;
  _memoria.ModoSistema = modoSistemaInicio;

  _memoria.TempoModoRelogio = true;

  _memoria.AlertaMetragem = false;
  _memoria.AlertaMetragemMetros = 0;
  _memoria.AlertaMetragemNivelProximidade = 0;

  if (modoSistema > 0)
  {
    _memoria.ModoSistema = modoSistema;
  }

  memoriaGravar();

  asm volatile ("  jmp 0");
}
