#ifndef DISPLAY_CPP
#define DISPLAY_CPP

#include <QWidget>
#include <QSpinBox>

#include "reader.h"
#include "git.h"

class QLineEdit;
class QPushButton;
class QLabel;

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:                                                                       
    DisplayWidget();
    DisplayWidget(QString &str);
    void showInitFile(int);
    void generateTree();
public slots:
    void showFile(int);
    void showFile(const QString &);
    void searchFile();
    void toGit(const QString &);

private:
    QLineEdit *lineEdit;
    QString filePath;
    QLabel *labelVersion;
    QPushButton *fileButton;
    QSpinBox *spinBox;
    Reader *reader;
    Git git;
    void   paintEvent ( QPaintEvent * event );
};

#endif // DISPLAY_HPP
