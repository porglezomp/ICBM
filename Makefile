all: MissileGame

OBJS=main.o vecutil.o rocket.o physics.o part.o booster.o

MissileGame: $(OBJS)
	g++ -o MissileGame $(OBJS) -L$(HOME)/usr/lib -lgraphicsmath0 -g

%.o : %.cpp constants.h debug.h
	g++ $< -c -I$(HOME)/usr/include -g

clean:
	$(RM) *.o

run: MissileGame
	open /Applications/Utilities/Terminal.app ./MissileGame