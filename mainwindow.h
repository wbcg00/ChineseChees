#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "item.h"
#include "qmap.h"
#include "qvector.h"
#include "qpixmap.h"
#include "qrect.h"
#include "QMouseEvent"
#include "qpainter.h"
#include "qpen.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitItems();
    void NewGame();
    void DeleteItemAtPoint(QPoint &pt,bool & res);
    void ChangeItemPoint(QPoint ptCur,QPoint ptTar);
    void DramItem(QPainter & p,Item& item);
    void GetMoveableAreas(Item &item,QVector<QPoint>& areas);

    void GetMoveableAreas_JU(Item &item, QVector<QPoint> &areas);
    void GetMoveableAreas_MA(Item &item, QVector<QPoint> &areas);
    void GetMoveableAreas_PAO(Item &item, QVector<QPoint> &areas);
    void GetMoveableAreas_SHI(Item &item, QVector<QPoint> &areas);
    void GetMoveableAreas_XIANG(Item &item, QVector<QPoint> &areas);
    void GetMoveableAreas_SHUAI(Item &item, QVector<QPoint> &areas);
    void GetMoveableAreas_BING(Item &item, QVector<QPoint> &areas);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void timerEvent(QTimerEvent *);
private:
    Ui::MainWindow *ui;
    int m_nItemWidth;
    int m_nItemHeigh;
    QPixmap m_ItemPixmap;
    QVector<Item> m_items;
    Item m_selectedItem;
    bool m_bIsExistSelectedItem;
    bool m_bIsRedRun;
    int m_timerID;
private:
    bool CheckItemAtPoint(QPoint pt,Item& it);
    void SetItemShow(Item& it,bool bShow);
};

#endif // MAINWINDOW_H
