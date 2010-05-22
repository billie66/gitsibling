//The code is written in terms of Qt offical tutorial, C++ GUI Programming with Qt 4
#ifndef Directory_H
#define Directory_H

#include<QListWidget>
#include<QDialog>

class QDialogButtonBox;

class Directory : public QDialog
{
    Q_OBJECT

public:
    Directory(const QMap<int, QString> &, QWidget *parent=0);
    QString selectedText() {return text;}
    void done(int result);

private:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;
    QString text;
};

#endif
