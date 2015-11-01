// controller.h - header for embedded control code
#ifndef _PID_H
#define _PID_H

#define PID_NUM_OLD_VALUES 3
typedef struct {
    // everything is here is supposed to be private
    // but for setting up the constants we'll access the members directly
    double P, I, D;
    double Const_P, Const_I, Const_D;
    double Alpha; // decay constant for integral term
    
    int num_values; // number of values read
    double old_values[PID_NUM_OLD_VALUES];
} Controller_PID;

inline void PID_Reset (Controller_PID* PID);
void PID_Update (Controller_PID* PID, double value);
inline double PID_Output (Controller_PID* PID);

#endif
