#include "SimulatorView.h"
#include "Stage.h"

SimulatorView::SimulatorView() {

}

SimulatorView::SimulatorView(Stage *stage, Controller *controller, std::vector<State *> states, SimulatedSub* simSub, SimulatedEnvironment* simEnv, Qt3D::QEntity* rootEntity)
    : View(stage, controller, states) {
    this->simSub = simSub;
    this->simEnv = simEnv;
    this->rootEntity = rootEntity;

}

SimulatorView::~SimulatorView() {
    window->close();
    container->close();
    delete engine;
    delete logger;
}

void SimulatorView::update(int id) {

}

void SimulatorView::initialize() {
    // Window sizing
    QSize minSize = QSize(100, 100);
    QSize maxSize = QSize(1920, 1080);

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
    container->setParent(this); // Allows container to be shown when this is
    container->setMinimumSize(minSize); // Can be as small as 100 pixels by 100 pixels
    container->setMaximumSize(maxSize); // Can be as large as

    // Install Key Event filter into this widget (affects all children widget as well)
    window->installEventFilter(this);

    // Initialize the Simulator 3D Engine
    //TODO: Use dependency injection here instead
    engine = new SimulatorEngine(container, window, simSub, simEnv, rootEntity);
    engine->initialize();
}

QSize SimulatorView::sizeHint() const {

}

QSize SimulatorView::minimumSizeHint() const {

}

QWindow *SimulatorView::getWindow() {
    return window;
}

bool SimulatorView::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Q) {
            logger->info("Q Button pressed.  Exiting Simulator View");
            //window->close();
            //container->close();
            stage->exit();
        }
        if(keyEvent->key() == Qt::Key_M) {
            logger->info("M Button pressed.  Exiting Simulator View");
            //window->close();
            //container->close();
            stage->switchToMenuView();
        }
    }
    return QObject::eventFilter(obj, event);
}

void SimulatorView::makeQImage(cv::Mat imgData, QImage &imgHolder) {

}

