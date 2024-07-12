#include "worker.h"
#include <QDebug>
#include <QThread>

Worker::Worker(QObject *parent)
    : QObject{parent}
{
    qDebug()<<"Worker()";
}

Worker::~Worker()
{
    qDebug()<<"~Worker()";
}

void Worker::doWork()
{
    qDebug() << "Worker::doWork() starting work...";
    for (int i = 0; i < 10 && !m_stopRequested.loadRelaxed(); ++i) {
        QThread::sleep(1);
        qDebug() << i;
    }
    qDebug() << "Worker::doWork() finished work.";
    emit finished();
}

void Worker::stopWork()
{
    qDebug() << "Worker::stopWork() stopping work...";
    m_stopRequested.storeRelaxed(1); // 设置停止标志
}
