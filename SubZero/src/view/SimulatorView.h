#ifndef SIMULATORVIEW_H
#define SIMULATORVIEW_H

#include <QWindow>

#include "Logger.h"
#include "SimulatorEngine.h"
#include "View.h"

class SimulatorView : public View {
public:
    SimulatorView();
    SimulatorView(Stage* stage, Controller* controller, std::vector<State*> states, SimulatedSub* simSub, SimulatedEnvironment* simEnv, Qt3D::QEntity* rootEntity);
    ~SimulatorView();

    virtual void update(int id);
    virtual void initialize();
    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

    QWindow* getWindow();

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    Logger* logger = new Logger("SimulatorView");

    SimulatorEngine* engine;
    SimulatedSub* simSub;
    SimulatedEnvironment* simEnv;
    Qt3D::QEntity* rootEntity;

    QWidget* container;
    QWindow* window;
    QSurfaceFormat* format;

    void makeQImage(cv::Mat imgData, QImage& imgHolder);

};

#endif // SIMULATORVIEW_H
