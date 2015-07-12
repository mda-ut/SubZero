#include "SIMFPGA.h"

/** =========================================================
 *  CONSTRUCTOR AND DESTRUCTOR
 *  =========================================================
 */


SIMFPGA::SIMFPGA() : SIMInterface()
{
    //this->logger = new Logger("SIMFPGA");

    PropertyReader* SIMFPGAProp = new PropertyReader("../../SIMfishy/src/settings/SIMFPGA.txt");
    SIMFPGAProp->load();
    this->directory = SIMFPGAProp->getProperty("DIRECTORY");
    this->BUF_SIZE = std::stoi(SIMFPGAProp->getProperty("BUF_SIZE"));
    this->openStream(INFP);
    this->openStream(OUTFP);
    this->openStream(LOGFP);
    this->abort = 0;
    this->readThread = std::thread(&SIMFPGA::read,this);
}

SIMFPGA::~SIMFPGA()
{
    this->abort = 1;
    this->readThread.join();
    this->clear();
    this->write("power failed\n");
    this->closeStream(INFP);
    this->closeStream(OUTFP);
    this->closeStream(LOGFP);
}

/** =========================================================
 *  STREAM OPERATIONS
 *  =========================================================
 */


void SIMFPGA::openStream(int stream)
{
    switch (stream)
    {
    case INFP:
        infp = fopen((directory+"infp.txt").c_str(),"r");
        if (infp == 0) {
           // this->logger->error("infp failed to open");
        }
        break;
    case OUTFP:
        outfp = fopen((directory+"outfp.txt").c_str(),"w");
        if (outfp == 0) {
//            this->logger->error("outfp failed to open");
        }
        break;
    case LOGFP:
        logfp = fopen((directory+"outlogfp.txt").c_str(),"w");
        if (logfp == 0) {
//            this->logger->error("logfp failed to open");
        }
        break;
    }
}

void SIMFPGA::closeStream(int stream)
{
    switch (stream)
    {
    case INFP:
        fclose(infp);
        break;
    case OUTFP:
        fclose(outfp);
        break;
    case LOGFP:
        fclose(logfp);
        break;
    }
}

long SIMFPGA::filesize(){
    long size = 0;
    fflush(infp);
    std::rewind(infp);
    std::fseek(infp,0,SEEK_END);
    size = std::ftell(infp);
    std::rewind(infp);
    return size;
}

void SIMFPGA::read()
{
    char buf[BUF_SIZE];
    long size = 0;
    while (!this->abort) {
        size = this->filesize();
        if (size > 0) {
            std::fgets(buf,BUF_SIZE,infp);
            this->clear();
            this->execCmd(std::string(buf));
            // wait for the infp to be cleared.
            while (!this->abort && this->filesize()!=0)
                continue;
        }
    }
}

void SIMFPGA::write(std::string output)
{
    fprintf(outfp,"%s",output.c_str());
    fflush(outfp);
    fprintf(logfp,"%s",output.c_str());
    fflush(logfp);
}

void SIMFPGA::clear()
{
    this->closeStream(OUTFP);
    this->openStream(OUTFP); // openStream uses the w mode.. it creates empty file to pipe
//    std::system(("sed -e \'d\' -i "+directory+"outfp.txt").c_str()); // del all lines via term
}

/** =========================================================
 *  CMD EXECUTION FUNTIONS
 *  =========================================================
 */


void SIMFPGA::execCmd(std::string cmd)
{
    std::string output;
    if (cmd == "gax\n")
        output = "1\n";
    if (cmd == "gay\n")
        output = "2\n";
    if (cmd == "gaz\n")
        output = "3\n";
    if (cmd == "gd\n")
        output = "4.0\n";
    if (cmd == "ga\n")
        output = "120.5\n";
    this->write(cmd);
    this->write(output);
}
