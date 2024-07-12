#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "worker.h"
#include "workerthread.h"

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void onWorkerFinished();


private:
    WorkerThread *workerThread;
    Worker *worker;


signals:
    void startWorker();
    void stopWorker();


};
#endif // MAINWINDOW_H
