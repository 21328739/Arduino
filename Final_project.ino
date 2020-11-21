
#include <SoftwareSerial.h>                                   //SoftwareSerial eklendi
#include <DHT.h> //DHT11 sensör kütüphanemizi ekliyoruz.
#include <BH1750.h> //bu kütüphaneyi de ekledik.
#define DHTPIN 2
#define DHTTYPE DHT11 
BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);
String agAdi = "LONG LIVE BOB";                 //Ag adi    
String agSifresi = "&);8k8jsa62?dn7(q!";           //Ag sifresi 
int rxPin = 10;                                               //ESP8266 RX pini
int txPin = 11;                                               //ESP8266 TX pini


String ip = "184.106.153.149";                                //Thingspeak adresi
float sicaklik, nem, isik, carbonmonoxide;



SoftwareSerial esp(rxPin, txPin);                             

void setup() {  
   Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  lightMeter.begin();
  Serial.begin(9600);  //Seri port ile haberleşme
  Serial.println("Started");
  esp.begin(115200);                                          
  esp.println("AT");                                      
  Serial.println("AT Yollandı");
  while(!esp.find("OK")){                                     
    esp.println("AT");
    Serial.println("ESP8266 Bulunamadı.");
  }
  Serial.println("OK Komutu Alındı");
  esp.println("AT+CWMODE=1");                               
  while(!esp.find("OK")){                                    
    esp.println("AT+CWMODE=1");
    Serial.println("Ayar Yapılıyor....");
  }
  Serial.println("Client olarak ayarlandı");
  Serial.println("Aga Baglaniliyor...");
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");    
  while(!esp.find("OK"));                                     
  Serial.println("Aga Baglandi.");
  delay(1000);
}
void loop() {
  esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");           
  if(esp.find("Error")){                                      
    Serial.println("AT+CIPSTART Error");
  }
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
 
  uint16_t intensity = lightMeter.readLightLevel();
  isik = intensity;
  sicaklik = t;
  nem = h;
  carbonmonoxide = analogRead(A3);
  String veri = "GET https://api.thingspeak.com/update?api_key=LJL6U422IM1E92YW";   
  veri += "&field1=";
  veri += String(nem);
  veri += "&field2=";
  veri += String(carbonmonoxide);//Göndereceğimiz nem değişkeni
  veri += "&field3=";
  veri += String(sicaklik);
  veri += "&field4=";
  veri += String(isik);
  veri += "\r\n\r\n"; 
  esp.print("AT+CIPSEND=");                                   
  esp.println(veri.length()+2);
  delay(2000);
  if(esp.find(">")){                                          
    esp.print(veri);                                          
    Serial.println(veri);
    Serial.println("Veri gonderildi.");
    delay(1000);
  }
  Serial.println("Baglantı Kapatildi.");
  esp.println("AT+CIPCLOSE");                                //Bağlanti kapali
  delay(1000);                                               
}
