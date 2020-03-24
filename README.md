# LCD_Driver_AVR_

It is driver for LCD_Matrix suitable for Atmega32
the project include src code of driver and hex file (for Atmega32) 
the driver has flexibility to connect LCD 5x7matrix (D4-D7, 4bit) "OR" 5x7matrix (D0-D7, 8bit)


I separated the Project into: header file "prototype.h" -- implementation file "prototype.c" -- MainProgram "main.c"

For defines(that is where you can customize POTRs & Pins) , implementation of needed function and main program respectively.





NOTE: attach VEE to potentiometer to Adjust contrast in simulation I attached this to GND 
Also,...I assumed that I will be write to screen only so I attached R/W pin to GND
