#include "global_var.h"

void getMode(mode_t* mode)
{
    globalVar_mode = *mode;
    Serial.println(globalVar_mode);
}

void getMotion(motion_t* motion)
{
    globalVar_motion = *motion;
}
