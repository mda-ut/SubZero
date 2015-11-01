#include "QuickTaskAdder.h"

QuickTaskAdder::QuickTaskAdder()
{
    /**
     * This class is intended to perform the
     * addTask application for the specific controller tasks
     * by partitioning add task into several argumentless
     * variations. This will allow the signal slot method
     * to be used with qt's argumentless functions such
     * as clicked()
     */

    /**
      * This class must have its initialize function called
      * with a valid controller before its members may be
      * used.
      */

}


void QuickTaskAdder::initializeQuickTaskAdder(Controller *controllerOriginal)
{
 this->controller = controllerOriginal;
}

