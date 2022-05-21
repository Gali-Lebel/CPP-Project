#include "Structure.h"

Structure::Structure(string name , pair<double,double> location):SimObject(name){
     this->location = {location};
     isVisited = {false};
}

pair<double,double> Structure::getLocation() const{
     return location;
}

void Structure::setIsVisited(bool visit){
     isVisited = visit;
}

bool Structure::getIsVisited() const{
     return isVisited;
}

double Structure::getLenFromSource() const{
    return LenFromSource;
}

void Structure::setLenFromSource(double len){
    this->LenFromSource = len;
}