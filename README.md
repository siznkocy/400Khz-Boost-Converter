# 400Khz-Boost-Converter.

What this design entails:

    - frequnecy response PID controller.
    - 400kHz switching friequnecy (fs).
    - Attiny45.

Technonology:

    - ATMEL framework - Developing source code.
    - MATLAB/simscape - To tune the PID controller
    - Proteus 8 proffesional - Circuit design and source code troubleshooting.

This converter is set to boost input voltage from 5 to 9 volts and yield 15 volts output.
___________________________________________________________________________________________
_Fig.1: **Boost Converter output(GREEN), input(RED), and Feedback(BLUE) waveforms**_

![image](https://user-images.githubusercontent.com/78805923/139595978-2fbab535-78b0-40de-81d2-8177ea1fc05a.png)
____________________________________________________________________________________________
_Fig.2: **intergator clamping**_

![image](https://user-images.githubusercontent.com/78805923/139598214-67826ea3-7eba-4b74-a3a5-54245f6c48f2.png)

Figure 2, a code snippet can be seen. its limits the total value of the I (from PID).
What is on fig 2 is crucial for the controller without these boundaries controller response will be delayed.
____________________________________________________________________________________________

_Fig.3: **Boost converter Circuit-board reference schematics**_

![PCB_PCB_dc2dcBoostConverter_2021-05-30](https://user-images.githubusercontent.com/78805923/139595820-2ff03fc0-ec1a-4082-b722-916d37e336b9.png)
