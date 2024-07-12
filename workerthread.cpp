#include "workerthread.h"
#include <QDebug>

WorkerThread::WorkerThread(QObject *parent)
    : QThread{parent}
{
    qDebug()<<"WorkerThread()";
}

WorkerThread::~WorkerThread()
{
    qDebug()<<"~WorkerThread()";
}
