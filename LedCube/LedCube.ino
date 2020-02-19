/**************************************************************
 Name    : CapellaCube
 By      : Gabriel Capella

 Controle um cubo 8x8x8

 Date    : 27 July, 2015
 Version : 0.1
 Notes   : Using a 8x74HC595
 
****************************************************************/
#include <TimerOne.h>


#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_Z 3
#define CUBE_SIZE 8

#include <math.h>
#include <stdint.h>

//Pin connected to ST_CP of 74HC595
int latchPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 13;
////Pin connected to DS of 74HC595
int dataPin = 11;

byte data[8][8];
int vidas = 0;


void setup() {
  Serial.begin(9600);
  Initilize();
  //Serial.println(1);//TODO remover
  //Teste de efeitos
  /*
  effect_random_filler(75,1);
  effect_random_filler(75,0);
  fill(0x00);
  effect_rain(100);
  fill(0x00);
  effect_stringfly2("Capella");
  fill(0x00);
  effect_loadbar(100);
  fill(0x00);
  effect_box_shrink_grow(3,1,1,1000);
  fill(0x00);
  boingboing(1000,150, 1, 2);
  fill(0x00);
  */
//  sendplane_rand_z (0, 1000, 10000);
  fill(0x00);
  effect_planboing(3, 700);
  effect_planboing(2, 700);
  
//  effect_stringfly2("Harduime");
  
}

void loop()
{
    vidas++;
    fill(0x00);
    delay(500);
    effect_random(random(513), 50);
    delay(500);
    gol_play(100);//o parametro eh o tempo entre iteracoes 100
    delay(500);
    effect_planboing(3, 700);
    effect_planboing(2, 700);
    fill(0x00);
//contagem de vidas
//   String v = String(vidas);
//    char vi[6];
//    v.toCharArray(vi, 6);
//    effect_stringfly2(vi);
//    effect_planboing(1, 700);
//    effect_planboing(3, 700);
    delay(1000);
}
