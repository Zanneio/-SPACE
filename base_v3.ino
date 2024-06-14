

#include <SPI.h>
#include <RH_RF95.h>

// for Feather32u4 RFM9x
/*
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
*/

 
// for feather m0 RFM9x
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

 
/* for shield 
#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 7
*/
 
/* Feather 32u4 w/wing
#define RFM95_RST     11   // "A"
#define RFM95_CS      10   // "B"
#define RFM95_INT     2    // "SDA" (only SDA/SCL/RX/TX have IRQ!)
*/
 
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
 
 
#define RF95_FREQ 433.0
 
RH_RF95 rf95(RFM95_CS, RFM95_INT);


 
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  
  Serial.begin(9600);
  Serial.print("hi");
  while (!Serial) {
    delay(1);
  }



 // digitalWrite(LED, LOW);
  delay(100);
 
  //Serial.println("Feather LoRa RX Test!");  
 
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
// digitalWrite(LED, HIGH);
  while (!rf95.init()) {
    //while (1);
  }
 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    while (1);
  }
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}
 
void loop()
{
 digitalWrite(13, LOW);
 digitalWrite(12, LOW);    
 digitalWrite(11, LOW);      
  if (rf95.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      //RH_RF95::printBuffer("Received: ", buf, len);
      Serial.print("Got: ");
      Serial.println((char*)buf);
      char* IncomingMessage=(char*)buf;

        if(buf[0]=='3'){
          digitalWrite(13, HIGH);
          tone(6,2500);
          delay(500);  
          noTone(6); // wait for a second
          digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
          delay(500); 
        }
        if(buf[0]=='2'){
           digitalWrite(12, HIGH);
           tone(6,1500);// turn the LED on (HIGH is the voltage level)
          delay(1000);  
             noTone(6);// wait for a second
          digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
          delay(1000);
        }
           if(buf[0]=='1'){
          digitalWrite(11, HIGH);
          tone(6,500);
          delay(1000);  
          noTone(6); // wait for a second
          digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
          delay(1000); 
        }

        

        //Identify Packet
         if(buf[0]=='S'){//(char)77){
        if(buf[1]=='p'){//(char)97){
        if(buf[2]=='i'){//(char)114){
        if(buf[3]=='n'){//(char)115){
        if(buf[4]=='.'){

      
        
        //Decode Packet
          String msg_field[8];
          getCSVfields(IncomingMessage,msg_field);
          
          float Temp=msg_field[1].toFloat();
          float Pressure=msg_field[2].toFloat();
          float Humidity=msg_field[3].toFloat();

          float Altitude=msg_field[4].toFloat();
          float Latitude=msg_field[5].toFloat();
          float Longtitude=msg_field[6].toFloat();
          
          int PacketId=msg_field[7].toInt();

          //Proccess Packet
          Serial.print("Got Packet ");
          Serial.println(PacketId);

          Serial.print("Temp "); Serial.print(Temp); Serial.print(" ");
          Serial.print("Pressure "); Serial.print(Pressure); Serial.print(" ");
          Serial.print("Humidity "); Serial.print(Humidity); Serial.print(" ");
          
          Serial.print("Altitude "); Serial.print(Altitude); Serial.print(" ");
          Serial.print("Latitude "); Serial.print(Latitude); Serial.print(" ");
          Serial.print("Longtitude "); Serial.print(Longtitude); Serial.print(" ");
          Serial.print("PacketId "); Serial.print(PacketId); Serial.println(" ");

        }
        }}}}




       Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
 
      // Send a reply

      if(Serial.available()>0){
        if(Serial.read() == 'T'){
      uint8_t data[] = "got reply";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Serial.println("Sent a reply");
      }}
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
}

byte getCSVfields(char input_buffer[],String msg_field[])
{
    byte _sentencePos = 0;
    byte _comma_count = 0;
    msg_field[_comma_count] = "";
    while (1)
    {
        if (input_buffer[_sentencePos] == NULL) break;
        if (input_buffer[_sentencePos] == 44)
        {
            _comma_count++;
            msg_field[_comma_count] = "";
            _sentencePos++;
        }
        else
        {
            msg_field[_comma_count] += input_buffer[_sentencePos];
            _sentencePos++;
        }
    }
    return _comma_count + 1;

 
        
}
