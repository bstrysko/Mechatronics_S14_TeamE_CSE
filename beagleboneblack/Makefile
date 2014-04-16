#
# Mechatronics (Spring 2014)
# Team Name: Explorare
#
# Team Member Names:
# Brent Strysko
# Wen Li
# Caroline Colombo
# Funan Ma
# 
# @author Brent Strysko
#
# Makefile for Beaglebone Code
#
# Created On: 2/1/14
#

LINK_TARGET = main

OBJS =  \
 project.o \
 src/main.o \
 src/explorer.o

DEPFILES = $(patsubst %.o,%.dep,$(OBJS))

CFLAGS = -Iinclude/ -I/usr/include/ $(shell pkg-config --cflags opencv)
LIBS = -l VisualCSEDefectDetector $(shell pkg-config --libs opencv) -l VisualCSEDefectDetector -l RGBColorSensorArray -l DriveSubsystem -l I2CMaster -l AVRI2CBootloader -l IntelHexParser -l CSEComsProtocol

REBUILDABLES = $(OBJS) $(LINK_TARGET) $(DEPFILES)

all : $(LINK_TARGET)
	@echo "Build complete"

clean :
	rm -f $(REBUILDABLES)
	@echo "Clean complete"

$(LINK_TARGET) : $(OBJS)
	g++ -g -o $@ $^ $(LIBS)

%.o : %.cpp
	g++ $(CFLAGS) -g -o $@ -c $< $(LIBS)

%.dep : %.cpp
	g++ -M $(CFLAGS) $< > $@ $(LIBS)

include $(OBJS:.o=.dep)
