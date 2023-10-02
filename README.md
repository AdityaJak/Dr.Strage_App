# Dr. Strange

![image](https://user-images.githubusercontent.com/113259131/206882889-e0f07c98-ff58-4326-8798-731f67dd70af.png)


## Overview
Dr. Strange is a Windows/MacOS platform Modern C++ application, it is an application for doctors/nurses to keep their patients' information and share that information with other doctors. It can share patient information and possibly save lives in emergency cases. Moreover, it helps improve patient management in big hospital networks by minimizing new patient registration efforts.

## A list of Completed Features
-Login based on user type and give different level of access.
-Add new hospital
-Add new hospital admin for hospitals
-Add new doctor for hospitals.
-Add, update patients. Create appointments for patients.

## Instruction on How to Use The Application
-Download latest release.
-Run the application
-We have test users added for each user type. You can also create your own Hospital, Hospital Admin, and doctors. 
-You can use followin users to login to apllication.

Admin User:
Username: lula, password: password

Hospital Admin User:
Username: watertownadmin, Password: password1@

Doctor:
Username: frankwatertown, password: password1@

Note: There is known bug about application crashing. If application crashes without any erros message, you can just run it and try again.

## Development Configuration Instructions
- Download Qt from https://www.qt.io/download-open-source (It requires free registration)
- During installation select one of the compilers.(Example: Desktop Qt 6.4.0 MinGW 64-bit)
- Clone the code from github
- Open QT and Open Project and go to code folder in github local clone, then select "CMakeLists.txt"
- Go to Projects Tab on left side of QT and select the compiler you downloaded during instalation.(Example: Desktop Qt 6.4.0 MinGW 64-bit)

![image](https://user-images.githubusercontent.com/113259131/206882918-eb3120fb-89f0-4b12-87f4-a217575f22d3.png)


- Click build button from left tab or build menu on top menu.
- If build is successful, you should be able to run the application, but we need to copy SQL drivers into compiled folder.
- Copy the SQL dll files and sqldriver folder into your compiled folder.

![image](https://user-images.githubusercontent.com/113259131/206882964-c28a81e8-e458-4bf3-a22c-1a65e274766e.png)



## Instruction on How to Use The Application
-Download latest release.
-Run the application
-We have test users added for each user type. You can also create your own Hospital, Hospital Admin, and doctors. 
-You can use followin users to login to apllication.

Admin User:
Username: lula, password: password

Hospital Admin User:
Username: watertownadmin, Password: password1@

Doctor:
Username: frankwatertown, password: password1@

Note: There is known bug about application crashing. If application crashes without any erros message, you can just run it and try again.


## Deployment
- Copy the compiled DrStrange.exe file to an empty folder.
- Open MinGW terminal from start menu, then cd into the folder.
- Run deploy command: "windeployqt DrStrange.exe"
- Once it is completed, copy the files from resource folder(sql folder and sql dll files) into this folder.
- Run the application

## Team Members
-  Adithya Jakkaraju - Team Leader
-  Junyang Zhang(github: LukaDoncic7777777) - Requirement Leader
-  Huiyu Yi - QA leader
-  Erhan Ozturk - Design & Implementation leader
-  Qikun Xu - Git & Configuration Leader
-  Gaoyi Hu - Security Leader

## Tools and configuration setup

- IDE: Qt, Visual Studio Code
- Unit Testing: QT C++ testing
- Version Control: Git
- Project Management: Pivotal Tracker
- Platform: Virtual Machine, QT platform, DBeavor 
- Communication: Discord, Wechat, Gmail


