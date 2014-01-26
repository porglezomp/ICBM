all: MissileGame.exe

OBJS=main.o vecutil.o rocket.o physics.o part.o booster.o

MissileGame.exe: $(OBJS)
	g++ -o MissileGame.exe $(OBJS) -L$(HOME)/usr/lib -lgraphicsmath0 -g

%.o : %.cpp constants.h debug.h
	g++ $< -c -I$(HOME)/usr/include -g

clean:
	$(RM) *.o

run: MissileGame.exe
	open /Applications/Utilities/Terminal.app ./MissileGame
