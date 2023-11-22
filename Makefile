# Project Name
TARGET = RNBOTest
APP_TYPE=BOOT_SRAM

# Sources
CPP_SOURCES = main.cpp rnbo_source.cpp compat/RNBO.cpp

# Library Locations
LIBDAISY_DIR = ../libDaisy
RNBO_DIR = rnbo

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

CPPFLAGS += -Wno-pragmas -Wno-strict-aliasing -Wno-sign-compare -Wno-psabi -fexceptions -DRNBO_SIMPLEENGINE -DRNBO_USE_FLOAT32
C_INCLUDES += -Icompat -I$(RNBO_DIR) -I$(RNBO_DIR)/common
