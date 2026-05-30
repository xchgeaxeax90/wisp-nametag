####### MCU #######

## STC8H1K08 STC8H8K64U
MCU                 ?= STC8H1K08
MCU_IRAM            ?= 256
# 1024, 2048, 3072, 4096, 8192
MCU_XRAM            ?= 1024
# 8192, 16384, 32768, 65536
MCU_CODE_SIZE       ?= 8192

##### Project #####

PROJECT             ?= app
# The path for generated files
BUILD_DIR           = build

TOOCHAIN_PREFIX     ?=

# C source folders
USER_CDIRS          := .
# C source single files
USER_CFILES         :=
USER_INCLUDES       := .


## STC8H1K08 36.864MHz
LIB_FLAGS           := __CONF_FOSC=24010000UL \
					__CONF_MCU_MODEL=MCU_MODEL_STC8H1K08 \
					__CONF_CLKDIV=0x00 \
					__CONF_IRCBAND=0x00 \
					__CONF_VRTRIM=0x1F \
					__CONF_IRTRIM=0xB5 \
					__CONF_LIRTRIM=0x00 

include ./library.mk
