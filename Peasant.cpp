#include "Peasant.h"

Peasant::Peasant(string name, pair<double,double> location):Agent(name){
    setLocation(location);
    health = {10};
    package = {0};
    packageLoad = {0};
    lengthSource = {0};
    lengthDestination = {0};
    timeInFarm = {0};
    timeInCastle = {0};
    timeBeatsToSource = {0};
    timeBeatsToDes = {0};
    cordinateSource.first = {0};
    cordinateSource.second = {0};
    cordinateDes.first  = {0};
    cordinateDes.second = {0};
    flagDes = {false};
    flagSource = {false};
    setSpeed(5);
    setState("Stopped");
}

int Peasant::getHealth() const{
    return health;
}

void Peasant::setHealth(int health){
    this->health = health;
}

int Peasant::getPackage() const{
    return package;
}

void Peasant::setPackage(int package){
    this->package = package;
}

shared_ptr<SimObject> Peasant::getSource() const{
    return source;
}

void Peasant::setSource(shared_ptr<SimObject> source){
    this->source = source;
}

void Peasant::currentState(){
    cout<<"Peasant "<<getName()<<" at ("<<fixed<<setprecision(2)<<getLocation().first<<", "<<getLocation().second;
    cout<<"), ";
    if(getState() == "Dead"){
        cout<<getState()<<endl;
    }
    else if(getState() == "Stopped"){
        cout<<getState()<<", with "<<package<<" package and "<<health<<" health."<<endl;
    }
    else{
        cout<<getState()<<", speed "<<setprecision(2)<<getSpeed()<<" km/h, with "<<package<<" package and "<<health<<" health."<<endl;
    }
}

void Peasant::stopCommand(){
    lengthSource = 0;
    lengthDestination = 0;
    timeInFarm = 0;
    timeInCastle = 0;
    timeBeatsToSource = 0;
    timeBeatsToDes = 0;
    cordinateSource.first = 0;
    cordinateSource.second = 0;
    cordinateDes.first  = 0;
    cordinateDes.second = 0;
    flagDes = false;
    flagSource = false;
}

void Peasant::update(){
    if(getState() == "Stopped"){
        stopCommand();
    }
    else if(timeInFarm == 0 && timeInCastle == 0){
        string state = "Heading to " + source->getName();
        setState(state);
        timeBeatsToSource--;
        pair<double,double> temp;
        temp.first = getLocation().first + cordinateSource.first;
        temp.second = getLocation().second + cordinateSource.second;
        setLocation(temp);
        if(timeBeatsToSource == 0){
            setLocation(source->getLocation());
            timeInFarm = 1;
        }
    }
    else if(timeInFarm == 1 && timeInCastle == 0 && flagSource == false){
        string state = "Loading packages in " + source->getName();
        setState(state);
        source->setAmount(source->getAmount()-packageLoad);
        flagSource = true;
    }
    else if(timeInFarm == 1 && timeInCastle == 0 && flagSource == true && flagDes == false){
        timeBeatsToDes--;
        string state = "Heading to " + getDestination()->getName();
        setState(state);
        pair<double,double> temp;
        temp.first = getLocation().first + cordinateDes.first;
        temp.second = getLocation().second + cordinateDes.second;
        setLocation(temp);
        if(timeBeatsToDes == 0){
            setLocation(getDestination()->getLocation());
            timeInCastle = 1;
            flagDes = true;
        }
    }
    else if(timeInFarm == 1 && timeInCastle == 1 && flagSource == true && flagDes == true){
        getDestination()->setAmount(getDestination()->getAmount()+package);
        string state = "Unpacking packages in " + getDestination()->getName();
        setState(state);
        flagDes = false;
        flagSource = false;
        if(health < 20){
            health++;
        }
    }
    else if(timeInFarm == 1 && timeInCastle == 1 && flagSource == false && flagDes == false){
        setState("Stopped");
        package = 0;
        packageLoad = 0;
    }
}

void Peasant::stratWorking(shared_ptr<SimObject> source,shared_ptr<SimObject> destination){
    this->source = source;
    setDestination(destination);
    if(source->getAmount() < 0 && package <= 5){
        //trow
    }
    if(source->getAmount() > 5){
        packageLoad = 5 - package;
        package = 5;
    }
    else{
        packageLoad = 5 - package;
        package = source->getAmount();
    }
    double x,y,distance;
    x = getLocation().first-source->getLocation().first;
    y = getLocation().second-source->getLocation().second;
    distance = (sqrt(x*x+y*y));
    double trail = (distance/getSpeed())*10;
    lengthSource = distance;
    timeBeatsToSource = ceil(trail);

    cordinateSource.first = ((x*(-1)/trail));
    cordinateSource.second = ((y*(-1)/trail));

    x = source->getLocation().first-destination->getLocation().first;
    y = source->getLocation().second-destination->getLocation().second;
    distance = (sqrt(x*x+y*y));
    trail = (distance/getSpeed())*10;
    lengthDestination = distance;
    timeBeatsToDes = ceil(trail);

    cordinateDes.first = ((x*(-1)/trail));
    cordinateDes.second = ((y*(-1)/trail));
    
    setState("Moving");
    timeInFarm = 0;
    timeInCastle = 0;
    flagSource = false;
    flagDes = false;
}

void Peasant::distanceFromMe(shared_ptr<SimObject> des){
    double X = sqrt(((getLocation().first - des->getLocation().first)*(getLocation().first - des->getLocation().first))
    +((getLocation().second - des->getLocation().second)*(getLocation().second - des->getLocation().second)));
    shared_ptr<Knight> s = dynamic_pointer_cast<Knight>(des);
    s->setLenFromPeasent(X*10); 
}

string Peasant::what() const{
    return "Peasant";
}