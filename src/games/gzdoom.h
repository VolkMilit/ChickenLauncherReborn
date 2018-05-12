#ifndef GZDOOM_H
#define GZDOOM_H

#include <QString>
#include <QProcess>
#include <QMessageBox>

class Gzdoom
{
    public:
        Gzdoom();
        ~Gzdoom();

        void setIwad(const QString &iwad);
        void setPwads(const QStringList &pwads);
        void setExe(const QString &exe);
        void setNoMusic(const bool music);
        void setNoSound(const bool sound);
        void setNoSFX(const bool sfx);
        void setMap(const QString &map);
        void setDemo(const QString &demo);
        void setConfig(const QString &config);

        void start();

    private:
        struct params
        {
            QString iwad;
            QStringList pwads;
            QString exe;
            bool nomusic;
            bool nosound;
            bool nosfx;
            QString map;
            QString demo;
            QString config;
        } params;
};

#endif // GZDOOM_H
