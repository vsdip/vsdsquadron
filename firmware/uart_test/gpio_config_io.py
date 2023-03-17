# number of IO in the configuration stream for each chain
NUM_IO = 19

# defines these values for IO configurations
C_MGMT_OUT = 0
C_MGMT_IN = 1
C_USER_BIDIR = 2
C_DISABLE = 3
C_ALL_ONES = 4
C_USER_BIDIR_WPU = 5
C_USER_BIDIR_WPD = 6
C_USER_IN_NOPULL = 7
C_USER_OUT = 8

config_h = [
    C_MGMT_OUT,  #37
    C_MGMT_IN,  #36
    C_MGMT_IN,  #35
    C_MGMT_OUT,  #34
    C_MGMT_IN,  #33
    C_MGMT_IN,  #32
    C_MGMT_IN,  #31
    C_MGMT_OUT,  #30
    C_MGMT_IN,  #29
    C_MGMT_OUT,  #28
    C_MGMT_IN,  #27
    C_MGMT_OUT,  #26
    C_MGMT_IN,  #25
    C_MGMT_OUT,  #24
    C_MGMT_IN,  #23
    C_MGMT_OUT,  #22
    C_MGMT_IN,  #21
    C_MGMT_OUT,  #20
    C_MGMT_IN,  #19
]

del config_h[NUM_IO:]

config_l = [
    C_MGMT_IN,   #0
    C_MGMT_IN,   #1
    C_MGMT_OUT,   #2
    C_MGMT_IN,   #3
    C_MGMT_IN,   #4
    C_MGMT_OUT,   #5
    C_MGMT_OUT,   #6
    C_MGMT_OUT,   #7
    C_MGMT_IN,   #8
    C_MGMT_OUT,   #9
    C_MGMT_IN,   #10
    C_MGMT_IN,   #11
    C_MGMT_IN,   #12
    C_MGMT_IN,   #13
    C_MGMT_OUT,   #14
    C_MGMT_IN,   #15
    C_MGMT_OUT,   #16
    C_MGMT_IN,   #17
    C_MGMT_OUT,   #18
]

del config_l[NUM_IO:]
