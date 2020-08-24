#ifndef TIMESPEC_H
#define TIMESPEC_H

extern "C" {
#include <time.h>
#include <pthread.h>
}

bool operator<(const struct timespec &t1, const struct timespec &t2);

namespace Time {
/* set the current time to -time- structure  */
    void now(struct timespec &time);

/* set into -time- the result of -time- + -sec.nsec-
 * sec: seconds to jump
 * nsec: nanoseconds to jump
 */
    void jump(struct timespec &time, int sec, int nsec);
/* set into -time- the result of a jump of -s- seconds */
    void jumps(struct timespec &time, int s);
/* set into -time- the result of a jump of -ns- nanoseconds (1e-9 s) */
    void jumpns(struct timespec &time, int ns);
/* set into -time- the result of a jump of -us- microseconds (1e-6 s) */
    void jumpus(struct timespec &time, int us);
/* set into -time- the result of a jump of -ms- miliseconds (1e-3 s) */
    void jumpms(struct timespec &time, int ms);

    extern pthread_mutex_t mutex_delay;
    void delay_init();

    void delayns(int ns);
    void delayus(int us);
    void delayms(int ms);
    void delays(int s);

}

#endif // TIMESPEC_H
