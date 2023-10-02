#ifndef CHECKVALIDPHONE_H
#define CHECKVALIDPHONE_H

#include <QString>

class checkphone{
public:
    bool check(QString phone){
        if (phone.length() != 12){
            return false;
        }
        bool checkdash = true;
        for (quint32 i = 0; i < phone.length(); i++){
            if (phone.at(3) != '-' && phone.at(7) != '-'){
                checkdash = false;
            }
        }
        return checkdash;
    }
};







#endif // CHECKVALIDPHONE_H
