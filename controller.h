#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "boardmodel.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    BoardModel *getModel() const;

public slots:
    void deleteAt(int x, int y);

private:
    BoardModel* model;

};

#endif // CONTROLLER_H
