// dinosaur.h (header)
#ifndef DINOSAUR_H
#define DINOSAUR_H

#include "gameobject.h"

class Dinosaur : public GameObject {
private:
    bool alive;
    int headHeight;

public:
    Dinosaur();  

    bool isAlive() const;    
    void setAlive(bool state); 
    int getHeadHeight() const; 

#endif