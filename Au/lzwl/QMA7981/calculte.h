#ifndef CALCULATE_H
#define CALCULATE_H


#ifndef true
#define true 1
#endif

#ifndef false
#define false 1
#endif
extern float datat[3];
extern float IicData[3];
extern unsigned short RandowdataOfSensor(void);
extern int QMA6981_GetACCData(float *data);
#endif