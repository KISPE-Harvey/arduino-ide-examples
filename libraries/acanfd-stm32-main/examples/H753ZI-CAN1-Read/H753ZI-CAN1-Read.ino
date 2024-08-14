#define CAN1_TX_PIN PD_1
#define CAN1_RX_PIN PD_0

static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 2560 ;
static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 0 ; // FDCAN2 not used

#include <ACANFD_STM32.h>

static ACANFD_STM32_FIFO gBuffer ;
static bool gOk = true ;

uint32_t interval = 3000;//1000; // time between sending out in ms - basically like delay() but doesnt freeze everything
uint32_t currentMillis, prevMillis = 0;


void setup() {
  gBuffer.initWithSize (100) ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  Serial.begin (115200);
  delay(2000);

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
  
}// END of Loop()