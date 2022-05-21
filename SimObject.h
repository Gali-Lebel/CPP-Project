#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#include<iostream>
#include<list>
#include<utility>

using namespace std;

class SimObject{
    private:
        string name;
    public:
        SimObject(string name);
        string getName() const;
        virtual pair<double,double> getLocation() const = 0;
        virtual int getAmount() const = 0;
        virtual void setAmount(int amount) = 0;
        virtual void update() = 0; 
        virtual void currentState() = 0;
        virtual string what() const = 0;
        virtual ~SimObject(){}     
};
#endif