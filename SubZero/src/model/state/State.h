#ifndef STATE_H_
#define STATE_H_
#include "Data.h"
#include <string>
#include <list>
#include <set>
#include <QMutex>
#include <QMutexLocker>

#include "Logger.h"

class View;

enum StateType {
    FRONTCAM,
    DOWNCAM,
    FPGA
};

class State {

private:
    Logger* logger = new Logger("State");

protected:
    //boolean to signal if a new frame has started
    bool frameStarted;

    //boolean to signal if the state is currently in use
    bool inUse;

    //the length of the linked list
    //The amount of frames that the state will hold
    //ZERO INDEXED
    int maxLength;

    int stateID;
    std::set<View*> viewers;
    QMutex mutex;

    /**
     * Gets a pointer to a deep copy of the newest raw State
     * @return data = pointer to the deep copy of the raw State
     */
    virtual Data* getRaw() = 0;

    /**
     * Gets a pointer to the deep copy of the raw State _i_ frames before
     * @param i = how many frames ago the raw State was recorded (zero indexed; newest frame = 0)
     * @return a pointer to the deep copy of the raw State data _i_ frames before this function call
     */
    virtual Data* getRaw(int i) = 0;

public:

    State(int stateID);	//constructor
    /**
     * Construct a state with a limit of frames _framesStored_ (Zero indexed)
     * ie, frameStored = 10, this State will store 11 frames
     */
    State(int stateID, int framesStored);

    virtual ~State();	//deconstructor

    void addViewer(View* view);
    void notifyViewers();

    void init();

    /**
     * Returns a deep copy of an State specified with the _ID_ at _i_ frames before this call
     * @param ID = id of the State that is needed
     * @param i = how many frames ago was the State stored (zero indexed; newest frame = 0)
     * @return returns the pointer to a deep copied State
     */
    virtual Data* getState (std::string ID, int i) = 0;

    /**
     * Returns a deep copy of the latest State specified with the _ID_
     * (same as calling getState(ID, 0))
     * @param ID = id of the State that is needed
     * @return returns the pointer to a deep copied State
     */
    virtual Data* getState (std::string ID) = 0;

};
#endif /* SRC_MODEL_STATE_STATE_H_ */
