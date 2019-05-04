/*
 * DRV8825 - Stepper Motor Driver Driver (A4988-compatible)
 * Indexer mode only.
 *
 * Copyright (C)2015 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#ifndef DRV8825_BUFFERED_H
#define DRV8825_BUFFERED_H
#include <Arduino.h>
#include "DRV8825.h"

class DRV8825_buffered : public DRV8825 {

private:
    uint16_t *buffer;

public:
    DRV8825_buffered(short steps, short dir_pin, short step_pin, short enable_pin, uint16_t *buffer);
    void begin(float rpm=60, short microsteps=1);
    void stepStart();
    void stepFinish();
    void enable(void) override;
    void disable(void) override;
};
#endif // DRV8825_BUFFERED_H
