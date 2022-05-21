#ifndef MODEL_H
#define MODEL_H

#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<utility>
#include<memory>
#include<algorithm>

#include "Castle.h"
#include "Farm.h"
#include "Peasant.h"
#include "Knight.h"
#include "Thug.h"
#define SIXTEEN 16
using namespace std;

class Model{
    private:
        Model();
        int time;
        static Model *ptr;
        vector<shared_ptr<SimObject>> structureList;
        vector<shared_ptr<SimObject>> agentList;
        vector<shared_ptr<SimObject>> simObjectList;
        vector<shared_ptr<SimObject>> knigthList;
        vector<shared_ptr<SimObject>> thugVec;
        friend class Singleton;
        ~Model(){}
    public:
        static Model& getInstance();
        Model(const Model& lhs) = delete;
        Model(Model&& rhs) = delete;
        Model& operator=(const Model& lhs) = delete;
        Model& operator=(Model&& rhs) = delete;
        vector<shared_ptr<SimObject>>& getSimObjectList();
        vector<shared_ptr<SimObject>>& getStructureList();
        vector<shared_ptr<SimObject>>& getAgentList();
        vector<shared_ptr<SimObject>> getObjectOnY(int y, double scale);
        void createWorld(char* argv[]);
        void addAgent(string line);
        bool checkNameAgent(string name) const;
        bool checkNameStructur(string name) const;
        bool checkPackage(int package) const;
        void sortByYaxis(vector<shared_ptr<SimObject>>& vec);
        void sortByXaxis(vector<shared_ptr<SimObject>>& vec);
        void move(string name, string line);
        int getTime() const;
        void setTime();
        void update();
        void status() const;
        void actionPeasant(string line, int findAgent);
        void actionKnight(string line, int findAgent);
        void actionThug(string line, int findAgent, string name);

        struct SortVectorByY{
            bool operator()(shared_ptr<SimObject> i, shared_ptr<SimObject> j){
                return i->getLocation().second > j->getLocation().second;
            }
        }sortVectorByY;

        struct SortVectorByX{
            bool operator()(shared_ptr<SimObject> i, shared_ptr<SimObject> j){
                return i->getLocation().first < j->getLocation().first;
            }
        }sortVectorByX;

        class FileNotOpen{};
        class WrongArguments{};
        class AgentNotExist{};
        class StructureNotExist{};
};
#endif