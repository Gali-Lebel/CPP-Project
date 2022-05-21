#include "SimObject.h"

SimObject::SimObject(string name){
    this->name = name;
}

string SimObject::getName() const{
    return name;
}