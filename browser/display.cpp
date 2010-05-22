#include <QLayout>
#include <QStringList>
#include <QDebug>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QFileInfo>
#include <iostream>

#include "display.h"
#include "directory.h"
#include "git.h"

using namespace std;

//DisplayWidget::DisplayWidget(QString &str): filePath(str) 
DisplayWidget::DisplayWidget()
//back in 558481f9, the above line is 
//DisplayWidget::DisplayWidget() :  QWidget()
//I changed it since the base class defualt constructor will 
//be called no matter you have ": QWidget" here or not
{
    QGridLayout *layout = new QGridLayout;
    fileButton = new QPushButton;
    fileButton->setText(tr("File"));
    layout->addWidget( fileButton, 0, 0 );
    lineEdit = new QLineEdit;
    lineEdit->setReadOnly( TRUE );
    layout->addWidget( lineEdit, 0, 1 );
    reader = new Reader;
    layout->addWidget( reader, 1, 0, 1, 4 );
    labelVersion = new QLabel;
    labelVersion->setText(tr("Version"));
    layout->addWidget( labelVersion, 0, 2 );
    spinBox = new QSpinBox;
    spinBox->setPrefix("v");
    spinBox->setWrapping(true);
    layout->addWidget( spinBox , 0, 3 );
    connect( spinBox, SIGNAL( valueChanged(int) ), this, SLOT( showFile(int) ));
    connect( fileButton, SIGNAL( clicked() ), this, SLOT( searchFile() ));
    connect( lineEdit, SIGNAL( textChanged(const QString &) ), 
                              this, SLOT( toGit(const QString &) ));
    connect( lineEdit, SIGNAL( textChanged(const QString &) ), 
                              this, SLOT( showFile(const QString &) ));
    setLayout(layout);

    git.getBranch();
    git.getTree();
}

void DisplayWidget::paintEvent ( QPaintEvent * event )
{
//cout<<"paintEvent.."<<endl;//there are repaint() all the time, why? FIXME
//repaint() can be called by many reason, I think this is natrual
}

void DisplayWidget::showFile(const QString &showFile)
{
    reader->openFile(showFile);
}

void DisplayWidget::showFile(int i)
{
    git.getSinglePatch(i);
    reader->openFile("singlePatch");
}

void DisplayWidget::toGit(const QString &file)
{
    git.setFileName(file);
    git.startGit();
    git.generatePatches();
    git.generateRevisions();
    int num = git.commits();
    showInitFile(num);
}

void DisplayWidget::showInitFile(int totalVersion)
{
//The order of the two statements must be as follow, or the result will not be perfect.
//The spinBox doesn't display the maxium version number when the lineEdit changed its text.   
    spinBox->setRange(0,totalVersion-1);
    spinBox->setValue(totalVersion-1);
}

void DisplayWidget::searchFile()
{
    QString dirTree = git.getDataTree();
    dirTree = dirTree.simplified();
    QStringList listDir = dirTree.split(" ");
    
    QMap<int, QString> map;
    for (int i = 0, j = 0; i < listDir.size(); i++, j++)
        map.insert(i, listDir.at(j));
        
// The Dialog is limited to listing files and subdirectories of the current directory, 
// but the contents of subdirs can't be viewed.So it will be settled in a good way.       
// Maybe replace QListWidget with QTreeWidget .     
    Directory *dir = new Directory(map, this);
    if (dir->exec()){
        QString fileName;
        fileName = dir->selectedText();
        QFileInfo fi(fileName);
        fileName = fi.absoluteFilePath();
        lineEdit->setText(fileName);
    }
    delete dir;
}
