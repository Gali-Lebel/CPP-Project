#include "Thug.h"

Thug::Thug(string name, pair<double,double> location):Agent(name){
    setLocation(location);
    setSpeed(0);
    setState("Stopped");
    power = {5};
    lengthDes = {0};
    timeBeats = {0};
    cordinate.first = {0};
    cordinate.second = {0};
}

int Thug::getPower() const{
    return power;
}

void Thug::setPower(int power){
    this->power = power;
}

void Thug::positionCommand(pair<double,double> station, double speed){
    setTarget(station);
    setCommand("position");
    setState("Moving");
    if(speed > 30){
        setSpeed(30);
    }
    else{
        setSpeed(speed);
    }

    double x,y,distance;
    x = getLocation().first - station.first;
    y = getLocation().second- station.second;
    distance = sqrt(x*x+y*y);
    double trail = (distance/getSpeed())*10;
    lengthDes = distance;
    timeBeats = ceil(trail);

    cordinate.first = ((x*(-1)/trail));
    cordinate.second = ((y*(-1)/trail));
}

void Thug::courseCommand(int angle,double speed){
    setAngle(angle);
    setCommand("course");
    setState("Moving");
    if(speed > 30){
        setSpeed(30);
    }
    else{
        setSpeed(speed);
    }

    double pi =3.141592653589793238463; 
    
    double Vx = getSpeed()*(sin(angle*(pi/180)));
    double Vy = getSpeed()*(cos(angle*(pi/180)));
    
    cordinate.first = Vx/10; 
    cordinate.second = Vy/10;
}

void Thug::stopCommand(){
    lengthDes = 0;
    timeBeats = 0;
    setSpeed(0);
    cordinate.first = 0;
    cordinate.second = 0;
}

void Thug::currentState(){
    cout<<"Thug "<<getName()<<" at ("<<fixed<<setprecision(2)<<getLocation().first<<", "<<getLocation().second;
    cout<<"), ";
    if(getState() == "Stopped"){
        cout<<getState()<<", with power "<<power<<"."<<endl;
    }
    else if(getCommand() == "course"){
        cout<<"Heading on course "<< setprecision(2) << getAngle() <<" deg, speed "<<setprecision(2)<<getSpeed()<<" km/h, power "<<power<<"."<<endl; 
    }
    else if(getCommand() == "position"){
        cout<<"Heading to position ("<< setprecision(2) << setprecision(2) <<getTarget().first<<", "<<getTarget().second <<"), speed "<<setprecision(2)<<getSpeed()<<" km/h, power "<<power<<"."<<endl;
    }
    else if(getState() == "Dead"){
        cout<<getState()<<endl;
    }
}

void Thug::update(){
    if(getState() == "Stopped"){
        stopCommand();
    }
    else if(getCommand() == "position"){
        timeBeats--;
        if(timeBeats == 0){
            setLocation(getTarget());
            setState("Stopped");
        }
        else{
            pair<double,double> temp;
            temp.first = getLocation().first + cordinate.first;
            temp.second = getLocation().second + cordinate.second;
            setLocation(temp); 
        }
    }
    else if(getCommand() == "course"){
        pair<double,double> temp;
        temp.first = getLocation().first + cordinate.first;
        temp.second = getLocation().second + cordinate.second;
        setLocation(temp); 
    }
}

void Thug::attack(vector<shared_ptr<SimObject>> knigthList){
    shared_ptr<Peasant> temp = dynamic_pointer_cast<Peasant>(attackPeasent);
    double x,y,distance;
    x = getLocation().first - temp->getLocation().first;
    y = getLocation().second- temp->getLocation().second;
    distance = (sqrt(x*x+y*y))*10;
    if(distance <= 1){
        if(power > temp->getHealth() && temp->getHealth() != 0){
            for(int i=0;i<knigthList.size();i++){
                temp->distanceFromMe(knigthList.at(i));
            }
            sortKnightVec(knigthList);
            shared_ptr<Knight> closetKnight = dynamic_pointer_cast<Knight>(knigthList.at(0));
            if(closetKnight->getLenFromPeasent() >= 2.5){
                power++;
                setCommand("Stopped");
                setLocation(temp->getLocation());
                temp->setHealth(temp->getHealth()-1);
                temp->setPackage(0);
                if(temp->getHealth() == 0){
                    temp->setCommand("Dead");
                }
                else{
                    temp->setCommand("Stopped");
                }
            }
            else{
                power--;
                setCommand("Stopped");
                setLocation(temp->getLocation());
            }
        }
        else{
            power--;
            setCommand("Stopped");
            setLocation(temp->getLocation());
        }
    }
    else{
        setCommand("Stopped");
    }
}

void Thug::sortKnightVec(vector<shared_ptr<SimObject>>& vec){
    sort(vec.begin(), vec.end(), sortKnigth);
}

void Thug::bullyAttack(shared_ptr<SimObject> attackPeasent){
    this->attackPeasent = attackPeasent;
}

string Thug::what() const{
    return "Thug";
}