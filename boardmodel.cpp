#include "boardmodel.h"

BoardModel::BoardModel(QObject* obj)
    :QObject(obj), m_width(35), m_height(35), m_row(15), m_col(15)
{
    m_color.append(QColor("red"));
    m_color.append(QColor("blue"));
    m_color.append(QColor("yellow"));
}

short BoardModel::width() const
{
    return m_width;
}

void BoardModel::setWidth(short newWidth)
{
    m_width = newWidth;
    emit dataChangeed();
}

short BoardModel::height() const
{
    return m_height;
}

void BoardModel::setHeight(short newHeight)
{
    m_height = newHeight;
    emit dataChangeed();
}

short BoardModel::row() const
{
    return m_row;
}

void BoardModel::setRow(short newRow)
{
    m_row = newRow;
    emit dataChangeed();
}

short BoardModel::col() const
{
    return m_col;
}

void BoardModel::setCol(short newCol)
{
    m_col = newCol;
    emit dataChangeed();
}

const QVector<QColor> &BoardModel::getColors() const
{
    return m_color;
}

void BoardModel::setColor(const QVector<QColor> &newColor)
{
    m_color = newColor;
    emit dataChangeed();
}

void BoardModel::addColor(const QColor &newColor)
{
    m_color.emplaceBack(newColor);
    emit dataChangeed();
}

const QVector<QVector<QColor> > &BoardModel::getBoard() const
{
    return m_board;
}

void BoardModel::setBoard(const QVector<QVector<QColor> > &newBoard)
{
    m_board = newBoard;
    emit dataChangeed();
}

bool BoardModel::isGameOver()
{
    int count = 0;
    for(int j = 0; j < m_col; j++) {
        for(int i = m_row - 1; i >= 0; i--) {
            auto color = m_board[i][j];
            if(color == QColor("black"))
                break;
            count++;
            if(i-1 >= 0 && m_board[i-1][j] == color)
                return false;
            if(j+1 < m_col && m_board[i][j+1] == color)
                return false;
        }
    }
    emit gameOver(count);
    return true;
}

void BoardModel::deleteAt(int x, int y)
{
    if(m_board[y][x] == QColor("black")) return;

    auto color = m_board[y][x];

    if((y-1 >= 0 && m_board[y-1][x] == color) ||
       (x+1 < m_col && m_board[y][x+1] == color) ||
       (y+1 < m_row && m_board[y+1][x] == color) ||
       (x-1 >= 0 && m_board[y][x-1] == color))
    {
        deleteSame(x, y);
        compact();
        emit dataChangeed();
        isGameOver();
    }
}

void BoardModel::deleteSame(int x, int y)
{
    if(x < 0 || x >= m_col) return;
    if(y < 0 || y >= m_row) return;

    auto color = m_board[y][x];
    m_board[y][x] = QColor("black");

    if(y-1 >= 0 && m_board[y-1][x] == color)
        deleteSame(x, y-1);

    if(x+1 < m_col && m_board[y][x+1] == color)
        deleteSame(x+1, y);

    if(y+1 < m_row && m_board[y+1][x] == color)
        deleteSame(x, y+1);

    if(x-1 >= 0 && m_board[y][x-1] == color)
        deleteSame(x-1, y);
}

void BoardModel::compact()
{
    // push down
    int find_ptr = 0;

    for(int j = 0; j < m_col; j++) {
        find_ptr = m_row-1;
        for(int i = m_row-1; i >= 0; i--) {
            if(m_board[i][j] == QColor("black")) {
                if(find_ptr > i)
                    find_ptr = i;
                while(--find_ptr >= 0) {
                    if(m_board[find_ptr][j] != QColor("black")) {
                        m_board[i][j] = m_board[find_ptr][j];
                        m_board[find_ptr][j] = QColor("black");
                        break;
                    }
                }
                if(find_ptr < 0)
                    break;
            }
        }
    }

    // push right to left
    find_ptr = 0;
    int i = m_row-1;
    for(int j = 0; j < m_col; j++) {
        if(m_board[i][j] == QColor("black")) {
            if(find_ptr < j)
                find_ptr = j;
            while(++find_ptr < m_col) {
                if(m_board[i][find_ptr] != QColor("black")) {
                    int row = i;
                    while(row >= 0 && m_board[row][find_ptr] != QColor("black")) {
                        m_board[i][j] = m_board[row][find_ptr];
                        m_board[row][find_ptr] = QColor("black");
                        row--;
                        i--;
                    }
                    i = m_row-1;
                    break;
                }
            }
            if(find_ptr >= m_col)
                break;
        }
    }
}

