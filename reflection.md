Self-Driving Car Engineer Nanodegree Program

Understand P, I, D values
P
This reflects how much the system is away from the desired state.
This has linear contribution to the control output( turn= KP * error).

This should also be the main source of error in the control output.

I
This reflects the error cause by noise or sensor or drift.

D
This reflects how fast the system state is changing away from the desired state. Large D value allows fast reaction to the environment.


Choose P, I, D values

First I set I to 0 because there's no error in the measurement of the car from the center of the lane.
Then I choose a reasonable P value, around 0.1 as the starting point. D value is gradually added to check the performance.

