#ifndef COMMANDCCR_H
#define COMMANDCCR_H

#include "Command.h"

class CommandCCR : public Command {

    public:
        CommandCCR();

        virtual void execute();
};

#endif // COMMANDCCR_H
