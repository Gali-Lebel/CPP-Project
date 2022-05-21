#include "Agent.h"

Agent::Agent(string name):SimObject(name){}

pair<double,double> Agent::getLocation() const{
    return location;
}

void Agent::setLocation(pair<double,double> location){
    this->location = location;
}

string Agent::getState() const{
    return state;
}

void Agent::setState(string state){
    this->state = state;
}

shared_ptr<SimObject> Agent::getDestination() const{
    return destination;
}

void Agent::setDestination(shared_ptr<SimObject> destination){
    this->destination = destination;
}
pair<double,double> Agent::getTarget() const{
    return target;
}

void Agent::setTarget(pair<double,double> target){
    this->target = target;
}

double Agent::getSpeed() const{
    return speed;
}

void Agent::setSpeed(double speed){
    this->speed = speed;
}

string Agent::getCommand() const{
    return command;
}

void Agent::setCommand(string command){
    this->command = command;
}

int Agent::getAngle() const{
    return angle;
}

void Agent::setAngle(int angle){
    this->angle = angle;
}

