#include <ESP8266WiFi.h>
#include "ThingSpeak.h" 
#include <FirebaseArduino.h>

bool ac_kapa;
const char *ssid = "************";
const char *password = "****************";

#define SECRET_CH_ID 1283208          // Secret channel ID si
const char *SECRET_READ_APIKEY = "CKVTL85V296OZEDV";  // write api key

#define FIREBASE_HOST "iot-final2-a9d7c-default-rtdb.firebaseio.com"   // baglanilacak olan firebase host adresi
#define FIREBASE_AUTH "yQNTfA9waZaVSKJBIWtqlGUSBS2eLfchEdahizYU"  

WiFiClient  wifi_istemci;
//************************************************************
void setup() {
  Serial.begin(9600);                   //seri portu baslat
  delay(1500);                          // 1500 ms = 1.5sn
  Serial.println("Wifi agına baglanıyor");
  
  WiFi.mode(WIFI_STA);                  // istasyon modunda çalış
  WiFi.begin(ssid, password);           // SSID si yukarıda belirtilmiş olan wifi a bağlan
  
  while (WiFi.status() != WL_CONNECTED) // baglanti kuruldu mu?
  {                                     // kurulmadiysa kurulana kaddar 
    delay(500);                         // 500 ms bekle
    Serial.print(".");                  // ekrana . koy    
  }
  
  Serial.println("");
  Serial.println("Wifi erisim noktasina baglanildi");

  Serial.print("Alinan IP adresi: ");
  Serial.println(WiFi.localIP());       // wifi agindan alinan IP adresini yazdir.

  ThingSpeak.begin(wifi_istemci);  // Initialize ThingSpeak

  Serial.println("Connecting Firebase Realtime Database");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
//************************************************************//
void loop() 
{
 float deger = ThingSpeak.readFloatField(SECRET_CH_ID, 5 , SECRET_READ_APIKEY);   

  int statusCode=ThingSpeak.getLastReadStatus();
  if(statusCode != 200)
    
  Serial.println("Okuma basarisiz. HTTP hata kodu " + String(statusCode));

  Serial.print("Okunan deger: ");
  Serial.println(deger);
  delay(3000);   

    if(deger > 24)
    {
      bool ac_kapa = false;
    }
    else
    {
      bool ac_kapa = true;
    }

  Firebase.setBool("201713171019", (ac_kapa)); 
  
  if (Firebase.failed()) 
  {
      Serial.print("Hata kodu:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000); 
}
