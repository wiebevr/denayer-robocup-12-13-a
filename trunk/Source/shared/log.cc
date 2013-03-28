/**
*@class Log
*@brief Interface for Staticlog
*@author De Schutter Bob / Elias Puttemans
*@date 04-2011
*
*
*/
#include "log.h"
using namespace std;

Log::Log(string classType)
{
    //STDOUT("log object constructor");
    sl_ = Staticlog::getInstance();
    setCt(classType);
    sl_->stuur(this->getCt(),"init Log class from "+this->getCt(), DEFPRIOR);
}
void Log::setCt(string classType)
{
    ct_ = classType;
}
string Log::getCt()
{
    return this->ct_;
}
void Log::stuur(int prior, string bericht)
{
    //STDOUT("Log::stuur int");
    if(sl_ != NULL)
        sl_->stuur( this->getCt(),bericht,prior );
}
void Log::stuur(string bericht)
{
    //STDOUT("Log::stuur default");
    if(sl_ != NULL)
        sl_->stuur( this->getCt(),bericht, DEFPRIOR );
}

void Log::stuurf(const char *form, ... ){

	va_list lijst;
	string str;

	va_start(lijst, form);

	str = Log::formStr(lijst, form);

    if(sl_ != NULL)
        sl_->stuur( this->getCt(),str, DEFPRIOR );

	va_end(lijst);
}


void Log::stuurf(int prior, const char *form, ... ){

	string str;
	va_list lijst;
	va_start(lijst, form);

	str = Log::formStr( lijst, form);

    if(sl_ != NULL)
        sl_->stuur( this->getCt(),str, prior );

	va_end(lijst);
}

void Log::stuurf( string form, ... ){

	string str;
	va_list lijst;
	va_start(lijst, form);

	str = Log::formStr( lijst, form.c_str());

    if(sl_ != NULL)
        sl_->stuur( this->getCt(),str, DEFPRIOR );

	va_end(lijst);
}

void Log::stuurf(int prior, string form, ... ){

	string str;
	va_list lijst;
	va_start(lijst, form);

	str = Log::formStr( lijst, form.c_str());

    if(sl_ != NULL)
        sl_->stuur( this->getCt(),str, prior );

	va_end(lijst);
}

string Log::formStr( va_list lijst,const char *form ){

	int index;
	char c;
	string str;

	//run trough string, check if there is an % to trigger on
	index = 0;
	while( *(form+index) != '\0' ){

		if( *(form+index) == '%' ){
			index++;
			switch( *(form+index) ) {
				case 'd':
					str.append( Log::tostr( va_arg(lijst, int)) );
				break;
				case 'c':
					c = va_arg(lijst, int);
					str.append( &c, (size_t) 1 );
				break;
				case 's':
					str.append( va_arg(lijst, char*) );
				break;
				case 'f':
					str.append( Log::tostr( va_arg(lijst, double)) );
				break;
				default:
					str.append( "__keyword '");
					str.append( (form+index));
					str.append("' not supported__" );
				break;
			}
		}else{
			str.append( (form+index), (size_t) 1 );
		}
		index++;
	}
	return str;
}

string Log::tostr( int param ){
	stringstream ss;
	ss << param;
	return ss.str();
}

string Log::tostr( float param ){
	stringstream ss;
	ss << param;
	return ss.str();
}

string Log::tostr( double param ){
	stringstream ss;
	ss << param;
	return ss.str();
}

Log::~Log()
{
    sl_->stuur(this->getCt(),this->getCt()+"'s destructor called", DEFPRIOR );
    //STDOUT("Log::~Log");
}
