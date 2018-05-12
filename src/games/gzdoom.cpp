#include "gzdoom.h"
#include <QDebug>

Gzdoom::Gzdoom()
{
}

Gzdoom::~Gzdoom()
{
}

void Gzdoom::start()
{
    QStringList pwads_list = params.pwads;
    QString pwads;
    for (QString item : pwads_list)
        pwads += item + " ";

    QProcess *executable = new QProcess;
    executable->start("x-terminal-emulator -e " + params.exe + " -IWAD " + params.iwad + " -file " + pwads);

    /*executable->waitForFinished();
    qDebug() << executable->readAllStandardOutput();*/

    if (executable->error() == QProcess::Crashed)
        QMessageBox::critical(0, "Error!", executable->errorString(), QMessageBox::Ok);
}

void Gzdoom::setConfig(const QString &config)
{
    params.config = config;
}

void Gzdoom::setDemo(const QString &demo)
{
    params.demo = demo;
}

void Gzdoom::setExe(const QString &exe)
{
    params.exe = exe;
}

void Gzdoom::setIwad(const QString &iwad)
{
    params.iwad = iwad;
}

void Gzdoom::setMap(const QString &map)
{
    params.map = map;
}

void Gzdoom::setNoMusic(const bool music)
{
    params.nomusic = music;
}

void Gzdoom::setNoSFX(const bool sfx)
{
    params.nosfx = sfx;
}

void Gzdoom::setNoSound(const bool sound)
{
    params.nosound = sound;
}

void Gzdoom::setPwads(const QStringList &pwads)
{
    params.pwads = pwads;
}
