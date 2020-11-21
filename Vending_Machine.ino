#include <LiquidCrystal.h>

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

//Urunlerin verildigi analog girisler
#define Gofret A5
#define Kek A6
#define Su A7
#define Cikolata 2
//Urunlerin verildigi digital girisler
#define Gofret_fiyati 6
#define Cikolata_fiyati 5
#define Kek_fiyati 4
#define Su_fiyati 3

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

int stok_gofret;
int stok_cikolata;
int stok_kek;
int stok_su = 1;
//Bakiye Degiskenleri
float bakiye, bakiye_gecici;
// Baslangictaki urun stoklari



unsigned long mil;

void setup() {
  stok_gofret = 12;
  stok_cikolata = 23;
  stok_kek = 6;
  stok_su = 33;
  lcd.begin(16, 2);

  // atilan toplam para miktari
  bakiye = 0.0;
  pinMode(bes_kr, INPUT_PULLUP); //leds as i/p
  pinMode(on_kr, INPUT_PULLUP);
  pinMode(yirmibes_kr, INPUT_PULLUP);
  pinMode(elli_kr, INPUT_PULLUP);
  pinMode(yuz_kr, INPUT_PULLUP);
  pinMode(Gofret, OUTPUT);
  pinMode(Kek, OUTPUT);
  pinMode(Su, OUTPUT);
  pinMode(Cikolata, OUTPUT);
  pinMode(Gofret_fiyati, INPUT_PULLUP);
  pinMode(Kek_fiyati, INPUT_PULLUP);
  pinMode(Su_fiyati, INPUT_PULLUP);
  pinMode(Cikolata_fiyati, INPUT_PULLUP);
}

void bakiye_ekle() {

  bakiye_gecici = bakiye ;
  if (digitalRead(bes_kr) == LOW)
    bakiye = bakiye + 5;
  digitalRead(on_kr);
  if (digitalRead(on_kr) == LOW)
    bakiye = bakiye + 10;
  digitalRead(yirmibes_kr);
  if (digitalRead(yirmibes_kr) == LOW)
    bakiye = bakiye + 25;
  digitalRead(elli_kr);
  if (digitalRead(elli_kr) == LOW)
    bakiye = bakiye + 50;
  digitalRead(yuz_kr);
  if (digitalRead(yuz_kr) == LOW)
    bakiye = bakiye + 100;
  if (bakiye != bakiye_gecici) {
    lcd.print("Bakiye: ");
    lcd.print(bakiye, 2);
    lcd.print(" TL  ");
  }


}

void loop() {
  lcd.clear();
  mil = millis();
  bakiye_ekle();
  delay(1000);
  lcd.clear();
  // atilan para tutarini goster
  lcd.setCursor(0, 0);

  delay(1000);

  lcd.setCursor(0, 1);
  if (mil && 0x200 ) lcd.print("URUN SECINIZ    ");
  {

    lcd.clear();
    if (digitalRead(Gofret_fiyati) == LOW  ) {
      if (stok_gofret > 0) {

        if (bakiye > 350) {
          bakiye = bakiye - 350;
          stok_gofret -= 1;
          digitalWrite(A5, HIGH);
          lcd.print("Bakiye: ");
          lcd.print(bakiye, 2);
          lcd.print(" TL  ");
          delay(1000);
          digitalWrite(A5, LOW);

        }
        else
          lcd.print(" Bakiye yetersizdir.  ");
        delay(1000);
      }
      else
        lcd.print(" Gofret kalmadi.  ");
      delay(1000);

    }
    if (digitalRead(Cikolata_fiyati) == LOW) {
      if (stok_cikolata > 0) {
        if ( bakiye > 475) {
          bakiye = bakiye - 475;
          stok_cikolata -= 1 ;
          digitalWrite(2, HIGH);
          lcd.print("Bakiye: ");
          lcd.print(bakiye, 2);
          lcd.print(" TL  ");
          delay(1000);
          digitalWrite(2, LOW);

        }
        else
          lcd.print(" Bakiye yetersizdir.  ");
        delay(1000);
      }


      else
        lcd.print(" Cikolata kalmadi.  ");
      delay(1000);
    }
    if (digitalRead(Kek_fiyati) == LOW) {
      if (stok_kek > 0) {
        if (bakiye > 225) {
          bakiye = bakiye - 225;
          stok_kek -= 1;
          digitalWrite(A6, HIGH);
          lcd.print("Bakiye: ");
          lcd.print(bakiye, 2);
          lcd.print(" TL  ");
          delay(1000);
          digitalWrite(A6, LOW);
        }
        else
          lcd.print(" Bakiye yetersizdir.  ");
        delay(1000);
      }
      else
        lcd.print(" Kek kalmadi.  ");
      delay(1000);
    }
    if (digitalRead(Su_fiyati) == LOW ) {
      if (stok_su > 0) {
        if (bakiye > 150) {
          bakiye = bakiye - 150;
          stok_su -= 1;
          digitalWrite(A7, HIGH);
          lcd.print("Bakiye: ");
          lcd.print(bakiye, 2);
          lcd.print(" TL  ");
          delay(1000);
          digitalWrite(A7, LOW);
        }
        else
          lcd.print(" Bakiye yetersizdir.  ");
        delay(1000);
      }
      else
        lcd.print(" Su kalmadi.  ");
      delay(1000);
    }
    else if (
      lcd.print("                "));
  }
}
