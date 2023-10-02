#ifndef CHECKVALIDPASSWORD_H
#define CHECKVALIDPASSWORD_H

#include <QString>

class CheckValidPass{
public:
    bool checkvalid(QString password){
        quint32 digit = -1, charac = -1, space = -1, punct = -1;
        for (quint32 i = 0; i < password.length(); i++){
            if (password.at(i).isLetter()){
                charac = 1;
            }
            if (password.at(i).isPunct()){
                punct = 1;
            }
            if (!password.at(i).isSpace()){
                space = 1;
            }
            if(password.at(i).isDigit()){
                digit = 1;
            }
        }
        if (charac == -1 || digit == -1 || space == -1 || punct == -1){
            return false;
        }
        return true;
    }
};
































#endif
