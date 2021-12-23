/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EVENT_H_
#define __EVENT_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//define macro for max queue size
#define MAX_EVENT_QUEUE_SIZE 6


/*Instantiate---------------------------------------------------------*/

//create enum for the different events that can occur (that we care about)
typedef enum
{
    NO_EVENT,
    RISING_EDGE, //rising edge
    TIM1_OVERFLOW,  //timer 1 overflow
    TIM2_OVERFLOW  //timer 2 overflow
} event_type;

//create a struct to hold the specific event 
typedef struct ev_queue
{
    //create queue
    event_type queue[MAX_EVENT_QUEUE_SIZE];
    //size of queue variable
    uint16_t queueSize;
    //start of queue variable
    uint16_t queueStart;
    //end of queue variable
    uint16_t queueEnd;
} ev_queue;

/*Function definitions---------------------------------------------------------*/

//initialize the event queue
void initQueue(void);

//function to add event to queue
void addToQueue(event_type new_event);

//function to service the event at the front of the queue
void removeFromQueue(void);

//function to remove event from queue
void serviceEventQueue(void);

#ifdef __cplusplus
}
#endif

#endif /*__EVENT_H_ */