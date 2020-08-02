#include "global_var.h"

static mode_t* globalVar_mode;
static motion_t* globalVar_motion;
static BreakDown globalVar_BkDnVar;
static Floor globalVar_Floor;
static bool globalVar_DoorStatus;   

void setMode(mode_t* mode)
{
    globalVar_mode = mode;
}

void setMotion(motion_t* motion)
{
    globalVar_motion = motion;
}

void setBkDn(BreakDown BkDn)
{
    globalVar_BkDnVar.ESP = BkDn.ESP;
    globalVar_BkDnVar.GRL = BkDn.GRL;
    globalVar_BkDnVar.VSP = BkDn.VSP;
}

void setFloor(int* TF, int* CF)
{
    globalVar_Floor.CF = *CF;
    globalVar_Floor.TF = *TF;
}

void setDoorStatus(bool *doorStatus)
{
    globalVar_DoorStatus = *doorStatus;
}

mode_t getMode(void)
{
    return(*globalVar_mode);
}

motion_t getMotion(void)
{
    return(*globalVar_motion);
}

BreakDown getBkDn(void)
{
    return(globalVar_BkDnVar);
}

Floor getFloor(void)
{
    return(globalVar_Floor);
}

bool getDoorStatus(void)
{
    return(globalVar_DoorStatus);
}