#ifndef WPROCESSQUEUE_H
#define WPROCESSQUEUE_H

//基于QT QThreadPool封装的任务处理队列类  该类只使用一个线程，按添加顺序逐一处理队列中的任务。
//每个任务都是继承至 QRunnable
//使用步骤
//1. 在main函数开始在栈上创建一个wProcessQueueAutoRelease对象，负责程序退出后自动释放任务队列单例指针。
//2. 继承wProcessTask，新类为SomeTask，重载void run() override {...} 函数。
//3. 如果需要进度更新，绑定wProcessQueue::progressChanged信号
//4. 在需要多线程运行的地方SomeTask* ptr = new SomeTask(); 然后调用wProcessQueue::getIntances()->addProcessTaskForRun(ptr)

#include <QObject>

#include <QRunnable>
#include <QThreadPool>
#include <string>
#include <vector>

using std::vector;
using std::string;

//一个处理任务
class wProcessTask:public QObject, public QRunnable
{
Q_OBJECT

public:
    //重载函数
    //virtual void run() = 0;

    //val 0-100
    inline void setProgress(int val) { emit progress(val);}
    //status of task, usually use 0 for success.
    inline void setDone(int status,QString info="") {emit done(status,info);}
    virtual inline ~wProcessTask(){}

signals:
    //val 0-100.
    void progress(int val) ;
    void done(int val,QString info);

};

class wProcessQueueAutoRelease ;

class wProcessQueue : public QObject
{
    Q_OBJECT
public:
    static wProcessQueue* getInstance() ;

    //the task pointer is managed by wProcessQueue.
    void addProcessTaskForRun(wProcessTask* task) ;


    inline void resetTaskCount(){totalTaskCount=0;doneTaskCount=0;}

public slots:
    //receive task signal
    void onTaskProgress(int val) ;
    //receive task signal
    void onTaskDone(int status,QString info) ;

signals:
    //task is done, or task is added , or current task emit progress will emit this signals!
    //type = 0 is progress changed, type=1 is task done happend.
    void progressChanged(int type, int doneTaskCnt,int totalTaskCnt, int progressOrStatus, QString currTaskDoneInfo );
    //only for progress of one task.
    void simplyProgressChanged(int progressVal);//一个任务进度变化
    void simplyTaskDone(int doneCnt,int allCnt);//每个任务完成时触发，成功失败都触发

private:
    friend class wProcessQueueAutoRelease;
    wProcessQueue();
    inline ~wProcessQueue(){} ;
    static wProcessQueue* s_ptrInstance ;

    int totalTaskCount ;
    int doneTaskCount ;

};

//auto release for wProcessQueue instance pointer
class wProcessQueueAutoRelease{
public:
    inline wProcessQueueAutoRelease(){}
    inline ~wProcessQueueAutoRelease(){if(wProcessQueue::getInstance()!=nullptr) delete wProcessQueue::s_ptrInstance;
                                      wProcessQueue::s_ptrInstance=nullptr;}

};

#endif // WPROCESSQUEUE_H
