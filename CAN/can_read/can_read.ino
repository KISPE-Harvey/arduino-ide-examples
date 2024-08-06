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

  Last updated 05/08/2024 Harvey Nixon
*/
#define CAN1_TX_PIN PD_1
#define CAN1_RX_PIN PD_0

static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 2560 ;
static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 0 ; // FDCAN2 not used

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

void floatToCharArray(float value, char* buffer, int bufferSize, int width, int precision){
  dtostrf(value, width, precision, buffer);
}

static uint32_t pseudoRandomValue (void) {
  static uint32_t gSeed = 0 ;
  gSeed = 8253729U * gSeed + 2396403U ;
  return gSeed ;
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
  Serial.println("    CAN FD Read Example");
  delay(2000);
    ACANFD_STM32_Settings settings (1000 * 1000, DataBitRateFactor::x4) ;
  settings.mModuleMode = ACANFD_STM32_Settings::NORMAL_FD; // Found in CANFDMessage.h lines 53 - 58

    const uint32_t errorCode = fdcan1.beginFD (settings) ;

  Serial.print ("Message RAM required minimum size: ") ;
  Serial.print (fdcan1.messageRamRequiredMinimumSize ()) ;
  Serial.println (" words") ;
 
 if (0 == errorCode) {
    Serial.println ("can configuration ok") ;
  }else{
    Serial.print ("Error can configuration: 0x") ;
    Serial.println (errorCode, HEX) ;
  }
}

void loop() {
  //--- Receive frame
  CANFDMessage receivedFrame ;
  if (gOk && fdcan1.receiveFD0 (receivedFrame)) {
    CANFDMessage storedFrame ;
    //gOk = gBuffer.remove (storedFrame) ;
    //if (!gOk) {
      //Serial.println ("gBuffer is empty") ;
    //}else{
      gReceiveCount += 1 ;
      bool sameFrames = storedFrame.id == receivedFrame.id ;
      if (sameFrames) {
        sameFrames = storedFrame.type == receivedFrame.type ;
      }
      if (sameFrames) {
        sameFrames = storedFrame.len == receivedFrame.len ;
      }
      if (storedFrame.type != CANFDMessage::CAN_DATA) {
        for (uint32_t i=0 ; (i<receivedFrame.len) && sameFrames ; i++) {
          sameFrames = storedFrame.data [i] == receivedFrame.data [i] ;
        }
      }
      //if (!sameFrames) {
        //gOk = false ;
      Serial.println();
      Serial.println("------------------------------------------------------------------------------");
      Serial.println();
      Serial.println("Reveived: ");

        for (uint32_t i=0 ; (i<receivedFrame.len); i++) {
          Serial.print(receivedFrame.data[i] );Serial.print(" ");
        }
      Serial.println();
      Serial.println("------------------------------------------------------------------------------");
      Serial.println();

        //Serial.println(String(receivedFrame.data[8]));
        // Serial.println ("Receive error") ;
        // Serial.print ("  IDF: 0x") ;
        // Serial.print (storedFrame.id, HEX) ;
        // Serial.print (" :: 0x") ;
        // Serial.println (receivedFrame.id, HEX) ;
        // Serial.print ("  TYPE: ") ;
        // Serial.print (storedFrame.type) ;
        // Serial.print (" :: ") ;
        // Serial.println (receivedFrame.type) ;
        // Serial.print ("  LENGTH: ") ;
        // Serial.print (storedFrame.len) ;
        // Serial.print (" :: ") ;
        // Serial.println (receivedFrame.len) ;
      }
    //}
  
  }

//}
