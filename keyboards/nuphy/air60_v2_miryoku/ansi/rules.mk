SRC += side.c
SRC += rf.c
SRC += sleep.c
SRC += rf_driver.c
UART_DRIVER_REQUIRED = yes

# DT_PRINT  “Dynamic Tapping Term Print”: Types the current tapping term, in milliseconds
# DT_UP     “Dynamic Tapping Term Up”: Increases the current tapping term by 5ms
# DT_DOWN   “Dynamic Tapping Term Down”: Decreases the current tapping term by 5ms
DYNAMIC_TAPPING_TERM_ENABLE = yes
