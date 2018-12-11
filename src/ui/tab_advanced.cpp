#include "mainwindow.h"

void MainWindow::on_le_gz_map_textChanged(const QString &arg1)
{
    const QString &last_iwad = ui.lw_iwad->currentItem()->text();
    if (last_iwad.contains("DOOM.WAD", Qt::CaseInsensitive) \
            || last_iwad.contains("heretic", Qt::CaseInsensitive) \
            || last_iwad.contains("wolf", Qt::CaseInsensitive))
    {
        if (!arg1.isEmpty())
        {
            if (arg1.at(0).isDigit())
                ui.le_gz_map->setText("E" + QString(arg1.at(0)).toUtf8());

            if (arg1.length() >= 3)
                if (arg1.at(2).isDigit())
                    ui.le_gz_map->setText("E" + QString(arg1.at(1)).toUtf8() + "M" + QString(arg1.at(2)).toUtf8());
        }
    }
}
