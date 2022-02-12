# NOTE THAT YOU WILL NEED TO SET UNUSED PARAMETERS TO NO IN ORDER FOR TOOLCHAIN TO NOT INCLUDE THE LIB AT ALL
# NOTE THAT DIFFERENT TOOL CHAIN aka WINDOWS and LINUX WILL GENERATE DIFFERENT BINARY FILE SIZE. TAKE THAT INTO CONSIDERATION WHEN GENERATING CONFIG
OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no
TAP_DANCE_ENABLE = yes
EXTRAFLAGS += -flto
