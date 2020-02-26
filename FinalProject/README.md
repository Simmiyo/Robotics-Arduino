- HARDWARE: 
     1. 2x Stepper Motors taken from old DVD drives: for moving the pen left and right, and the paper forward and backwards
     2. 2x Servo Motors: for pulling the pen up and down with the help of some strings
     3. 2x L293D ICs Motor drivers: for an easier control of the dvd's stepper motors
     4. 2x BreadBoards (3x optionally)
     5. 2x Supply Modules HW-131: for powering the stepper motors, as the usb connected Arduino Uno does not give enough for that task
     6. 2x Power Adapters
     7. 1x 1k ohms Rezsitor
     8. 1x 330 ohms Rezistor
     9. 1x Blue LED: brings attention to the user that the color needs to be changed
     10. 1x Active Piezzo Buzzer: same task as the Blue LED
     11. 1x Arduino Uno: controls all the mechanisms
     
     https://ibb.co/b374dFK (an image with the hardware)
     
     Video: https://youtu.be/lbaO_4wK41Q
     
     
 - HOW TO USE:
     - As an ordinary user, you don't really need to concern about following an amount of complicated steps in order to bring the mechanism to life. Everything you are expected to fulfill consists in loading an image and attaching a gCode file to the program, which will guide the moves of the device towards plotting the your picture.
     It is warmly recommanded the usage of Inkscape, a free open-source software, that allows you to create a sketch for the machine to reproduce. You can find [here](https://inkscape.org/release/inkscape-0.92.4/) (Suggestion: version 0.48.5). However, if you have never worked with a similar software before, here are some tutorials to teach you about printing text or various icons on Inkscape [here](https://youtu.be/KD50yDop8kQ) and [here](https://youtu.be/7BFa0k6FJcc).
     - To upload the gCode files, here is an useful extension [here](https://github.com/martymcguire/inkscape-unicorn). As color commands are not native to gCode, some files will need to be replaced in the extension with others found in the unicorn folder within this repository. These files have been specifically modified in order to work with this CNC MACHINE(i.e. added color commands).
     - Finally, you will have to use the gctrl.pde processing program, which extracts the gCode files and uploads them to the Ardunio, the location they are processed. Use [Proccesing](https://processing.org/) and the gctrl.pde aplication found [here](https://github.com/damellis/gctrl/blob/master/gctrl.pde). Afterwards, the only task left is to start Proccesing, uploading the gctrl.pde aplication to it.
 This should bring up the following window: https://cdn.instructables.com/FAB/UNTL/IHP6UI22/FABUNTLIHP6UI22.LARGE.jpg?auto=webp&frame=1&width=528&fit=bounds
     From the opned window you can use:
          - the arrow keyes - to move the plotter along the X and Y axis;
          - the PageUp and PageDown - to lift the pen and bring it back down;
          - 0 - to set home to the current direction (i.e. establish the starting point); 
          - p - to select the port that is connected to Arduino Uno;
          - g - to upload the desired gCode File. 
     - Once the gCode file is uploaded, the DRAWING MACHINE will begin doing its job. The machine offers you the opportunity to change the color of the ink by pausing the drawing process. This break is alerted by the Blue LED, which lights up, and by the Buzzeer, which plays a tune of 1K HZ for the duration of 10 sec (the time in which the user is allowed to change the color). After this mentioned period of time, the Led and the buzzer turn off and the plotter continues drawing from where it left.  
