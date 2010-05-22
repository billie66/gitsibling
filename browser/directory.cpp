#include<QPushButton>
#include<QDialogButtonBox>
#include<QGridLayout>
#include<QListWidgetItem>
#include<QString>
#include<QMap>
#include<QMapIterator>
#include<QDebug>

#include "directory.h"

Directory::Directory(const QMap<int, QString> &entryList,
              QWidget *parent) : QDialog(parent) 
{
    listWidget = new QListWidget;
    QMapIterator<int, QString> i(entryList);
    while(i.hasNext()){
        i.next();
        QListWidgetItem *item = new QListWidgetItem(i.value(),listWidget);
        //item->setIcon();
        item->setData(Qt::UserRole, i.key());
    }

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(listWidget, 0, 0);
    layout->addWidget(buttonBox, 1, 0);
    setLayout(layout);
    setWindowTitle(tr("File List"));

}

void Directory::done(int result)
{
    if (result == QDialog::Accepted){
        QListWidgetItem *item = listWidget->currentItem();
        if(item)
            text= item->text();
    }
    QDialog::done(result);
}
