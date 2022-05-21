#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<utility>
#include<memory>
#include<algorithm>

#include "View.h"
#include "Model.h"

using namespace std;

class Controller{
    private:
        View v;
    public:
        Controller(char* argv[]);
        Controller(const Controller& lhs) = delete;
        Controller(Controller&& rhs) = delete;
        Controller& operator=(const Controller& lhs) = delete;
        Controller& operator=(Controller&& rhs) = delete;
        void run();
        void show();
        void go();
        ~Controller(){}

        class WrongInput{};
        class ExceptAnInteger{};
        class OutOfRange{};
        class ExceptDouble{};
        class EndProgram{};
        class WrongArgument{};
        class AgentNotExist{};
        class StructureNotExist{};

};
#endif