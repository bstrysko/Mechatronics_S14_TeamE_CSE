LINK_TARGET = main

OBJS =  \
 project.o \
 src/main.o \
 src/application/application.o \
 src/application/window.o \
 src/camera.o \
 src/color.o \
 src/drive_system.o \
 src/explorer.o \
 src/frame/rgb_frame.o \
 src/frame/thresh_frame.o \
 src/frame/frame.o \
 src/frame/hsv_frame.o \
 src/frame/text_frame.o \
 src/rgb_sensor.o

DEPFILES = $(patsubst %.o,%.dep,$(OBJS))

CFLAGS = -Iinclude/ $(shell pkg-config --cflags opencv)
LIBS = $(shell pkg-config --libs opencv) -l I2CMaster

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
