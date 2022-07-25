/* ArduinoBlocks.com */
/* Project: Smart2car */
/* Author: Jordi Rodriguez */

#include <Wire.h>
#include "ABlocks_LiquidCrystal_I2C.h"
#include "ABLocks_TimerFreeTone.h"

double Iluminacion;
double Distancia;
boolean b_Linea_izquierda;
boolean b_Linea_derecha;
int l298n_ena=6;
int l298n_in1=7;
int l298n_in2=8;
int l298n_in3=9;
int l298n_in4=10;
int l298n_enb=5;
LiquidCrystal_I2C lcd_1(0x27,16,2);

void Rotar_luces() {
	digitalWrite(13,HIGH);
	delay(200);
	digitalWrite(13,LOW);
	delay(200);
	digitalWrite(2,HIGH);
	delay(200);
	digitalWrite(2,LOW);
	delay(200);
	digitalWrite(3,HIGH);
	delay(200);
	digitalWrite(3,LOW);
	delay(200);
	digitalWrite(12,HIGH);
	delay(200);
	digitalWrite(12,LOW);
	delay(200);
}
void Bip_Bip() {
	TimerFreeTone(11,500,100);
	delay(100);
	TimerFreeTone(11,500,100);
}
void Encender_luces() {
	digitalWrite(13,HIGH);
	digitalWrite(2,HIGH);
	digitalWrite(3,HIGH);
	digitalWrite(12,HIGH);
}
double fnc_ultrasonic_distance(int _t, int _e){
	unsigned long dur=0;
	digitalWrite(_t, LOW);
	delayMicroseconds(5);
	digitalWrite(_t, HIGH);
	delayMicroseconds(10);
	digitalWrite(_t, LOW);
	dur = pulseIn(_e, HIGH, 18000);
	if(dur==0)return 999.0;
	return (dur/57);
}

void Apagar_luces() {
	digitalWrite(13,LOW);
	digitalWrite(2,LOW);
	digitalWrite(3,LOW);
	digitalWrite(12,LOW);
}

void setup()
{
  	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(A3, INPUT);
	pinMode(A1, OUTPUT);
	pinMode(A0, INPUT);
	pinMode(A2, INPUT);
	pinMode(4, INPUT);
	lcd_1.begin();
	lcd_1.noCursor();
	lcd_1.backlight();
	lcd_1.clear();
	lcd_1.setCursor(0, 0);
	lcd_1.print(String("***Smart2 Car***"));
	lcd_1.setCursor(3, 1);
	lcd_1.print(String("Modo demo"));
	for (int count = 0; count < 3; count++) {
		Rotar_luces();
	}
	Bip_Bip();

}


void loop()
{

  	lcd_1.clear();
  	Iluminacion = map(analogRead(A3),0,1023,0,100);
  	if ((Iluminacion >= 50)) {
  		Encender_luces();
  	}
  	else {
  		Apagar_luces();
  	}

  	Distancia = (unsigned long)(fnc_ultrasonic_distance(A1,A0));
  	lcd_1.setCursor(0, 0);
  	lcd_1.print(String("Distancia= ")+String(Distancia));
  	b_Linea_izquierda = digitalRead(A2);
  	b_Linea_derecha = digitalRead(4);
  	lcd_1.setCursor(0, 1);
  	lcd_1.print(String(b_Linea_izquierda)+String("-Izq"));
  	lcd_1.setCursor(11, 1);
  	lcd_1.print(String("Der-")+String(b_Linea_derecha));
  	delay(200);

}