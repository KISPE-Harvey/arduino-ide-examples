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

  Development and test code for the STM32H753VIT uC

  Last updated 16/08/2024 Harvey Nixon
*/
#define CAN1_TX_PIN PA12
#define CAN1_RX_PIN PA11

// #define CAN2_TX_PIN PB13
// #define CAN2_RX_PIN PB12

static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 2560 ;
static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 0 ; // FDCAN2 not used

// static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 0 ;// FDCAN1 not used
// static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 2560 ; 

#include <ACANFD_STM32.h>

static ACANFD_STM32_FIFO gBuffer ;

int datatype = 1;
int counter =0;
float send_data;
float pressure = 1120.64;
float temperature = 21.25;
float accelerationX = 9.81;
float accelerationY = -0.12;
float accelerationZ = 0.10;

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

char str_data[8];
char hex_data[8];

void floatToCharArray(float value, char* buffer, int bufferSize, int width, int precision){
  dtostrf(value, width, precision, buffer);
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

// class CANMessage {
//   public : uint32_t id = 0 ;  // Frame identifier
//   public : bool ext = false ; // false -> standard frame, true -> extended frame
//   public : bool rtr = false ; // false -> data frame, true -> remote frame
//   public : uint8_t idx = 0 ;  // This field is used by the driver
//   public : uint8_t len = 0 ;  // Length of data (0 ... 8)
//   public : union {
//     uint8_t  data    [8] = {0, 0, 0, 0, 0, 0, 0, 0} ;
//   } ;

void loop() {
  currentMillis = millis();

  if (currentMillis - prevMillis > interval){

  // data
  switch(datatype){
    case 1: 
      send_data = pressure;
      data();
      break;
    case 2:
      send_data = temperature;
      data();
      break;
    case 3:
      send_data = accelerationX;
      data();
      break;
    case 4: 
      send_data = accelerationY;
      data();
      break;
    case 5:
      send_data = accelerationZ;
      data();
      break;
    case 6:
    datatype = 0;
    break;
    }
    ++datatype; 
 
      prevMillis = currentMillis;
  }// END of interval

} // END of Loop()

void data(){
  ++counter;
  Serial.println("------------------------------------------------------------------------------");
  Serial.print("Packet: ");Serial.println(counter);
  Serial.print("Data Type: ");Serial.println(datatype);

  floatToCharArray(send_data, str_data, sizeof(str_data), 8, 6);
  for (int i = 0; i < 8 ; i++){
    Serial.print(i);
    Serial.print(" ");
    Serial.println(str_data[i],HEX);
    }


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
    Serial.println(str_data[i]);

    }
  Serial.print("Data : ");
  Serial.print("\t");
  for (int i = 0; i < 8 ; i++){
    Serial.print(str_data[i]);
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
        frame.id &= 0x7FFU ;
      }
      switch (frame.type) {
      case CANFDMessage::CAN_DATA :
        gCanDataFrameCount += 1 ;
        //frame.len = 8; // random number between 1 and 8 
        frame.len = sizeof(str_data);
        for (uint32_t i=0 ; i<frame.len ; i++) {
          frame.data[i] = (str_data[i]);
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
  //const uint32_t sendStatus = fdcan2.tryToSendReturnStatusFD (frame) ; 


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