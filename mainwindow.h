#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::string GetStdoutFromCommand(std::string cmd);

private slots:
    void on_solveButton_clicked();
    void save();
    void load();
};

#endif // MAINWINDOW_H
