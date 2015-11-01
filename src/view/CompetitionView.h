#ifndef COMPETITIONVIEW_H
#define COMPETITIONVIEW_H

#include "View.h"
#include <thread>
#include <unistd.h>

class CompetitionView : public View {
public:

  CompetitionView(Stage* stage, Controller* controller);

    virtual void initialize();

public slots:
    virtual void update(int ID);

private:
 std::thread taskThread;
 void startCompetitionRun();
};

#endif // COMPETITIONVIEW_H
