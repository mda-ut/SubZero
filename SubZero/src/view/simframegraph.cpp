#include "simframegraph.h"
#include <QEntity>

SimFrameGraph::SimFrameGraph(QNode *parent): Qt3D::QViewport(parent)
{

}

void SimFrameGraph::initialize()
{

    /**
     *The framegraph follows a depth first tree structure
     *so the clear will be first added in order to clear the screen
     *before displaying the views (otherwise will clear the images)
     */


    //Viewport rect is proportionate to window size (this is maxrect)
    //this->setRect(  QRectF(0.0f, 0.0f, 1.0f, 1.0f ));//

    //1st branch
    clearBuffer = new Qt3D::QClearBuffer(this);
    clearBuffer->setBuffers(Qt3D::QClearBuffer::ColorDepthStencilBuffer);



    frontViewport = new Qt3D::QViewport(clearBuffer);
    frontViewport->setRect(  QRectF(0.0f, 0.0f, 0.5f, 1.0f ));// first half of screen
    frontCameraSelector = new Qt3D::QCameraSelector(frontViewport);




    //next branch
    downViewport = new Qt3D::QViewport(this);
    downViewport->setRect(  QRectF(0.5f, 0.0f, 1.0f, 1.0f ));// second half of screen
    downCameraSelector = new Qt3D::QCameraSelector(downViewport);



}


void SimFrameGraph::setCameras(Qt3D::QEntity *frontCamera, Qt3D::QEntity *downCamera)
{

    frontCameraSelector->setCamera(frontCamera);
    downCameraSelector->setCamera(downCamera);


}
