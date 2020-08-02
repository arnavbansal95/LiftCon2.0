#include "task.h"

static bool            taskVar_Critical = false;               // False: System Stop, True: Operational    
static mode_t          taskVar_mode = STARTUP;                 // Stores Current state of LiftOperation 
static mode_t          taskVar_mode_past = STARTUP;            // Stores Past state of LiftOperation 
static unsigned long   previousMillis[2] = {0, 0};             // will store last time 
static unsigned long   currentMillis[2];                       // will store current time
static const long      interval = 5000;                        // interval
static int             target_floor = -1;                      // Target Floor Level  (-1 for No Pending Input)
static int             current_floor = -1;                     // Current Floor Level (-1 for Undefined State)
static motor_t         taskVar_motorMode = WAITING;            // W: Waiting for Operation, R: Running
static motion_t        taskVar_motorMotion = IDLE;             // U: UP, D: DOWN, I: IDLE, H: HALT
static BreakDown       taskVar_BkDnVar;                        // Stores BreakDown info for Display
static uint8_t         taskVar_changeOver = 0;                 // Changeover from Maintainence Mode to Service Mode

bool CriticalCheck(void)
{
    static uint8_t taskVar_CriticalRes;
    taskVar_CriticalRes = ReadInput(INPUT_GLS) | ReadInput(INPUT_ESP) | ReadInput(INPUT_VSP); 
    taskVar_BkDnVar.ESP = ReadInput(INPUT_ESP);
    taskVar_BkDnVar.GRL = ReadInput(INPUT_GLS);
    taskVar_BkDnVar.VSP = ReadInput(INPUT_VSP);
    setMode(&taskVar_mode);              // Display Method
    setMotion(&taskVar_motorMotion);     // Display Method
    setBkDn(taskVar_BkDnVar);            // Display Method
    if(taskVar_mode == STARTUP)
    {
        if(taskVar_CriticalRes == LOW)
        {
            Serial.println(" Inital Critical Check: Passed ");
            Serial.println("     Service Mode Activated    ");
            taskVar_mode = SERVICE;
            taskVar_Critical = true;
        }
        if(taskVar_CriticalRes == HIGH)
        {
            Serial.println(" Inital Critical Check: Failed ");
            taskVar_Critical = false;
            digitalWrite(OUTPUT2_UPM, !taskVar_CriticalRes);
            digitalWrite(OUTPUT2_DNM, !taskVar_CriticalRes);
        }
        digitalWrite(OUTPUT2_MCN, !taskVar_CriticalRes);
    }
    else
    {
        if((taskVar_CriticalRes == LOW) && (!taskVar_Critical))
        {
            Serial.println("     Critical Check: Passed    ");
            taskVar_Critical = true;
        }
        if((taskVar_CriticalRes == HIGH) && (taskVar_Critical))
        {
            Serial.println("     Critical Check: Failed    ");
            taskVar_Critical = false;
            digitalWrite(OUTPUT2_UPM, !taskVar_CriticalRes);
            digitalWrite(OUTPUT2_DNM, !taskVar_CriticalRes);    
        }
        digitalWrite(OUTPUT2_MCN, !taskVar_CriticalRes);
    }
    if((!taskVar_Critical) && (taskVar_mode != BREAKDOWN))
    {
        taskVar_mode_past = taskVar_mode;
        taskVar_mode = BREAKDOWN; 
    }
    if((taskVar_Critical) && (taskVar_mode == BREAKDOWN))
    {
        taskVar_mode = taskVar_mode_past;
    }
    return(taskVar_Critical);
}

void CheckInterrupt(void)
{
    if(taskVar_mode == SERVICE || taskVar_mode == RESET || (taskVar_changeOver == 1))
    {   
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW) || (ReadInput(INPUT_RST) == LOW))
        {
            currentMillis[0] = millis();
            if (currentMillis[0] - previousMillis[0] >= interval) 
            {
                previousMillis[0] = currentMillis[0];
                if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
                {
                    if(taskVar_changeOver == 0)
                    {
                        Serial.println("   Maintenance Mode Activated  ");
                        taskVar_mode = MAINTENANCE;
                    }
                    taskVar_changeOver = 1;
                }
                if((ReadInput(INPUT_RST) == LOW) && (taskVar_mode == SERVICE))
                {
                    if((ReadInput(INPUT_FL0) == LOW) && (ReadInput(INPUT_FL1) == LOW) && (ReadInput(INPUT_FL2) == LOW) && (ReadInput(INPUT_FL3) == LOW))
                    {
                        Serial.println("       Reset Mode Activated    ");
                        taskVar_mode = RESET;
                    }
                }
            }
        }
        else
        {
            previousMillis[0] = millis();
            taskVar_changeOver = 0;
        }
    }
    if(taskVar_mode == MAINTENANCE || taskVar_changeOver == 2)
    {
        if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
        {
            currentMillis[1] = millis();
            if (currentMillis[1] - previousMillis[1] >= interval) 
            {
                previousMillis[1] = currentMillis[1];
                if((ReadInput(INPUT_BUP) == LOW) && (ReadInput(INPUT_BDN) == LOW))
                {
                    if(taskVar_changeOver == 0)
                    {
                        Serial.println("     Service Mode Activated    ");
                        taskVar_mode = SERVICE;
                    }
                    taskVar_changeOver = 2;
                }
            }
        }
        else
        {
            previousMillis[1] = millis();
            taskVar_changeOver = 0;
        }
    }
    SetTime();
}

bool DoorCheck(void)
{
    static uint8_t taskVar_DoorLimitStatus;
    taskVar_DoorLimitStatus = ReadInput(INPUT_DLS); 
    digitalWrite(OUTPUT2_DIN, taskVar_DoorLimitStatus);
    if(taskVar_DoorLimitStatus == LOW)
    {
        return(true);
    }
    else
    {
        Serial.println("        Door Open: Error       ");
        return(false);
    }
    
}

int GetTargetFloor(void)
{
    if(ReadInput(INPUT_FP0) == LOW)
    {
        return(0);
    }
    else if(ReadInput(INPUT_FP1) == LOW)
    {
        return(1);
    }
    else if(ReadInput(INPUT_FP2) == LOW)
    {
        return(2);
    }
    else if(ReadInput(INPUT_FP3) == LOW)
    {
        return(3);
    }
    /* else if(ReadInput(INPUT_FP4) == LOW)
    {
        return(4);
    }
    else if(ReadInput(INPUT_FP5) == LOW)
    {
        return(5);
    } */
    else
    {
        return(-1);
    }
    
}

int  GetCurrentFloor(void)
{
    if(ReadInput(INPUT_FL0) == HIGH)
    {
        return(0);
    }
    else if(ReadInput(INPUT_FL1) == HIGH)
    {
        return(1);
    }
    else if(ReadInput(INPUT_FL2) == HIGH)
    {
        return(2);
    }
    else if(ReadInput(INPUT_FL3) == HIGH)
    {
        return(3);
    }
    /* else if(ReadInput(INPUT_FL4) == HIGH)
    {
        return(4);
    }
    else if(ReadInput(INPUT_FL5) == HIGH)
    {
        return(5);
    } */
    else
    {
        return(-1);
    }
    
}


void LiftOperation(void)
{
    if(taskVar_Critical)
    {
        // Maintenance Mode
        if(taskVar_mode == MAINTENANCE)   
        {
            if(ReadInput(INPUT_BUP) == ReadInput(INPUT_BDN))
            {
                taskVar_motorMotion = IDLE;
                OutputMotion(taskVar_motorMotion, taskVar_mode);
            }
            else
            {
                if((ReadInput(INPUT_BUP) == LOW) || (ReadInput(INPUT_BDN) == LOW))
                {
                    delay(100);
                    if(ReadInput(INPUT_BUP) == LOW)
                    {
                        taskVar_motorMotion = UP;
                        OutputMotion(taskVar_motorMotion, taskVar_mode);
                    }
                    if(ReadInput(INPUT_BDN) == LOW)
                    {
                        taskVar_motorMotion = DOWN;
                        OutputMotion(taskVar_motorMotion, taskVar_mode);
                    }
                }
            }
        }
        // Reset Mode
        if(taskVar_mode == RESET)   
        {
            static bool DC, CC;
            DC = DoorCheck();
            CC = CriticalCheck();
            Serial.println(!DC && !CC);
            if(!DC && !CC)
            {
                taskVar_motorMotion = HALT;
                OutputMotion(taskVar_motorMotion, taskVar_mode);
            }
            if(DC && CC && (ReadInput(INPUT_FL0) == LOW))
            {
                taskVar_motorMotion = DOWN;
                OutputMotion(taskVar_motorMotion, taskVar_mode);
            }
            if(DC && CC && (ReadInput(INPUT_FL0) == HIGH))
            {
                digitalWrite(OUTPUT2_DNM, !ReadInput(INPUT_FL0));
                Serial.println("     Service Mode Activated    ");
                taskVar_mode = SERVICE; 
            }
        }
        if(taskVar_mode == SERVICE)   
        {
            static int TF;
            static int CF;    
            if(taskVar_motorMode == WAITING)
            {
                static bool DC, CC;
                DC = DoorCheck();
                CC = CriticalCheck();
                TF = GetTargetFloor();
                CF = GetCurrentFloor();
                Serial.print("      Target Floor:");
                Serial.println(TF);
                Serial.print("      Current Floor:");
                Serial.println(CF);
                if(DC && CC)
                {
                    taskVar_motorMotion = IDLE;
                }
                if((CF < 0) || (!DC))
                {
                    Serial.println("    Undefined State");
                    taskVar_motorMode = WAITING;
                }
                else
                {
                    if ((TF >= 0) && (TF != CF))
                    {
                        taskVar_motorMode = READY;
                    }       
                }
            }
            if((taskVar_motorMode == RUNNING) || (taskVar_motorMode == READY))
            {
                static bool DC, CC;
                CF = GetCurrentFloor();
                if (taskVar_motorMode == READY)
                {
                    Serial.print("      Target Floor:");
                    Serial.println(TF);
                    Serial.print("      Current Floor:");
                    Serial.println(CF); 
                }
                if ((TF >= 0) && (TF == CF))
                {
                    Serial.print("      Motion Floor:");
                    Serial.println(" REACHED");
                    taskVar_motorMode = WAITING;
                    taskVar_motorMotion = IDLE;
                    OutputMotion(taskVar_motorMotion);
                }
                if (((TF >= 0) && (TF < CF) && (taskVar_motorMode == READY)) || ((taskVar_motorMotion == DOWN) && (taskVar_motorMode = RUNNING)))
                {
                    if(ReadInput(INPUT_RLD) == LOW)
                    {
                        DC = DoorCheck();
                        CC = CriticalCheck();
                        if(DC && CC)
                        {
                            Serial.print("      Motion Floor:");
                            Serial.println(" DOWN");
                            taskVar_motorMode = RUNNING;
                            taskVar_motorMotion = DOWN;
                            OutputMotion(taskVar_motorMotion, taskVar_mode);
                        }
                        else
                        {
                            OutputMotion(HALT);
                        }
                    }
                    else
                    {
                        // Undefined State, take Notice
                        taskVar_motorMode = WAITING;
                        taskVar_motorMotion = IDLE;
                        OutputMotion(taskVar_motorMotion);
                    }
                }
                if (((TF >= 0) && (TF > CF) && (taskVar_motorMode == READY)) || ((taskVar_motorMotion == UP) && (taskVar_motorMode = RUNNING)))
                {
                    if(ReadInput(INPUT_RLU) == LOW) 
                    {
                        DC = DoorCheck();
                        CC = CriticalCheck();
                        if(DC && CC)
                        {
                            Serial.print("      Motion Floor:");
                            Serial.println(" UP");
                            taskVar_motorMode = RUNNING;
                            taskVar_motorMotion = UP;
                            OutputMotion(taskVar_motorMotion, taskVar_mode);
                        }
                        else
                        {
                            OutputMotion(HALT);
                        }
                    }
                    else
                    {
                        // Undefined State, take Notice
                        taskVar_motorMode = WAITING;
                        taskVar_motorMotion = IDLE;
                        OutputMotion(taskVar_motorMotion);
                    }
                }
            }
            setFloor(&TF, &CF);
            delay(200);
        }
    }        
}

