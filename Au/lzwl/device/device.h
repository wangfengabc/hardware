#ifndef DEVINCE_H_
#define DEVINCE_H_

#define DEVICEOfSWRITER
#define deviceOfAUX_M 4

#include "compiler.h"

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define FIRMWARE_VERSION_ID_LEN 32    //°æ±¾
static unsigned char RW_FIRMWARE_VERSION_ID[FIRMWARE_VERSION_ID_LEN]={'L','D','S','W','-','R','F','I','D','-','R','W','2','.','3','.','0','1','-','2','0','1','8','0','3','0','6','_','b','e','t','a'};

#ifdef DEVICEOfSMARTNODE
#include "tagdevice.h"
#define DEVofChannel    1
#endif

#ifdef DEVICEOfDWRITER
#include "rwdevice.h"
#define DEVofChannel    1
#endif

#ifdef DEVICEOfRELAYER
#include "redevice.h"
#define DEVofChannel    2
#endif

#ifdef DEVICEOfBASESTATION
#include "bsdevice.h"
#define DEVofChannel    2
#endif

#ifdef  DEVICEOfLOCATOR
#include "locdevice.h"
#define DEVofChannel    4
#endif

#ifdef deviceOfAUX_M
#include "auxdevice.h"
#define DEVofChannel    1
#endif

#ifdef DEVICEOfHANDLE
#include "hdevice.h"
#endif

#endif