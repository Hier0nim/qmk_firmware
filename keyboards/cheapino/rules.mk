CAPS_WORD_ENABLE = yes
CUSTOM_MATRIX = lite
WS2812_DRIVER = vendor
RGBLIGHT_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
SRC += encoder.c
SRC += ghosting.c
SRC += matrix.c

# DT_PRINT  “Dynamic Tapping Term Print”: Types the current tapping term, in milliseconds
# DT_UP     “Dynamic Tapping Term Up”: Increases the current tapping term by 5ms
# DT_DOWN   “Dynamic Tapping Term Down”: Decreases the current tapping term by 5ms
DYNAMIC_TAPPING_TERM_ENABLE = yes
