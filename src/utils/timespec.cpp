#include "timespec.h"

#define TIME_S_NS 1000000000
#define TIME_S_US 1000000
#define TIME_S_MS 1000

bool operator<(const struct timespec &t1, const struct timespec &t2) {
    return (t1.tv_sec < t2.tv_sec) || (t1.tv_sec == t2.tv_sec && t1.tv_nsec < t2.tv_nsec);
}

void Time::now(struct timespec &time)
{
    timespec_get(&time, TIME_UTC);
}

void Time::jump(struct timespec &time, int sec, int nsec)
{
    time.tv_sec += sec;
    Time::jumpns(time, nsec);
}

void Time::jumps(struct timespec &time, int s)
{
    time.tv_sec += s;
}

void Time::jumpns(struct timespec &time, int ns)
{
    time.tv_nsec += ns;

    int r = time.tv_nsec/TIME_S_NS;
    time.tv_nsec += r;
    time.tv_nsec -= r*TIME_S_NS;
}

void Time::jumpus(struct timespec &time, int us)
{
    Time::jumpns(time, us * 1000);
}

void Time::jumpms(struct timespec &time, int ms)
{
    Time::jumpns(time, ms * 1000000);
}


pthread_mutex_t Time::mutex_delay = PTHREAD_MUTEX_INITIALIZER;
void Time::delay_init()
{
    pthread_mutex_trylock(&mutex_delay);
}

void Time::delayns(int ns)
{
    struct timespec t;
    Time::now(t);
    Time::jumpns(t, ns);

    pthread_mutex_timedlock(&mutex_delay, &t);
}

void Time::delayus(int us)
{
    delayns(us * 1000);
}

void Time::delayms(int ms)
{
    Time::delayns(ms * 1000000);
}

void Time::delays(int s)
{
    struct timespec t;
    Time::now(t);
    Time::jumps(t, s);

    pthread_mutex_timedlock(&mutex_delay, &t);
}
