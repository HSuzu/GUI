#include "Thread.h"

Thread::Task::taskBuffer_t Thread::Task::taskBuffer;
Thread::aliasBuffer_t Thread::aliasBuffer;

void Thread::Task::initTaskBuffer()
{
    auto &mutex = taskBuffer.mutex;
    mutex.lock();
    taskBuffer.threads[self()];
    mutex.unlock();
}

void Thread::alias(const char *alias)
{
    auto &mutex = aliasBuffer.mutex;
    mutex.lock();
    aliasBuffer.aliases[alias] = self();
    mutex.unlock();
}

Thread::tid_t Thread::identify(const char *alias)
{
    MutexScope(aliasBuffer.mutex);
    return aliasBuffer.aliases[alias];
}

void Thread::Task::assignTo(const char *alias, std::function<void(void)> signal)
{
    assignTo(identify(alias), signal);
}

void Thread::Task::assignTo(Thread::tid_t thread, std::function<void(void)> signal)
{
    auto &mutex = taskBuffer.mutex;
    mutex.lock();
    taskList_t list = taskBuffer.threads[thread];
    mutex.unlock();

    list.mutex.lock();
    list.tasks.push_back({self(), signal});
    list.mutex.unlock();
}


void Thread::Task::processAll()
{
    if(!hasPendingTask()) return;

    auto &mutex = taskBuffer.mutex;
    mutex.lock();
    taskList_t list = taskBuffer.threads[self()];
    mutex.unlock();

    list.mutex.lock();
    for(auto &it : list.tasks)
    {
        it.task();
    }
    list.mutex.unlock();
}

void Thread::Task::processOne()
{
    if(!hasPendingTask()) return;

    retrieveTask().task();
}


bool Thread::Task::hasPendingTask()
{
    return (taskBuffer.threads[self()].tasks.size() != 0);
}

Thread::Task::task_t Thread::Task::retrieveTask()
{
    auto &mutex = taskBuffer.mutex;
    mutex.lock();
    taskList_t list = taskBuffer.threads[self()];
    mutex.unlock();

    list.mutex.lock();
    task_t task = list.tasks.front();
    list.tasks.pop_front();
    list.mutex.unlock();

    return task;
}
