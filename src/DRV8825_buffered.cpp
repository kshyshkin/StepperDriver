/*
 * DRV8825 - Stepper Motor Driver Driver
 * Indexer mode only.

 * Copyright (C)2015 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include "DRV8825_buffered.h"


DRV8825_buffered::DRV8825_buffered(short steps, short dir_pin, short step_pin, short enable_pin, uint16_t *buffer)
:DRV8825(steps, dir_pin, step_pin, enable_pin)
{
	this->buffer = buffer;
	this->enable_active_state = LOW;
}

/*
 * Initialize pins, calculate timings etc
 */
void DRV8825_buffered::begin(float rpm, short microsteps){
    *(this->buffer) |= 1 << dir_pin; // Dir pin HIGH
    *(this->buffer) &= ~(1 << step_pin); //Step pin LOW

    if IS_CONNECTED(enable_pin){
        disable();
    }

    this->rpm = rpm;
    setMicrostep(microsteps);

    enable();
}

/*
 * Enable/Disable the motor by setting a digital flag
 */
void DRV8825_buffered::enable(void){
    if IS_CONNECTED(enable_pin){
    	if (enable_active_state == HIGH)
    		*(this->buffer) |= 1 << enable_pin; // set enable HIGH
    	else
    		*(this->buffer) &= ~(1 << enable_pin); // set enable LOW
    };
    delayMicros(2);
}

void DRV8825_buffered::disable(void){
    if IS_CONNECTED(enable_pin){
        if (enable_active_state == HIGH)
    		*(this->buffer) &= ~(1 << enable_pin); // set enable LOW
    	else
    		*(this->buffer) |= 1 << enable_pin; // set enable HIGH
    }
}

void DRV8825_buffered::stepStart(void){
	*(this->buffer) |= 1 << step_pin;
}

void DRV8825_buffered::stepFinish(void){
	*(this->buffer) &= ~(1 << step_pin);
}