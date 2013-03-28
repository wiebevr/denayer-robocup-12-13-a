#include "thread.h"
#include <iostream>
using namespace std;

pthread_cond_t received_bytes;
pthread_mutex_t received_mutex;

Thread::Thread()
{
    cout << "Thread::Thread()" << endl;
    pthread_cond_init(&received_bytes,NULL);
    pthread_mutex_init(&received_mutex,NULL);
}
Thread::~Thread()
{
    cout << "Thread::~Thread()" << endl;
}
void Thread::start(void *arg)
{
    int ret;
    this->arg = arg;

    //if you get an error here (undefined reference to 'pthread_create')
    //please include -lpthread to your linker options
    if ((ret = pthread_create(&_id, NULL, &Thread::exec, this)) != 0)
    {
        //^ READ THE COMMENT IF ERROR ^
        cout << strerror(ret) << endl;
        throw "Error";
    }
}
void Thread::join()
{
    // Allow the thread to wait for the termination status
    pthread_join(_id, NULL);
}
// Function that is to be executed by the thread
void *Thread::exec(void *thr)
{
    reinterpret_cast<Thread *> (thr)->run();
    return thr;
}

void Thread::mutex_lock()
{
	pthread_mutex_lock(&received_mutex);
}

void Thread::mutex_unlock()
{
	pthread_mutex_unlock(&received_mutex);
}

void Thread::wait_condition()
{
	pthread_cond_wait(&received_bytes, &received_mutex);
}

void Thread::signal_condition()
{
	pthread_cond_signal(&received_bytes);
}
