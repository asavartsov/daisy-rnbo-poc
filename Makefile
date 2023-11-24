# Project Name
TARGET = RNBOTest
APP_TYPE=BOOT_SRAM

# Library Locations
LIBDAISY_DIR = libDaisy
RNBO_DIR = rnbo

# Sources
CPP_SOURCES = main.cpp rnbo_source.cpp compat/RNBO.cpp

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

RNBO_DEFS = -DRNBO_SIMPLEENGINE -DRNBO_USE_FLOAT32 -DRNBO_NOJSONPRESETS
RNBO_FLAGS = -Wno-pragmas -Wno-strict-aliasing -Wno-sign-compare -Wno-psabi -fexceptions

CFLAGS += $(RNBO_DEFS) $(RNBO_FLAGS)
CPPFLAGS += $(RNBO_DEFS) $(RNBO_FLAGS)
C_INCLUDES += -Icompat -I$(RNBO_DIR) -I$(RNBO_DIR)/common
