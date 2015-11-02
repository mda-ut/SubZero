#include "SimBufferWindow.h"
#include <QPixmap>
#include <QGuiApplication>
#include <QScreen>
#include <thread>

SimBufferWindow::SimBufferWindow(SimulatedSub* simSub, SimulatedEnvironment* simEnv, Qt3D::QEntity* rootEntity, Properties* properties) {
    this->simSub = simSub;
    this->simEnv = simEnv;
    this->rootEntity = rootEntity;
    this->properties = properties;
}

SimBufferWindow::~SimBufferWindow() {
    container->close();
    delete logger;
}

void SimBufferWindow::update(int id) {

}

void SimBufferWindow::initialize() {
    // Window sizing
    QSize minSize = QSize(1280, 480);
    QSize maxSize = QSize(1280, 480);

    // Obscurity and depth perception modifiers
    int depthBufferSize = 16;   // 8,16,24 and 32 bit  but fixing at 16 bit b/c expecting obscure environment
    int multiSampleAntiAliasingSamples = 4; // Number of samples to take of each pixel if multi-sample anti-aliasing is used

    // Setup the window
    format = new QSurfaceFormat();
    format->setProfile(QSurfaceFormat::NoProfile);  // In case OpenGl version less than 3.2
    format->setDepthBufferSize(depthBufferSize);    // In water don't see too far ahead so reducing depth perception from standard 24
    format->setSamples(multiSampleAntiAliasingSamples); // For multisample based anti-aliasing


    window = new QWindow();
    window->setSurfaceType(QSurface::OpenGLSurface);    // Set to use OpenGl for rendering & painting
    window->setFormat(*format);
    window->create();

    container = new QWidget();
    container = createWindowContainer(window);

    container->setMinimumSize(minSize); // Can be as small as 100 pixels by 100 pixels
    container->setMaximumSize(maxSize); // Can be as large as
    engine = new SimulatorEngine(container, window, simSub, simEnv, rootEntity);
    engine->initialize();

    frontCam = std::stoi(properties->getProperty("FRONT_CAM"));
    downCam = std::stoi(properties->getProperty("DOWN_CAM"));
    connect(this, SIGNAL(grabWidget(int)), this, SLOT(updatePixmap(int)));
}

QWindow *SimBufferWindow::getWindow() {
    return window;
}
// If inImage exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inImage's
// data with the cv::Mat directly
//    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
inline cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true )
{
   switch ( inImage.format() )
   {
      // 8-bit, 4 channel
      case QImage::Format_RGB32:
      {
         cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );
//         QPixmap::grabWindow(window->winId()).save("testsim.png");
         //imshow("test",mat);
         return (inCloneImageData ? mat.clone() : mat);
      }

      // 8-bit, 3 channel
      case QImage::Format_RGB888:
      {
         if ( !inCloneImageData )
            qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";

         QImage   swapped = inImage.rgbSwapped();

         return cv::Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
      }

      // 8-bit, 1 channel
      case QImage::Format_Indexed8:
      {
         cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

         return (inCloneImageData ? mat.clone() : mat);
      }

      default:
         qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
         break;
   }

   return cv::Mat();
}

// If inPixmap exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inPixmap's data
// with the cv::Mat directly
//    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
inline cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true )
{
   return QImageToCvMat( inPixmap.toImage(), inCloneImageData );
}

void SimBufferWindow::updatePixmap(int position) {
    QPixmap temp = window->screen()->grabWindow(window->winId());
    if (position == frontCam) {
//        pixmap = container->grab(QRect(0,0,320,240));
        pixmap = temp.copy(QRect(0,0,640,480));
    } else if (position == downCam) {
//        pixmap = container->grab(QRect(320,0,320,240));
        pixmap = temp.copy(QRect(640,0,640,480));
    } else {
        logger->warn("Invalid simulated camera position of " + std::to_string(position));
//        pixmap = container->grab(QRect(0,0,320,240));
        pixmap = temp.copy(QRect(0,0,640,480));
    }
    pixmapSet = true;
}

cv::Mat SimBufferWindow::getImg(int position) {
    mutex.lock();
    pixmapSet = false;
    emit grabWidget(position);
    while(!pixmapSet) {
        std::this_thread::yield();
    }
    cv::Mat mat = QPixmapToCvMat(pixmap);
    cv::cvtColor(mat, mat, cv::COLOR_BGRA2RGB, 3);
    imshow("mattest", mat);
    mutex.unlock();
    return mat;
}


