Definitons
In this lab work, your task is to build a simple parking assistant. You are required to
create a circuit with an Arduino board, 2x16 LCD Display, Buzzer and Ultrasonic
Sensor. When you correctly assembled the circuit, you will need to write a source code
to implement parking assistant system using Arduino Software (IDE).
Experiment
You will design a circuit of buzzer and ultrasonic sensor. You will write an Arduino
program to monitor distance and indicate the distance by a buzzer. In the first row of
LCD Display, distance data (in metric units), which is acquired from ultrasonic
sensor will be displayed. In the second row of LCD Display, one of the following
texts will be displayed: “Too Far”, “Far”, “Close”, “Too Close”, “Crashed”.
Buzzing interval of the buzzer component will be directly proportional to distance
value. If distance is larger, buzzer will produce tone with longer silence intervals, if
distance is smaller, buzzer will buzz with shorter silence intervals. Moreover for each
interval different tones should be used.
Also when distance is 5 cm., buzzer will play a melody that resembles “Game Over”
melodies of old computer games.

Intervals are:
Distance > 1 m → “Too Far”
Distance ϵ [51 cm, 100 cm] → “Far”
Distance ϵ [21 cm, 50 cm] → “Close”
Distance ϵ [5 cm, 20cm] → “Too Close”
Distance <5 cm → “Crashed”

Your program should also display relevant description on the serial monitor window
in an interval of 2 seconds. The text format should be as follow:

Date: 17.06.2021 - Hour: 19:17:12 – Distance: 30 cm.
It is close.
------------------------------------
Date: 17.06.2021 - Hour: 19:17:14 – Distance: 15 cm.
It is too close.
------------------------------------
Date: 17.06.2021 - Hour: 19:17:16 – Distance: 2 cm.
It is crashed.
------------------------------------
