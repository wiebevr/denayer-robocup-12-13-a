/**
*@class Log
*@brief Interface for Staticlog
*@author De Schutter Bob / Elias Puttemans
*@date 04-2011
*
*
*/

#ifndef log_H
#define log_H

#include <stdarg.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdio>
#include "staticlog.h"

///default priority, for when a msg is send without a specified priority
#define DEFPRIOR 5

//#ifndef STDOUT
//#define STDOUT(msg) if(0) cout << msg << endl;
//#endif
using namespace std;

class Log
{
public:
    /**
     * @brief Constructor
     * @param classType Type klasse die Log aanspreekt (voor snel eigen log output in het bestand te zoeken)
     * @sa Log::stuur()
     */
    Log(string classType);
    /**
     * @brief Append msg to logfile
     * @param bericht msg you append to logfile
     * @param prior Priority of the msg (1-5) with 1 being critical and 5 not important
     */
    void stuur(int prior, string bericht);
    /**
     * @brief Append msg to logfile
     *
     * Function for when priority is omitted, defaults to DEFPRIOR
     * @param bericht msg you append to logfile
     */
    void stuur(string bericht);
    /**
     * @brief Append formatted msg to logfile
     * @param prior Priority of the msg (1-5) with 1 being critical and 5 not important
     * @param form Format of the string (only: %d, %c, %s, %f)
     * @param ... Additional arguments (the values of %d, %c, %s, %f)
     */
    void stuurf( const char *form, ...);
    void stuurf( int prior, const char *form, ...);
    void stuurf( string form, ...);
    void stuurf( int prior, string form, ...);
    /**
     * @brief Destructor
     */
    ~Log();
private:
    /**
     * @brief pointer to Staticlog object (unique instance)
     */
    Staticlog *sl_;
    /**
     * @brief Variable to store which class the msg came from (should be set once by sender)
     */
    string ct_;
    /**
     * @brief Function to adjust private variabele ct_
     * @sa ct_
     */
    void setCt(string classType);
    /**
     * @brief Function to request ct_
     * @sa Log::ct_
     */
    string getCt(void);
    /**
     * @brief This functions builds the string with its additional arguments
     * @sa stuurf
     */
    string formStr( va_list lijst, const char *form );
    /**
     * @brief conversion functions for formStr
     * @sa formStr
     */
    string tostr( int param );
    string tostr( float param );
    string tostr( double param );

};
#endif /* log */
