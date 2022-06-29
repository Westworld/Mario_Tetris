# Mix of Mario Bros. and Tetris Clock

This is a clone based on:
https://github.com/jnthas/mariobros-clock/b

and

xxx.



## Modification made for Mario:

- removed Wifi Connection assistant and replaced with hard coded credentials using WifiMulti. Benefit: allows to enter network access credentials for 2 networks, makes moving the clock from office/home (etc) easy. And allows to handle daylight saving time update
- rewrote to virtual matrix display, allows usage of two 64x32 panels instead of one 64x64 panel
- overwrote standard pins to allow different, much more easy, routing from ESP32 to HUB75.

## Modification for Tetris
WIP


## PCB 
A simple board to hold ESP32 and HUB75 was created with Eagle. Mil files to use a CNC to create your own PCB is enclosed.
![Board](https://github.com/Westworld/Mario_Tetris/blob/main/Eagle_PCB/routing.png?raw=true)

## Case
Instead of a case a holder (to mount 2 panels) with a stand is enclosed.