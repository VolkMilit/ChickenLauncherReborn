#include "directorylist.h"

QStringList DirectoryList::scan(const QString &dir, const QStringList &ext)
{
    QStringList tmp;

    QDirIterator it(dir, ext, QDir::Files);
    while (it.hasNext())
        tmp.push_back(it.next());

    std::sort(tmp.begin(), tmp.end());

    return tmp;
}
