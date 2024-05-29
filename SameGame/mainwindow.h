#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "boardmodel.h"
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void gameOver(int count);
    void initGame();

private:
    Ui::MainWindow *ui;
    BoardModel model;
    Board *boardWidget;
};
#endif // MAINWINDOW_H
