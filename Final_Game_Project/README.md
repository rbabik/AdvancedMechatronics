Overview & Header/CPP Files

To achieve our desired mechatronics behavior, our system used three inputs which were human mechanical input to drive the catapult, turning off the dial (potentiometer) to set the difficulty, and pressing the start button. Non-contact magnetic sensors were also used for each target to determine if the target states were upright as driven by six separate DC motors. With all of the electronic interactive components as well as while in the various system states, audio and visual feedback are provided through the LED strip, Processing screen, and tablet speakers.

To control the various subsystems, a detailed software package was developed. The software system utilized the following header and cpp files.

Main: Main file for the program which initializes all of the subsystems and then runs a while(1) loop to constantly monitor several systems and service events from the queue.

State Machine: The state machine runs the game by responding to events passed from the queue and entering the system into the proper state.

Event: The event file manages the queue and passses events in order to the state machine to handle.

Game: The game keeps track of the user’s score and the current overall status of targets while playing.

Interrupt: The interrupt file has functions to respond to ARR overflows on the target timer, rising edge detection on the start button, and magnetic sensor changes.

GPIO: The GPIO file handles the pin configurations for the start button, the analog potentiometer, the magnetic sensors, and the LED strip.

GPIO_motor: This file handles all of the pin configurations for the direction and enabling of the six motors.

ADC: This file manages the potentiometer by reading in the analog values to pass to the DMA.

DMA: The DMA stores values passed from the ADC which can then be retrieved in the Main while(1) loop to set the gameplay difficulty level.

Motor: This file manages enabling and disabling the motors and driving them both up and down.

Magnet: The magnet file is a wrapper file to the GPIO file as it gets the current state of the magnetic sensors.

Target: The target file manages all of the logic to determine which targets are currently active, decide how many and which to drive up, and provides current target states.

LED: The LED file is a wrapper file the GPIO functions related to driving the LED on and off.

Timer: The timer file handles both the global timer and the target timer through various get and set functions.

