#include <WiFi.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
String apiKey = "FTY1Txxxxxxx1NGU";
 
const char* ssid = "********************************";
const char* password = "********************************";
 
const char* server = "api.thingspeak.com";
 
RF24 radio(4, 5); 
const uint64_t address = 0xF0F0F0F0E1LL;
 
struct MyVariable
{
  byte soilmoisturepercent;
  byte nitrogen;
  byte phosphorous;
  byte potassium;
  byte temperature;
};
MyVariable variable;
 
WiFiClient client;
 
void setup() 
{
  Serial.begin(115200);
  radio.begin();                  //Starting the Wireless communication
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
  
  Serial.println("Receiver Started....");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 
int recvData()
{
  if ( radio.available() ) 
  {
    radio.read(&variable, sizeof(MyVariable));
    return 1;
    }
    return 0;
}
 
 
void loop()
{
  if(recvData())
  {
 
  Serial.println("Data Received:");
  
  Serial.print("Soil Moisture: ");
  Serial.print(variable.soilmoisturepercent);
  Serial.println("%");
 
  Serial.print("Nitrogen: ");
  Serial.print(variable.nitrogen);
  Serial.println(" mg/kg");
  Serial.print("Phosphorous: ");
  Serial.print(variable.phosphorous);
  Serial.println(" mg/kg");
  Serial.print("Potassium: ");
  Serial.print(variable.potassium);
  Serial.println(" mg/kg");
 
  Serial.print("Temperature: ");
  Serial.print(variable.temperature);
  Serial.println("*C");
 
  Serial.println();
 
  if (client.connect(server, 80)) 
  {
        String postStr = apiKey;
        postStr += "&field1=";
        postStr += String(variable.soilmoisturepercent);
        postStr += "&field2=";
        postStr += String(variable.nitrogen);
        postStr += "&field3=";
        postStr += String(variable.phosphorous);
        postStr += "&field4=";
        postStr += String(variable.potassium);
        postStr += "&field5=";
        postStr += String(variable.temperature);
        postStr += "\r\n\r\n\r\n\r\n\r\n";
        
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);
        delay(1000);
        Serial.println("Data Sent to Server");
      }
        client.stop();
  }
}