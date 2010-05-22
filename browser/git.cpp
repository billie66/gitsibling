#include <QDebug>
#include <QTemporaryFile>
#include <QList>
#include <QVariant>
#include <QTextStream>
#include <QProcess>
#include <iostream>
#include <QFileInfo>
#include "git.h"

using namespace std;

Git::Git(const QString &str): fileName(str)
{
}
Git::~Git() {}

/*
we can use this function to detect if we start git-reader in a repo or not
*/
bool Git::isFileInRepo()
{
    QProcess cmd;
//    cmd.setWorkingDirectory(fileInfo.absolutePath());
//   cout<<"absolutePath"<<qPrintable(fileInfo.absolutePath())<<endl;
    //'git rev-parse --is-inside-work-tree', inspired by qgit/src/git_stratup.cpp
    cmd.start("git", QStringList()<<"rev-parse"<<"--is-inside-work-tree");

    if (!cmd.waitForStarted())
        cout << "failed" << endl;
    
    if (!cmd.waitForFinished())
        cout<<"failed"<<endl;
    
    QByteArray ba;
    ba = cmd.readAllStandardOutput();
    ba = ba.trimmed();   //remove the trailing '\n'
    QString s(ba);       //easy to convert QByteArray->QString

    if(s == "true")
        return true;
    else
        return false;

}

void Git::startGit()
{
    QString patchFile = "filePatch";          
    QFileInfo fileInfo(fileName);

    QProcess cmd;
    cmd.setStandardOutputFile(patchFile, QIODevice::WriteOnly | QIODevice::Truncate);
    cmd.setWorkingDirectory(fileInfo.absolutePath()); 
    cmd.start("git", QStringList()<<"log"<<"-p"<<"--follow"<<fileName);
    if (!cmd.waitForFinished())
    {
        cout<<"failed"<<endl;
    }
}

void Git::generatePatches()
{
    QFile file("filePatch");
    if (!file.open(QIODevice::ReadOnly)){
        std::cerr << "can not open file for reading:" 
                        << qPrintable(file.errorString()) << std::endl;
       return;
    }

    QTextStream in(&file);
    int row = 0;
    if (!strVector.isEmpty())
        strVector.clear();
    if (!lineNum.isEmpty())
        lineNum.clear();

    while (!in.atEnd())
    {
        ++row;
        QString line = in.readLine();
        QString firstWord = line.left(6);
        if (firstWord == "commit")
            lineNum.append(row);
        strVector.append(line);
    }

//  foreach (int value, lineNum)
//      cout << "value:" << value << endl;
//  cout << "row:" << row << endl;
}

void Git::getSinglePatch(int ver)
{
    QFile Patch("singlePatch");
    if (!Patch.open(QIODevice::WriteOnly)){
        std::cerr << "can not open file for reading:" 
                      << qPrintable(Patch.errorString()) << std::endl;
       return;
    }
    QTextStream out(&Patch);
    if (ver == 0){
        for (int i=0; i < lineNum.at(1)-1; i++)
        out << strVector.at(i) + "\n";
    }
    else if (ver == lineNum.count()-1){
        for (int i = lineNum.at(ver)-1; i < strVector.count(); i++)
        out << strVector.at(i) + "\n";
    }
    else{
        for (int i = lineNum.at(ver)-1; i < lineNum.at(ver+1)-1; i++)
        out << strVector.at(i) + "\n";
    }
}

void Git::generateRevisions()
{
    totalCommits = 0;
    QTemporaryFile numFile;
    if (!numFile.open())
        return;
    QString num = numFile.fileName();
    QProcess log;
    log.setStandardOutputFile(num, QIODevice::WriteOnly);
    log.start("git", QStringList()<<"log"<<"--pretty=oneline"<<"--follow"<<fileName);
    if (!log.waitForFinished())
    {
        cout<<"failed"<<endl;
    }
    numFile.close();
    QFile file1(num);
    if (!file1.open(QIODevice::ReadOnly)){
        cerr << "Cannot open file for reading:"
                      << qPrintable(file1.errorString()) << endl;
        return;
    }
    QTextStream infile(&file1);

    while (!infile.atEnd()){
        QString line = infile.readLine();
        ++totalCommits;
    }
    cout << "totalCommits:" << totalCommits << endl;
}

void Git::getBranch()
{
    QByteArray name;
    QString str;
    QStringList list;
    QProcess cmd;
    cmd.start("git", QStringList() << "branch");
    
    if (!cmd.waitForStarted())
         cout << "wrong" << endl;

    if (!cmd.waitForFinished())
         cout << "wrong" << endl;

    name = cmd.readAll();
    str = QString(name);
    str = str.simplified();
    list = str.split(" ");
    int i=0;
    while (i != list.size()){
        if(list.at(i) == "*"){
            branch = list.at(i+1);
          break;
        }
        ++i;
    }
    qDebug() << "branch name:" << branch;
}

void Git::getTree()
{
    QByteArray dir;
    QStringList argument;
    argument << "ls-tree" << "--name-only" << branch;

    QProcess cmd1;
    cmd1.start("git", argument);
    if (!cmd1.waitForStarted())
         cout << "wrong" << endl;

    if (!cmd1.waitForFinished())
         cout << "wrong" << endl;

    dir = cmd1.readAll();
    tree = QString(dir);
 //   qDebug()<<tree;
}

QString Git::getDataTree() const
{
    return tree;
}
