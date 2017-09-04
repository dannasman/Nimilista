#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTextFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString searchString = ui->lineEdit->text();
    ui->textEdit->find(searchString, QTextDocument::FindWholeWords);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString addString = ui->lineEdit->text();
    QFile file("nimilista.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
             return;

    QTextStream out(&file);
    out << addString << "\n";
    file.close();
    loadTextFile();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString deleteString = ui->lineEdit->text();
    QFile file("nimilista.txt");
    if(!deleteString.isEmpty())
    {
        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QString string;
            QTextStream text(&file);
            while(!text.atEnd())
            {
                QString line = text.readLine();
                if(!line.contains(deleteString))
                    string.append(line + "\n");
            }
            file.resize(0);
            text << string;
            file.close();
            loadTextFile();
        }
    }
}

void MainWindow::loadTextFile()
{
    QFile inputFile("./nimilista.txt");
    inputFile.open(QIODevice::ReadWrite);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->textEdit->setPlainText(line);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}
