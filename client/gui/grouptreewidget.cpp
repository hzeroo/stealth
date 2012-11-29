#include "grouptreewidget.h"

GroupTreeWidget::GroupTreeWidget(bool expanded,QWidget* parent)
{

    this->expanded=false;

    QGridLayout* mainLayout=new QGridLayout();
    QGridLayout* frameLayout=new QGridLayout();
    mainLayout->setMargin(0);
    frameLayout->setMargin(0);
    mainLayout->setSpacing(0);
    frameLayout->setSpacing(0);

    frame=new QFrame();
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setLayout(frameLayout);
    /* frame->setStyleSheet("QFrame{border-radius: 10px; border: 1px solid grey; padding: 8 8px;}");*/
    mainLayout->addWidget(frame);
/*
    QPushButton* btnExpand=new QPushButton();
    btnExpand->setFlat(true);
    frameLayout->addWidget(btnExpand);
    connect(btnExpand,SIGNAL(clicked()),SLOT(on_btnExpand_clicked()));
*/
    treewidget=new CustomTreeWidget();
    treewidget->setFocusPolicy(Qt::NoFocus);
    treewidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    treewidget->setRootIsDecorated(false);
    treewidget->setHeaderHidden(true);
    treewidget->setColumnCount(2);
    treewidget->setIndentation(0);
    treewidget->setAnimated(true);
    treewidget->setIconSize(QSize(40,40));
    treewidget->header()->setStretchLastSection(false);
    treewidget->header()->setResizeMode(0,QHeaderView::Stretch);
    treewidget->header()->setResizeMode(1,QHeaderView::Fixed);
    treewidget->setColumnWidth(1,200);
    treewidget->setFrameShape(QFrame::NoFrame);
    if(!expanded) treewidget->hide();
    frameLayout->addWidget(treewidget);

/*
    QHBoxLayout* nl=new QHBoxLayout();
    nl->setMargin(0);
    nl->setSpacing(4);
    iconLabel=new QLabel();
    iconLabel->setPixmap(QPixmap(":/res/img/bullet_arrow_down.png"));
    iconLabel->setScaledContents(true);
    iconLabel->setFixedSize(24,24);
    nl->addWidget(iconLabel);
    QLabel* groupLabel=new QLabel("Grupo 1");
    QFont font = groupLabel->font();
    font.setPointSize(10);
    font.setBold(true);
    groupLabel->setFont(font);
    nl->addWidget(groupLabel);
    nl->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding));
    QLabel* numItemsLabel=new QLabel("0 equipos");
    nl->addWidget(numItemsLabel);
    nl->addSpacerItem(new QSpacerItem(4,1,QSizePolicy::Fixed,QSizePolicy::Fixed));
    btnExpand->setLayout(nl);
*/
    this->setLayout(mainLayout);
}

GroupTreeWidget::~GroupTreeWidget()
{
}

void GroupTreeWidget::addItem(QTreeWidgetItem* item)
{
    item->setIcon(0,QIcon(":/res/img/the-dark-knight-the-joker-02.png"));
    QGraphicsView* gvSpeed=new QGraphicsView();
    gvSpeed->setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    gvSpeed->setFocusPolicy(Qt::NoFocus);
    gvSpeed->setStyleSheet("border: 1px solid black");
    gvSpeed->setFixedHeight(50);
    gvSpeed->setFixedWidth(200);
    treewidget->addTopLevelItem(item);
    treewidget->setItemWidget(treewidget->topLevelItem(0),1,gvSpeed);


    /* DEMO */
    QGraphicsScene* scene=new QGraphicsScene();
    scene->setSceneRect(gvSpeed->rect());

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i=0;i<3;i++)
    {
        QColor color;

        switch(i)
        {
            case 0:
                color=Qt::green;
            break;
            case 1:
                color=Qt::red;
            break;
            case 2:
                color=Qt::blue;
            break;
        }

        QPen pen;
        pen.setColor(color);
        pen.setWidth(2);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        int lastX=0,lastY=0;

        for(int i=0;i<20;i++)
        {
            int newHeight=qrand()%48;
            scene->addLine(lastX,lastY,lastX+10,newHeight,pen);
            lastX+=10;
            lastY=newHeight;
        }
    }


    scene->addText("DEMO");
    gvSpeed->setScene(scene);
    gvSpeed->fitInView(scene->sceneRect());
    /* /DEMO */
}

void GroupTreeWidget::setExpanded(bool expanded)
{
    if(expanded)
    {
        emit expandedChanged(this);
        frame->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        treewidget->show();
        iconLabel->setPixmap(QPixmap(":/res/img/bullet_arrow_down.png"));
        this->expanded=true;
    }
    else
    {
        frame->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        treewidget->hide();

        iconLabel->setPixmap(QPixmap(":/res/img/bullet_arrow_left.png"));
        this->expanded=false;
    }
}

bool GroupTreeWidget::isExpanded()
{
    return this->expanded;
}

void GroupTreeWidget::on_btnExpand_clicked()
{
    if(!this->isExpanded()) setExpanded(true);
}

void GroupTreeWidget::on_treewidget_itemClicked(QTreeWidgetItem *item, int column)
{
    item->setExpanded(!item->isExpanded());
}
