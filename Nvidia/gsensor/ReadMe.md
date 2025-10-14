## gsensor_atc3xxx.c
This program is a command-line utility for testing the LSM6DSL, a 3-axis accelerometer and gyroscope, over an I2C communication bus.

**Functions:**
  - Hardware Communication: 
    It directly communicates with the sensor using a specific I2C device file (defaults to /dev/i2c-7) and the sensor's I2C address (0x6B).
  - Initialization: 
    The program sends commands to the sensor to wake it up and configure both the accelerometer and gyroscope into a "High performance" mode at a 416Hz data rate.
  - Data Acquisition: 
    The core logic of the program is to Read the initial accelerometer and gyroscope values for the X, Y, and Z axes.
