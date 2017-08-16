CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		game.o Board.o Bomb.o BomberMan.o Character.o Ghost.o Point.o util.o

LIBS =		-lopengl32 -lglu32 -lfreeglut

TARGET =	game.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
