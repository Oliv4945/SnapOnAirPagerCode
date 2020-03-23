/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>

// Display configurationb
#include <bb_uc1701.h>

#define DC_PIN 12
#define CS_PIN 14
#define RST_PIN 15
#define MOSI_PIN 19
#define SCK_PIN 18
#define LED_PIN 27 
#define FLIP180 0
#define INVERT 0

//define the pins used by the transceiver module
#define ss 5
#define rst 0
#define dio0 22

String LoRaData;

void setup() {

  // DISPLAY
    uc1701Init(DC_PIN, RST_PIN, LED_PIN, CS_PIN, MOSI_PIN, SCK_PIN, FLIP180, INVERT, -1);
    uc1701SetContrast(235);
    uc1701Fill(0);    
    uc1701WriteString(0,1,(char *)"LORA SETUP OK", 0, FONT_NORMAL);
    uc1701WriteString(0,2,(char *)"Listening ...", 0, FONT_NORMAL);


    //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
 // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    String LevelS="RSSI"+LoRa.packetRssi();

    // DISPLAY
    uc1701Init(DC_PIN, RST_PIN, LED_PIN, CS_PIN, MOSI_PIN, SCK_PIN, FLIP180, INVERT, -1);
    uc1701SetContrast(235);
    uc1701Fill(0);    
    uc1701WriteString(0,1,(char *)"Got it", 0, FONT_NORMAL);
    uc1701WriteString(0,2,(char *)"Level", 0, FONT_NORMAL);

    
  }
}
