import sys
from nucleo_api import *

#------------------------------------------------------
# calibration.py
#------------------------------------------------------
# Micropython calibration test for Nucleo
# with Caravel development board hat
# See calibration_test2.c for details of the method,
# and the numbered steps referenced below.  Missing
# steps are happening on the side of the Caravel
# chip.
#
# How to use:
# (1) Run the calibrate.hex on an MPW-two caravel chip
# (2) Reset the caravel chip
# (3) Run mpremote
# (4) Type "from calibration import *"
# (5) Type "calibrate()"
#
# Calibration runs and returns a list of GPIO
# channels that have dependent hold violations.
#
#------------------------------------------------------
# Written by Tim Edwards
# February 11, 2023
#------------------------------------------------------

def calibrate():
    # Step (1)
    # Start by ensuring that GPIO[0] is output and value 0,
    # and all other channels are set to input (disabled).

    for channel in range(0, 38):
        Dio(f"IO_{channel}").set_state(False)

    for channel in range(0, 38):
        Dio(f"IO_{channel}").set_value(0)

    Dio("IO_0").set_value(0)
    Dio("IO_0").set_state(True)

    # Step (3)
    # Set all pins on the low side to output and value 1

    for channel in range(0, 19):
        Dio(f"IO_{channel}").set_value(1)

    for channel in range(0, 19):
        Dio(f"IO_{channel}").set_state(True)

    # Step (6)
    # Wait for GPIO[37] to go high (low side calibration done)

    print('Waiting for Caravel to calibrate low side.')
    while Dio("IO_37").get_value() == 0:
        pass

    print('Low side complete')

    # Disable the low side GPIO pins (set to input)
    # except for GPIO[0]

    for channel in range(1, 38):
        Dio(f"IO_{channel}").set_state(False)

    for channel in range(1, 19):
        Dio(f"IO_{channel}").set_value(0)

    # Set all pins on the high side to output and value 1

    for channel in range(19, 38):
        Dio(f"IO_{channel}").set_value(1)

    for channel in range(19, 38):
        Dio(f"IO_{channel}").set_state(True)

    # Step (7)
    # Set GPIO[0] low, then release it.

    Dio("IO_0").set_value(0)
    Dio("IO_0").set_state(False)

    # Step (11)
    # Wait for GPIO[0] to go high (high side calibration done)

    print('Waiting for Caravel to calibrate high side.')
    while Dio("IO_0").get_value() == 0:
        pass

    print('High side complete')

    # Disable the high side GPIO pins (set to input)
    # except for GPIO[37]

    for channel in range(19, 37):
        Dio(f"IO_{channel}").set_state(False)

    for channel in range(19, 37):
        Dio(f"IO_{channel}").set_value(0)

    # Step (12)
    # Set GPIO[37] low, then release it.

    Dio("IO_37").set_value(0)
    Dio("IO_37").set_state(False)

    # Step (14)
    # Wait for GPIO[0] to go low

    print('Waiting for Caravel to generate result.')
    while Dio("IO_0").get_value() == 1:
        pass

    print('Result generated')

    # Get the value for all channels
    deps = []
    dep_x = ''
    dep_y = ''
    for channel in range(0, 38):
        if Dio(f"IO_{channel}").get_value() == 1:
            deps.append(f"IO_{channel}")
            dep_x += '1'
            dep_y = '1' + dep_y
        else:
            dep_x += '0'
            dep_y = '0' + dep_y

    dep_r = hex(int(dep_y[19:], 2))
    dep_l = hex(int(dep_x[19:], 2))

    print('Dependent violations at channels: ' + ', '.join(deps))
    print('')
    print('DEP_R = ' + dep_r)
    print('DEP_L = ' + dep_l)
    print('')
    print('Done!')

#----------------------------------------------------------
# If called as application
#----------------------------------------------------------

if __name__ == '__main__':
    calibrate()
    sys.exit(0)
