#include "reader.h"
#include <QtGui>

Reader::Reader()
{
    setupEditor();
    setCentralWidget(editor);
}
Reader::~Reader()
{
    cout<<"~Reader(): bye"<<endl;
}

void Reader::setupEditor()
{
    editor = new QTextEdit;
    highlighter = new Highlighter(editor->document());
    QFont font;
    font.setFamily("Lucica");
    font.setFixedPitch(true);
    font.setPointSize(13);
    editor->setFont(font);
    editor->setReadOnly(TRUE);
}

//cp from /home/peter/qtsdk-2010.01/qt/examples/richtext/syntaxhighlighter
void Reader::openFile(const QString &path)
{
//    QString fileName = path;
    fileName = path;

    if (!fileName.isEmpty()) 
    {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            editor->setPlainText(file.readAll());
    }
}
