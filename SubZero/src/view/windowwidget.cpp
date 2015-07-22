#include "windowwidget.h"
#include <QScreen>
#include <QSize>

WindowWidget::WindowWidget(QWidget *parent): QWidget(parent)
{

}

void WindowWidget::initialize()
{
    //Window sizing
    QSize minSize = QSize(100,100);
    QSize maxSize = QSize (1920,1080);

    //Obscurity and depth perception modifiers
    int depthBufferSize = 16;//8,16,24 and 32 bit  but fixing at 16 bit b/c expecting obscure environment
    int multisampleAntiAliasingSamples = 4;//#Samples to take of each pixel if multisample anti-aliasing is used


    // Setup the window
    windowFormat = new QSurfaceFormat;
    windowFormat->setProfile( QSurfaceFormat::NoProfile);//In case OpenGl version less than 3.2
    windowFormat->setDepthBufferSize(depthBufferSize);// In water don't see too far ahead so reducing depth perception from standard 24
    windowFormat->setSamples(multisampleAntiAliasingSamples);// For multisample based anti-aliasing

    window = new QWindow;
    window->setSurfaceType( QSurface::OpenGLSurface); //Set to use OpenGl for rendering & painting
    window->setFormat(*windowFormat);
    window-> create();

    container = new QWidget();
    container = createWindowContainer(window);
    container->setParent(this);//Allows containter to be shown when this is
    container->setMinimumSize(minSize);// Can be as small as 100 pixels by 100 pixels
    container->setMaximumSize(maxSize);// can be as large as


}

QWindow *WindowWidget::getWindow()
{
    return window;
}

QSurfaceFormat *WindowWidget::getFormat()
{
    return windowFormat;
}

void WindowWidget::showWindow()
{
    container->show();
}

QWidget *WindowWidget::getContainer()
{
    return container;
}
