#ifndef ITEM_H
#define ITEM_H

#include "qpainter.h"
#include "qpoint.h"
enum ITEM_TYPE{
    ITEM_SHUAI = 0, /*帅*/
    ITEM_SHI,       /*士*/
    ITEM_XIANG,     /*象*/
    ITEM_JU,        /*车*/
    ITEM_MA,        /*马*/
    ITEM_PAO,       /*炮*/
    ITEM_BING,      /*兵*/
    ITEM_MAX
};
enum ITEM_COLOR{
    COLOR_RED=0,    /*红方*/
    COLOR_BLACK,    /*黑方*/
    COLOR_MAX
};

class Item
{
public:
    Item();
    Item(ITEM_TYPE type,ITEM_COLOR color,QPoint p);
    ~Item();
public:
    ITEM_TYPE m_type;/*棋子类型*/
    ITEM_COLOR m_color;/*红方黑方*/
    QPoint m_pt;
    bool m_bShow;     /*是否显示*/
};

#endif // ITEM_H
