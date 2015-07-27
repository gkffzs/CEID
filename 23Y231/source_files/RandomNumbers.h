#ifndef RANDOM_NUMBERS_H
#define RANDOM_NUMBERS_H

/* Function that generates random integers. */
inline unsigned int getIntRandomNumber(int nLow, int nHigh){
    return (rand() % (nHigh - nLow + 1)) + nLow;
}

/* Function that generates random floats. */
inline float getFloatRandomNumber(int nLow, int nHigh){
    return static_cast <float> (getIntRandomNumber(nLow,nHigh)) / static_cast <float> (10);
}

#endif


