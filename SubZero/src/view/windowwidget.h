#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include <QWindow>
#include <QWidget>

/**
 * @brief The WindowWidget class
 * Creates an opengl surface window wrapped
 * in a widget container. The surface is what
 * displays the environment.
 */


class WindowWidget: public QWidget
{
    Q_OBJECT
public:
    WindowWidget(QWidget *parent = 0);
    void initialize();
    QWindow *getWindow();//getter for the QWindow
    QSurfaceFormat *getFormat();//getter for the windowformat
    QWidget *getContainer();//getter for the container in the widget


private:
    /**
     * @param window pointer to the window (and the surface)
     * must be cast to a QSurface * using
     *  QVariant::fromValue(static_cast<QSurface *>(view->getWindow() )))
     * to be used as a surface screen for the QAspectEngine's data
     *
     * @param windowFormat Holds all formating and OpenGL version
     * related parameters (see profile, majorversion and minor version)
     * in the Qt documentation for more details
     *
     * @param container Widget which is used to wrap the window.
     * The widget that should be manipulated to modify the window is this
     * container (not this class itself).
     */


    QWindow *window;
    QSurfaceFormat *windowFormat;
    QWidget *container;
};

#endif // WINDOWWIDGET_H
