#ifndef MYBINFILE_H
#define MYBINFILE_H

#define STM32F070

#if defined (STM32F070)
 #include "stm32f0xx.h"
#else
 #error "Target MCU header file is not defined or unsupported."
#endif


#define MYBINARYIMAGE_TERMINATION 0x00000000
#define MYBINARYIMAGE_START       0x00000000
#define MYBINARYIMAGE_FINISH      0x00001098
#define MYBINARYIMAGE_LENGTH      0x00001098

extern const unsigned long MyBinaryImage_termination;
extern const unsigned long MyBinaryImage_start;
extern const unsigned long MyBinaryImage_finish;
extern const unsigned long MyBinaryImage_length;
extern const unsigned char MyBinaryImage[];
#endif /* MYBINFILE_H */





