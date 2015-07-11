//#include "guiview.h"
//#include <QImage>
//#include <QString>
//#include <QHBoxLayout>
//#include <QVBoxLayout>
//
//
//GuiView::GuiView()
//{
//    actionSelector = new QComboBox;
//    affirmButton = new QPushButton;
//
//
//    sceneFront = new QGraphicsScene;
//    sceneDown = new QGraphicsScene;
//    viewFront = new QGraphicsView(sceneFront);
//    viewDown = new QGraphicsView(sceneDown);
//    viewFront->show();
//    viewDown->show();
//
//
//
//    sonarStrength = new QLabel("Sonar Strength");
//    displaySize = new QSize(800,600);
//    pixmap = new QPixmap(*displaySize);
//
//
//    //Set the size of the scenes and views to the displaySize
//    //Front camera is the first (leftmost) camera
//
//    sceneFront->setSceneRect(0,0,displaySize->width(),displaySize->height());
//    sceneDown->setSceneRect(displaySize->width(),displaySize->height(),displaySize->width(),displaySize->height());
//    viewFront->setFixedSize(*displaySize);
//    viewDown->setFixedSize(*displaySize);
//
//
//    //Setup the layout
//    QHBoxLayout *viewLayout = new QHBoxLayout;
//    viewLayout->addWidget(viewFront);
//    viewLayout->addWidget(viewDown);
//
//    QHBoxLayout *selectorLayout = new QHBoxLayout;
//    selectorLayout->addWidget(actionSelector);
//    selectorLayout->addWidget(affirmButton);
//
//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addLayout(viewLayout);
//    mainLayout->addLayout(selectorLayout);
//    mainLayout->addWidget(sonarStrength);
//
//}
//
//
//
//QPixmap GuiView::makeQPixmap(cv::Mat *imgData)
//{
//    // http://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-orqpixmap
//    //Assuming rgb, need to add a check for other formats and null.
//
//    QPixmap p(*displaySize);
//
//    QImage image(imgData->data, imgData->cols, imgData->rows,
//                 imgData->step, QImage::Format_RGB32);
//
//    p.fromImage(image);
//    return p;
//}
//
//
//
//
//void GuiView::displayUpdate(cv::Mat *img,QGraphicsScene* scene)
//{
//
//    //Create the new image
//    //then clear the scene so the screen doesn't have a large 'load time' as you replace the image
//
//    *pixmap = makeQPixmap(img);
//    scene->clear();
//    scene->addPixmap(*pixmap);
//}
//
//
//
//
//void GuiView::update(cv::Mat *imgLocFront, cv::Mat *imgLocDown, int *sonarLoc)
//{
//    displayUpdate(imgLocFront,sceneFront);
//    displayUpdate(imgLocDown,sceneDown);
//    sonarStrength->setText("Sonar strength"+ QString::number(*sonarLoc));
//
//
//}
//
//
