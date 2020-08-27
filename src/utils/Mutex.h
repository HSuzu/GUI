#ifndef MUTEX_H
#define MUTEX_H

extern "C" {
#include <pthread.h>
}

class Mutex
{
private:
    pthread_mutex_t _mutex;

public:
    Mutex() : _mutex(PTHREAD_MUTEX_INITIALIZER) {}
    ~Mutex()
    {
        unlock();
        pthread_mutex_destroy(&_mutex);
    }

    inline void
    lock()
    {
        pthread_mutex_lock(&_mutex);
    }

    inline void
    unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }

    inline void
    trylock()
    {
        pthread_mutex_trylock(&_mutex);
    }

    inline void
    timedlock(const struct timespec &abs_time)
    {
        pthread_mutex_timedlock(&_mutex, &abs_time);
    }
};

class MutexScope
{
private:
    Mutex *_mutex;
public:
    MutexScope() : _mutex(nullptr) {}
    MutexScope(MutexScope &&other) : _mutex(other._mutex)
    {
        other._mutex = nullptr;
    }

    MutexScope(Mutex &mutex) : _mutex(&mutex)
    {
        _mutex->lock();
    }

    ~MutexScope()
    {
        if(_mutex != nullptr) _mutex->unlock();
    }
};

#endif // MUTEX_H
