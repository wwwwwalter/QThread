#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    workerThread = new WorkerThread(this);
    worker = new Worker();

    worker->moveToThread(workerThread);
    // connect(workerThread, &QThread::started, worker, &Worker::doWork);
    connect(this,&MainWindow::startWorker,worker,&Worker::doWork,Qt::QueuedConnection);
    connect(this,&MainWindow::stopWorker,worker,&Worker::stopWork,Qt::QueuedConnection);

    // connect(worker, &Worker::finished, workerThread, &QThread::quit);
    connect(worker, &Worker::finished, this, &MainWindow::onWorkerFinished);

    connect(workerThread, &QThread::finished, worker, &Worker::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater);


    // 启动线程，但不工作
    workerThread->start();
}

MainWindow::~MainWindow()
{
    if (workerThread && workerThread->isRunning()) {
        workerThread->quit();
        qDebug()<<"quit()";
        workerThread->wait(); // 等待线程结束
        qDebug()<<"wait()";
    }
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    qDebug()<<"MainWindow::startButton()";
    QMetaObject::invokeMethod(worker, "doWork", Qt::QueuedConnection);
}

void MainWindow::on_stopButton_clicked()
{
    qDebug()<<"MainWindow::stopButton()";
    QMetaObject::invokeMethod(worker, "stopWork", Qt::DirectConnection);
}

void MainWindow::onWorkerFinished()
{
    qDebug() << "MainWindow::onWorkerFinished() worker has finished work.";
}
