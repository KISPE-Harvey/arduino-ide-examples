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
int count = 0;

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

static uint32_t pseudoRandomValue (void) {
  static uint32_t gSeed = 0 ;
  gSeed = 8253729U * gSeed + 2396403U ;
  return gSeed ;
}

// Have the user choose/input the data they want to send
// have it send when the user presses the button

CANFDMessage frame ;

char str_data[8];

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

  frame.ext = (0) ;

  // state where is in and what it means
  frame.type = CANFDMessage::Type (1);

  showMenu();

}

void showMenu(){
  Serial.println("Options:");
  Serial.println("id : Generate a new ID - default is 0x17C");
  Serial.println("dlc : Change the size of the data being sent in bytes between 1 - 8 - default and maximum is 8");
  Serial.println("data : Change the Data to send - input a float or integer");
  Serial.println("Enter the aspect you would like to change");
}

void changeID() {
  const uint32_t r = pseudoRandomValue () ;
  frame.id = r & 0x1FFFFFFFU ;
}

void DataInput(){
  Serial.println("Enter a value to send integrer, string or float: ");
  //str_data = Serial.read();

}

void changeDLC(){
  

  int new_dlc = Serial.read();
  if (new_dlc != 1 || new_dlc != 2 || new_dlc != 3 || new_dlc != 4 || new_dlc != 5 || new_dlc != 6 || new_dlc != 7 || new_dlc != 8){
    Serial.println("Invalid input");
    ++count;
    if (count > 1){
      showMenu();
    }
    changeDLC();
  } else {
    frame.len = new_dlc;
  }

}

void CheckForSerialCommand(){
  if (Serial.available() != 0){
    char choice = Serial.read();

    switch (choice){
      case '\n':
      case '\r':
        break;
      case 'id':
      case 'ID':
        Serial.println("Enter new length between 1 - 8 bytes");
        changeID();
        showMenu();  
        break;
      case 'dlc':
      case 'DLC':
        changeDLC();
        showMenu();
        break;  
      case 'data':
      case 'DATA':
        DataInput();
        break;
      default:
        showMenu();
        break;
    }



  }

}


void loop() {
  CheckForSerialCommand();



}
