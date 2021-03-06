#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <iostream>
#include <QTextDocument>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);
    //oid QSyntaxHighlighter::highlightBlock ( const QString & text )
    // [pure virtual protected]

    //Highlights the given text block. This function is called when
    //necessary by the rich text engine, i.e. on text blocks which
    // have changed.
private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;
    QTextCharFormat addFormat;
    QTextCharFormat minusFormat;
};
#endif
//QTextEdit *editor = new QTextEdit;
//MyHighlighter *highlighter = new MyHighlighter(editor->document());

//After this your highlightBlock() function will be called automatically
//whenever necessary. 
//http://doc.trolltech.com/4.6/qsyntaxhighlighter.html#highlightBlock
