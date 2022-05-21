#ifndef FARM_H
#define FARM_H

#include<iostream>
#include<list>

#include "Structure.h"

using namespace std;

class Farm : public Structure{
    private:
        int amount;
        int rate;    
    public:
        Farm(string name , pair<double,double> location, int amount, int rate);
        int getRate() const;
        int getAmount() const;
        void setAmount(int amount);  
        void currentState(); 
        void update();
        string what() const;
        ~Farm(){}
};
#endif