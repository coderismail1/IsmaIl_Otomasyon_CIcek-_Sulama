#define BLYNK_PRINT Serial

// İlgili Kütüphaneler eklendi
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Projenize ait Auth Token. Uygulama içinden veya mail adresinizden erişebilirsiniz 
char auth[] = "O5_BCa7FwZLDRGqQ8o41KZHgPbVv5Ys-"; 

//WiFi ağ adınız ve parolanız 
char ssid[] = "SİSTEM-1"; 
char pass[] = "Apple6464";

int sensorPin = A0; // Sensör bağlantı pini 
int sensorDeger;
bool mail = true;
int role = 5; // D1
int led1 = 0 ; //D3
int led2 = 12 ;// D6
int buzzer = 13; // D7

BlynkTimer timer;

//Sensörümüzün verdiği değerleri okuyup verileri uygulamamıza gönderiyoruz.
void sensorOku()
{
  sensorDeger = analogRead(sensorPin); // Sensör okunarak alınan veri sensorDeger değişkenine eşitleniyor. 
  Blynk.virtualWrite(V1, sensorDeger); // sensorDeger verisi Blynk uygulamasında V1 pinine gönderiliyor. 

  //Sensör verisi 700 ün üstüne çıktığında ve mail değişkeni true oldugunda döngü çalışır.
  if (sensorDeger > 700 && mail) {
    Blynk.email("ismail645864@icloud.com", "Subject: Sulama Sistemi", "Bitkinizin suya ihtiyacı var. Sulama sistemini açmak için uygulamaya gidin"); //Mail adresiniz, Konu, İçerik
    mail = false; 
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    
    digitalWrite(buzzer, HIGH);
    
  }

  //Sensör verisi 300 ün altında düştüğünde döngü çalışır.
  if (sensorDeger < 650) {
    digitalWrite(role,HIGH ); // Bitki yeterince sulandıgında role otomatik olarak kapanır.
    digitalWrite(led1, HIGH);
     digitalWrite(led2, LOW);
    mail = true; 
  }
}


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(role, OUTPUT); // role pinini ÇIKIŞ olarak ayarlıyoruz
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Saniyede 1 defa sensorOku fonksiyonu çağırıyoruz
  timer.setInterval(10L, sensorOku);
}

void loop()
{
  Blynk.run();
  timer.run();
}
