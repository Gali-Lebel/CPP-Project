#include "Farm.h"

Farm::Farm(string name , pair<double,double> location, int amount, int rate): Structure(name, location){
    this->amount = {amount};
    this->rate = {rate};
}

int Farm::getRate() const{
    return rate;
}

int Farm::getAmount() const{
    return amount;
}

void Farm::setAmount(int amount){
    this->amount = amount;
}  

void Farm::currentState(){
    cout<<"Farm "<<getName()<<" at position ("<<setprecision(2)<<getLocation().first<<", "<<getLocation().second;
    cout<<"), Inventory: "<<getAmount()<<endl;
    
} 

void Farm::update(){
    amount += rate;
}

string Farm::what() const{
    return "Farm";
}