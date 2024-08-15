/*
  _  _______  _____ _____  ______ 
 | |/ /_   _|/ ____|  __ \|  ____|
 | ' /  | | | (___ | |__) | |__   
 |  <   | |  \___ \|  ___/|  __|  
 | . \ _| |_ ____) | |    | |____ 
 |_|\_\_____|_____/|_|    |______|                                 
   _____ _____        _____ ______ 
  / ____|  __ \ /\   / ____|  ____|
 | (___ | |__) /  \ | |    | |__   
  \___ \|  ___/ /\ \| |    |  __|  
  ____) | |  / ____ \ |____| |____ 
 |_____/|_| /_/    \_\_____|______|                         

  Development and test code for the RP2040 uC
  
  Last updated 15/08/2024 Harvey Nixon

*/

#include <Adafruit_MCP2515.h>

#define CS_PIN    5


// Set CAN bus baud rate
#define CAN_BAUDRATE (250000)
Adafruit_MCP2515 mcp(CS_PIN);

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("------------------------------------------------"); 
  Serial.println();
  Serial.println("  _  _______  _____ _____  ______ ");
  Serial.println(" | |/ /_   _|/ ____|  __ \\|  ____|");
  Serial.println(" | ' /  | | | (___ | |__) | |__   ");
  Serial.println(" |  <   | |  \\___ \\|  ___/|  __|  ");
  Serial.println(" | . \\ _| |_ ____) | |    | |____ ");
  Serial.println(" |_|\\_\\_____|_____/|_|    |______|");
  Serial.println();
  Serial.println("------------------------------------------------");
  Serial.println();
  Serial.println("MCP2515 CAN receiver Test Example for RP2040");
  Serial.println();
  delay(2000);

  if (!mcp.begin(CAN_BAUDRATE)) {
    Serial.println("Error initializing MCP2515.");
    while(1) delay(10);
  }
  Serial.println("MCP2515 chip found");
}

void loop() {
  // try to parse packet
  int packetSize = mcp.parsePacket();

  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (mcp.packetExtended()) {
      Serial.print("extended ");
    }

    if (mcp.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(mcp.packetId(), HEX);

    if (mcp.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(mcp.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      while (mcp.available()) {
        Serial.print((char)mcp.read());
      }
      Serial.println();
    }

    Serial.println();
  }
}