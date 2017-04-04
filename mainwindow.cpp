#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    QObject::connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::load);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_solveButton_clicked()
{
    std::string filename = "test.lp";
    std::ofstream outputFile(filename.c_str(), std::ofstream::out | std::ofstream::trunc);

    std::stringstream ss;

    if(ui->maxRadioButton->isChecked()){
        ss << "max: " + ui->objFuncBox->toPlainText().toStdString() + ";\n";
        qDebug() << QString::fromStdString("max: " + ui->objFuncBox->toPlainText().toStdString() + ";\n");
    }
    else if(ui->minRadioButton->isChecked()){
        ss << "min: " + ui->objFuncBox->toPlainText().toStdString() + ";\n";
        qDebug() << QString::fromStdString("min: " + ui->objFuncBox->toPlainText().toStdString() + ";\n");
    }

    std::string s = ui->constraintsBox->toPlainText().toStdString();

    std::istringstream iss (s);
    while(!iss.eof()){
        std::string s1;
        getline(iss, s1);
        ss << s1 << ";\n";

    }

    ss = std::stringstream(ss.str().substr(0, ss.str().size()-1));

    outputFile << ss.str();

    outputFile.close();

    ui->outputBox->setText(QString::fromStdString(GetStdoutFromCommand("/usr/local/bin/lp_solve -S3 test.lp")));

}


std::string MainWindow::GetStdoutFromCommand(std::string cmd) {

    std::string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
    while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
            pclose(stream);
    }
    return data;
}

void MainWindow::save(){

    QString filename = QFileDialog::getSaveFileName(this, "Save file", "", ".lp");
    std::ofstream outputFile(filename.toStdString().c_str(), std::ofstream::out | std::ofstream::trunc);

    std::stringstream ss;

    if(ui->maxRadioButton->isChecked()){
        ss << "max: " + ui->objFuncBox->toPlainText().toStdString() + ";\n";
        qDebug() << QString::fromStdString("max: " + ui->objFuncBox->toPlainText().toStdString() + ";\n");
    }
    else if(ui->minRadioButton->isChecked()){
        ss << "min: " + ui->objFuncBox->toPlainText().toStdString() + ";\n";
        qDebug() << QString::fromStdString("min: " + ui->objFuncBox->toPlainText().toStdString() + ";\n");
    }

    std::string s = ui->constraintsBox->toPlainText().toStdString();

    std::istringstream iss (s);
    while(!iss.eof()){
        std::string s1;
        getline(iss, s1);
        ss << s1 << ";\n";
    }

    ss = std::stringstream(ss.str().substr(0, ss.str().size()-1));

    outputFile << ss.str();

    outputFile.close();
    qDebug() << filename;
}

void MainWindow::load(){
    QString filename = QFileDialog::getOpenFileName(this, "OPEN FILE", "", "LP FILES (*.lp*)");
    std::ifstream inputFile(filename.toStdString().c_str());

    int count = 0;

    std::stringstream ss;

    while(!inputFile.eof()){
        std::string s1;
        getline(inputFile, s1);
        s1 = s1.substr(0, s1.size() - 1);
        if(count == 0){
            s1 = s1.substr(5, s1.size() - 5);
            ui->objFuncBox->setPlainText(QString::fromStdString(s1));
        }
        else{
            ss << s1 << "\n";
        }
        count++;
    }
    ss = std::stringstream(ss.str().substr(0, ss.str().size()-1));
    ui->constraintsBox->setPlainText(QString::fromStdString(ss.str()));
}
