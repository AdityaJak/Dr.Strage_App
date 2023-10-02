#ifndef USERLOGIN_H
#define USERLOGIN_H
#include <QString>

struct UserLogIn {

    QString UserClinician;
    QString ID;
    QString Role;
    QString EmailID;
    QString LoginID;
    QString Password;
    QString BadLoginCount;
    QString ChallengeAnswer;
    QString ChallengeQuesiton;
    QString ChangePassword;
    QString DatePasswordChanged;

   //Constructer
    UserLogIn(const QString& UserClinician, const QString& ID, const QString& Role, const QString& EmailID, const QString& LoginID, const QString& Password, const QString& BadLoginCount, const QString& ChallengeAnswer, const QString& ChallengeQuesiton, const QString& ChangePassword, const QString& DatePasswordChanged) :
        UserClinician(UserClinician),
        ID(ID),
        Role(Role),
        EmailID(EmailID),
        LoginID(LoginID),
        Password(Password),
        BadLoginCount(BadLoginCount),
        ChallengeAnswer(ChallengeAnswer),
        ChallengeQuesiton(ChallengeQuesiton),
        ChangePassword(ChangePassword),
        DatePasswordChanged(DatePasswordChanged)
    {}
};

#endif // USERLOGIN_H
