#ifndef AGENT_H
#define AGENT_H

#include<iostream>
#include<list>
#include<utility> 
#include<memory>
#include <iomanip>

#include "SimObject.h"

using namespace std;

class Agent : public SimObject{
    private:
        pair<double,double> location; /*the agent is in this location*/
        string state;
        shared_ptr<SimObject> destination;
        pair<double,double> target; /*on the way to this target*/
        double speed; 
        string command;
        int angle;
    public:
        Agent(string name);
        virtual pair<double,double> getLocation() const;
        virtual void setLocation(pair<double,double> location);
        string getState() const;
        void setState(string state);
        shared_ptr<SimObject> getDestination() const;
        void setDestination(shared_ptr<SimObject> destination);
        pair<double,double> getTarget() const;
        void setTarget(pair<double,double> target);
        double getSpeed() const;
        void setSpeed(double speed);
        virtual int getAmount() const {return -1;}
        virtual void setAmount(int amount) {}
        string getCommand() const;
        void setCommand(string command);
        int getAngle() const;
        void setAngle(int angle);
        virtual void update() = 0; 
        virtual void currentState() = 0;
        virtual string what() const = 0;
        virtual ~Agent(){}
};
#endif