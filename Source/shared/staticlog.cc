#include "staticlog.h"
using namespace std;

Staticlog *Staticlog::instance_ = NULL;

Staticlog* Staticlog::getInstance()
{
    if(!instance_)
        instance_= new Staticlog;
    return instance_;
}
Staticlog::Staticlog()
{
#if TRUNCAT == 1
    out.open(LOGFILE,ios::out | ios::trunc);
#else
    out.open(LOGFILE,ios::out | ios::app);
#endif
    if(!out){
        cout << "Kan " << LOGFILE << " niet openen"<<endl;
    }
}
void Staticlog::stuur(string bron, string bericht, int prior)
{
    //STDOUT("Staticlog::stuur");
    if(out.is_open())
    {
        time_t raw;
        struct tm* timeinfo;
        char tijd[80],machine[50];

        time(&raw);
        timeinfo = localtime(&raw);
        strftime(tijd,80,"%x %X",timeinfo);

        sprintf(machine,"%-10s",bron.c_str());
        out << "[" << prior     << "]"
            << "[" << tijd      << "]"
            << "[" << machine   << "]"
            << "[" << bericht   << "]"
            << endl;
    }
    else
    {
        cout << "Error: file is niet open\n";
    }
}

Staticlog::~Staticlog()
{
    //STDOUT("Staticlog::~Saticlog");
    out.close();
    cout << "Statische klasse afgesloten\n";
}
