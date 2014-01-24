all: MissileGame

OBJS=main.o vecutil.o rocket.o

MissileGame: $(OBJS)
	g++ -o MissileGame $(OBJS) -L$(HOME)/usr/lib -lgraphicsmath0

%.o : %.cpp constants.h
	g++ $< -c -I$(HOME)/usr/include

clean:
	$(RM) *.o

run: MissileGame
	open /Applications/Utilities/Terminal.app ./MissileGame