#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QString>
#include <QFileDialog>
#include <QWidget>
#include <QProcess>
#include <QToolTip>
#include <QPoint>

#include <fstream>

#include "parser.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:

    void on_Start_clicked();

    void on_BlogPositionBrowser_clicked();

    void on_imgBrowser_clicked();


    void on_tagsEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

};

#endif // MAINWINDOW_H
