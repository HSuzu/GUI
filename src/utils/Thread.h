#pragma once

#ifndef THREAD_H
#define THREAD_H

extern "C" {
#include <pthread.h>
}

#include <unordered_map>
#include <list>

#include "Hash.h"
#include "Mutex.h"

namespace Thread {

    using tid_t = pthread_t;
    inline tid_t self() { return pthread_self(); }

    struct aliasBuffer_t {
        std::unordered_map<const char *, tid_t, Utils::hash<const char *> > aliases;
        Mutex mutex;
    };

    extern aliasBuffer_t aliasBuffer;

    void alias(const char *alias);

    tid_t identify(const char *alias);

    namespace Task {
        struct task_t {
            tid_t source;
            std::function<void(void)> task;
        };

        struct taskList_t {
            std::list<task_t> tasks;
            Mutex mutex;
        };

        struct taskBuffer_t {
            std::unordered_map<tid_t, taskList_t > threads;
            Mutex mutex;
        };

        extern taskBuffer_t taskBuffer;


        void initTaskBuffer();

        void assignTo(const char *alias, std::function<void(void)> task);
        void assignTo(tid_t thread, std::function<void(void)> task);

        void processAll();
        void processOne();

        bool hasPendingTask();
        task_t retrieveTask();
    }
}

#endif // THREAD_H
