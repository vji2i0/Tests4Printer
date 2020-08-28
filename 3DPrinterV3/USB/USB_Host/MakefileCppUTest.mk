#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
#COMPONENT_NAME = BookCode_CppUTest

#--- Inputs ----#
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .
CPPUTEST_HOME = ../../../cpputest-3.7.2#/home/vji2i0/TDD/cpputest-3.7.2
TEST_FOLDER = ./#/home/vji2i0/TDD/3DPrinterV3/USB/USB_Host
FIRMWARE_FOULDER = ./firmware#/home/vji2i0/TDD/3DPrinterV3/USB/USB_Host/firmware

SRC_DIRS = \
  .\
  $(FIRMWARE_FOULDER)/src\

TEST_SRC_DIRS = \
	.\
    $(TEST_FOLDER)/tests\

INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  $(FIRMWARE_FOULDER)/inc\

MOCKS_SRC_DIRS = \
  $(CPPUTEST_HOME)/src/CppUTestExt\

CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -Werror
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
LD_LIBRARIES = -lpthread


ifeq ($(CPPUTEST_HOME),)
$(info CPPUTEST_HOME not set! See README.txt)
else
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
endif
