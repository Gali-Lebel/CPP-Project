#include "Controller.h"

Controller::Controller(char* argv[]){
    try{
        Model::getInstance().createWorld(argv);
    }
    catch(...){
        throw EndProgram();
    }
}

void Controller::run(){
    string line, command;
    string space = " ";
    int index;
    while(true){
        try{
            cout<<"Time "<<Model::getInstance().getTime()<<": Enter command: ";
            getline(cin,line);
            index = line.find(space);
            command = line.substr(0,index);
            line = line.substr(index+1, line.size()); 
            if(command == "create"){
                try{
                    Model::getInstance().addAgent(line);
                }catch(Model::WrongArguments e){
                    throw WrongArgument();
                }
            }
            else if(command == "go"){
                Model::getInstance().update();
            }
            else if(command == "status"){
                Model::getInstance().status();
            }
            else if(command == "default"){
                v.setDefaults();
            }
            else if(command == "size"){
                for(int i = 0; i < line.size(); i++){
                    if(!isdigit(line.at(i))){
                        throw ExceptAnInteger();
                    }
                }
                stringstream ss;
                ss<<line;
                int size;
                ss>>size;
                if(size < 6 || size >= 30){
                    throw OutOfRange();
                }
                v.setSize(size);
            }
            else if(command == "zoom"){
                for(int i = 0; i < line.size(); i++){
                    if(!isdigit(line.at(i)) && line.at(i) != '.'){
                        throw ExceptDouble();
                    }
                }
                stringstream ss;
                ss<<line;
                double scale;
                ss>>scale;
                if(scale <= 0){
                    throw OutOfRange();
                }
                v.setScale(scale);
            }
            else if(command == "show"){
                v.draw();
            }
            else if(command == "pan"){
                index = line.find(space);
                if(index == -1){
                    throw WrongInput();
                }
                string num1, num2;
                num1 = line.substr(0,index);
                num2 = line.substr(index+1, line.size());
                for(int i = 0; i < num1.size(); i++){
                    if(!isdigit(num1.at(i)) && num1.at(i) != '-'){
                        throw ExceptAnInteger();
                    }
                }
                for(int i = 0; i < num2.size(); i++){
                    if(!isdigit(num2.at(i)) && num2.at(i) != '-'){
                        throw ExceptAnInteger();
                    }
                }
                stringstream s1,s2;
                s1<<num1;
                s2<<num2;
                int number1, number2;
                s1>>number1;
                s2>>number2;
                pair<double,double> temp;
                temp.first = number1;
                temp.second = number2;
                v.setOrigin(temp);
            }
            else if(command == "exit"){
                cout << "Bye Bye! watch out for thugs :)" << endl;
                return;
            }
            else{
                try{
                    Model::getInstance().move(command, line);
                }
                catch(Model::WrongArguments e){
                    throw WrongArgument();
                }
                catch(Model::AgentNotExist e){
                    throw AgentNotExist();
                }
                catch(Model::StructureNotExist e){
                    throw StructureNotExist();
                }
            }
        }
        catch(WrongInput e){
            cerr << "ERROR: wrong input." << endl;
        }
        catch(ExceptAnInteger e){
            cerr << "ERROR: Excepted an integer." << endl;
        }
        catch(OutOfRange e){
            cerr << "ERROR: Out of range." << endl;
        }
        catch(ExceptDouble e){
            cerr << "ERROR: Except a double." << endl;
        }
        catch(WrongArgument e){
            cerr << "ERROR: wrong argument! try again." << endl;
        }
        catch(AgentNotExist e){
            cerr << "ERROR: wrong argument! the agent is not exist. try again." << endl;
        }
        catch(StructureNotExist e){
            cerr << "ERROR: wrong argument! the structure is not exist. try again." << endl;
        }
    }
}

void Controller::show(){
    v.draw();
}

void Controller::go(){
    Model::getInstance().update();
}