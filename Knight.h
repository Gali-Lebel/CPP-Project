#ifndef KNIGHT_H
#define KNIGHT_H

#include<iostream>
#include<vector>
#include<utility>
#include<memory>
#include<cmath>
#include<algorithm>

#include "Agent.h"
#include "Structure.h"

using namespace std;

class Knight : public Agent{
    private:
        vector<shared_ptr<SimObject>> station;
        string source;
        int lengthDes;
        int timeBeats;
        pair<double,double> cordinate;
        double LenFromPeasent;
    public:
        Knight(string name, string place, pair<double,double> location, vector<shared_ptr<SimObject>> station);
        string getSource() const;
        void setSource(string source);
        virtual void update();
        virtual void currentState();
        double getLenFromPeasent() const;
        void setLenFromPeasent(double loc);
        void destinationCommand(shared_ptr<SimObject> station);
        void positionCommand(pair<double,double> station);
        void courseCommand(int angle);
        void stopCommand();
        void distanceFromMe(shared_ptr<SimObject> des);
        void sortKnightVec(vector<shared_ptr<SimObject>>& vec);
        string what() const;
        virtual ~Knight(){}   

        struct SortStation{
            bool operator()(shared_ptr<SimObject> i, shared_ptr<SimObject> j){
                shared_ptr<Structure> s = dynamic_pointer_cast<Structure>(i);
                shared_ptr<Structure> d = dynamic_pointer_cast<Structure>(j);
                return s->getLenFromSource() < d->getLenFromSource();
            }
        }sortStation;
};
#endif