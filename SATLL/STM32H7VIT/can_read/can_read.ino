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
// #define CAN1_TX_PIN PB9
// #define CAN1_RX_PIN PB8
// #define CE_CAN PB0

#define CAN1_TX_PIN PD_1
#define CAN1_RX_PIN PD_0

// #define CAN2_TX_PIN PB13
// #define CAN2_RX_PIN PB12

static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 2560 ;
static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 0 ; // FDCAN2 not used

// static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 0 ;// FDCAN1 not used
// static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 2560 ; 

#include <ACANFD_STM32.h>

static ACANFD_STM32_FIFO gBuffer ;
static bool gOk = true ;

uint32_t interval = 3000;//1000; // time between sending out in ms - basically like delay() but doesnt freeze everything
uint32_t currentMillis, prevMillis = 0;
//RX TX
HardwareSerial Serial3(PD8, PD9);



void setup() {
  gBuffer.initWithSize (100) ;

  //pinMode (LED_BUILTIN, OUTPUT) ;
  //Serial.begin (115200);
  Serial3.begin (115200);
  delay(2000);
  
  // Serial.println("------------------------------------------------------------------------------");
  // Serial.println();
  // Serial.println("  _  _______  _____ _____  ______ ");
  // Serial.println(" | |/ /_   _|/ ____|  __ \\|  ____|");
  // Serial.println(" | ' /  | | | (___ | |__) | |__   ");
  // Serial.println(" |  <   | |  \\___ \\|  ___/|  __|  ");
  // Serial.println(" | . \\ _| |_ ____) | |    | |____ ");
  // Serial.println(" |_|\\_\\_____|_____/|_|    |______|");
  // Serial.println();
  // Serial.println("------------------------------------------------------------------------------");
  //Serial.println("    CAN FD Read Example");
  Serial3.println("    CAN FD Read Example");
  delay(2000);
  //ACANFD_STM32_Settings settings (1000 * 1000, DataBitRateFactor::x4) ;
  ACANFD_STM32_Settings settings (250 * 1000, DataBitRateFactor::x1) ;
  //settings.mModuleMode = ACANFD_STM32_Settings::NORMAL_FD; // Found in CANFDMessage.h lines 53 - 58
  settings.mModuleMode = ACANFD_STM32_Settings::NORMAL_FD;

    const uint32_t errorCode = fdcan1.beginFD (settings) ;
    //const uint32_t errorCode = fdcan2.beginFD (settings) ;

  // Serial.print ("Message RAM required minimum size: ") ;
  // Serial.print (fdcan1.messageRamRequiredMinimumSize ()) ;
  // Serial.println (" words") ;
  //   Serial3.print ("Message RAM required minimum size: ") ;
  // Serial3.print (fdcan1.messageRamRequiredMinimumSize ()) ;
  // Serial3.println (" words") ;
 
//  if (0 == errorCode) {
//     Serial.println ("can configuration ok") ;
//   }else{
//     Serial.print ("Error can configuration: 0x") ;
//     Serial.println (errorCode, HEX) ;
//   }
}

void loop() {
  //--- Receive frame
  CANFDMessage receivedFrame ;
  if (fdcan1.availableFD0()){
    Serial3.println("Data Avaliable");
    delay(100);

  }


  if (gOk && fdcan1.receiveFD0(receivedFrame)) {

  //if (gOk && fdcan2.receiveFD1 (receivedFrame)) {      
    CANFDMessage storedFrame ;
    // Serial.println();
    // Serial.println("------------------------------------------------------------------------------");   
    // Serial.println();    
    // Serial.print("|---ID--|");Serial.print("|---LENGTH---|");Serial.println("|-------------------------DATA------------------------|");
    // Serial.print("   ");Serial.print(receivedFrame.id, HEX);Serial.print("\t");Serial.print("\t");Serial.print(receivedFrame.len);Serial.print("\t");
    // for (int i = 0; i < receivedFrame.len; i++){
    // Serial.print(receivedFrame.data[i]);
    // Serial.print("   ");
    // }
    // Serial.println();
    // Serial.println("------------------------------------------------------------------------------");
    // Serial.println();
    Serial3.println();
    Serial3.println("------------------------------------------------------------------------------");   
    Serial3.println();    
    Serial3.print("|---ID--|");Serial3.print("|---LENGTH---|");Serial3.println("|-------------------------DATA------------------------|");
    Serial3.print("   ");Serial3.print(receivedFrame.id, HEX);Serial3.print("\t");Serial3.print("\t");Serial3.print(receivedFrame.len);Serial3.print("\t");
    for (int i = 0; i < receivedFrame.len; i++){
    Serial3.print(receivedFrame.data[i]);
    Serial3.print("   ");
    }
    Serial3.println();
    Serial3.println("------------------------------------------------------------------------------");
    Serial3.println();
  }
  
}// END of Loop()