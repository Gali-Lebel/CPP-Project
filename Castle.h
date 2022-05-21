#ifndef CASTLE_H
#define CASTLE_H

#include<iostream>
#include<list>

#include "Structure.h"

using namespace std;

class Castle : public Structure{
    private:
        int amount;
    public:
        Castle(string name , pair<double,double> location, int amount);
        int getAmount() const;
        void setAmount(int amount);  
        void currentState();     
        void update(){}
        string what() const;
        ~Castle(){}
};
#endif