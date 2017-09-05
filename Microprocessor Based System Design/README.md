## Introduction
The DE0 Development and Education board is designed in a compact size with all the essential tools for novice users to gain knowledge in areas of digital logic, computer organization and FPGAs. It is equipped with Altera Cyclone III 3C16 FPGA device, which offers 15,408 LEs. The board provides 346 user I/O pins, and is loaded with a rich set of features that makes it suitable to be used for advanced university and college courses, as well as the development of sophisticated digital systems. The DE0 combines the Altera low-power, low-cost, and high performance Cyclone III FPGA to control the various features of the DE0 Board. The DE0 Development Board includes software, reference designs, and accessories required to ensure the user simple access in evaluating their DE0 Board.

## About This Project
### Lab 1
* Objective
	* To gain familiarity with the Cortex-M software development tool
	* To understand the access of memory-mapped I/O components for Cortex-M processor.
	* To develop assembly programs that perform simple I/O functions for Cortex-M processor.
* Tasks
	* Exercise A
		* Configure the µVision4 IDE for the DE0/Cortex-M1 target platform, and then download the sample assembly program, Blink_LED.s, to the target platform.
	* Exercise B
		* Write an assembly program to blink the odd and even LEDs in an alternate pattern. 
	* Exercise C
		* Modify your earlier assembly program that alternately blinks the odd/even LEDs to also sample the slide switch position. Add the code such that when a particular slide switch is on the ‘UP’ position, the corresponding LED will also remain turn on (i.e. no blinking). 
	* Exercise D
		* Modify your earlier assembly program that alternately blinks the odd/even LEDs to also sample the slide switch position. Add the code such that when a particular slide switch is on the ‘UP’ position, the corresponding LED will also remain turn on (i.e. no blinking). 
		

### Lab 2
* Objective
	* To familiarize and develop C language based embedded programs to access memory-mapped I/O devices for Cortex-M processor.
* Tasks
	* Exercise A
		* Repeate Lab 1 Exercise A in C language
	* Exercise B
		* Repeate Lab 1 Exercise B in C language
	* Exercise C
		* Repeate Lab 1 Exercise C in C language
	* Exercise D
		* Repeate Lab 1 Exercise D in C language 
	* Exercise E
		* Combine all functions

### Lab 3
* Objective
	* To familiarize with operations of the I2C serial interfaces through programming exercises to access various peripherals available on the TAB platform
* Tasks
	* Exercise A
		* Display character on the single-digit 7-Seg display on the TAB. The following figure shows the circuit connection of the display.
	* Exercise B
		* Unlike the expander interface IC, typical I/O device will contain registers that allow the microprocessor to configure the device, to control the device operation as well as to query (status) information about the device. The TAB platform contains an I2C digital temperature sensor - TMP100. This device uses a semiconductor temperature sensor with on-chip ADC to convert and output temperature information in digital value through its I2C interface pins
		* Access the Configuration Register (number = 01h) and the Temperature Register (number = 00h). However, these two registers can only be accessed indirectly through another register, the Pointer Register. To access a register in the TMP100, its register number must be written/stored into the Pointer Register first. The register number for the Pointer Register is by default the first byte transferred after the I2C slave address byte with the R/W bit set to LOW (i.e. the 2nd byte in the I2C data transfer sequence after performing a slave address data byte with Write command). Subsequent read or write operation(s) will then be performed on the register based on the register number stored in the Pointer Register. The Configuration Register (01h) allows the user to configure the resolution of the sensor. In this Lab, the sensor will be configured to have 12-bit resolution (by having value 60h written into the Configuration Register. (Refer to TMP100’s datasheet for detail of this setting.) The 2-byte read-only Temperature Register (00h) stores the output of the most recent conversion. These two bytes must be read one after the other in order to obtain the complete data. The first 12 bits of the two bytes combined will indicate the temperature with all remaining bits equal to zero
