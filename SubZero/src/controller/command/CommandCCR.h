/*
 * CommandCCR.h
 *
 *  Created on: Jun 6, 2015
 *      Author: LuckyChewie
 *
 *  This is a dummy Command that we used on Jun 6 for testing.
 *  The idea was to display on stdout the Creedence Clearwater Revival (CCR) lyric - "Hey, Tonight!"
 */

#ifndef COMMANDCCR_H
#define COMMANDCCR_H

#include "Command.h"

class CommandCCR : public Command {

    public:
        CommandCCR();

        virtual void execute();
};

#endif // COMMANDCCR_H
