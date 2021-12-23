/* Includes ------------------------------------------------------------------*/
#include "Game.h"
#include "magnets.h"

/* Macros ------------------------------------------------------------------*/


/* Module Variables ----------------------------------------------------*/

uint16_t score; //seconds
uint16_t numTargetsUp; //stores the number of targets up currently
uint16_t prevNumTargetsUp; //stores the number of targets up on previous check

/* functions ------------------------------------------------------------------*/

//initialize score for game to zero and other startup stuff
void initGame(void)
{
    score = 0;
    prevNumTargetsUp = 0;
    numTargetsUp = 0;
}

//up the current score
void incrementScore(uint16_t numHitDown)
{
    score = score + numHitDown;
}

//decrease the current score by one
void decrementScore(void)
{
    score = score - 1;
}

//get back the current score
uint16_t getScore(void)
{
    return score;
}

//returns the number of targets currently up
uint16_t getTargetUpCount(void)
{
    uint16_t numTargetsUp = 0;
    //loop through 6 sensors
    for (int i=0; i<6; i=i+1)
    {
        //add 1 for each target that is up
        numTargetsUp = numTargetsUp + getMagneticSensorState(i); //UNCOMMENT THIS!
    }
    //update the previous number of targets up
    prevNumTargetsUp = numTargetsUp; 
    
    return numTargetsUp;
}

//returns the number of targets currently up
uint16_t getPrevTargetUpCount(void)
{
    return prevNumTargetsUp;
}