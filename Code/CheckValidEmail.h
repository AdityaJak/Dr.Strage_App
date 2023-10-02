#ifndef CHECKVALIDEMAIL_H
#define CHECKVALIDEMAIL_H
#include <iostream>
#include <QString>
class CheckValid{
public:
    bool is_valid(QString email)
    {
        quint32 At = -1, Dot = -1;
        for (quint32 i = 0; i < email.length(); i++) {
            // If the character is '@'
            if (email.at(i) == '@') {
                At = i;
            }
            // If character is '.'
            else if (email.at(i) == '.') {
                Dot = i;
            }
        }
        if (At == -1 || Dot == -1){
            return false;
        }
        // If Dot is present before At
        if (At > Dot){
            return false;
        }
        // If Dot is present at the end
        return !(Dot >= (email.length() - 1));
    }
};
#endif
