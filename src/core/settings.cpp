#include "settings.h"

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

/* ___     _                            _
  | _ \___| |_ _  _ _ _ _ _   __ ____ _| |_  _ ___
  |   / -_)  _| || | '_| ' \  \ V / _` | | || / -_)
  |_|_\___|\__|\_,_|_| |_||_|  \_/\__,_|_|\_,_\___|
*/

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

//foreground_color
void Settings::setForegroundColor(const QString &value)
{
    writeSettings(defaultSettings, "settings", "ForegroundColor", value);
}

QString Settings::getForegroundColor()
{
    QString ret = readSettings(defaultSettings, "settings", "ForegroundColor");
    return ret;
}

//hide program instead of close
void Settings::setHide(const short value)
{
    writeSettings(defaultSettings, "settings", "hide", value);
}

short Settings::getHide()
{
    short ret = readIntSettings(defaultSettings, "settings", "Hide");
    return ret;
}

//hide program when game start
void Settings::setHideGame(const short value)
{
    writeSettings(defaultSettings, "settings", "HideGame", value);
}

short Settings::getHideGame()
{
    short ret = readIntSettings(defaultSettings, "settings", "HideGame");
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

/* ___             _   _
  | __|  _ _ _  __| |_(_)___ _ _  ___
  | _| || | ' \/ _|  _| / _ \ ' \(_-<
  |_| \_,_|_||_\__|\__|_\___/_||_/__/
*/

bool Settings::fileExist(const QString &file)
{
    /*QFile f(file);

    QFile settings(defaultSettings);
    QString defaultProfileFile = getCurrentProfile();
    QFile profile(defaultProfileFile);

    if (!f.exists())
    {
        QMessageBox::critical(this, "", "Seams to file " + file
                              + " doesn't exist. Launcher create new settings.ini and new default.ini if they missig.");

        //settings.ini
        if (!settings.exists())
        {
            setForegroundColor("Blue");
            setHide(1);
            setOffWadPath(0);
            setCurrentProfile("default.ini");
        }

        //default.ini
        if (!profile.exists())
        {
            setAdvCmdParam("");
            setAdvExeParam("");
            setExePath("gzdoom");
            setIwadDir("$HOME/games/DOOM/IWAD");
            setPwadDir("$HOME/games/DOOM/PWAD");
            setLastIwad("DOOM.WAD");
        }

        return false;
    }

    return true;*/
}

void Settings::writeAllSettings(const QString &file)
{
    //[WAD]
    /*writeSettings(file, "WAD", "iwad_dir", myUi->le_iwad->text());
    writeSettings(file, "WAD", "iwad_dir", myUi->le_pwad->text());*/

    //[Port]
    /*writeSettings(file, "Port", "port_exe", myUi->le_exe->text());
    writeSettings(file, "Port", "additional_port_param", myUi->le_adv_port_param->text());
    writeSettings(file, "Port", "additional_cmd_param", myUi->le_adv_cmd_param->text());*/
}

void Settings::readAllSettings(const QString &file)
{
    //[WAD]
    /*myUi->le_iwad->setText(readSettings(file, "WAD", "iwad_dir"));
    myUi->le_pwad->setText(readSettings(file, "WAD", "pwad_dir"));*/

    //[Port]
    /*myUi->le_exe->setText(readSettings(file, "Port", "port_exe"));
    myUi->le_adv_port_param->setText(readSettings(file, "Port", "additional_port_param"));
    myUi->le_adv_cmd_param->setText(readSettings(file, "Port", "additional_cmd_param"));

    if (readIntSettings(file, "Port", "water") == 1)
        myUi->cb_darkplaces_water->setChecked(true);

    //[Network]
    if (readIntSettings(file, "Network", "enabled") == 1)
        myUi->gb_join->setChecked(true);

    myUi->le_ip->setText(readSettings(file, "Network", "ip"));
    myUi->le_port->setText(readSettings(file, "Network", "ip_port"));*/
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
