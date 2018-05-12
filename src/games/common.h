#include <QDir>
#include <QString>

class GamesPaths
{
    public:
        static QString getGzdoomDir()
        {
            return QDir::homePath() + "/.config/gzdoom/";
        }

        static QString getDarkplacesDir()
        {
            return QDir::homePath() + "/.darkplaces/";
        }

    private:
        GamesPaths();
};
