#include "plotterwindow.h"
#include "ui_plotterwindow.h"
#include <QFileDialog>
#include <QThread>
#include "FileOpener.h"
#include "TecplotFile.h"
#include <iostream>
#include <mgl2/qmathgl.h>
#include <mgl2/mgl.h>
#include <MglTecplotDrawer.h>
#include <QStandardItemModel>

PlotterWindow::PlotterWindow(QWidget *parent) :
    QMainWindow(parent),
    tecplot_data("BadData"),
    ui(new Ui::PlotterWindow)
{
    ui->setupUi(this);
    ui->pbframe->hide();
    QMGL = new QMathGL(ui->mglFrame);
    QMGL->hide();
    QMGL->setZoom(false);
    QMGL->setRotate(true);
    drawer = NULL;

}

PlotterWindow::~PlotterWindow()
{
    delete ui;
}

void PlotterWindow::doOpen(QString fileName)
{
    opener_thread = new QThread( );
    opener   = new FileOpener(fileName);
    opener->moveToThread(opener_thread);

    connect( opener_thread, SIGNAL(started()), opener, SLOT(doOpen()) );
    connect( opener, SIGNAL(openFinished()), opener_thread, SLOT(quit()) );
    connect( opener_thread, SIGNAL(finished()), this, SLOT(finishOpen()) );
    connect( opener_thread, SIGNAL(finished()), opener_thread, SLOT(deleteLater()) );
    connect(&timer, SIGNAL(timeout()), this, SLOT(handleTimer()));

    opener_thread->start();
    timer.start(10);
}

void PlotterWindow::onOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Tecplot files (*.*)"));
    if (fileName.size() == 0)
        return;
    QMGL->hide();
    ui->mglFrame->hide();
    ui->pbframe->show();
    ui->openFileLabel->setText(tr("Opening ") + fileName + "...");
    ui->openFilePB->setValue(0);

    doOpen(fileName);
}

void PlotterWindow::handleTimer()
{
    ui->openFilePB->setValue(opener->getOpenPercent());
}

void PlotterWindow::finishOpen()
{
    timer.stop();
    ui->pbframe->hide();
    ui->mglFrame->show();
    QMGL->show();
    tecplot_data = opener->getData();
    delete drawer;
    drawer = new MglTecplotDrawer(tecplot_data);
    QMGL->setDraw(drawer);
    QMGL->setSize(ui->mglFrame->geometry().width(),ui->mglFrame->geometry().height());
    QMGL->update();

    ui->zonesComboBox->addItem("All zones");

    for (auto i : tecplot_data.zones())
        ui->zonesComboBox->addItem( QString::fromStdString(i->name()));

     checkbox_model = new QStandardItemModel;
    for (auto v :tecplot_data.vars())
    {
          QStandardItem* item = new QStandardItem;
          item->setText(QString::fromStdString(v->name()));
          item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
          item->setData(Qt::Checked, Qt::CheckStateRole);
          checkbox_model->insertRow(0, item);
      }

      ui->varsComboBox->setModel(checkbox_model);
      connect(checkbox_model, SIGNAL(dataChanged ( const QModelIndex&, const QModelIndex&)), this, SLOT(varsChanged(const QModelIndex&, const QModelIndex&)));

}

void PlotterWindow::varsChanged(const QModelIndex& i1, const QModelIndex&i2)
{
    int checkState =  checkbox_model->itemFromIndex(i1)->checkState();

    cout <<i1.row()<<" "<<i1.column()<<" "<<i1.internalId()<<endl;
    if(checkState == Qt::Checked)
    {
        drawer->enableVar(i1.row(),true);
    }
    else if(checkState == Qt::Unchecked)
    {
        drawer->enableVar(i1.row(),false);
    }

    QMGL->update();

}

void PlotterWindow::zoneChanged(int zone)
{
    this->drawer->showZone(zone-1);
    QMGL->update();
}

void PlotterWindow::contourChanged(bool checked)
{
    this->drawer->enableContour(checked);
    QMGL->update();
}

void PlotterWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

   QMGL->setSize(ui->mglFrame->geometry().width(),ui->mglFrame->geometry().height());
   QMGL->update();

   // Your code here.
}
