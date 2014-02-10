LINK_TARGET = main

OBJS =  \
 main.o \
 src/application/window.o \
 src/camera.o \
 src/color.o \
 src/drive_system.o \
 src/explorer.o \
 src/frame/rgb_frame.o \
 src/frame/thresh_frame.o \
 src/frame/frame.o \
 src/frame/hsv_frame.o \
 src/i2c/i2c_bus.o \
 src/i2c/i2c_device.o \
 src/rgb_sensor.o

CFLAGS = -Iinclude/ $(shell pkg-config --cflags opencv)
LIBS = $(shell pkg-config --libs opencv)

REBUILDABLES = $(OBJS) $(LINK_TARGET)

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
