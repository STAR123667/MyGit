
#ifndef STM32_ENCODER_H
#define STM32_ENCODER_H



/******************************************************************************/
void Encoder_init(void);
void Encoder_Index_init(void);
float getAngle_ABZ(void);
float getVelocity_ABZ(void);
/******************************************************************************/
extern  unsigned char index_found;
extern  unsigned char index_needsSearch;
extern  float velocity_index_search;
/******************************************************************************/


#endif
