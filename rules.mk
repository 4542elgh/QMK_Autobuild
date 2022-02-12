OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
TAP_DANCE_ENABLE = yes # Allow you to tap twice for a different key
CONSOLE_ENABLE = no # no need for this
MOUSEKEY_ENABLE = no # no need for this
EXTRAFLAGS += -flto # Linker optimizer
