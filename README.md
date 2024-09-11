# heat_measure_car_brakes

I started this project back in 2020 and managed to get it working. I got a bit to busy, sold my trackcar and formated my harddrive during the years and lost the code I wrote.
Figuring it out again and probably make it cleaner, better and will document all the stuff needed to get this working for your car.
If you think something is missing or could be written better please let me know.

All is written with Arduino IDE.
I use a Teensy LC as the base, because it's small, has i2c and 5v available. I'm not sure any more if 5v is a requirement, but usbpower defaults to 5v so I think it's also practical.

* The heat is measured with mlx90614 sensors. These can measure an object from -70 up to +380 degrees Celsius. The one I use already has a 10k ohm resistor build-in.
* The display used is a 0.91inch 128x32 I2C OLED scherm SSD1306. It's is not realy needed and realy small, but it is kind of handy with this experiment.
* HC-06 Bluetooth Slave Modul HC-06 4-Pin

Next to that it's advisable for testing to use a breadboard and plugin you hardware.

The code written is using a modified library because there are multiple mlx90614 sensor addresses and the default code can only handle the default address 0x5A.

I found out these mlx90614 sensor are difficult to change there address with Arduino. But if you have a Raspberry Pi program kit, it's much easier to accomplish. 
You will need to run this code: https://github.com/olegkutkov/allsky/blob/master/src/utils/mlx90614
Check the README, and you will find how to change the i2c address
