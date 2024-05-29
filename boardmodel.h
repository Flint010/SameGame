#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QObject>
#include <QColor>
#include <QVector>

class BoardModel: public QObject
{
   Q_OBJECT
public:
    BoardModel(QObject* obj = nullptr);

    short width() const;
    void setWidth(short newWidth);

    short height() const;
    void setHeight(short newHeight);

    short row() const;
    void setRow(short newRow);

    short col() const;
    void setCol(short newCol);

    const QVector<QColor> &getColors() const;
    void setColor(const QVector<QColor> &newColor);
    void addColor(const QColor &newColor);

    const QVector<QVector<QColor>> &getBoard() const;
    void setBoard(const QVector<QVector<QColor> > &newBoard);

    bool isGameOver();

public slots:
    void deleteAt(int x, int y);

signals:
    void dataChangeed();
    void gameOver(int);

private:
    void deleteSame(int, int);
    void compact();

private:
    short m_width;
    short m_height;
    short m_row;
    short m_col;
    QVector<QColor> m_color;
    QVector<QVector<QColor>> m_board;
};

#endif // BOARDMODEL_H
