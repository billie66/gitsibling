#include <QApplication>
#include <iostream>
#include <QMessageBox>
#include "display.h"
#include "git.h"
/*!
@brief main of all

the des of main goes here

@param nIndex 0: Update, 1:Install, 2:Erase
*/
// the code is modified as my idea. 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Git git;
    if(!git.isFileInRepo()){
        QMessageBox tip;
        tip.setText("The file is not in git repo.");
        int value = tip.exec();
        if (value == QMessageBox::Ok)
            return -1;
    }
    DisplayWidget display;
    display.resize(640, 512);
    display.setWindowTitle("the name of the file, baseName(absPath)");
    display.setGeometry(100,100,1300,700);
    display.show();
    return app.exec();
}

