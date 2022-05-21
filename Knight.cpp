#include "Knight.h"

Knight::Knight(string name, string place, pair<double,double> location, vector<shared_ptr<SimObject>> station):Agent(name){
    setLocation(location);
    source = {place};
    setSpeed(10);
    setState("Stopped");
    this->station = move(station);
    cordinate.first = {0};
    cordinate.second = {0};
    timeBeats = {0};
    lengthDes = {0};
    LenFromPeasent = {-1};
    setCommand("");
}

string Knight::getSource() const{
    return source;
}

void Knight::setSource(string source){
    this->source = source;
}

void Knight::destinationCommand(shared_ptr<SimObject> station){
    setDestination(station);
    setCommand("destination");
    double x,y,distance;
    x = getLocation().first - station->getLocation().first;
    y = getLocation().second- station->getLocation().second;
    distance = sqrt(x*x+y*y);
    double trail = (distance/getSpeed())*10;
    lengthDes = distance;
    timeBeats = ceil(trail);

    cordinate.first = ((x*(-1)/trail));
    cordinate.second = ((y*(-1)/trail));
    
}

void Knight::positionCommand(pair<double,double> station){
    setTarget(station);
    setCommand("position");

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

void Knight::courseCommand(int angle){
    setAngle(angle);
    setCommand("course");
    double pi =3.141592653589793238463; 
    
    double Vx = sin(angle*(pi/180));
    double Vy = cos(angle*(pi/180));
    
    cordinate.first = Vx;
    cordinate.second = Vy;
}

void Knight::stopCommand(){
    lengthDes = 0;
    timeBeats = 0;
    cordinate.first = 0;
    cordinate.second = 0;
    LenFromPeasent = -1;
}

void Knight::update(){
    if(getCommand()==""){
        if(timeBeats == 0){
            for(int i=0;i<station.size();i++){
                distanceFromMe(station.at(i));
            }
            sortKnightVec(station);
            bool placeToVisit = false;
            shared_ptr<Structure> s;
            for(int i=0;i<station.size();i++){
                s = dynamic_pointer_cast<Structure>(station.at(i));
                if(!s->getIsVisited() && s->getName() != source){
                    placeToVisit = true;
                    setDestination(station.at(i));
                    s->setIsVisited(true);
                    break;
                }
            }
            if(!placeToVisit){
                for(int i=0;i<station.size();i++){
                    s = dynamic_pointer_cast<Structure>(station.at(i));
                    s->setIsVisited(false);
                }
                s = dynamic_pointer_cast<Structure>(station.at(0));
                setDestination(station.at(0));
                s->setIsVisited(true);
            }
            double x,y,distance;
            x = getLocation().first - s->getLocation().first;
            y = getLocation().second- s->getLocation().second;
            distance = ceil(sqrt(x*x+y*y));
            int trail = ceil(distance/getSpeed());
            lengthDes = distance;
            timeBeats = trail;
            if(x <= 0){
                cordinate.first = ((x*(-1)/trail));
            }
            else{
                cordinate.first = ((x/trail)); 
            }
            if(y <= 0){
                cordinate.second = ((y*(-1)/trail));
            }
            else{
                cordinate.second = ((y/trail)); 
            }
            setState("Moving on");
            pair<double,double> temp;
            temp.first = getLocation().first + cordinate.first;
            temp.second = getLocation().second + cordinate.second;
            setLocation(temp);
            timeBeats--;
            if(timeBeats == 0){
                setLocation(getDestination()->getLocation());
                setState("Stopped");
            }
        }
        else{
            timeBeats--;
            pair<double,double> temp;
            temp.first = getLocation().first + cordinate.first;
            temp.second = getLocation().second + cordinate.second;
            setLocation(temp);
            if(timeBeats == 0){
                setLocation(getDestination()->getLocation());
            }
        }
    }
    else if(getCommand() == "destination"){
        timeBeats--;
        setState("Moving on");
        if(timeBeats == 0){
            setLocation(getDestination()->getLocation());
            setCommand("");
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
    else if(getCommand() == "position"){
        timeBeats--;
        if(timeBeats == 0){
            setLocation(getTarget());
            setCommand("");
            setState("Stopped");
        }
        else{
           pair<double,double> temp;
            temp.first = getLocation().first + cordinate.first;
            temp.second = getLocation().second + cordinate.second;
            setLocation(temp); 
        }
    }
    else if(getCommand()=="stop"){
        stopCommand();
        setCommand("");
    }
}

void Knight::currentState(){
    cout<<"Knight "<<getName()<<" at ("<<fixed<<setprecision(2)<<getLocation().first<<", "<<getLocation().second;
    cout<<"), ";
    if(getState() == "Stopped"){
        cout<<getState()<<endl;
    }
    else if(getCommand() == "course"){
        cout<<"Heading on course "<< setprecision(2) << getAngle() <<" deg, speed "<<setprecision(2)<<getSpeed()<<" km/h"<<endl; 
    }
    else if(getCommand() == "position"){
        cout<<"Heading to position ("<< setprecision(2) <<getTarget().first<<", "<<getTarget().second <<"), speed "<<setprecision(2)<<getSpeed()<<" km/h"<<endl; 
    }
    else if(getCommand() == "destinaion"){
        cout<<"Heading to " << getDestination()->getName() <<", speed "<<setprecision(2)<<getSpeed()<<" km/h"<<endl; 
    }
    else{
        cout<<"Heading to " << getDestination()->getName() <<", speed "<<setprecision(2)<<getSpeed()<<" km/h"<<endl; 
    }
}

void Knight::distanceFromMe(shared_ptr<SimObject> des){
    double X = sqrt(((getLocation().first - des->getLocation().first)*(getLocation().first - des->getLocation().first))
    +((getLocation().second - des->getLocation().second)*(getLocation().second - des->getLocation().second)));
    shared_ptr<Structure> s = dynamic_pointer_cast<Structure>(des);
    s->setLenFromSource(X*10); 
}

void Knight::sortKnightVec(vector<shared_ptr<SimObject>>& vec){
    sort(vec.begin(), vec.end(), sortStation);
}

double Knight::getLenFromPeasent() const{
    return LenFromPeasent;
}
        
void Knight::setLenFromPeasent(double loc){
    LenFromPeasent = loc;
}

string Knight::what() const{
    return "Knight";
}