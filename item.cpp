#include "item.h"

Item::Item()
{

}


Item::Item(ITEM_TYPE type,ITEM_COLOR color,QPoint p):m_type(type),m_color(color),m_pt(p),m_bShow(true)
{

}
Item::~Item()
{

}
