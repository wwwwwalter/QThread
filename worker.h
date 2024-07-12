#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
    ~Worker();

public slots:
    void doWork();
    void stopWork();

signals:
    void finished();
    void error(QString err);

private:
    QAtomicInt m_stopRequested;
};

#endif // WORKER_H
