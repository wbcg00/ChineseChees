#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#define TRACE

#ifdef TRACE
#define tcout qDebug()
#else
#define tcout /\/
#endif
#define RECT_WIDTH 55
#define RECT_HEIGHT 56

//棋盘左上定点像素值（35，45），棋盘的格子大小（96，96）
#define START_X (36-RECT_WIDTH/2)
#define START_Y (45-RECT_HEIGHT/2)
//#define START_X 0
//#define START_Y 0

#define GRID_ROWS 11
#define GRID_COLS 10
#define POS_ROW GRID_ROWS-1 //棋盘一共10行
#define POS_COL GRID_COLS-1 //棋盘一共9列
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化棋盘
    QPixmap qipan(":/image/ChessBoard.png");
    this->setFixedSize(qipan.size());

    QPalette pal;
    pal.setBrush(QPalette::Window,QBrush(qipan));
    this->setPalette(pal);

    m_ItemPixmap = QPixmap(":/image/items.png");
    m_nItemHeigh=m_ItemPixmap.height()/ITEM_MAX;
    m_nItemWidth = m_ItemPixmap.width()/COLOR_MAX;

    m_selectedItem.m_pt=QPoint(-1,-1);
    NewGame();
    m_timerID =startTimer(500);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::InitItems()
{
    m_items.clear();

    //初始化黑方棋子
    Item b_item1(ITEM_JU,COLOR_BLACK,QPoint(0,0));
    Item b_item2(ITEM_MA,COLOR_BLACK,QPoint(1,0));
    Item b_item3(ITEM_XIANG,COLOR_BLACK,QPoint(2,0));
    Item b_item4(ITEM_SHI,COLOR_BLACK,QPoint(3,0));
    Item b_item5(ITEM_SHUAI,COLOR_BLACK,QPoint(4,0));
    Item b_item6(ITEM_SHI,COLOR_BLACK,QPoint(5,0));
    Item b_item7(ITEM_XIANG,COLOR_BLACK,QPoint(6,0));
    Item b_item8(ITEM_MA,COLOR_BLACK,QPoint(7,0));
    Item b_item9(ITEM_JU,COLOR_BLACK,QPoint(8,0));
    Item b_item10(ITEM_PAO,COLOR_BLACK,QPoint(1,2));
    Item b_item11(ITEM_PAO,COLOR_BLACK,QPoint(7,2));
    Item b_item12(ITEM_BING,COLOR_BLACK,QPoint(0,3));
    Item b_item13(ITEM_BING,COLOR_BLACK,QPoint(2,3));
    Item b_item14(ITEM_BING,COLOR_BLACK,QPoint(4,3));
    Item b_item15(ITEM_BING,COLOR_BLACK,QPoint(6,3));
    Item b_item16(ITEM_BING,COLOR_BLACK,QPoint(8,3));

   //初始化红方棋子
    Item r_item1(ITEM_JU,COLOR_RED,QPoint(0,9));
    Item r_item2(ITEM_MA,COLOR_RED,QPoint(1,9));
    Item r_item3(ITEM_XIANG,COLOR_RED,QPoint(2,9));
    Item r_item4(ITEM_SHI,COLOR_RED,QPoint(3,9));
    Item r_item5(ITEM_SHUAI,COLOR_RED,QPoint(4,9));
    Item r_item6(ITEM_SHI,COLOR_RED,QPoint(5,9));
    Item r_item7(ITEM_XIANG,COLOR_RED,QPoint(6,9));
    Item r_item8(ITEM_MA,COLOR_RED,QPoint(7,9));
    Item r_item9(ITEM_JU,COLOR_RED,QPoint(8,9));
    Item r_item10(ITEM_PAO,COLOR_RED,QPoint(1,7));
    Item r_item11(ITEM_PAO,COLOR_RED,QPoint(7,7));
    Item r_item12(ITEM_BING,COLOR_RED,QPoint(0,6));
    Item r_item13(ITEM_BING,COLOR_RED,QPoint(2,6));
    Item r_item14(ITEM_BING,COLOR_RED,QPoint(4,6));
    Item r_item15(ITEM_BING,COLOR_RED,QPoint(6,6));
    Item r_item16(ITEM_BING,COLOR_RED,QPoint(8,6));

    m_items.push_back(b_item1);
    m_items.push_back(b_item2);
    m_items.push_back(b_item3);
    m_items.push_back(b_item4);
    m_items.push_back(b_item5);
    m_items.push_back(b_item6);
    m_items.push_back(b_item7);
    m_items.push_back(b_item8);
    m_items.push_back(b_item9);
    m_items.push_back(b_item10);
    m_items.push_back(b_item11);
    m_items.push_back(b_item12);
    m_items.push_back(b_item13);
    m_items.push_back(b_item14);
    m_items.push_back(b_item15);
    m_items.push_back(b_item16);

    m_items.push_back(r_item1);
    m_items.push_back(r_item2);
    m_items.push_back(r_item3);
    m_items.push_back(r_item4);
    m_items.push_back(r_item5);
    m_items.push_back(r_item6);
    m_items.push_back(r_item7);
    m_items.push_back(r_item8);
    m_items.push_back(r_item9);
    m_items.push_back(r_item10);
    m_items.push_back(r_item11);
    m_items.push_back(r_item12);
    m_items.push_back(r_item13);
    m_items.push_back(r_item14);
    m_items.push_back(r_item15);
    m_items.push_back(r_item16);
}
void MainWindow::NewGame()
{
    InitItems();
    m_bIsRedRun=false;
    m_bIsExistSelectedItem = false;
}

void MainWindow::DeleteItemAtPoint(QPoint &pt, bool &res)
{
    for(int i =0;i<m_items.size();i++){
        if(m_items[i].m_pt == pt){
            res =(m_items[i].m_type == ITEM_SHUAI);
            m_items.erase(m_items.begin()+i);
            return;
        }
    }
}

void MainWindow::ChangeItemPoint(QPoint ptCur, QPoint ptTar)
{
    for(int i = 0;i<m_items.size();i++)
    {
        if(m_items[i].m_pt == ptCur){
            m_items[i].m_pt = ptTar;
            m_items[i].m_bShow =true;
            update();
            break;
        }
    }
}

void MainWindow::DramItem(QPainter &p, Item& item)
{
    if(!item.m_bShow){
        return;
    }
    QRect rcSrc(m_nItemWidth*item.m_color,
                m_nItemHeigh*item.m_type,
                m_nItemWidth,
                m_nItemHeigh);

    QRect rcTarget(START_X + item.m_pt.x()*RECT_WIDTH,
                   START_Y + item.m_pt.y()*RECT_HEIGHT,
                   RECT_WIDTH,
                   RECT_HEIGHT);
    p.drawPixmap(rcTarget,m_ItemPixmap,rcSrc);
}

void MainWindow::GetMoveableAreas(Item& item, QVector<QPoint> &areas)
{
    switch (item.m_type) {
    case ITEM_BING:
        GetMoveableAreas_BING(item,areas);
        break;
    case ITEM_JU:
         GetMoveableAreas_JU(item,areas);
        break;
    case ITEM_MA:
         GetMoveableAreas_MA(item,areas);
        break;
    case ITEM_PAO:
         GetMoveableAreas_PAO(item,areas);
        break;
    case ITEM_SHI:
         GetMoveableAreas_SHI(item,areas);
        break;
    case ITEM_SHUAI:
         GetMoveableAreas_SHUAI(item,areas);
        break;
    case ITEM_XIANG:
          GetMoveableAreas_XIANG(item,areas);
        break;
    default:
        break;
    }
}

void MainWindow::GetMoveableAreas_JU(Item &item, QVector<QPoint> &areas)
{
    //棋子“车”的计算可移动区域算法简介：
    //1，向4个方向上依次遍历点，把空点都加入。
    //当碰到棋子时停止，如果是同色棋子，不加入；是异色棋子，则加入（该处认为可走，因为可以吃子）

    //往上
    int y = item.m_pt.y();
    while (y>0) {
        QPoint ptNew = QPoint(item.m_pt.x(),y-1);
        Item tmp_it;
        if(CheckItemAtPoint(ptNew,tmp_it))
        {
            if(tmp_it.m_color != item.m_color)//敌方棋子，可以吃一次
            {
                areas.push_back(ptNew);
            }
            //是自己的棋子，不可以走了
            break;

        }else{
             areas.push_back(ptNew);
             y--;
        }
    }
    //往下
    y = item.m_pt.y();
    while(y<POS_COL){
         QPoint ptNew = QPoint(item.m_pt.x(),y+1);
         Item tmp_it;
         if(CheckItemAtPoint(ptNew,tmp_it))
         {
             if(tmp_it.m_color != item.m_color)//敌方棋子，可以吃一次
             {
                 areas.push_back(ptNew);
             }
             //是自己的棋子，不可以走了
             break;

         }else{
             areas.push_back(ptNew);
             y++;
         }
    }
    //往左
    int x= item.m_pt.x();
    while(x>0){
        QPoint ptNew = QPoint(x-1,item.m_pt.y());
        Item tmp_it;
        if(CheckItemAtPoint(ptNew,tmp_it))
        {
            if(tmp_it.m_color != item.m_color)//敌方棋子，可以吃一次
            {
                areas.push_back(ptNew);
            }
            //是自己的棋子，不可以走了
            break;

        }else{
             areas.push_back(ptNew);
             x--;
        }
    }
    //往右
    x= item.m_pt.x();
    while(x<POS_COL){
        QPoint ptNew = QPoint(x+1,item.m_pt.y());
        Item tmp_it;
        if(CheckItemAtPoint(ptNew,tmp_it))
        {
            if(tmp_it.m_color != item.m_color)//敌方棋子，可以吃一次
            {
                areas.push_back(ptNew);
            }
            //是自己的棋子，不可以走了
            break;

        }else{
             areas.push_back(ptNew);
             x++;
        }
    }
}

void MainWindow::GetMoveableAreas_MA(Item &item, QVector<QPoint> &areas)
{
    //棋子“马”的计算可移动区域算法简介：
    //1，求出8个待选位置，8个位置的偏移是（-2，-1）（-2，1）（2，-1）（2，1）（1，-2）（1，2）（-1，-2）（-1，2）存在关系：|x|+|y|=3
    //2，判断待选位置是否在棋盘内
    //3，判断中间是否有卡位的棋子
    //4，位置上是否已存在同色棋子
    Item tmp_it;
    for(int i = -2;i<=2 ;i++)    {
        for(int j = -2;j<=2;j++){
            if(qAbs(i)+qAbs(j) == 3){
                QPoint ptNew =item.m_pt + QPoint(i,j);
                if(ptNew.x()<0||ptNew.x()>POS_COL||ptNew.y()<0||ptNew.y()>POS_COL)
                {
                    //越界
                    continue;
                }
                //算出卡位位置坐标
                QPoint ptOffset(0,0);
                if(qAbs(i)<qAbs(j) ){
                    if(j <0)
                    {
                        ptOffset= QPoint(0,-1);
                    }
                    else
                    {
                        ptOffset= QPoint(0,1);
                    }
                }else{
                    if(i <0)
                    {
                        ptOffset= QPoint(-1,0);
                    }
                    else
                    {
                        ptOffset= QPoint(1,0);
                    }
                }

                QPoint ptStack = item.m_pt + ptOffset;
                if(!CheckItemAtPoint(ptStack,tmp_it)){
                    areas.push_back(ptNew);
                }

            }
        }
    }
}

void MainWindow::GetMoveableAreas_PAO(Item &item, QVector<QPoint> &areas)
{
    bool ptZhidian = false;
    //往上
    int y = item.m_pt.y();
    while (y>0) {
        QPoint ptNew = QPoint(item.m_pt.x(),y-1);
        Item tmp_it;
        if(CheckItemAtPoint(ptNew,tmp_it))
        {
            if(tmp_it.m_color != item.m_color && ptZhidian)//敌方棋子，可以吃一次
            {
                areas.push_back(ptNew);
                break;
            }
            //是自己的棋子，不可以走了
            ptZhidian =true;

        }else{
            if(!ptZhidian){ //除了 炮架 后的空位置，都可以走
                areas.push_back(ptNew);
            }
        }
        y--;
    }

    //往下
    y = item.m_pt.y();
    ptZhidian = false;
    while (y<POS_ROW) {
        QPoint ptNew = QPoint(item.m_pt.x(),y+1);
        Item tmp_it;
        if(CheckItemAtPoint(ptNew,tmp_it))
        {
            if(tmp_it.m_color != item.m_color && ptZhidian)//敌方棋子，可以吃一次
            {
                areas.push_back(ptNew);
                break;
            }
            //是自己的棋子，不可以走了
            ptZhidian =true;

        }else{
            if(!ptZhidian){ //除了 炮架 后的空位置，都可以走
                areas.push_back(ptNew);
            }
        }
        y++;
    }

    //往左
    int x = item.m_pt.x();
    ptZhidian = false;
    while (x>0) {
        QPoint ptNew = QPoint(x-1,item.m_pt.y());
        Item tmp_it;
        if(CheckItemAtPoint(ptNew,tmp_it))
        {
            if(tmp_it.m_color != item.m_color && ptZhidian)//敌方棋子，可以吃一次
            {
                areas.push_back(ptNew);
                break;
            }
            //是自己的棋子，不可以走了
            ptZhidian =true;

        }else{
            if(!ptZhidian){ //除了 炮架 后的空位置，都可以走
                areas.push_back(ptNew);
            }
        }
        x--;
    }
    //往右

    x = item.m_pt.x();
    ptZhidian = false;
    while (x<POS_COL) {
        QPoint ptNew = QPoint(x+1,item.m_pt.y());
        Item tmp_it;
        if(CheckItemAtPoint(ptNew,tmp_it))
        {
            if(tmp_it.m_color != item.m_color && ptZhidian)//敌方棋子，可以吃一次
            {
                areas.push_back(ptNew);
                break;
            }
            //是自己的棋子，不可以走了
            ptZhidian =true;

        }else{
            if(!ptZhidian){ //除了 炮架 后的空位置，都可以走
                areas.push_back(ptNew);
            }
        }
        x++;
    }
}

void MainWindow::GetMoveableAreas_SHI(Item &item, QVector<QPoint> &areas)
{
    Item tmp_it;
    for(int i=-1;i<=1;i=i+2){
        for(int j=-1;j<=1;j=j+2){
            QPoint ptNew =item.m_pt + QPoint(i,j);
            if(ptNew.x()<3||
               ptNew.x()>5||
               ptNew.y()<0||
              (ptNew.y()>2 && ptNew.y()<7)||
               ptNew.y()>9)
            {
                //越界
                continue;
            }
            if(CheckItemAtPoint(ptNew,tmp_it)){
                if(tmp_it.m_color!=item.m_color){
                    areas.push_back(ptNew);
                }
            }
            else{
                 areas.push_back(ptNew);
            }
        }
    }
}

void MainWindow::GetMoveableAreas_XIANG(Item &item, QVector<QPoint> &areas)
{
    Item tmp_it;//目标位置
    Item stack_it;//象眼位置
    for(int i=-2;i<=2;i=i+4){
        for(int j=-2;j<=2;j=j+4){
            QPoint ptStack = item.m_pt +QPoint(i/2,j/2);
            QPoint ptNew =item.m_pt + QPoint(i,j);
            //有效性判断
            if( ptNew.x()<0 ||
                ptNew.x()>POS_COL ||
                ptNew.y()==1 ||
                ptNew.y()==3 ||
                ptNew.y()==6||
                ptNew.y()==8){
                continue;
            }


            //象眼位置判断
            if(CheckItemAtPoint(ptStack,stack_it)){//象眼有棋子
                continue;
            }

            if(CheckItemAtPoint(ptNew,tmp_it)){
                if(tmp_it.m_color!=item.m_color){
                    areas.push_back(ptNew);
                }
            }
            else{
                 areas.push_back(ptNew);
            }
        }
    }
}

void MainWindow::GetMoveableAreas_SHUAI(Item &item, QVector<QPoint> &areas)
{
    Item tmp_it;
    QVector<QPoint> pos;
    pos.push_back(QPoint(-1,0));
    pos.push_back(QPoint(0,-1));
    pos.push_back(QPoint(1,0));
    pos.push_back(QPoint(0,1));
    for(int i = 0;i<pos.size();i++){
        QPoint ptNew =item.m_pt + pos[i];
        if(ptNew.x()<3||
           ptNew.x()>5||
           ptNew.y()<0||
          (ptNew.y()>2 && ptNew.y()<7)||
           ptNew.y()>9)
        {
            //越界
            continue;
        }
        if(CheckItemAtPoint(ptNew,tmp_it)){
            if(tmp_it.m_color!=item.m_color){
                areas.push_back(ptNew);
            }
        }
        else{
             areas.push_back(ptNew);
        }

    }
}

void MainWindow::GetMoveableAreas_BING(Item &item, QVector<QPoint> &areas)
{
    Item tmp_it;
    QVector<QPoint> posRed;
    posRed.push_back(QPoint(-1,0));
    posRed.push_back(QPoint(0,-1));
    posRed.push_back(QPoint(1,0));
    QVector<QPoint> posBlack;
    posBlack.push_back(QPoint(-1,0));
    posBlack.push_back(QPoint(0,1));
    posBlack.push_back(QPoint(1,0));
    //红往上
    QPoint ptNew;
    if(item.m_color == COLOR_RED){
        for(int i =0; i<posRed.size();i++){
          if(item.m_pt.y()<=4){
            ptNew = item.m_pt + posRed[i];
          }else{
            ptNew = item.m_pt + posRed[1];
          }
          if(ptNew.x()<0 ||
              ptNew.x()>POS_COL||
              ptNew.y()<0||
              ptNew.y()>POS_ROW){
              continue;
          }

          if(CheckItemAtPoint(ptNew,tmp_it)){
              if(tmp_it.m_color!=item.m_color){
                  areas.push_back(ptNew);
              }
          }
          else{
               areas.push_back(ptNew);
          }

    }


    }
    //黑往下
    else if(item.m_color == COLOR_BLACK){
        for(int i =0; i<posBlack.size();i++){
          if(item.m_pt.y()<POS_ROW&&item.m_pt.y()>4 ){
            ptNew = item.m_pt + posBlack[i];
          }else{
            ptNew = item.m_pt + posBlack[1];
          }
          if(ptNew.x()<0 ||
              ptNew.x()>POS_COL||
              ptNew.y()<0||
              ptNew.y()>POS_ROW){
              continue;
          }

          if(CheckItemAtPoint(ptNew,tmp_it)){
              if(tmp_it.m_color!=item.m_color){
                  areas.push_back(ptNew);
              }
          }
          else{
               areas.push_back(ptNew);
          }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    for(int i=0;i<m_items.size();++i){
        DramItem(p,m_items[i]);
    }
//    QPen pen;
//    pen.setWidth(2);
//    p.setPen(pen);
    //生成辅助线
    for(int i=0 ; i<GRID_ROWS;i++){
         p.drawLine(START_X,START_Y+RECT_HEIGHT*i,START_X+(GRID_COLS-1)*RECT_WIDTH,START_Y+RECT_HEIGHT*i);
    }
    for(int i=0 ; i<GRID_COLS;i++){
          p.drawLine(START_X+i*RECT_WIDTH,START_Y,START_X+i*RECT_WIDTH,START_Y+(GRID_ROWS-1)*RECT_HEIGHT);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //拿到鼠标按下点的坐标

    int x = e->x();
    int y = e->y();
    //在有效范围外的话不响应
    if(x<START_X||x>START_X+(GRID_COLS-1)*RECT_WIDTH||y<START_Y||y>START_Y+(GRID_ROWS-1)*RECT_HEIGHT){
        qDebug()<<"按下位置无效";
        return;
    }
    QPoint pt;
    pt.setX((x-START_X)/RECT_WIDTH);
    pt.setY((y-START_Y)/RECT_HEIGHT);
    tcout<<"mousePressEvent:["<<pt.x()<<","<<pt.y()<<"]";

    if(m_bIsExistSelectedItem){
        if(pt == m_selectedItem.m_pt){//点击已选中棋子无效
            return;
        }
        //点击其它非选中棋子
        Item clickItem;
        if(CheckItemAtPoint(pt,clickItem)){//点击位置有棋子
            //改选棋子
            if( (m_bIsRedRun&&clickItem.m_color == COLOR_RED )||
                (!m_bIsRedRun && clickItem.m_color != COLOR_RED)){
                SetItemShow(m_selectedItem,true);
                m_selectedItem = clickItem;
                return;
            }
        }//end  if(CheckItemAtPoint(pt,clickItem))
        //判断能走能吃
        QVector<QPoint> moveAreas;
        GetMoveableAreas(m_selectedItem,moveAreas);
        //获得已选棋子的可走区域
        //获得敌方 将帅的位置
        //如果包含将帅位置，则有"将军"的提示音
        if(moveAreas.contains(pt)){//包含当前点击位置，则可以走到该位置
            bool isDeleteShuai = false;
            DeleteItemAtPoint(pt,isDeleteShuai);
            ChangeItemPoint(m_selectedItem.m_pt,pt);
            if(isDeleteShuai){
                QString  res = m_bIsRedRun?QString("红方胜利！"):QString("黑方胜利！");
                QMessageBox::information(NULL,  "GAME OVER  ",res, QMessageBox::Yes , QMessageBox::Yes);
                NewGame();
            }
            m_bIsExistSelectedItem = false;
            m_bIsRedRun=!m_bIsRedRun;
            update();
        }



    }else{//选中棋子
        Item clickItem;
        if(CheckItemAtPoint(pt,clickItem)){//点击位置有棋子
            if( (m_bIsRedRun&&clickItem.m_color == COLOR_RED )||
                 (!m_bIsRedRun && clickItem.m_color == COLOR_BLACK)){
                m_selectedItem = clickItem;
                m_bIsExistSelectedItem =true;
                tcout<<m_selectedItem.m_bShow;

              }
           }

    }
}
void MainWindow::timerEvent(QTimerEvent *)
{
    for(int i = 0 ;i< m_items.size();i++){
        if(m_items[i].m_pt==m_selectedItem.m_pt){
            m_items[i].m_bShow=!m_items[i].m_bShow;
            tcout<<m_items[i].m_color<<m_items[i].m_type<<m_items[i].m_bShow;
            update();
            break;
        }
    }
}

bool MainWindow::CheckItemAtPoint(QPoint pt, Item &it)
{
    foreach(Item tmp, m_items){
        if(tmp.m_pt == pt){
           it = tmp;
           return true;
        }
    }
    return false;
}

void MainWindow::SetItemShow(Item &it, bool bShow)
{
    for(int i = 0 ;i< m_items.size();i++){
        if(m_items[i].m_pt==it.m_pt){
            m_items[i].m_bShow = bShow;
            break;
        }
    }
}
