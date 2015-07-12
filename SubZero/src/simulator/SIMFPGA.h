#ifndef SIMFPGA_H
#define SIMFPGA_H

#include "SIMInterface.h"

#define INFP 0
#define OUTFP 1
#define LOGFP 2

class SIMFPGA : public SIMInterface
{
private:

    /** =========================================================
     *  MEMBERS
     *  =========================================================
     */

    /*
     * Thread for the read function to continue polling.
     */
    std::thread readThread;

    /*
     * Input stream... The Fish writes to this stream.
     */
    FILE* infp;

    /*
     * Output stream... The Fish reads this stream.
     */
    FILE* outfp;

    /*
     * Log stream for the outputs to outfp
     */
    FILE* logfp;

    /*
     * The relative location of the infp and outfp.txt files are here
     */
    std::string directory;

    /*
     * The size of the infp read buffer is set through SIMFPGA.txt
     * settings file
     */
    unsigned int BUF_SIZE;

    /*
     * Switch to escape infinite loops.
     */
    int abort;

public:

    /** =========================================================
     *  CONSTRUCTOR AND DESTRUCTOR
     *  =========================================================
     */

    /**
     * @brief SIMFPGA construcotr
     */
    SIMFPGA();

    /**
     * @brief ~SIMFPGA destructor
     */
    virtual ~SIMFPGA();

    /** =========================================================
     *  STREAM OPERATIONS
     *  =========================================================
     */

    /**
     * @brief openStream opens the stream to talk with the code
     * using SIMfishy for simulation (aka The Fish). The location
     * of this stream is coordinated w/ The Fish.
     *
     * @param stream    enum INFP for the input file or OUTFP for the output file
     */
    void openStream(int stream);

    /**
     * @brief closeStream closes the stream.
     *
     * @param stream    enum INFP or OUTFP, see openStream()
     */
    void closeStream(int stream);

    /**
     * @brief isEmpty checks the size of infp.
     * @return long bytes
     */
    long filesize();

    /**
     * @brief read waits for a cmd to be written to INFP, invokes
     * the cmd's execution, then write the cmd itself (to confirm
     * the reception of the cmd) and the results of the cmd to
     * the OUTFP stream. It is requested that INFP is cleared
     * after the confirmation.
     */
    void read();

    /**
     * @brief write to the OUTFP stream.
     *
     * @param output    string to write out, you may use \n for new line.
     */
    void write(std::string output);

    /**
     * @brief clear the OUTFP stream. Clear occurs after receiving
     * a cmd from the INFP stream, but its occurance is not
     * restricted to that situation.
     */
    void clear();

    /** =========================================================
     *  CMD EXECUTION FUNCTIONS
     *  =========================================================
     */


    /**
     * @brief execCmd matchs the cmd from INFP to an action.
     *
     * @param cmd   the cmd to execute
     */
    void execCmd(std::string cmd);
};

#endif // SIMFPGA_H
