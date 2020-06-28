#ifndef GLOBAL_VAR_H_
#define GLOBAL_VAR_H_

typedef enum
{
    SERVICE,
    MAINTENANCE,
    RESET,
    STARTUP,
    BREAKDOWN
} mode_t;

typedef enum
{
    UP,
    DOWN,
    IDLE
} motion_t;

static mode_t globalVar_mode = STARTUP;
static motion_t globalVar_motion = IDLE;

#endif