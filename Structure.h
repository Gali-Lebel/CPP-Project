#ifndef STRUCTURE_H
#define STRUCTURE_H

#include<iostream>
#include<list>
#include <iomanip>

#include "SimObject.h"

using namespace std;

class Structure : public SimObject{
    private:
        pair<double,double> location;    
        bool isVisited;
        double LenFromSource;
    public:
        Structure(string name , pair<double,double> location);
        virtual pair<double,double> getLocation() const;
        void setIsVisited(bool visit);
        bool getIsVisited() const;
        virtual int getAmount() const = 0;
        virtual void setAmount(int amount) = 0;
        double getLenFromSource() const;
        void setLenFromSource(double len);
        virtual void update() = 0;
        virtual void currentState() = 0;
        virtual string what() const = 0;
        virtual ~Structure(){}
};
#endif