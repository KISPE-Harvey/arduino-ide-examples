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

  Development and test code for the STM32H753ZIT uC

  Last updated 06/08/2024 Harvey Nixon
*/
#define CAN1_TX_PIN PD_1
#define CAN1_RX_PIN PD_0

static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 2560 ;
static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 0 ; // FDCAN2 not used

#include <ACANFD_STM32.h>

static ACANFD_STM32_FIFO gBuffer ;

static const uint32_t PERIOD = 5000 ;
static uint32_t gBlinkDate = PERIOD ;
static uint32_t gSentCount = 0 ;
static uint32_t gReceiveCount = 0 ;
static bool gOk = true ;
static uint32_t gCANRemoteFrameCount = 0 ;
static uint32_t gCanDataFrameCount = 0 ;
static uint32_t gCanFDNoBRSDataFrameCount = 0 ;
static uint32_t gCanFDWithBRSDataFrameCount = 0 ;
static uint32_t gStandardFrameCount = 0 ;
static uint32_t gExtendedFrameCount = 0 ;

uint32_t interval = 3000;//1000; // time between sending out in ms - basically like delay() but doesnt freeze everything
uint32_t currentMillis, prevMillis = 0;
int datatype = 1;
int counter =0;
float send_data;
char str_data[8];
char hex_data[8];

String serin;
char vel[8];

void floatToCharArray(float value, char* buffer, int bufferSize, int width, int precision){
  dtostrf(value, width, precision, buffer);
}

void data(){
  ++counter;
  Serial.println("------------------------------------------------------------------------------");
  Serial.print("Packet: ");Serial.println(counter);
  Serial.print("Data Type: ");Serial.println(datatype);

  //floatToCharArray(send_data, str_data, sizeof(str_data), 8, 6);
  // for (int i = 0; i < 8 ; i++){
  //   Serial.print(i);
  //   Serial.print(" ");
  //   Serial.println(str_data[i],HEX);
  //   }


  const uint8_t sendBufferIndex = 0 ;
  
  //--- Send frame
  CANFDMessage frame ;

  // set can frame data to all 0s
  for (uint32_t i=0 ; i<frame.len ; i++) {
    frame.data [i] = 0 ;
    // this is where the data is 
    // going to create a loop to send data
    }
  for (int i = 0; i < 8 ; i++){
    Serial.print("Character ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(vel[i]);

    }
  Serial.print("Data : ");
  Serial.print("\t");
  for (int i = 0; i < 8 ; i++){
    Serial.print(vel[i]);
    Serial.print("\t");
  }
  Serial.println();

  // Layout the frame structure
  // ID, FRAMEs ETC
  frame.idx = sendBufferIndex ;
  
  //   public : bool ext = false ; // false -> standard frame, true -> extended frame
  frame.ext = (0) ;

  // state where is in and what it means
  frame.type = CANFDMessage::Type (1);
  
    //frame.type = CANFDMessage::Type (r << 30) ;
    //frame.type = CANFDMessage::CANFD_NO_BIT_RATE_SWITCH  ;
    //frame.id = & r 0x1FFFFFFFU ;
  //   public : uint32_t id = 0 ;  // Frame identifier  
  frame.id = 0x1FFFFFFFU ;

   // if (gOk && (!gBuffer.isFull ()) && fdcan1.sendBufferNotFullForIndex (sendBufferIndex)) {
      if (frame.ext) {
        gExtendedFrameCount += 1 ;
      }else{
        gStandardFrameCount += 1 ;
        frame.id &= 0x1 ;
      }
      switch (frame.type) {
      case CANFDMessage::CAN_DATA :
        gCanDataFrameCount += 1 ;
        //frame.len = 8; // random number between 1 and 8 
        frame.len = sizeof(vel);
        for (uint32_t i=0 ; i<frame.len ; i++) {
          frame.data[i] = (vel[i]);
          // this is where the data is 
          // going to create a loop to send data
        }
      break ;
      }

  // print the CAN frame
    Serial.print("Ascii: ");
    for (int i = 0; i < frame.len; i++){
      Serial.print(frame.data[i]);
      Serial.print("\t");
    }

  Serial.println();
  const uint32_t sendStatus = fdcan1.tryToSendReturnStatusFD (frame) ;  

  Serial.println();      
  Serial.print("|---ID--|");Serial.print("|---LENGTH---|");Serial.println("|-------------------------DATA------------------------|");
  Serial.print("   ");Serial.print(frame.id, HEX);Serial.print("\t");Serial.print("\t");Serial.print(frame.len);Serial.print("\t");
  for (int i = 0; i < frame.len; i++){

    Serial.print(frame.data[i]);
    Serial.print("   ");
  }
  Serial.println();
  Serial.println("------------------------------------------------------------------------------");
  Serial.println();  
  
  if (sendStatus == 0) {
      gSentCount += 1 ;
      Serial.print("SENT Packet:");Serial.println(counter);
      Serial.println("------------------------------------------------------------------------------");
    }else{
      gOk = false ;
      Serial.print ("Send status error 0x") ;
      Serial.println (sendStatus, HEX) ;
      Serial.println("------------------------------------------------------------------------------");
    }
  Serial.println();

} //end of data






void readSerial(){
 
 if (Serial.available() > 0) {
    // read the incoming byte:
    serin = Serial.readString();
    serin.trim();
    serin.toCharArray(vel, 8);
      data();
  }


}




void setup() {
  gBuffer.initWithSize (100) ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  Serial.begin (115200);
  delay(2000);
  
  Serial.println("------------------------------------------------------------------------------");
  Serial.println();
  Serial.println("  _  _______  _____ _____  ______ ");
  Serial.println(" | |/ /_   _|/ ____|  __ \\|  ____|");
  Serial.println(" | ' /  | | | (___ | |__) | |__   ");
  Serial.println(" |  <   | |  \\___ \\|  ___/|  __|  ");
  Serial.println(" | . \\ _| |_ ____) | |    | |____ ");
  Serial.println(" |_|\\_\\_____|_____/|_|    |______|");
  Serial.println();
  Serial.println("------------------------------------------------------------------------------");
  Serial.println("    CAN FD Transmit Example");
  delay(2000);

    ACANFD_STM32_Settings settings (1000 * 1000, DataBitRateFactor::x4) ;
  settings.mModuleMode = ACANFD_STM32_Settings::NORMAL_FD; // Found in CANFDMessage.h lines 53 - 58

  const uint32_t errorCode = fdcan1.beginFD (settings) ;
 if (0 == errorCode) {
    Serial.println ("can configuration ok") ;
  }else{
    Serial.print ("Error can configuration: 0x") ;
    Serial.println (errorCode, HEX) ;
  }




}

void loop() {
  readSerial();

CANFDMessage receivedFrame ;
  if (gOk && fdcan1.receiveFD0 (receivedFrame)) {
    CANFDMessage storedFrame ;
    Serial.println();
    Serial.println("------------------------------------------------------------------------------");   
    Serial.println();    
    Serial.print("|---ID--|");Serial.print("|---LENGTH---|");Serial.println("|-------------------------DATA------------------------|");
    Serial.print("   ");Serial.print(receivedFrame.id, HEX);Serial.print("\t");Serial.print("\t");Serial.print(receivedFrame.len);Serial.print("\t");
    for (int i = 0; i < receivedFrame.len; i++){
    Serial.print(receivedFrame.data[i]);
    Serial.print("   ");
    }
    Serial.println();
    Serial.println("------------------------------------------------------------------------------");
    Serial.println();
  }



}
