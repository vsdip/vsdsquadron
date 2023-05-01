# gpio_config_def.py file for part 003
# io_config -- version 1.2.1
voltage = 1.60
analog = False

H_NONE        = 0  
H_DEPENDENT   = 1  
H_INDEPENDENT = 2  
H_SPECIAL     = 3  
H_UNKNOWN     = 4  

# voltage: 1.6
# configuration failed in gpio[5], anything after is invalid
gpio_l = [
['IO[0]', H_NONE],
['IO[1]', H_INDEPENDENT],
['IO[2]', H_DEPENDENT],
['IO[3]', H_DEPENDENT],
['IO[4]', H_INDEPENDENT],
['IO[5]', H_UNKNOWN],
['IO[6]', H_UNKNOWN],
['IO[7]', H_UNKNOWN],
['IO[8]', H_UNKNOWN],
['IO[9]', H_UNKNOWN],
['IO[10]', H_UNKNOWN],
['IO[11]', H_UNKNOWN],
['IO[12]', H_UNKNOWN],
['IO[13]', H_UNKNOWN],
['IO[14]', H_UNKNOWN],
['IO[15]', H_UNKNOWN],
['IO[16]', H_UNKNOWN],
['IO[17]', H_UNKNOWN],
['IO[18]', H_UNKNOWN],
]
# voltage: 1.6
# IO configuration chain was successful
gpio_h = [
['IO[37]', H_NONE],
['IO[36]', H_DEPENDENT],
['IO[35]', H_INDEPENDENT],
['IO[34]', H_INDEPENDENT],
['IO[33]', H_INDEPENDENT],
['IO[32]', H_INDEPENDENT],
['IO[31]', H_INDEPENDENT],
['IO[30]', H_INDEPENDENT],
['IO[29]', H_INDEPENDENT],
['IO[28]', H_INDEPENDENT],
['IO[27]', H_INDEPENDENT],
['IO[26]', H_INDEPENDENT],
['IO[25]', H_INDEPENDENT],
['IO[24]', H_INDEPENDENT],
['IO[23]', H_INDEPENDENT],
['IO[22]', H_INDEPENDENT],
['IO[21]', H_INDEPENDENT],
['IO[20]', H_INDEPENDENT],
['IO[19]', H_INDEPENDENT],
]
