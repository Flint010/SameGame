#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent)
    : QObject{parent}, model(new BoardModel)
{

}

Controller::~Controller()
{
    delete model;
}

void Controller::deleteAt(int x, int y)
{
    model->deleteAt(x,y);
}

BoardModel *Controller::getModel() const
{
    return model;
}
