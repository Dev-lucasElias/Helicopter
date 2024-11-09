// missile.h
#ifndef MISSILE_H
#define MISSILE_H

#include "gameobject.h"

class Missile : public GameObject {
private:
	bool active;

public:
	Missile();

	bool isActive() const;
	void setActive(bool state);
};

#endif