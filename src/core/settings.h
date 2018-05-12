#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QSettings>

#include "ui_mainwindow.h"

class Settings
{
    public:
        Settings();
        ~Settings();

        bool fileExist(const QString &file);

        QString getProfilesDir();
        QString getLauncherSettingsFile();
        QString getLauncherHomeDir();

        void readAllSettings(const QString &file);
        void writeAllSettings(const QString &file);

        QString readSettings(const QString &file, const QString &group, const QString &value);
        int readIntSettings(const QString &file, const QString &group, const QString &value);

        /***settings.ini***/
        /*[settings]*/

        //profile
        void setCurrentProfile(const QString &profile);
        QString getCurrentProfile();
        QString getDefaultProfileName();

        //off_wad_path
        void setOffWadPath(const short value);
        short getOffWadPath();

        //foreground_color
        void setForegroundColor(const QString &value);
        QString getForegroundColor();

        //hide program instead of close
        void setHide(const short value);
        short getHide();

        //hide program when game start
        void setHideGame(const short value);
        short getHideGame();

        //default_tab
        void setDefaultTab(const short value);
        short getDefaultTab();

        //last_iwas_dir
        void setLastIwadDir(const QString &value);
        QString getLastIwadDir();

        //last_pwad_dir
        void setLastPwadDir(const QString &value);
        QString getLastPwadDir();


        /***${profile_name}.ini***/
        /*[WAD]*/

        //last_iwad
        void setLastIwad(const QString &value);
        QString getLastIwad();

        //last_pwad
        void setLastPwad(const QString &value);
        QString getLastPwad();

        //iwad_dir
        void setIwadDir(const QString &value);
        QString getIwadDir();

        //pwad_dir
        void setPwadDir(const QString &value);
        QString getPwadDir();

        /*[Port]*/
        //game_port
        void setGamePort(const QString &value);
        QString getGamePort();

        //port_exe
        void setExePath(const QString &value);
        QString getExePath();

        //adv_exe_param
        void setAdvExeParam(const QString &value);
        QString getAdvExeParam();

        //adv_cmd_param
        void setAdvCmdParam(const QString &value);
        QString getAdvCmdParam();

        //config
        void setConfigFile(const QString &value);
        QString getConfigFile();

        //water (darkpalces specific)
        void setDarkplacesWater(const short value);
        short getDarkplacesWater();

        /*[Network]*/
        //enabled
        void setNetworkEnabled(const short value);
        short getNetworkEnabled();

        //ip
        void setIpAdress(const QString &value);
        QString getIpAdress();

        //port
        void setIpPort(const QString &value);
        QString getIpPort();

    private:
        Ui::MainWindow *myUi;

        QString home;
        QString defaultSettings;
        QString profilesDir;
        QString defaultProfile;

        void writeSettings(const QString &file, const QString &group, const QString &value, const QString &var);
        void writeSettings(const QString &file, const QString &group, const QString &value, const short var);
};

#endif // BASECONFIG_H
