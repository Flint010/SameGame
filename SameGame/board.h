#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "boardmodel.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();

    void setModel(const BoardModel& newModel);

signals:
    void pressedAt(int x, int y);

public slots:
    void newData();

private:
    const BoardModel *model;


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
};

#endif // BOARD_H
