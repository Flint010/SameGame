#include "board.h"
#include <QPainter>
#include <QMouseEvent>

Board::Board(QWidget *parent)
    : QWidget{parent}, model(nullptr)
{

}

Board::~Board()
{
    qDebug() << "~Board()";
}

void Board::setModel(const BoardModel &newModel)
{
    if(model)
        disconnect(model, SIGNAL(dataChanged), this, SLOT(newData));

    model = &newModel;
    connect(model, SIGNAL(dataChangeed()), this, SLOT(newData()));
    newData();
}

void Board::newData()
{
    auto board = model->getBoard();
    if(board.empty())
        return;

    QRect rect(0, 0, board[0].size()*model->width(), board.size()*model->height());
    if(rect != this->rect()){
        this->setMinimumSize(QSize(board[0].size()*model->width(),board.size()*model->height()));
//        setGeometry(0, 0, board[0].size()*model->width(), board.size()*model->height());
    }

    repaint();

}

void Board::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBackground(QBrush("white"));
    painter.setPen(QPen(QBrush("black"),2));

    auto board = model->getBoard();
    if(board.empty())
        return;

    auto H = model->height();
    auto W = model->width();

    for(int i = 0; i < model->row(); i++) {
        for(int j = 0; j < model->col(); j++) {

            painter.setBrush(board[i][j]);

            QRect rect;
            rect.setTopLeft(QPoint(j*W, i*H));
            rect.setBottomRight(QPoint(j*W+W, i*H+H));

            painter.drawRect(rect);
        }
    }
}

void Board::mousePressEvent(QMouseEvent *event)
{
    auto x = event->pos().x();
    auto y = event->pos().y();

    if(x < 0 && x > this->width() && y < 0 && y > this->height())
        return;

    emit pressedAt(x/model->width(), y/model->height());
    qDebug() << y/model->height() << " " << x/model->width();
}


