#ifndef PLOTTERWINDOW_H
#define PLOTTERWINDOW_H

#include <QMainWindow>
#include "FileOpener.h"
#include <TecplotData.h>
#include <mgl2/qmathgl.h>
#include <MglTecplotDrawer.h>
#include <QModelIndex>
#include <QStandardItemModel>
namespace Ui {
class PlotterWindow;
}

class PlotterWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PlotterWindow(QWidget *parent = 0);
    ~PlotterWindow();

public slots:
    void onOpen();
    void finishOpen();
    void handleTimer();
    void zoneChanged(int zone);
    void contourChanged(bool checked);
    void varsChanged(const QModelIndex&, const QModelIndex&);

private:
    void doOpen(QString fileName);
    void resizeEvent(QResizeEvent* event);

    QThread *opener_thread;
    FileOpener *opener;
    QTimer timer;
    TecplotData tecplot_data;
    MglTecplotDrawer *drawer;
    Ui::PlotterWindow *ui;
    QStandardItemModel *checkbox_model;
    QMathGL *QMGL;
};

#endif // PLOTTERWINDOW_H
