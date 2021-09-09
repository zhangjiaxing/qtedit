#include <QDebug>
#include <QtWidgets>

#include "qeditwindow.h"


QEditWindow::QEditWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->createMenus();
    this->file = nullptr;
    this->centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QBoxLayout *vbox= new QVBoxLayout(centralWidget);
    vbox->setMargin(0);

    this->edit = new QTextEdit(centralWidget);
    vbox->addWidget(this->edit);

    this->centralWidget->setLayout(vbox);
    this->resize(900, 600);
}


QEditWindow::~QEditWindow()
{
}

void QEditWindow::createMenus()
{
    QMenu *file = this->menuBar()->addMenu("File");
    QAction *openAct = file->addAction("Open");
    QAction *saveAct = file->addAction("Save");
    QAction *closeAct = file->addAction("Close");
    QAction *exitAct = file->addAction("Exit");

    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(closeAct, SIGNAL(triggered()), this, SLOT(closeFile()));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

}

void QEditWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName();
    if(filename.isEmpty()){
        return;
    }else{
        this->closeFile();
    }

    this->file = new QFile(filename, this);
    bool ret = file->open(QIODevice::ReadOnly | QIODevice::Text);
    if(!ret){

        QMessageBox::information(this, "open failed", "open failed", QMessageBox::Ok);
    }else{

        QByteArray content_bytes = file->readAll();
        QString content = QString::fromUtf8(content_bytes);
        this->edit->document()->setPlainText(content);
        this->file->close();
    }
}

void QEditWindow::saveFile()
{
    if(this->file == nullptr){
        return;
    }

    QString content = this->edit->document()->toPlainText();
    if(this->file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text) and (file->write(content.toUtf8()) != -1)){
        this->closeFile();
        this->edit->document()->clear();
        QMessageBox::information(this, "save successed", "save successed", QMessageBox::Ok);
    }else{
        QMessageBox::information(this, "save failed", "save failed", QMessageBox::Ok);
    }
}

void QEditWindow::closeFile()
{
    if(this->file != nullptr){
        this->file->close();
        this->file = nullptr;
    }
    this->edit->document()->clear();
}

