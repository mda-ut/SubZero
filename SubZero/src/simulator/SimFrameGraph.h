#ifndef SIMFRAMEGRAPH_H
#define SIMFRAMEGRAPH_H

#include <QViewport>
#include <QClearBuffer>
#include <QCameraSelector>
#include <QSize>
#include <QSizeF>

/**
 * @brief The SimFrameGraph class
 * This class creates a framegraph tree
 * that allows two cameras to render at once.
 * The camera names frontCamera and downCamera
 * are respective of their intended upVector
 * orientations for the purpose of the simulation
 * project.
 *
 * The frame graph tree is traversed with a depth
 * first search. goindg down one brach then coming up
 * to take any turns.n The simplest for is of
 * root->clear buffer->viewport->camera selector.
 * The latter two elements can be switched.
 * The overall state described by the tree is used to
 * create a set of rendering steps called a renderview
 * (note that placing the buffer at the end will
 * result in the image being replaced by the buffer
 * as it is rendered)
 *
 *
 * --------------------
 * 2 Cameras
 *
 * Note trying to make each branch like a simple
 * framegraph with its own buffer (which should work)
 * results in parts of each viewport not buffering properly
 * as does following the qml examples having the
 * first branch the clear buffer and subsequent
 * branches viewports with their own camera selectors
 *
 *
 * Anothertree to achieve the desired result was used
 *
 * 1st brach: clear buffer -> viewport ->camera selector
 * (front)
 *
 * 2nd brach: viewport -> camera selector (down)
 *
 *
 */

class SimFrameGraph: public Qt3D::QViewport
{
public:
    SimFrameGraph(QNode *parent = 0);
    void initialize();

    //Create function to simulatneously
    //setup cameras for both frontand down
    //viewports (by calling viewport::setCamera
    void setCameras(Qt3D::QEntity *frontCamera,
                    Qt3D::QEntity *downCamera);

    Qt3D::QClearBuffer *clearBuffer;

    //Screen on which camera is displayed
    Qt3D::QViewport *frontViewport;
    Qt3D::QViewport *downViewport;

    //eponymous
    Qt3D::QCameraSelector *frontCameraSelector;
    Qt3D::QCameraSelector *downCameraSelector;


};

#endif // SIMFRAMEGRAPH_H
