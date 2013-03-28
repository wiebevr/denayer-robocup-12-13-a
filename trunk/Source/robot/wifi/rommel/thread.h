/**
 * @class Thread
 * @author De Schutter Bob
 * @date 03-2011
 * @brief Multithreading class
 */
#ifndef thread_H
#define thread_H
#include <iostream>
#include <string.h>
#include <pthread.h>
using namespace std;


extern pthread_cond_t received_bytes;
extern pthread_mutex_t received_mutex;

class Thread
{
private:
	pthread_t _id;
	// Prevent copying or assignment
	Thread(const Thread& arg);
	Thread& operator=(const Thread& rhs);
protected:
	void *arg;

	static void *exec(void *thr);
public:
	Thread();
	virtual ~Thread();
	unsigned int tid() const;
	void start(void *arg = NULL);
	void join();
	void mutex_lock();
	void mutex_unlock();
	void wait_condition();
	void signal_condition();
	virtual void run() = 0;
};
#endif
