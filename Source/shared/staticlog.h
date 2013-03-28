/**
*@class Staticlog
*@brief Singleton class for uniform access to logfile
*@author De Schutter Bob
*@date 04-2011
*
* @section source Sources
* log.h
* log.cpp
*
* @section working Writes data to the logfile
*
* @section destination Destination
* log.h
* log.cpp
*
* @sa Log
*
*/

#ifndef staticlog_H
#define staticlog_H

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

#define LOGFILE  "log.txt"
#define TRUNCAT  1
#define LOGOUTP  0
#ifndef STDOUT
#define STDOUT(msg) if(LOGOUTP==1) cout << msg << endl;
#endif

using namespace std;

class Staticlog
{
public:
    /**
     * @brief Function that checks if an instance of that class already exists
     *
     * If it doesn't exist: create one. If an instance exists: return that one
     * @return Pointer to the staticlog instance
     */
    static Staticlog *getInstance();

    /**
     * @brief Add msg to logfile
     * @param bron Which class the msg came from
     * @param bericht The msg to be written in the logfile
     * @sa Log::stuur
     */
    void stuur(string bron, string bericht, int prior);
private:
    /**
     * @brief Static constructor.
     *
     * Declared static so only one instance can exist at the same time. This instance will be used by everyone
     * from the interface class Log. The reason is that a file can only be accessed with write permissions once.
     * It is declared private to ensure no one can create a second instance.
     * @sa Staticlog::instance()
     */
    Staticlog();
    /**
     * @brief Destructor
     *
     * It is declared private to ensure no one can delete the instance. It will be deleted when the main program exits.
     * If it is deleted, other classes will be getting null pointers exceptions - Segmentation fault. (Dangling pointer)
     */
    ~Staticlog();

    /**
     * @brief Pointer to unique instance of this class
     */
    static Staticlog *instance_;

    /**
     * @brief Filepointer to the logfile
     */
    ofstream out;
};
#endif /* log */
