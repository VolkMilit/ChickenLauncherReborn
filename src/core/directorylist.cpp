#include "directorylist.h"

QVector<QString> DirectoryList::scan(const QString &dir, QStringList ext)
{
    QVector<QString> tmp;

    QDirIterator it(dir, ext, QDir::Files);
    while (it.hasNext())
        tmp.push_back(it.next());

    std::sort(tmp.begin(), tmp.end());

    return tmp;
}
