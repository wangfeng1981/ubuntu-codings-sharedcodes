#include "wprocessqueue.h"
#include <iostream>

using std::cout;
using std::endl;

wProcessQueue* wProcessQueue::s_ptrInstance = nullptr;

wProcessQueue::wProcessQueue()
{
    totalTaskCount = 0;
    doneTaskCount = 0 ;
}

wProcessQueue* wProcessQueue::getInstance(){
    if( wProcessQueue::s_ptrInstance==nullptr ){
        wProcessQueue::s_ptrInstance = new wProcessQueue() ;
    }
    return wProcessQueue::s_ptrInstance ;
}

void wProcessQueue::addProcessTaskForRun(wProcessTask* task)
{
    ++totalTaskCount;
    QObject::connect(task , &wProcessTask::progress , this , &wProcessQueue::onTaskProgress) ;
    QObject::connect(task , &wProcessTask::done , this , &wProcessQueue::onTaskDone) ;

    cout<<"start 1"<<endl;
    QThreadPool::globalInstance()->start(task) ;
    cout<<"start 2"<<endl;
}

void wProcessQueue::onTaskProgress(int val)
{
    emit progressChanged(0 , doneTaskCount , totalTaskCount , val , "") ;
    emit simplyProgressChanged(val) ;
}

void wProcessQueue::onTaskDone(int status,QString info)
{
    ++ doneTaskCount;
    emit progressChanged(1 , doneTaskCount , totalTaskCount , status , info) ;
    emit simplyTaskDone(doneTaskCount ,totalTaskCount ) ;
}
