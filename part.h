#ifndef PART_H
#define PART_H 1

class rocket;

class part {
protected:
	rocket *parent;
public:
	part(rocket*);
	virtual void update();
	virtual float mass() = 0;
	virtual void print() = 0;
};

#endif