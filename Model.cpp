#include "Model.h"

Model::Model(){
    time = {0};
}

Model& Model::getInstance(){
    if(ptr!= nullptr){
        return *ptr;
    }
    ptr = new Model();
    return *ptr;
}

int Model::getTime() const{
    return time;
}

void Model::setTime(){
    time++;
}

vector<shared_ptr<SimObject>>& Model::getSimObjectList(){
    return simObjectList;
}

vector<shared_ptr<SimObject>>& Model::getStructureList(){
    return structureList;
}

vector<shared_ptr<SimObject>>& Model::getAgentList(){
    return agentList;
}

void Model::createWorld(char* argv[]){
    string castle = argv[1];
    string farm = argv[2];
    ifstream castleFile,farmFile;
    castleFile.open(castle);
    if(!castleFile.is_open()){
        cerr << "The file is not open!"<<endl;
        throw FileNotOpen();
    }
    
    farmFile.open(farm);
    if(!farmFile.is_open()){
        cerr << "The file is not open!"<<endl;
        throw FileNotOpen();
    }
    string line,comma=",";
    string name,bracket1="(",bracket2=")";
    string num1,num2,pack,portion;
    int index,index2,package,rate;
    double number1,number2;
    while(getline(castleFile,line)){
        index = line.find(comma);
        if(index==-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        name = line.substr(0,index);
        line = line.substr(index+1,line.size());
        index = line.find(bracket1);
        index2 = line.find(comma);
        if(index==-1 || index2==-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        num1 = line.substr(index+1,index2-1);
        line = line.substr(index2+1,line.size());
        index = line.find(bracket2);
        if(index==-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        num2 = line.substr(0,index);
        line = line.substr(index+2,line.size());
        index = line.find(comma);
        if(index!=-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        pack = line.substr(index+1,line.size());

        stringstream s1,s2,s3;
        s1<<num1;
        s1>>number1;
        s2<<num2;
        s2>>number2;
        s3<<pack;
        s3>>package;
        if(!(checkNameStructur(name)&&checkPackage(package))){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        pair <double, double> location;
        location.first = number1;
        location.second = number2;
        shared_ptr<SimObject> c1 = make_shared<Castle>(name,location,package);
        structureList.push_back(c1);
        simObjectList.push_back(c1);
    }
    castleFile.close();

    while(getline(farmFile,line)){
        index = line.find(comma);
        if(index==-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        name = line.substr(0,index);
        line = line.substr(index+1,line.size());
        index = line.find(bracket1);
        index2 = line.find(comma);
        if(index==-1 || index2==-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        num1 = line.substr(index+1,index2-1);
        line = line.substr(index2+1,line.size());
        index = line.find(bracket2);
        if(index==-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        num2 = line.substr(0,index);
        line = line.substr(index+2,line.size());
        index = line.find(comma);
        if(index==-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        pack = line.substr(0,index);
        line = line.substr(index+1,line.size());
        index = line.find(comma);
        if(index!=-1){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        portion = line.substr(0,line.size());

        stringstream s1,s2,s3,s4;
        s1<<num1;
        s1>>number1;
        s2<<num2;
        s2>>number2;
        s3<<pack;
        s3>>package;
        s4<<portion;
        s4>>rate;

        if(!(checkNameStructur(name)&&checkPackage(package)&&checkPackage(rate))){
            cerr << "The argument in the file are wrong"<<endl;
            throw WrongArguments();
        }
        pair <double, double> location;
        location.first = number1;
        location.second = number2;
        shared_ptr<SimObject> f1 = make_shared<Farm>(name,location,package,rate);
        structureList.push_back(f1);
        simObjectList.push_back(f1);
    }
    farmFile.close();
}

void Model::addAgent(string line){
    string space = " ",bracket1="(",bracket2=")",comma=",";
    int index, index2;
    index = line.find(space);
    if(index == -1){
        throw WrongArguments();
    }
    string name = line.substr(0,index);
    if(!(checkNameAgent(name))){
        throw WrongArguments();
    }
    line = line.substr(index+1, line.size());
    index = line.find(space);
    if(index == -1){
        throw WrongArguments();
    }
    string agent = line.substr(0,index);
    line = line.substr(index+1, line.size());
    if(agent == "Peasant" || agent == "Thug"){
        string num1,num2;
        double number1, number2;
        index = line.find(bracket1);
        index2 = line.find(comma);
        if(index==-1 || index2==-1){
            throw WrongArguments();
        }
        num1 = line.substr(index+1,index2-1);
        line = line.substr(index2+1,line.size());
        index = line.find(bracket2);
        if(index==-1){
            throw WrongArguments();
        }
        num2 = line.substr(0,index);

        stringstream s1,s2;
        s1<<num1;
        s1>>number1;
        s2<<num2;
        s2>>number2;

        pair <double, double> location;
        location.first = number1;
        location.second = number2;
        if(agent == "Peasant"){
            shared_ptr<SimObject> P1 = make_shared<Peasant>(name,location);
            agentList.push_back(P1);
            simObjectList.push_back(P1);
        }
        else{
            shared_ptr<SimObject> T1 = make_shared<Thug>(name,location);
            agentList.push_back(T1);
            simObjectList.push_back(T1);
        }
    }
    if(agent == "Knight"){
        string nameLocation = line;
        int size = structureList.size();
        bool find = false;
        pair<double,double> location;
        for(int i = 0; i < size; i++){
            if(structureList.at(i)->getName() == nameLocation){
                location.first = structureList.at(i)->getLocation().first;
                location.second = structureList.at(i)->getLocation().second;
                find = true;
                break;
            }
        }
        if(!find){
            throw WrongArguments();
        }
        shared_ptr<SimObject> K1 = make_shared<Knight>(name,nameLocation,location,structureList);
        agentList.push_back(K1);
        simObjectList.push_back(K1);
        knigthList.push_back(K1);
    }

}

bool Model::checkNameAgent(string name) const{
    for(int i = 0; i < agentList.size(); i++){
        if(agentList.at(i)->getName() == name){
            return false;
        }
    }
    int len = name.size();
    return len <= SIXTEEN;
}

bool Model::checkNameStructur(string name) const{
    for(int i = 0; i < structureList.size(); i++){
        if(structureList.at(i)->getName() == name){
            return false;
        }
    }
    int len = name.size();
    return len <= SIXTEEN;
}

bool Model::checkPackage(int package) const{
    return package >= 0;
}

void Model::sortByYaxis(vector<shared_ptr<SimObject>>& vec){
    sort(vec.begin(), vec.end(), sortVectorByY);
}

void Model::sortByXaxis(vector<shared_ptr<SimObject>>& vec){
    sort(vec.begin(), vec.end(), sortVectorByX);
}

vector<shared_ptr<SimObject>> Model::getObjectOnY(int y, double scale){
    int size = simObjectList.size();
    vector<shared_ptr<SimObject>> tmpVec;
    for(int i=0; i< size; i++){
        if(simObjectList.at(i)->getLocation().second <= y && simObjectList.at(i)->getLocation().second > (y-scale)){
            tmpVec.push_back(simObjectList.at(i));
        }
    }
    sortByXaxis(tmpVec);
    return tmpVec;
}

void Model::update(){
    int size = simObjectList.size();
    for(int i = 0; i < size; i++){
        simObjectList.at(i)->update();
    }
    shared_ptr<Thug> T; 
    for(int i = 0; i < thugVec.size(); i++){
        T = dynamic_pointer_cast<Thug>(thugVec.at(i));
        T->attack(knigthList);
    }
    if(!thugVec.empty()){
        thugVec.clear();
    }
    time++;
}

void Model::move(string name, string line){
    int findAgent=-1;
    for(int i = 0; i < agentList.size(); i++){
        if(agentList.at(i)->getName() == name){
            findAgent = i;
            break;
        }
    }
    if(findAgent == -1){
        throw AgentNotExist();
    }
    string myKind = agentList.at(findAgent)->what();
    if(myKind == "Peasant"){
        try{
            actionPeasant(line,findAgent);
        }
        catch(WrongArguments e){
            throw WrongArguments();
        }
        catch(StructureNotExist e){
            throw StructureNotExist();
        }
    }
    else if(myKind == "Knight"){
        try{
            actionKnight(line,findAgent);
        }
        catch(WrongArguments e){
            throw WrongArguments();
        }
        catch(AgentNotExist e){
            throw AgentNotExist();
        }
    }
    else if(myKind == "Thug"){
        try{
            actionThug(line,findAgent, name);
        }
        catch(WrongArguments e){
            throw WrongArguments();
        }
        catch(StructureNotExist e){
            throw StructureNotExist();
        }
    }
    else{
        throw WrongArguments();
    }
}

void Model::actionPeasant(string line, int findAgent){
    string space = " ";
    string command;
    int index;
    string farm,castle;
    index = line.find(space);
    if(index==-1){
        if(line=="stop"){
            shared_ptr<Peasant> p = dynamic_pointer_cast<Peasant>(agentList.at(findAgent));
            p->setState("Stopped");
            return;
        }
        else{
            throw WrongArguments();
        }
    }
    command = line.substr(0,index);
    line = line.substr(index+1,line.size());
    if(command != "start"){
        throw WrongArguments();
    }

    index = line.find(space);
    if(index==-1){
        throw WrongArguments();
    }
    farm = line.substr(0,index);
    line = line.substr(index+1,line.size());
    index = line.find(space);
    if(index!=-1){
        throw WrongArguments();
    }
    castle = line;
    shared_ptr<SimObject> source;
    shared_ptr<SimObject> destination;
    int cnt=0;
    for(int i=0;i<structureList.size();i++){
        if(structureList.at(i)->getName()==farm){
            source = structureList.at(i);
            cnt++;
        }
        if(structureList.at(i)->getName()==castle){
            destination = structureList.at(i);
            cnt++;
        }
    }
    if(cnt!=2){
        throw StructureNotExist();
    }
    shared_ptr<Peasant> p = dynamic_pointer_cast<Peasant>(agentList.at(findAgent));
    p->stratWorking(source,destination);
}

void Model::actionKnight(string line, int findAgent){
    string space = " ";
    string command;
    int index;
    string farm,castle;
    index = line.find(space);
    if(index==-1){
        if(line=="stop"){
            shared_ptr<Knight> p = dynamic_pointer_cast<Knight>(agentList.at(findAgent));
            p->setState("Stopped");
            p->setCommand("stop");
            return;
        }
        else{
            throw WrongArguments();
        }
    }
    command = line.substr(0,index);
    line = line.substr(index+1,line.size());
    if(command == "course"){
        for(int i = 0; i < line.size(); i++){
            if(!isdigit(line.at(i))){
               throw WrongArguments();
            }
        }
        stringstream s1;
        s1<<line;
        int angle;
        s1>>angle;
        shared_ptr<Knight> p = dynamic_pointer_cast<Knight>(agentList.at(findAgent));
        p->courseCommand(angle);
    }
    else if(command == "destination"){
        bool found = false;
        index = line.find(space);
        line = line.substr(index+1, line.size());
        if(index!=-1){
            throw WrongArguments();
        }
        shared_ptr<Structure> s;
        for(int i=0; i < structureList.size();i++){
            if(structureList.at(i)->getName() == line){
                s = dynamic_pointer_cast<Structure>(structureList.at(i));
                found = true;
            }
        }
        if(found == false){
            throw StructureNotExist();
        }
        shared_ptr<Knight> p = dynamic_pointer_cast<Knight>(agentList.at(findAgent));
        p->destinationCommand(s);
    }
    else if(command == "position"){
        string bracket1="(",bracket2=")",comma=",";
        string num1,num2;
        double number1, number2;
        index = line.find(bracket1);
        int index2 = line.find(comma);
        if(index==-1 || index2==-1){
            throw WrongArguments();
        }
        num1 = line.substr(index+1,index2-1);
        line = line.substr(index2+1,line.size());
        index = line.find(bracket2);
        if(index==-1){
            throw WrongArguments();
        }
        num2 = line.substr(0,index);
        line = line.substr(index+1,line.size());
        if(line.size()!=1){
            throw WrongArguments();
        }
        stringstream s1,s2;
        s1<<num1;
        s1>>number1;
        s2<<num2;
        s2>>number2;
        pair <double, double> location;
        location.first = number1;
        location.second = number2;
        shared_ptr<Knight> p = dynamic_pointer_cast<Knight>(agentList.at(findAgent));
        p->positionCommand(location);
    }
    else{
        throw WrongArguments();
    }
}

void Model::actionThug(string line, int findAgent, string name){
    string space = " ";
    string command;
    int index;
    string farm,castle;
    index = line.find(space);
    if(index==-1){
        if(line=="stop"){
            shared_ptr<Thug> p = dynamic_pointer_cast<Thug>(agentList.at(findAgent));
            p->setState("Stopped");
            return;
        }
        else{
            throw WrongArguments();
        }
    }
    command = line.substr(0,index);
    line = line.substr(index+1,line.size());
    if(command == "course"){
        index = line.find(space);
        if(index==-1){
            throw WrongArguments();
        }
        string tmpCourse = line.substr(0,index);
        for(int i = 0; i < tmpCourse.size(); i++){
            if(!isdigit(tmpCourse.at(i))){
               throw WrongArguments();
            }
        }
        line = line.substr(index+1,line.size());
        for(int i = 0; i < line.size(); i++){
            if(!isdigit(line.at(i)) && line.at(i) != '.'){
               throw WrongArguments();
            }
        }
        stringstream s1,s2;
        s1<<tmpCourse;
        s2<<line;
        int angle;
        double speed;
        s1>>angle;
        s2>>speed;
        shared_ptr<Thug> p = dynamic_pointer_cast<Thug>(agentList.at(findAgent));
        p->courseCommand(angle,speed);
    }
    
    else if(command == "position"){
        string bracket1="(",bracket2=")",comma=",";
        string num1,num2;
        double number1, number2,speed;
        index = line.find(bracket1);
        int index2 = line.find(comma);
        if(index==-1 || index2==-1){
            throw WrongArguments();
        }
        num1 = line.substr(index+1,index2-1);
        line = line.substr(index2+1,line.size());
        index = line.find(bracket2);
        if(index==-1){
            throw WrongArguments();
        }
        num2 = line.substr(0,index);
        line = line.substr(index+1,line.size());
        for(int i = 0; i < line.size(); i++){
            if(!isdigit(line.at(i)) && line.at(i) != '.'){
               throw WrongArguments();
            }
        }

        stringstream s1,s2,s3;
        s1<<num1;
        s1>>number1;
        s2<<num2;
        s2>>number2;
        s3<<line;
        s3>>speed;

        pair <double, double> location;
        location.first = number1;
        location.second = number2;
        
        shared_ptr<Thug> p = dynamic_pointer_cast<Thug>(agentList.at(findAgent));
        p->positionCommand(location,speed);
    }
    else if(command == "attack"){
        shared_ptr<Thug> T; 
        shared_ptr<Peasant> P;
        int count = 0;
        for(int i = 0; i < agentList.size(); i++){
            if(agentList.at(i)->getName() == name){
                T = dynamic_pointer_cast<Thug>(agentList.at(i));
                count++;
            }
            if(agentList.at(i)->getName() == line){
                P = dynamic_pointer_cast<Peasant>(agentList.at(i));
                count++;
            }
        }
        if(count != 2){
            throw AgentNotExist();
        }
        T->bullyAttack(P);
        thugVec.push_back(T);
    }
    else{
        throw WrongArguments();
    }
}

void Model::status() const{
    int size = simObjectList.size();
    for(int i = 0; i < size; i++){
        simObjectList.at(i)->currentState();
    }
}