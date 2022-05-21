#ifndef THUG_H
#define THUG_H

#include<iostream>
#include<vector>
#include<utility>
#include<memory>
#include<cmath>
#include<algorithm>

#include "Peasant.h"
#include "Knight.h"

using namespace std;

class Thug : public Agent{
    private:
        int power;
        int lengthDes;
        int timeBeats;
        pair<double,double> cordinate;
        shared_ptr<SimObject> attackPeasent;
    public:
        Thug(string name, pair<double,double> location);
        int getPower() const;
        void setPower(int power);
        void positionCommand(pair<double,double> station,double speed);
        void courseCommand(int angle,double speed);
        void stopCommand();
        virtual void update();
        virtual void currentState();
        void bullyAttack(shared_ptr<SimObject> attackPeasent);
        void attack(vector<shared_ptr<SimObject>> knigthList);
        void sortKnightVec(vector<shared_ptr<SimObject>>& vec);
        string what() const;
        virtual ~Thug(){}    

        struct SortKnigth{
            bool operator()(shared_ptr<SimObject> i, shared_ptr<SimObject> j){
                shared_ptr<Knight> s = dynamic_pointer_cast<Knight>(i);
                shared_ptr<Knight> d = dynamic_pointer_cast<Knight>(j);
                return s->getLenFromPeasent() < d->getLenFromPeasent();
            }
        }sortKnigth;
};
#endif