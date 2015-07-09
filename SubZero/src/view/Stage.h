#ifndef STAGE_H
#define STAGE_H

#include <QWidget>
#include <QSize>
#include <QBoxLayout>
#include "Logger.h"
#include "View.h"

class Stage : public QWidget {

    Q_OBJECT

private:
    Logger* logger = new Logger("Stage");

    View* currentView;
    QBoxLayout* stageLayout;

public:
    explicit Stage(QWidget *parent = 0);
    ~Stage();

    /**
     * @brief initialize Initializes the Stage with the default settings
     */
    void initialize();

    /**
     * @brief setViewContent Changes the current View to the new specified View by deleting the previous View and stopping its Controller.  It's connections are also disconnected
     * @param view the new View to display on the Stage
     */
    void setViewContent(View* view);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:

public slots:

};

#endif // STAGE_H
