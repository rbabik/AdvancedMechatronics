/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EVENT_H_
#define __EVENT_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//define macro for max queue size
#define MAX_EVENT_QUEUE_SIZE 30


/*Instantiate---------------------------------------------------------*/

//create enum for the different events that can occur (that we care about)
typedef enum
{
    FILL_EVENT,
    RISING_EDGE_SENSOR, //one for each mag sensor or just one needed?
    RISING_EDGE_START_BUTTON, 
    INIT_GAME_TIMER_OVERFLOW,
    GAME_PLAY_TIMER_OVERFLOW,
    TARGET_TIMER_OVERFLOW,
    RESULTS_TIMER_OVERFLOW,
    NO_EVENT

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