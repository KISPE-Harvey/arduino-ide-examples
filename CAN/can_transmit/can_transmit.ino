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

  Last updated 02/08/2024 Harvey Nixon
*/
#define CAN1_TX_PIN PD_1
#define CAN1_RX_PIN PD_0

static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 2560 ;
static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 0 ; // FDCAN2 not used

#include <ACANFD_STM32.h>

static ACANFD_STM32_FIFO gBuffer ;

void setup() {
  gBuffer.initWithSize (100) ;
  pinMode (LED_BUILTIN, OUTPUT) ;
  Serial.begin (115200);
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
  Serial.println("    CAN FD Transmit Example");
  delay(2000);

  ACANFD_STM32_Settings settings (1000 * 1000, DataBitRateFactor::x4) ;
  settings.mModuleMode = ACANFD_STM32_Settings::NORMAL_FD; // Found in CANFDMessage.h lines 53 - 58

  Serial.print ("Bit Rate prescaler: ") ;
  Serial.println (settings.mBitRatePrescaler) ;
  Serial.print ("Arbitration Phase segment 1: ") ;
  Serial.println (settings.mArbitrationPhaseSegment1) ;
  Serial.print ("Arbitration Phase segment 2: ") ;
  Serial.println (settings.mArbitrationPhaseSegment2) ;
  Serial.print ("Arbitration SJW: ") ;
  Serial.println (settings.mArbitrationSJW) ;
  Serial.print ("Actual Arbitration Bit Rate: ") ;
  Serial.print (settings.actualArbitrationBitRate ()) ;
  Serial.println (" bit/s") ;
  Serial.print ("Arbitration Sample point: ") ;
  Serial.print (settings.arbitrationSamplePointFromBitStart ()) ;
  Serial.println ("%") ;
  Serial.print ("Exact Arbitration Bit Rate ? ") ;
  Serial.println (settings.exactArbitrationBitRate () ? "yes" : "no") ;
  Serial.print ("Data Phase segment 1: ") ;
  Serial.println (settings.mDataPhaseSegment1) ;
  Serial.print ("Data Phase segment 2: ") ;
  Serial.println (settings.mDataPhaseSegment2) ;
  Serial.print ("Data SJW: ") ;
  Serial.println (settings.mDataSJW) ;
  Serial.print ("Actual Data Bit Rate: ") ;
  Serial.print (settings.actualDataBitRate ()) ;
  Serial.println (" bit/s") ;
  Serial.print ("Data Sample point: ") ;
  Serial.print (settings.dataSamplePointFromBitStart ()) ;
  Serial.println ("%") ;
  Serial.print ("Exact Data Bit Rate ? ") ;
  Serial.println (settings.exactDataBitRate () ? "yes" : "no") ;

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

  pinMode(USER_BTN, INPUT);
  // USER_BTN is pin PC13
  
  // The LED pins get set out outputs so we can toggle them on or off
  pinMode(PB0,OUTPUT);  // Green LED
  pinMode(PE1,OUTPUT);  // Orange LED
  pinMode(PB14,OUTPUT); // Red LED

}

// class CANMessage {
//   public : uint32_t id = 0 ;  // Frame identifier
//   public : bool ext = false ; // false -> standard frame, true -> extended frame
//   public : bool rtr = false ; // false -> data frame, true -> remote frame
//   public : uint8_t idx = 0 ;  // This field is used by the driver
//   public : uint8_t len = 0 ;  // Length of data (0 ... 8)
//   public : union {
//     uint64_t data64        ; // Caution: subject to endianness
//     int64_t  data_s64      ; // Caution: subject to endianness
//     uint32_t data32 [2]    ; // Caution: subject to endianness
//     int32_t  data_s32 [2]  ; // Caution: subject to endianness
//     uint16_t data16 [4]    ; // Caution: subject to endianness
//     int16_t  data_s16 [4]  ; // Caution: subject to endianness
//     float    dataFloat [2] ; // Caution: subject to endianness
//     int8_t   data_s8 [8]   ;
//     uint8_t  data    [8] = {0, 0, 0, 0, 0, 0, 0, 0} ;
//   } ;

void loop() {

  const uint8_t sendBufferIndex = 0 ;
//--- Send frame
    CANFDMessage frame ;
    // Layout the frame structure
    // ID, FRAMEs ETC

    frame.idx = sendBufferIndex ;
    const uint32_t r = pseudoRandomValue () ;
    frame.ext = (r & (1 << 29)) != 0 ;
    frame.ext = (0) ;
    frame.type = CANFDMessage::Type (1);
    //frame.type = CANFDMessage::Type (r << 30) ;
    //frame.type = CANFDMessage::CANFD_NO_BIT_RATE_SWITCH  ;
    //frame.id = & r 0x1FFFFFFFU ;
    frame.id = 0x1FFFFFFFU ;
  if (gOk && (!gBuffer.isFull ()) && fdcan1.sendBufferNotFullForIndex (sendBufferIndex)) {
    if (frame.ext) {
      gExtendedFrameCount += 1 ;
    }else{
      gStandardFrameCount += 1 ;
      frame.id &= 0x7FFU ;
    }
    switch (frame.type) {
    // case CANFDMessage::CAN_REMOTE :
    //   gCANRemoteFrameCount += 1 ;
    //   frame.len = pseudoRandomValue () % 9 ;
    //   break ;
    case CANFDMessage::CAN_DATA :
      gCanDataFrameCount += 1 ;
      //frame.len = pseudoRandomValue () % 9 ;
      frame.len = 5; // random number between 1 and 8 
      for (uint32_t i=0 ; i<frame.len ; i++) {
        //frame.data [i] = uint8_t (pseudoRandomValue ()) ;
        frame.data [i] = uint8_t (i) ;
      }
    break ;
    // case CANFDMessage::CANFD_NO_BIT_RATE_SWITCH :
    //   gCanFDNoBRSDataFrameCount += 1 ;
    //   frame.len = CANFD_LENGTH_FROM_CODE [pseudoRandomValue () & 0xF] ;
    //   for (uint32_t i=0 ; i<frame.len ; i++) {
    //     frame.data [i] = uint8_t (pseudoRandomValue ()) ;
    //     //frame.data [i] = uint8_t (i) ;
    //   }
    //   break ;
    // case CANFDMessage::CANFD_WITH_BIT_RATE_SWITCH :
    //   gCanFDWithBRSDataFrameCount += 1 ;
    //   frame.len = CANFD_LENGTH_FROM_CODE [pseudoRandomValue () & 0xF] ;
    //   for (uint32_t i=0 ; i<frame.len ; i++) {
    //     frame.data [i] = uint8_t (pseudoRandomValue ()) ;
    //     //frame.data [i] = uint8_t (i) ;
    //   }
    //   break ;
    }
    //gBuffer.append (frame) ;
    const uint32_t sendStatus = fdcan1.tryToSendReturnStatusFD (frame) ;
    if (sendStatus == 0) {
      gSentCount += 1 ;
    }else{
      gOk = false ;
      Serial.print ("Send status error 0x") ;
      Serial.println (sendStatus, HEX) ;
    }
  }





} // END of Loop()
