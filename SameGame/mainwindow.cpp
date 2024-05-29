#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), boardWidget(new Board)
{
    ui->setupUi(this);

    ui->verticalLayout->addWidget(boardWidget);

    initGame();

    this->setFixedSize(0,0);

    boardWidget->setModel(model);
    connect(boardWidget, SIGNAL(pressedAt(int,int)), &model, SLOT(deleteAt(int,int)));
    connect(&model, SIGNAL(gameOver(int)), this, SLOT(gameOver(int)));
    connect(ui->action_6, SIGNAL(triggered(bool)), this, SLOT(initGame()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gameOver(int count)
{
    QMessageBox msgBox;
    if(count == 0) {
        msgBox.setText("You WIN!");
    }else {
        msgBox.setText("Game Over");
        msgBox.setInformativeText(QString("Number of remaining blocks: %1").arg(count));
    }
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::initGame()
{
    QVector<QVector<QColor>> board(model.row());

    for(int i = 0; i < model.row(); i++) {
        for(int j = 0; j < model.col(); j++) {
            board[i].append(model.getColors().at(rand()%model.getColors().size()));
        }
    }
    model.setBoard(board);
}




