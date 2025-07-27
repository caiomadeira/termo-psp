TARGET = Termo
OBJS = main.o src/common.o src/entry.o

INCDIR = 
CFLAGS = -O0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBS= -lpspnet_apctl -lpsphttp -lraylib -lphysfs -lcjson -lz -lglut -lGLU -lGL -lpspfpu -lpspvfpu -lpsppower -lpspaudio -lpspaudiolib -lmad -lpspmp3 -lpspjpeg
LIBDIR =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Termo Portable


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak