all: MissileGame.exe

OBJS=main.o vecutil.o rocket.o physics.o

MissileGame.exe: $(OBJS)
	g++ -o MissileGame.exe $(OBJS) -L$(HOME)/usr/lib -lgraphicsmath0

%.o : %.cpp constants.h
	g++ $< -c -I$(HOME)/usr/include

clean:
	$(RM) *.o

run: MissileGame.exe
	open /Applications/Utilities/Terminal.app ./MissileGame
