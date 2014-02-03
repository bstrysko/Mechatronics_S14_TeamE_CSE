all:
	g++ -I include/ -o main `find src/* | grep -i '.cpp'` main.cpp `pkg-config --cflags --libs opencv`
