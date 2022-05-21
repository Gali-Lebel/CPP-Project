#include "View.h"

View::View(){
    size = {25};
    scale = {2.00};
    origin.first = {0};
    origin.second = {0};
}

void View::draw() const{
    cout<<"Dsplay size: "<<size<<", scalse: "<<scale<<", origin: " ;
    cout<<"("<<setprecision(2)<<origin.first<<" ,"<<origin.second<<")"<<endl; 
    int column = ((size*scale)-scale)+origin.second;
    int countRow = column;
    int row = origin.first;
    int temp = scale*3;
    int count;
    if(size%3 == 0){
        count = 1;
    }
    else if(size%3 == 1){
        count = 0;
    }
    else{
        count = 2;
    }
    if(count == 1){
        column = column-(scale*2);
    }
    if(count == 2){
        column = column-(scale);
    }
    while(column >= (origin.second)){
        vector<shared_ptr<SimObject>> vec = Model::getInstance().getObjectOnY(countRow, scale);
        if(count % 3 == 0){
            if((column < 0 || column > 9) && (column > -10 && column < 100)){
                cout<<" "<<column<<" ";
            }
            else if((column > -1 && column < 9)){
                cout<<"  "<<column<<" ";
            }
            else{
                cout<<column<<" ";
            }
            if(vec.size() != 0){
                for(int i = row; i <= (((size*scale)-scale)+origin.first); i = i+scale){
                    if(vec.size() != 0){
                        if(vec.at(0)->getLocation().first >= (i) && vec.at(0)->getLocation().first < (i+scale)){
                            string name = vec.at(0)->getName();
                            cout<<name.at(0)<<name.at(1);
                            vector<shared_ptr<SimObject>>::iterator it; 
                            it = vec.begin();
                            vec.erase(it);
                            while(!vec.empty()){
                                if(vec.at(0)->getLocation().first == (i) && vec.at(0)->getLocation().first < (i+scale)){
                                    vec.erase(it);
                                }
                                else{
                                    break;
                                }
                            } 
                        }
                        else{
                            cout<<". "; 
                        }
                    }
                    else{
                       cout<<". "; 
                    }
                } 
            }
            else{
                for(int i = 0; i < size; i++){
                   cout<<". "; 
                }
            }
            cout<<endl;
            column = column-temp;
        }
        else{
            cout<<"    ";
            if(vec.size() != 0){
                for(int i = row; i <= (((size*scale)-scale)+origin.first); i = i+scale){
                    if(vec.size() != 0){
                        if(vec.at(0)->getLocation().first <= (i) && vec.at(0)->getLocation().first < (i+scale)){
                            string name = vec.at(0)->getName();
                            cout<<name.at(0)<<name.at(1);
                            vector<shared_ptr<SimObject>>::iterator it; 
                            it = vec.begin();
                            vec.erase(it);
                            while(!vec.empty()){
                                if(vec.at(0)->getLocation().first == (i) && vec.at(0)->getLocation().first < (i+scale)){
                                    vec.erase(it);
                                }
                                else{
                                    break;
                                }
                            }
                        }
                        else{
                            cout<<". "; 
                        }
                    }
                    else{
                       cout<<". "; 
                    }
                } 
            }
            else{
                for(int i = 0; i < size; i++){
                   cout<<". "; 
                }
            }
            cout<<endl;
        }
        countRow = countRow - scale;
        count++;
    }
    if((row < 0 || row > 9) && (row > -10 && row < 100)){
        cout<<"   "<<row;
    }
    else if((row > -1 && row < 9)){
        cout<<"    "<<row;
    }
    else{
        cout<<"  "<<row;
    }
    row = row + temp;
    while(row <= ((((size*scale)-scale)+origin.first))){
        if((row < 0 || row > 9) && (row > -10 && row < 100)){
            cout<<"    "<<row;
        }
        else if((row > -1 && row < 9)){
            cout<<"     "<<row;
        }
        else{
            cout<<"   "<<row;
        }
        row = row + temp;
    }
    cout<<endl;
}

void View::setSize(int size){
    this->size = size;
}

void View::setScale(double scale){
    this->scale = scale;
}

void View::setOrigin(pair<double,double> origin){
    this->origin.first = origin.first;
    this->origin.second = origin.second;
}

void View::setDefaults(){
    size = 25;
    scale = 2.00;
    origin.first = 0;
    origin.second = 0;
}