#ifndef VIEW_H
#define VIEW_H

#include<iostream>
#include<list>
#include<fstream>
#include<sstream>
#include<utility>
#include<memory>

#include "Model.h" 

using namespace std;

class View{
    private:
        int size;
        double scale;
        pair<double,double> origin;
    public:
        View();
        View(const View& lhs);
        View(View&& rhs);
        View& operator=(const View& lhs);
        View& operator=(View&& rhs);
        ~View(){}
        //void update_location(const std::string& name, pair<double,double> location);
        //void update_remove(const string& name); // Removes the name and its location; no error if the name is not present.
        void draw() const; /*prints out the current map*/
        void setSize(int size_); /*If the size is out of bounds will throw excpt*/
        void setScale(double scale_);/*If scale is not positive, will throw excpt*/
        void setOrigin(pair<double,double> origin_);
        void setDefaults();
};
#endif