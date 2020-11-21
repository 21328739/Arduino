/*
  Vending Machine Projesi
  Dort farkli urun satisi yapan otomatik satis makinesi
*/
// Paralarin atildigi analog girisler
#define bes_kr A0
#define on_kr A1
#define yirmibes_kr A2
#define elli_kr A3
#define yuz_kr A4

//Urunlerin secildigi analog girisler
#define Gofret A5
#define Kek A6
#define Su A7
#define Cikolata D2
//Urunlerin verildigi digital girisler
#define gofret_fiyati 6
#define cikolata_fiyati 5
#define kek_fiyati 4
#define su_fiyati 3

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int stok_gofret;
int stok_cikolata;
int stok_kek;
int stok_su;

float bakiye;

unsigned long mil;

void setup() {

  lcd.begin(16, 2);

  // Baslangictaki urun stoklari
  stok_gofret = 12;
  stok_cikolata = 23;
  stok_kek = 6;
  stok_su = 33;

  // atilan toplam para miktari
  bakiye = 0.0;
}
void bakiye_ekle() {
  if (digitalRead(bes_kr) == HIGH)
    bakiye = bakiye + 5;
  digitalRead(on_kr);
  if (digitalRead(on_kr) == HIGH)
    bakiye = bakiye + 10;
  digitalRead(yirmibes_kr);
  if (digitalRead(yirmibes_kr) == HIGH)
    bakiye = bakiye + 25;
  digitalRead(elli_kr);
  if (digitalRead(elli_kr) == HIGH)
    bakiye = bakiye + 50;
  digitalRead(yuz_kr);
  if (digitalRead(yuz_kr) == HIGH)
    bakiye = bakiye + 100;

}
void secim() {


}
void loop() {
  mil = millis();
  bakiye_ekle();
  // atilan para tutarini goster
  lcd.setCursor(0, 0);
  lcd.print("Bakiye: ");
  lcd.print(bakiye, 2);
  lcd.print(" TL  ");

  lcd.setCursor(0, 1);
  if (mil & 0x200) lcd.print("URUN SECINIZ    ");
  else lcd.print("                ");
  
  if (gofret_fiyati == HIGH ||  stok_gofret > 0) {
    if(bakiye > 350){
    bakiye = bakiye - gofret_fiyati;
    stok_gofret =-1;
    delay(1000);}
    else
    lcd.print(" Gofret stogu yetersizdir.  ");
  }
  if (cikolata_fiyati == HIGH  || stok_cikolata > 0) {
    if ( bakiye > 475){
    bakiye = bakiye - cikolata_fiyati;
    stok_cikolata = -1;
    delay(1000);}
    else
    lcd.print(" Cikolata stogu yetersizdir.  ");
  }
  if (kek_fiyati == HIGH || stok_kek > 0) {
     if(bakiye > 225){
    bakiye = bakiye - gofret_fiyati;
    stok_kek = -1;
    delay(1000);}
    else 
    lcd.print(" Kek stogu yetersizdir.  ");
  }
  if (su_fiyati == HIGH || stok_su > 0) {
    if(bakiye > 150){
    bakiye = bakiye - su_fiyati;
    stok_su = -1;
    delay(1000);}
    else
    lcd.print(" Su stogu yetersizdir.  ");

  }







}
