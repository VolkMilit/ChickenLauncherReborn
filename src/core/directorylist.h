#ifndef DIRECTORYLIST_H
#define DIRECTORYLIST_H

#include <QString>
#include <QVector>
#include <QDirIterator>
#include <QStringList>

//std headers
#include <algorithm> //std::sort as recommended by Qt docs

class DirectoryList
{
    public:
        static QVector<QString> scan(const QString &dir, QStringList ext);

    private:
        DirectoryList();
};

#endif // DIRECTORYLIST_H
