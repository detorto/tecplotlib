#ifndef FILEOPENER_H
#define FILEOPENER_H
#include <QObject>
#include <TecplotFile.h>
#include <QTimer>

class FileOpener : public QObject
{

Q_OBJECT
public:
    FileOpener(QString fileName);

    ~FileOpener();

    int getOpenPercent();
    TecplotData getData();

public slots:
    void doOpen();

signals:
    void openFinished();

private:
    QString fileName;
    TecplotFile *tfile;
};

#endif // FILEOPENER_H
