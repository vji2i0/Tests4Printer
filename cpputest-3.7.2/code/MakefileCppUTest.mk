#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = BookCode_CppUTest

#--- Inputs ----#
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .
CPPUTEST_HOME = /home/vji2i0/TDD/cpputest-3.7.2

SRC_DIRS = \
	src/util\
	src/IO \
#	src/HomeAutomation \
#	src/LedDriver \
#	src/dvr\
#	src/MyOS \
#	src/MyOS/posix \
#	src/zune \

#TEST_SRC_DIRS = \
#	.\
#	mocks\
#	mocks\
#	tests/LedDriver\
#	tests/stdio\
#	tests/util\
#	tests/IO\
#	tests/zune\
#	tests/HomeAutomation\
#	tests/dvr\
#	tests\
#	tests/MyOS\

TEST_SRC_DIRS = \
	.\
	tests/stdio\
    tests\
#	mocks\


INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  include/IO\
  include/util\
  include/HomeAutomation\
  include/LedDriver\
  include/MyOS\
  include/dvr\
  include/zune\
#  mocks\

MOCKS_SRC_DIRS = \
#	mocks\

CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -Werror
#CPPUTEST_CFLAGS = -std=c89
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
LD_LIBRARIES = -lpthread


ifeq ($(CPPUTEST_HOME),)
$(info CPPUTEST_HOME not set! See README.txt)
else
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
endif
