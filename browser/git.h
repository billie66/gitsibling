#ifndef GIT_H
#define GIT_H

#include <QWidget>

class Git : public QWidget
{
    Q_OBJECT

public:
    Git(): totalCommits(0) {}
    Git(const QString &str);
    bool isFileInRepo();
    void startGit();
    void generatePatches();
    void getSinglePatch(int);
    void generateRevisions();
    void setFileName(const QString &file){ fileName = file;} 
    int commits() const { return totalCommits;}
    void getBranch();
    void getTree();
    QString getDataTree() const; 
    ~Git();
public slots:

private:
    QString fileName;
    QString branch;
    QString tree;
    QString outPutString;
    QList<int> lineNum; 
    QVector<QString> strVector;
    int totalCommits;
};

#endif // GIT_H
