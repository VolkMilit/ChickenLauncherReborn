#include "gzdoom.h"
#include <QDebug>

Gzdoom::Gzdoom(QObject *parent) : QObject(parent)
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

    QString map;
    map = params.map;
    if (params.map.at(0) == QChar('E', false) && params.map.at(2) == QChar('M', false))
        map = params.map.mid(1,1) + " " + params.map.mid(3,3);

    QString join;
    if (!params.address.isEmpty())
        join = " -join " + params.address;

    QProcess *executable = new QProcess(this);

    connect(executable, qOverload<int>(&QProcess::finished), this, &Gzdoom::isfinish);

    executable->start("x-terminal-emulator -e " + params.exe +\
                      " -IWAD " + params.iwad +\
                      " -file " + pwads +\
                      " -warp " + map +\
                      " -skill " + QString::number(params.skill) +\
                      " -stdout " +\
                      join);

    /*executable->waitForFinished();
    qDebug() << executable->readAllStandardOutput();*/

    if (executable->error() == QProcess::Crashed)
        QMessageBox::critical(0, "Error!", executable->errorString(), QMessageBox::Ok);
}

void Gzdoom::setConfig(const QString &config)
{
    params.config = config;
}

void Gzdoom::enableDemoRecording(const bool demo)
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

void Gzdoom::setSkill(const int skill)
{
    params.skill = skill;
}

void Gzdoom::setAddress(const QString &address)
{
    params.address = address;
}
