#include "FileOpener.h"
#include "TecplotData.h"
#include <QTimer>

FileOpener::FileOpener(QString fileName)
{
    tfile = new TecplotFile(fileName.toUtf8().constData());
}

FileOpener::~FileOpener()
{
    delete tfile;
}

void FileOpener::doOpen()
{
    tfile->open();
    emit openFinished();
}

int FileOpener::getOpenPercent()
{
    return tfile->openingPersent();
}

TecplotData FileOpener::getData()
{
    return tfile->data();
}
