#ifndef GUI_H
#define GUI_H

#include <QtWidgets/QMainWindow>
//#include <qfiledialog.h>
#include "ui_GUI.h" // <ui_GUI.h>
//#include <qprocess.h>

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = Q_NULLPTR);

private:

    Ui::GUIClass ui;
private slots:
    void on_addButton_clicked();
    void on_loadButton_clicked();
    void on_saveButton_clicked();
    void on_encBox_changed();
    void on_delBox_changed();
    void on_addJunk_changed();
    void on_chgLoopBox_changed();
    void on_chgVarBox_changed();
    void on_openButton_clicked();
    void on_JunkerSumBox_changed();
    void on_JunkerSubBox_changed();
    void on_JunkerMulBox_changed();
    void on_JunkerConnectedBox_changed();
    void on_JunkerSemiConnectedBox_changed();
    void on_JunkerNonConnected_changed();
    void on_JunkerIncBox_changed();
};

#endif // GUI_H