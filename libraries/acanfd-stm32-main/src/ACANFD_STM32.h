//----------------------------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------------------------

#ifdef ARDUINO_NUCLEO_H743ZI2
  #include "ACANFD_STM32_NUCLEO_H743ZI2-objects.h"
#elif defined(ARDUINO_NUCLEO_H753ZI)
  #include "ACANFD_STM32_NUCLEO_H753ZI-objects.h" 
 #elif defined(ARDUINO_GENERIC_H753ZITX)
  #include "ACANFD_STM32_GENERIC_H753ZITX-objects.h"     
#elif defined(ARDUINO_GENERIC_H753VITX)
  #include "ACANFD_STM32_GENERIC_H753VITX-objects.h"    
#elif defined (ARDUINO_NUCLEO_G431KB)
  #include "ACANFD_STM32_NUCLEO_G431KB-object.h"
#elif defined (ARDUINO_NUCLEO_G474RE)
  #include "ACANFD_STM32_NUCLEO_G474RE-objects.h"
#else
  #error "Unhandled Nucleo Board"
#endif

//----------------------------------------------------------------------------------------
