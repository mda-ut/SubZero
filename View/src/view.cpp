/*
 * view.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: edem
 */



#include "view.h"

View::View(){
    viewFront = new QGraphicsView;
    viewDown = new QGraphicsView;
    scene = new QGraphicsScene;
    pixmap = new QPixmap;
    mainLayout = new QGridLayout;

}
