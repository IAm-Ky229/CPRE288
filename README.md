# CPRE 288 (Spring 2020)
This was introductory course in embedded systems. We programmed Roomba sensors to perform specific tasks in each lab. The end goal was to create a Roomba that could navigate using the sensors on the robot alone. The end of this semester produced some challenges to completing the final project as COVID caused everything to suddently go online.

###### Lab 1
Display a rotating banner on the LCD screen that is 20 characters wide. Useful for displaying data in real time.

###### Lab 2
Start to move the Roomba. Robot should be able to process a hit on its bumpers and be able to "go around" the obstacle.

###### Lab 3
Process pushbutton events and display different messages on the LCD depending on the pushed button.

###### Lab 4
Communicate with the Roomba via PuTTy. Pressing a key on the computer should result in an event occurring with the roomba (distance measurment, movement, etc).

###### Lab 5
Two-way communication with universal asynchronous receiver-transmitter (UART) / PuTTy. Send characters from the Roomba to the computer, and display them in the PuTTy terminal.

###### Lab 6
Convert an analog signal to a digital signal. Calibrate an IR sensor by taking measurments and plotting data to find the pattern in distance measurment.

###### Lab 7
Use a PWM signal to measure distance. A PING sensor sends out a wave travelling at the speed of sound, that will eventually come back and "hit" the sensor. Use the modulated wave's "high" time to determine distance from objects.

###### Lab 8
Begin using the servo. Move the servo to a specific location (number of degrees). Important lab as moving the servo allows us to move the IR sensor and PING sensor. The next lab utilized the servo functionality.

###### Lab 9
Use the servo to move the IR and PING sensor. By "rotating" the IR and PING sensors, we can determine the width of objects in front of the robot. We used the IR sensor to locate items, and the PING sensor to measure their actual distance. The arclength formula came in very handy for this lab, essentially using an angle and a radius to approximate object width.
