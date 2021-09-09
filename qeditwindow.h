#ifndef QEDITWINDOW_H
#define QEDITWINDOW_H

#include <QMainWindow>

class QTextEdit;
class QFile;


class QEditWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *centralWidget;
    QTextEdit *edit;
    QFile *file;

    void createMenus();
protected:


public:
    QEditWindow(QWidget *parent = nullptr);
    ~QEditWindow();

public slots:
    void openFile();
    void closeFile();
    void saveFile();
};
#endif // QEDITWINDOW_H
