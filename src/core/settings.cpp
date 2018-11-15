#include "settings.h"

#include <QDir>

Settings::Settings()
{
    #ifdef _WIN32
        home = QDir::homePath() + "\\ApplicationData\\ChickenLauncher\\";
    #else
        home = QDir::homePath() + "/.config/ChickenLauncher/";
    #endif

    defaultSettings = home + "settings.ini";
    profilesDir = home + "profiles/";
}

Settings::~Settings(){}

QString Settings::getLauncherHomeDir()
{
    return home;
}

QString Settings::getProfilesDir()
{
    return profilesDir;
}

QString Settings::getLauncherSettingsFile()
{
    return defaultSettings;
}

/***settings.ini***/
/*[settings]*/

//profile
QString Settings::getCurrentProfile()
{
    defaultProfile = readSettings(defaultSettings, "settings", "Profile");
    return profilesDir + defaultProfile + ".ini";
}

void Settings::setCurrentProfile(const QString &profile)
{
    writeSettings(defaultSettings, "settings", "Profile", profile);
}

QString Settings::getDefaultProfileName()
{
    defaultProfile = readSettings(defaultSettings, "settings", "Profile");
    return defaultProfile;
}

//off_wad_path
void Settings::setOffWadPath(const short value)
{
    writeSettings(defaultSettings, "settings", "OffWadPath", value);
}

short Settings::getOffWadPath()
{
    short ret = readIntSettings(defaultSettings, "settings", "OffWadPath");
    return ret;
}

//default tab
// 0 - profiles, 1 - wads
void Settings::setDefaultTab(const short value)
{
    writeSettings(defaultSettings, "settings", "DefaultTab", value);
}

short Settings::getDefaultTab()
{
    short ret = readIntSettings(defaultSettings, "settings", "DefaultTab");
    return ret;
}

//last iwad dir
void Settings::setLastIwadDir(const QString &value)
{
    writeSettings(defaultSettings, "settings", "LastIwadDir", value);
}

QString Settings::getLastIwadDir()
{
    QString ret = readSettings(defaultSettings, "settings", "LastIwadDir");
    return ret;
}

//last pwad dir
void Settings::setLastPwadDir(const QString &value)
{
    writeSettings(defaultSettings, "settings", "LastPwadDir", value);
}

QString Settings::getLastPwadDir()
{
    QString ret = readSettings(defaultSettings, "settings", "LastPwadDir");
    return ret;
}

/***${profile_name}.ini***/
/*[WAD]*/

//last_iwad
void Settings::setLastIwad(const QString &value)
{
    writeSettings(getCurrentProfile(), "WAD", "LastIwad", value);
}

QString Settings::getLastIwad()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "LastIwad");
    return ret;
}

//last_pwad
void Settings::setLastPwad(const QString &value)
{
    writeSettings(getCurrentProfile(), "WAD", "LastPwads", value);
}

QString Settings::getLastPwad()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "LastPwads");
    return ret;
}

//iwad_dir
void Settings::setIwadDir(const QString &value)
{
    writeSettings(getCurrentProfile(), "WAD", "IwadDir", value);
}

QString Settings::getIwadDir()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "IwadDir");
    return ret;
}

//pwad_dir
void Settings::setPwadDir(const QString &value)
{
    writeSettings(getCurrentProfile(), "WAD", "PwadDir", value);
}

QString Settings::getPwadDir()
{
    QString ret = readSettings(getCurrentProfile(), "WAD", "PwadDir");
    return ret;
}

//exe_path
void Settings::setExePath(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "PortExe", value);
}

QString Settings::getExePath()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "PortExe");
    return ret;
}

//adv_exe_param
void Settings::setAdvExeParam(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "AdditionalPortParam", value);
}

QString Settings::getAdvExeParam()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "AdditionalPortParam");
    return ret;
}

//adv_cmd_param
void Settings::setAdvCmdParam(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "AdditionalCmdParam", value);
}

QString Settings::getAdvCmdParam()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "AdditionalCmdParam");
    return ret;
}

//config
void Settings::setConfigFile(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "Config", value);
}

QString Settings::getConfigFile()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "Config");
    return ret;
}

//game_port
void Settings::setGamePort(const QString &value)
{
    writeSettings(getCurrentProfile(), "Port", "GamePort", value);
}

QString Settings::getGamePort()
{
    QString ret = readSettings(getCurrentProfile(), "Port", "GamePort");
    return ret;
}

//water (dakrplaces specific)
void Settings::setDarkplacesWater(const short value)
{
    writeSettings(getCurrentProfile(), "Port", "Water", value);
}

short Settings::getDarkplacesWater()
{
    short ret = readIntSettings(getCurrentProfile(), "Port", "Water");
    return ret;
}

/*[Network]*/
//enabled
void Settings::setNetworkEnabled(const short value)
{
    writeSettings(getCurrentProfile(), "Network", "Enabled", value);
}

short Settings::getNetworkEnabled()
{
    short ret = readIntSettings(getCurrentProfile(), "Network", "Enabled");
    return ret;
}

//ip
void Settings::setIpAdress(const QString &value)
{
    writeSettings(getCurrentProfile(), "Network", "IP", value);
}

QString Settings::getIpAdress()
{
    QString ret = readSettings(getCurrentProfile(), "Network", "IP");
    return ret;
}

//ip_port
void Settings::setIpPort(const QString &value)
{
    writeSettings(getCurrentProfile(), "Network", "IpPort", value);
}

QString Settings::getIpPort()
{
    QString ret = readSettings(getCurrentProfile(), "Network", "IpPort");
    return ret;
}

void Settings::writeSettings(const QString &file, const QString &group, const QString &value, const QString &var)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(value, var);
    settings.endGroup();
}

QString Settings::readSettings(const QString &file, const QString &group, const QString &value)
{
    QString rv;

    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    rv = settings.value(value).toString();
    settings.endGroup();

    return rv;
}

void Settings::writeSettings(const QString &file, const QString &group, const QString &value, const short var)
{
    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(value, var);
    settings.endGroup();
}

int Settings::readIntSettings(const QString &file, const QString &group, const QString &value)
{
    int rv;

    QSettings settings(file, QSettings::IniFormat);
    settings.beginGroup(group);
    rv = settings.value(value).toInt();
    settings.endGroup();

    return rv;
}
