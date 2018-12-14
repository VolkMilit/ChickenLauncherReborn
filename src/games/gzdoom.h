#ifndef GZDOOM_H
#define GZDOOM_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QMessageBox>

class Gzdoom : public QObject
{
    Q_OBJECT

    public:
        Gzdoom(QObject *parent = nullptr);
        virtual ~Gzdoom();

        void setIwad(const QString &iwad);
        void setPwads(const QStringList &pwads);
        void setExe(const QString &exe);
        void setNoMusic(const bool music);
        void setNoSound(const bool sound);
        void setNoSFX(const bool sfx);
        void setMap(const QString &map);
        void setSkill(const int skill);
        void enableDemoRecording(const bool demo);
        void setConfig(const QString &config);
        void setAddress(const QString &address);

        void start();

        void processOut();

    signals:
        void isfinish(int exitcode);

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
            int skill;
            bool demo;
            QString config;
            QString address;
        } params;

        QString output;
};

#endif // GZDOOM_H
