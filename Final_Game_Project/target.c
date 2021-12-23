/* Includes ------------------------------------------------------------------*/
#include "Game.h"
#include "timer.h"
#include "main.h"
#include "target.h"
#include "DMA.h"
#include "magnets.h"
#include "MOTOR.h"

/* Macros ------------------------------------------------------------------*/
uint8_t Howmany;
uint32_t FirstDigit;
uint32_t SecondDigit;
uint32_t ThirdDigit;
uint32_t FourthDigit;
uint32_t FifthDigit;
uint32_t Current;
uint8_t Num[5];
uint32_t reading;
uint8_t drivedown;
uint8_t driveup;
uint8_t drivedownguard;

/* Module Variables ----------------------------------------------------*/

/* functions ------------------------------------------------------------------*/
//initialize all the values
void Targetinit(void)
{
    uint8_t i;
    Howmany = 0;
    drivedownguard =0;
    FirstDigit = 0;
    SecondDigit = 0;
    ThirdDigit = 0;
    drivedown = 0;
    driveup = 0;
    reading = returnADC3StoredValue();
    for (i =0; i<5;i++){
        Num[i] = 0;
        }
    //paste the code to drive all the motors down
}
//*****************************************************
//The main idea of the randomness generator is to extract different bits of the values from ADC and timers 
//and manipulate these numbers to create randomness
//*****************************************************

//use both the timer and pot to create randomness
// this function determines how many targets go up
void HowmanyTarget(void)
{
    Current = getTimer4();    //current time need to change later
    Howmany = (((Current%10+(reading%10))%10)%5)+2; //the number should range from 2 to 5
}

//use both the timer and pot to create randomness
//This function determines which target goes up
void NumTarget(void){
    //we will use potentometer as the randomness genenrator
    uint32_t i;

    uint8_t Input[5]; //create an array to store the values
    for (i = 0; i<5; i++){
        Input[i] = 0;
        Num[i] = 0;
        }
    //reading = returnADC3StoredValue();
    //compute the position of targets that should go up. The math equations have been determined in a way
    // to ensure the probability for each number is relatively equal
    FirstDigit =  (Current%10);
    SecondDigit = reading/10%10 + (Current%10) + reading/100%10;
    ThirdDigit = reading/100%10 + (Current/10%10)+ (Current%10) + (reading/1000%10);
    FourthDigit =  (Current%10) +2;
    FifthDigit = reading/10%10 + (Current%10)+1;
    Input[0] = FirstDigit;
    Input[1] = SecondDigit;
    Input[2] = ThirdDigit;
    Input[3] = FourthDigit;
    Input[4] = FifthDigit;
    //make sure the max num is 6 because we only have 6 targets
    for (i =0; i<Howmany;i++){
        while(Input[i] > 6){
            Input[i] = Input[i]/2;
            }
            Num[i] = Input[i];
        }
    //check if the array has the same elements, if so, then divide by 2, just to create more randomness
    if (Num[0] == Num[1]){
        Num[0] = Num[1]/2;}
    else if (Num[1] == Num[2]){
        Num[1] = Num[2]/2;}
    else if (Num[2] == Num[3]){
        Num[2] = Num[3]/2;
        }
    else if (Num[3] == Num[4]){
        Num[3] = Num[3]/2;
        }
        //ensure that we always have targets up in case that all the numbers are zero
        while(Num[0] == 0&& Num[1] == 0 && Num[2] == 0 && Num[3] == 0 && Num[4] == 0){
        Num[(Current%10)%4] = (Current%10)%4+1;
        Num[(Current%10)%3] = (Current%10)%3+2;
        Num[(Current%10)%3] = (Current%10)%3+3;
        }
    }
//This function goes through the numbers in the Num array and activate respective targets
void ActivateTarget(void){
    HowmanyTarget();
    NumTarget();
    uint32_t i,j,k,h;
    if(driveup ==1 && drivedownguard == 0){
    for (i = 0; i<5; i++){
        //debugPrint2(Num[i]);
        if (Num[i] != 0)
            switch(Num[i]){
                case 1: 
                    //drive up the first motor
                    setMotorPosition(1,1);
                    //debugPrint(221);

                break;
                case 2: 
                    //drive up the second motor
                    setMotorPosition(2,1);
                    //debugPrint(222);
                break;
                case 3: 
                    //drive up the third motor
                    setMotorPosition(3,1);
                    //debugPrint(223);
                break;
                case 4: 
                    //drive up the fourth motor
                    setMotorPosition(4,1);
                    //debugPrint(224);
                break;
                case 5: 
                    //drive up the fifth motor
                    setMotorPosition(5,1);
                    //debugPrint(225);
                break;
                case 6: 
                    //drive up the sixth motor
                    setMotorPosition(6,1);
                    //debugPrint(226);
                break;
                }
        }
//        uint32_t currTime = getTimer4();
//        while ((getTimer4() - currTime) <= 1)
//        {
//        }
// create some slight delays to ensure that the targets are fully up. 
// The original issue we had was that the target would have some backlash. By driving the motor for a little bit longer 
// would prevent the targets from recoiling
        for(j=0;j<50000000;j++)
            for(h=0;h<100000000;h++)
                k = k+1; 
        DeactivateUp();
        Deactivate(); // if all targets are down. Make sure that we don't drive down the new ones
    }
}  
//This function checks if all the targets are down if so, put up new targets 
void CheckTarget(void)
{
    uint8_t i;
    uint8_t down;
    down = 0;
    for(i =0;i<6;i++)
    {
        if(getMagneticSensorState(i)==0)
            down = down +1;
    }
    
    if(down ==6)
        ActivateTarget();
}
// The following functions are guard control functions. 
void Activate(void)
{
    drivedown = 1;
}
    
void Deactivate(void)
{
    drivedown = 0;
}

uint8_t CheckActivate(void)
{
    return drivedown;
}
//Check which targets are up and drive them down
void driveMotorsDown(void)
{
if (CheckActivate()==1)
        {    
      
        if (getMagneticSensorState(0) ==1){
            setMotorPosition(1,0);
            drivedownguard = 1;   
            //debugPrint(111);
            }
                    
        if (getMagneticSensorState(1) ==1){
            setMotorPosition(2,0);
            drivedownguard = 1;
            //debugPrint(112);     
            }
            
        if (getMagneticSensorState(2) ==1){
            setMotorPosition(3,0);
            drivedownguard = 1;
            //debugPrint(113);
            }
                    
        if (getMagneticSensorState(3) ==1){
            setMotorPosition(4,0);
            drivedownguard = 1;
            //debugPrint(114);
            }

        if (getMagneticSensorState(4) ==1){
            setMotorPosition(5,0);
            drivedownguard = 1;
            //debugPrint(115);
            }

        if (getMagneticSensorState(5) ==1){
            setMotorPosition(6,0);
            drivedownguard = 1;
            //debugPrint(116);
            }
            
        //deactivate when all the motors are down
        if(drivedownguard ==1 && getMagneticSensorState(0) ==0 && getMagneticSensorState(1) ==0 && getMagneticSensorState(2) ==0 && getMagneticSensorState(3) ==0 && getMagneticSensorState(4) ==0 && getMagneticSensorState(5) ==0 )
        {
            //debugPrint(1234567);
            DISABLE_ALL_MOTORS();
            Deactivate();
            drivedownguard = 0;
            }
        
        }
}
// The following functions are guard control functions. 
void ActivateUp(void)
{
    driveup = 1;
}
    
void DeactivateUp(void)
{
    driveup = 0;
}

uint8_t CheckActivateUp(void)
{
    return driveup;
}