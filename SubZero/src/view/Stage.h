#ifndef STAGE_H
#define STAGE_H

#include <QWidget>
#include <QSize>
#include <QBoxLayout>
#include "Logger.h"
#include "SubZero.h"
#include "SubZeroFactory.h"

class Stage : public QWidget {

    Q_OBJECT

private:
    Logger* logger = new Logger("Stage");

    SubZeroFactory* subZeroFactory;
    SubZero* subZero;
    QBoxLayout* stageLayout;

public:
    explicit Stage(QWidget *parent = 0, SubZeroFactory* subZeroFactory = nullptr);
    ~Stage();

    /**
     * @brief initialize Initializes the Stage with the default settings
     */
    void initialize();

    /**
     * @brief setViewContent Changes the current View to the new specified View by deleting the previous View and stopping its Controller.  It's connections are also disconnected
     * @param view the new View to display on the Stage
     */
    void setViewContent(std::string type);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:

public slots:
    /**
     * @brief switchToGUIView
     */
    void switchToGUIView(void);

    /**
     * @brief switchToSimulatorView
     */
    void switchToSimulatorView();

    /**
     * @brief switchToGUIView
     */
    void switchToMenuView(void);

    /**
     * Cleans the queue; forces the last task to finish, then kills the sub
     */
    void exit(void);


};

#endif // STAGE_H
