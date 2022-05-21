#include "Castle.h"

Castle::Castle(string name , pair<double,double> location, int amount): Structure(name, location){
    this->amount = {amount};
}

int Castle::getAmount() const{
    return amount;
}

void Castle::setAmount(int amount){
    this->amount = amount;
}

void Castle::currentState(){
    cout<<"Castle "<<getName()<<" at position ("<<setprecision(2)<<getLocation().first<<", "<<getLocation().second;
    cout<<"), Inventory: "<<getAmount()<<endl;
    
} 

string Castle::what() const{
    return "Castle";
}