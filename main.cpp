#include<iostream>

#include "Controller.h"

using namespace std;

class Singleton{
    public:
        ~Singleton(){delete Model::ptr;} 
}Si;

Model* Model::ptr = nullptr;

int main(int argc,char* argv[]){
    if(argc!=3){
        cerr << "The file does not has enough argument" << endl;
        exit(EXIT_FAILURE);
    }
    try{
        Controller con(argv);
        con.run();
    } catch(Controller::EndProgram e){
        exit(EXIT_FAILURE);
    }

    return 0;
}