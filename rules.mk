# Disable unused features
VIA_ENABLE = no
WPM_ENABLE = no
NKRO_ENABLE = no
AUDIO_ENABLE = no
MAGIC_ENABLE = no
STENO_ENABLE = no
LEADER_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
UNICODE_ENABLE = no
MOUSEKEY_ENABLE = no
TERMINAL_ENABLE = no
KEY_LOCK_ENABLE = no
RGBLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no
SLEEP_LED_ENABLE = no
TAP_DANCE_ENABLE = no
VELOCIKEY_ENABLE = no
SWAP_HANDS_ENABLE = no
SPACE_CADET_ENABLE = no

# Common features
LTO_ENABLE = yes
WAIT_FOR_USB = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = no
BOOTLOADER = atmel-dfu
BOOTMAGIC_ENABLE = yes

# Main source file and source paths
SRC += neuhalje.c
VPATH += $(USER_PATH)/oled  $(USER_PATH)/rgb

# Combo support
COMBO_ENABLE = no
#
# Corne CRKBD
ifeq ($(KEYBOARD), crkbd/rev1)
	ifeq ($(strip $(TINY)),)
		RGB_MATRIX_ENABLE = yes
		RGB_MATRIX_CUSTOM_USER = yes
		SRC += rgb-matrix.c
	endif
	ifneq ($(strip $(OLED)),)
		OLED_ENABLE = yes
		OPT_DEFS += -D${OLED}
		ifeq ($(OLED), $(filter $(OLED), LEFTCAT RIGHTCAT CAT))
			SRC += oled-icons.c oled-bongocat.c
		else ifeq ($(OLED), $(filter $(OLED), LUNA FELIX))
			SRC += oled-icons.c oled-luna.c
		endif
	endif
endif
