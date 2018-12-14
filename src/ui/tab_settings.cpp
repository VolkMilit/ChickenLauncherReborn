#include "mainwindow.h"

void MainWindow::populateConfigList()
{
    const QStringList &scan = DirectoryList::scan(GamesPaths::getGzdoomDir(), QStringList() << "*.ini");

    for (const QString &item : scan)
    {
        QFileInfo file(item);
        ListHelper::addItem(ui.lw_port_config, file.baseName());
    }
}

void MainWindow::on_le_iwaddir_textChanged()
{
    populateIwadList();
}

void MainWindow::on_le_pwaddir_textChanged()
{
    populatePwadList();
}

void MainWindow::on_btn_config_new_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create new config"),
                                             tr("New config name:"), QLineEdit::Normal, "", &ok);

    text.remove(".ini");

    QFile file(GamesPaths::getGzdoomDir() + text + ".ini");
    if (file.exists() || text == "[default]")
    {
        QMessageBox::warning(this, "Error", "Config already exist.", QMessageBox::Ok);
        return;
    }

    if (ok && !text.isEmpty())
    {
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << "" << endl;
        }
        ListHelper::addItem(ui.lw_port_config, text);
    }
}

void MainWindow::on_btn_config_rename_clicked()
{
    QListWidgetItem *item = ui.lw_port_config->currentItem();

    if (!item)
        return;

    if (item->text() == "[default]")
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Rename config '") + item->text() + "'",
                                             tr("New config name:"), QLineEdit::Normal,
                                             item->text(), &ok);

    QFile file(GamesPaths::getGzdoomDir() + text + ".ini");
    if (file.exists())
    {
        QMessageBox::warning(this, "Error", "Config already exist.", QMessageBox::Ok);
        return;
    }

    if (ok && !text.isEmpty())
    {
        QFile::rename(GamesPaths::getGzdoomDir() + item->text() + ".ini", GamesPaths::getGzdoomDir() + text + ".ini");
        item->setText(text);
    }
}

void MainWindow::on_btn_config_delete_clicked()
{
    QListWidgetItem *item = ui.lw_port_config->currentItem();

    if (!item)
        return;

    if (item->text() == "[default]")
        return;

    QMessageBox message;
    message.setText("Warning!");
    message.setInformativeText("Are you sure you want to delete " + item->text() + " config?");
    message.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    message.setDefaultButton(QMessageBox::Cancel);
    int ok = message.exec();

    if (ok == QMessageBox::Ok)
    {
        QFile file(GamesPaths::getGzdoomDir() + item->text() + ".ini");
        file.remove();

        delete item;
    }
}

void MainWindow::on_lw_port_config_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous != nullptr)
    {
        QFont font2;
        font2.setBold(false);

        previous->setFont(font2);
    }

    if (current != nullptr)
    {
        QFont font;
        font.setBold(true);

        current->setFont(font);
    }
}

void MainWindow::on_btn_iwad_chooser_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,\
                                                    tr("Choose iwad directory"),\
                                                    QDir::homePath(),\
                                                    QFileDialog::ShowDirsOnly);

    if (dir.isEmpty())
        return;

    ui.le_iwaddir->setText(dir);
}

void MainWindow::on_btn_pwad_chooser_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,\
                                                    tr("Choose pwad directory"),\
                                                    QDir::homePath(),\
                                                    QFileDialog::ShowDirsOnly);
    if (dir.isEmpty())
        return;

    ui.le_pwaddir->setText(dir);
}

void MainWindow::on_btn_exe_chooser_clicked()
{
    QString dir = QFileDialog::getOpenFileName(this,\
                                                    tr("Choose exe directory"),\
                                                    QDir::homePath(),\
                                                    tr("Executable Files (*.* *.exe)"));
    if (dir.isEmpty())
        return;

    ui.le_executablepath->setText(dir);
}
