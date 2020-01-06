//#include <TimerOne.h>
#include <DS3231.h>
#include <IRremote.h>
#include <EEPROM.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Arduino.h>

LiquidCrystal_I2C _lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

DS3231  _relogio(SDA, SCL);
Time _tempo;

#define botaoPin 2
#define releAlimentacao 3
#define buzzerPin 7
#define controlePin 12

IRrecv _controle(controlePin);

decode_results _results;

long _interrupcao;
long _interrupcaoAnterior;

long _controleInterrupcao;
long _controleInterrupcaoAnterior;

struct Memoria {
  float Metros;
  float MetragemBase;
  float TamanhoPasso;
  long LargadaProva;
  long LargadaNeutro;
  byte ModoSistema;
  boolean TempoModoRelogio;
  boolean AlertaMetragem;
  float AlertaMetragemMetros;
  int AlertaMetragemNivelProximidade;
  int QuantidadeGravacao;
};

int _enderecoEEPROM;

Memoria _memoria;

#define Tempo_d 86400000
#define Tempo_h 3600000
#define Tempo_m 60000
#define Tempo_s 1000

char _telaLCD[2][16];
int _telaMapa[32];
int _telaMapaTL;

int _quantidadePassos;

#define modoSistemaFuncoes 0
#define modoSistemaInicio 1
#define modoSistemaLargada 2
#define modoSistemaNeutro 3
#define modoSistemaProva 4
#define modoSistemaCalibragem 5

String _tecla;
String _teclaPressionada;

#define teclaCima "511DBB"
#define teclaBaixo "A3C8EDDB"
#define teclaEsquerda "52A3D41F"
#define teclaDireita "20FE4DBB"
#define teclaOK "D7E84B1B"
#define teclaNumero1 "C101E57B"
#define teclaNumero2 "97483BFB"
#define teclaNumero3 "F0C41643"
#define teclaNumero4 "9716BE3F"
#define teclaNumero5 "3D9AE3F7"
#define teclaNumero6 "6182021B"
#define teclaNumero7 "8C22657B"
#define teclaNumero8 "488F3CBB"
#define teclaNumero9 "449E79F"
#define teclaNumero0 "1BC0157B"
#define teclaAsterisco "32C6FDF7"
#define teclaCharp "3EC3FC1B"

void setup() {
  pinMode(releAlimentacao, OUTPUT);
  digitalWrite(releAlimentacao, HIGH);

  _quantidadePassos = 0;

  _interrupcao = 0;
  _interrupcaoAnterior = 0;

  _controleInterrupcao = 0;
  _controleInterrupcaoAnterior = 0;

  _enderecoEEPROM = 0;
  /*
    Serial.begin(115200);
    Serial.println("1");
    Serial.print("_memoria.Metros:");
    Serial.println(_memoria.Metros);

    Serial.print("_memoria.MetragemBase:");
    Serial.println(_memoria.MetragemBase);

    Serial.print("_memoria.TamanhoPasso:");
    Serial.println(_memoria.TamanhoPasso);

    Serial.print("_memoria.LargadaProva:");
    Serial.println(_memoria.LargadaProva);

    Serial.print("_memoria.LargadaNeutro:");
    Serial.println(_memoria.LargadaNeutro);

    Serial.print("_memoria.ModoSistema:");
    Serial.println(_memoria.ModoSistema);

    Serial.print("_memoria.TempoModoRelogio:");
    Serial.println(_memoria.TempoModoRelogio);

    Serial.print("_memoria.AlertaMetragem:");
    Serial.println(_memoria.AlertaMetragem);

    Serial.print("_memoria.AlertaMetragemMetros:");
    Serial.println(_memoria.AlertaMetragemMetros);

    Serial.print("_memoria.AlertaMetragemNivelProximidade:");
    Serial.println(_memoria.AlertaMetragemNivelProximidade);

    Serial.println("---------------------------------------------------------");
  */
  memoriaCarregar();
  /*
    Serial.println("2");
    Serial.print("_memoria.Metros:");
    Serial.println(_memoria.Metros);

    Serial.print("_memoria.MetragemBase:");
    Serial.println(_memoria.MetragemBase);

    Serial.print("_memoria.TamanhoPasso:");
    Serial.println(_memoria.TamanhoPasso);

    Serial.print("_memoria.LargadaProva:");
    Serial.println(_memoria.LargadaProva);

    Serial.print("_memoria.LargadaNeutro:");
    Serial.println(_memoria.LargadaNeutro);

    Serial.print("_memoria.ModoSistema:");
    Serial.println(_memoria.ModoSistema);

    Serial.print("_memoria.TempoModoRelogio:");
    Serial.println(_memoria.TempoModoRelogio);

    Serial.print("_memoria.AlertaMetragem:");
    Serial.println(_memoria.AlertaMetragem);

    Serial.print("_memoria.AlertaMetragemMetros:");
    Serial.println(_memoria.AlertaMetragemMetros);

    Serial.print("_memoria.AlertaMetragemNivelProximidade:");
    Serial.println(_memoria.AlertaMetragemNivelProximidade);

    Serial.println("---------------------------------------------------------");

    Serial.print("EEPROM.read(_enderecoEEPROM):");
    Serial.println(EEPROM.read(_enderecoEEPROM));

    Serial.print("!memoriaValidar():");
    Serial.println(!memoriaValidar());
  */
  if (!memoriaValidar())
  {
    memoriaRedefinir(-1);
    /*
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
      _memoria.QuantidadeGravacao = 1;
    */
    
    /*
        Serial.print("(_memoria.Metros):");
        Serial.println((_memoria.Metros));
        Serial.println("3");
        Serial.print("_memoria.Metros:");
        Serial.println(_memoria.Metros);

        Serial.print("_memoria.MetragemBase:");
        Serial.println(_memoria.MetragemBase);

        Serial.print("_memoria.TamanhoPasso:");
        Serial.println(_memoria.TamanhoPasso);

        Serial.print("_memoria.LargadaProva:");
        Serial.println(_memoria.LargadaProva);

        Serial.print("_memoria.LargadaNeutro:");
        Serial.println(_memoria.LargadaNeutro);

        Serial.print("_memoria.ModoSistema:");
        Serial.println(_memoria.ModoSistema);

        Serial.print("_memoria.TempoModoRelogio:");
        Serial.println(_memoria.TempoModoRelogio);

        Serial.print("_memoria.AlertaMetragem:");
        Serial.println(_memoria.AlertaMetragem);

        Serial.print("_memoria.AlertaMetragemMetros:");
        Serial.println(_memoria.AlertaMetragemMetros);

        Serial.print("_memoria.AlertaMetragemNivelProximidade:");
        Serial.println(_memoria.AlertaMetragemNivelProximidade);

        Serial.println("---------------------------------------------------------");
    */
  }

  _relogio.begin();
  _lcd.begin (16, 2);
  _lcd.setBacklight(HIGH);
  limparLCD();
  criarCaracteres();

  _controle.enableIRIn();

  if (_memoria.ModoSistema == modoSistemaInicio)
  {
    configuracoes();
  }
  pinMode(botaoPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(botaoPin), passos_callback, RISING);

  if (_memoria.ModoSistema == modoSistemaInicio)
  {
    _memoria.ModoSistema = modoSistemaLargada;
    _memoria.TempoModoRelogio = true;
    /*
        Serial.println("4");
        Serial.print("_memoria.Metros:");
        Serial.println(_memoria.Metros);

        Serial.print("_memoria.MetragemBase:");
        Serial.println(_memoria.MetragemBase);

        Serial.print("_memoria.TamanhoPasso:");
        Serial.println(_memoria.TamanhoPasso);

        Serial.print("_memoria.LargadaProva:");
        Serial.println(_memoria.LargadaProva);

        Serial.print("_memoria.LargadaNeutro:");
        Serial.println(_memoria.LargadaNeutro);

        Serial.print("_memoria.ModoSistema:");
        Serial.println(_memoria.ModoSistema);

        Serial.print("_memoria.TempoModoRelogio:");
        Serial.println(_memoria.TempoModoRelogio);

        Serial.print("_memoria.AlertaMetragem:");
        Serial.println(_memoria.AlertaMetragem);

        Serial.print("_memoria.AlertaMetragemMetros:");
        Serial.println(_memoria.AlertaMetragemMetros);

        Serial.print("_memoria.AlertaMetragemNivelProximidade:");
        Serial.println(_memoria.AlertaMetragemNivelProximidade);

        Serial.println("---------------------------------------------------------");
    */
  }
  limparLCD();
  _tecla = "";
  _teclaPressionada = "";

  //Serial.begin(115200);
}

void loop() {

  if (_memoria.TamanhoPasso == 0)
  {
    escreverLCD(formatarDireita("Lost - Calibre  seu Passo! :)", 32, ' '));
  }
  else
  {
    if (_memoria.ModoSistema == modoSistemaProva)
    {
      if (_memoria.LargadaProva == 0 || _memoria.TempoModoRelogio)
      {
        escreverLCD(formatarDireita("Tempo:" + CharsToString(_relogio.getTimeStr()), 16, ' ') + formatarDireita("Metros:" + formatarEsquerda(FloatToString(_memoria.Metros, 0), 4, '0'), 16, ' '));
      }
      else
      {
        _tempo = _relogio.getTime();
        escreverLCD(formatarDireita("Tempo:" + TempoConverter(TempoConverter((int)_tempo.hour, (int)_tempo.min, (int)_tempo.sec) - _memoria.LargadaProva), 16, ' ') + formatarDireita("Metros:" + formatarEsquerda(FloatToString(_memoria.Metros, 0), 4, '0'), 16, ' '));
      }
    }
    else if (_memoria.ModoSistema == modoSistemaLargada)
    {
      _tempo = _relogio.getTime();
      if (_memoria.LargadaProva > 0 && _memoria.LargadaProva <= TempoConverter(_tempo.hour, _tempo.min, _tempo.sec))
      {
        _memoria.ModoSistema = modoSistemaProva;
      }
      else
      {
        if (_memoria.LargadaProva > 0)
        {
          escreverLCD(formatarDireita("Tempo:" + CharsToString(_relogio.getTimeStr()), 16, ' ') + formatarDireita("L:" + TempoConverter(_memoria.LargadaProva - TempoConverter((int)_tempo.hour, (int)_tempo.min, (int)_tempo.sec)), 16, ' '));

          Alertas(_memoria.LargadaProva - TempoConverter((int)_tempo.hour, (int)_tempo.min, (int)_tempo.sec));
        }
        else
        {
          escreverLCD(formatarDireita("Equipe: Lost", 16, ' ') + "Largada:00:00:00");
        }
      }
    }
    else if (_memoria.ModoSistema == modoSistemaNeutro)
    {
      _tempo = _relogio.getTime();
      if (_memoria.LargadaNeutro > 0 && _memoria.LargadaNeutro <= TempoConverter((int)_tempo.hour, (int)_tempo.min, (int)_tempo.sec))
      {
        _memoria.ModoSistema = modoSistemaProva;
      }
      else
      {
        if (_memoria.LargadaNeutro > 0)
        {
          _tempo = _relogio.getTime();
          escreverLCD(formatarDireita("Tempo:" + CharsToString(_relogio.getTimeStr()), 16, ' ') + formatarDireita("N:" + TempoConverter(_memoria.LargadaNeutro - TempoConverter((int)_tempo.hour, (int)_tempo.min, (int) _tempo.sec)), 16, ' '));

          Alertas(_memoria.LargadaNeutro - TempoConverter((int)_tempo.hour, (int)_tempo.min, (int)_tempo.sec));
        }
        else
        {
          escreverLCD(formatarDireita("Equipe: Lost", 16, ' ') + formatarDireita("Neutro:00:00:00", 16, ' '));
        }
      }
    }
  }
  _tecla = teclaPressionada(false);
  if (_tecla.length() > 0)
  {
    processar(&_tecla);
  }
}
