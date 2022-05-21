#ifndef PEASANT_H
#define PEASANT_H

#include<iostream>
#include<cstdlib>
#include<list>
#include<utility>
#include<memory>
#include<algorithm>
#include <cmath>
#include <ctgmath>

#include "Knight.h"

using namespace std;

class Peasant : public Agent{
    private:
        int health;
        int package;
        int packageLoad;
        shared_ptr<SimObject> source;
        double lengthSource;
        double lengthDestination;
        int timeInFarm;
        int timeInCastle;
        int timeBeatsToSource;
        int timeBeatsToDes;
        pair<double,double> cordinateSource;
        pair<double,double> cordinateDes;
        bool flagSource;
        bool flagDes;
    public:
        Peasant(string name, pair<double,double> location);
        int getHealth() const;
        void setHealth(int health);
        int getPackage() const;
        void setPackage(int package);
        shared_ptr<SimObject> getSource() const;
        void setSource(shared_ptr<SimObject> source);
        virtual void update();
        virtual void currentState();
        void stopCommand();
        void distanceFromMe(shared_ptr<SimObject> des);
        void stratWorking(shared_ptr<SimObject> source,shared_ptr<SimObject> destination);
        string what() const;
        virtual ~Peasant(){}    
};
#endif