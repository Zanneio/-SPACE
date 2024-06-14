
#include <SPI.h>
#include <RH_RF95.h>
 

//  for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//Pin Definitions Start
//#define BME_SCK 13
//#define BME_MISO 12
//#define BME_MOSI 11
//#define BME_CS 10

//#define MQ135pin 0
//#define MQ136pin 1

//Pin Definitions End

#define SEALEVELPRESSURE_PIR (1010)

Adafruit_BME280 bme; // I2C

uint32_t timer = millis();

 
/* Feather m0 w/wing 
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     6    // "D"
*/
 
#if defined(ESP8266)
  /* for ESP w/featherwing */ 
  #define RFM95_CS  2    // "E"
  #define RFM95_RST 16   // "D"
  #define RFM95_INT 15   // "B"
  
#elif defined(ESP32)  
  /* ESP32 feather w/wing */
  #define RFM95_RST     27   // "A"
  #define RFM95_CS      33   // "B"
  #define RFM95_INT     12   //  next to A
 
#elif defined(NRF52)  
  /* nRF52832 feather w/wing */
  #define RFM95_RST     7   // "A"
  #define RFM95_CS      11   // "B"
  #define RFM95_INT     31   // "C"
  
#elif defined(TEENSYDUINO)
  /* Teensy 3.x w/wing */
  #define RFM95_RST     9   // "A"
  #define RFM95_CS      10   // "B"
  #define RFM95_INT     4    // "C"
  
#endif
 
 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 433.0
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

long PacketId=0;
 
void setup() 
{
// pinMode(buzzer, OUTPUT);
 pinMode (9,INPUT);
 pinMode (12,INPUT);
 pinMode (11,INPUT);

char Message;

  bool status;
    status = bme.begin();  
    if (!status) {
        status = bme.begin(); 
    }
    
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  delay(100);
 
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

int counter=0;
 
  while (!rf95.init() && counter<100) {
    //Serial.println("LoRa radio init failed");
    counter+=1;
    delay(10);
  }

  if(counter<100){
    }else{
    //LoRa radio init failed
      }
    
  //Serial.println("LoRa radio init OK!");
 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM

counter=0;
 
  while (!rf95.setFrequency(RF95_FREQ) && counter<100) {
    //Serial.println("LoRa radio init failed");
    counter+=1;
    delay(10);
  }

  if(counter<100){
    }else{
    ///  Serial.println("LoRa Frequency Set Frequency failed");
      }
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);

  //gps init

   //gps init
  
}
 
 
void loop()
{
/*tone(buzzer, 1000);
  delay(1000);       
  noTone(buzzer);  
  delay(1000);    
*/

//find Values
float Latitude=-1;
float Longtitude=-1;
float Altitude=-1;

//gps main

//gps main

float Temperature=bme.readTemperature();
float Pressure=bme.readPressure()/100;
float Humidity=bme.readHumidity();
Altitude=bme.readAltitude(SEALEVELPRESSURE_PIR);
  
  delay(10); // Wait 1 second between transmits, could also 'sleep' here!
  Serial.println("Transmitting..."); // Send a message to rf95_server
   
  delay(10);
  byte data[400];
  
  BuildMessage(data,Temperature,Pressure,Humidity,Altitude,Latitude,Longtitude);

//Serial.println(data);
  
  rf95.send((uint8_t *)data, sizeof(data));
  
  delay(10);
 
  rf95.waitPacketSent();

  
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
 
 /// Serial.println("Waiting for reply...");
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
    /*
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
      */

bool RecognisedMessage=false;
      
      //char* IncomingMessage=(char*)buf;
      if(buf[0]=='S'){//(char)77){
        if(buf[1]=='p'){//(char)97){
        if(buf[2]=='i'){//(char)114){
        if(buf[3]=='n'){//(char)115){
        if(buf[4]=='.'){//(char)115){

//handle standard data
RecognisedMessage=true;
        
        }else{
        if(buf[4]=='R'){//(char)115){
        if(buf[5]=='.'){//(char)115){

        //handle remote command
        RecognisedMessage=true;

        
        }}
        
        }}}}}
       
    }
    else
    {
      ///Serial.println("Receive failed");
    }
  }
  else
  {
    ///Serial.println("No reply, is there a listener around?");
  }
  
}

void BuildMessage(byte* data,float Temperature,float Pressure,float Humidity,float Altitude,float Latidute,float Longtitude){
  
 String Message="";
 if (digitalRead(11) == HIGH ){
   Message+="1pin.,";}
 if (digitalRead(12) == HIGH ){
  Message+="2pin.,";}
 if (digitalRead(9) == HIGH ){
  Message+="3pin.,";}

  Message+=String(Temperature);
  Message+=",";
  Message+=String(Pressure);
  Message+=",";
  Message+=String(Humidity);
  Message+=",";
  Message+=String(Altitude);
  Message+=",";
  Message+=String(Latidute);
  Message+=",";
  Message+=String(Longtitude);
  Message+=",";
  Message+=String(PacketId);

//uncomment for message debug
Serial.println(Message);
int sizeofarray=sizeof(Message);


 Message.getBytes(data,Message.length()+2);
PacketId++;
  
  }

void printValues() {
  
}
