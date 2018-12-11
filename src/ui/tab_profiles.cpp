#include "mainwindow.h"

void MainWindow::on_btn_profiles_new_clicked()
{
    newProfileDialog dialog;
    bool ok = dialog.exec();

    if (ok)
        ListHelper::addItem(ui.tw_profiles, dialog.getName(), ":/gzdoom.svg");

    dialog.done(0);
}

void MainWindow::populateProfilesTable()
{
    ui.tw_profiles->setIconSize(QSize(50, 25));

    const QStringList &scan = DirectoryList::scan(settings->getProfilesDir(), QStringList() << "*.ini");

    for (auto i = 0; i < scan.size(); ++i)
    {
        const QString &port = settings->readSettings(scan.at(i), "Port", "GamePort");
        QString profileRow = scan.at(i);

        QFileInfo profile(profileRow.remove(".ini"));

        if (port == "GZDoom")
            ListHelper::addItem(ui.tw_profiles, profile.baseName(), ":/gzdoom.svg");
        else if (port == "Darkplaces")
            ListHelper::addItem(ui.tw_profiles, profile.baseName(), ":/darkplaces.svg");
        else if (port == "UHexen2")
            ListHelper::addItem(ui.tw_profiles, profile.baseName(), ":/uhexen2.svg");
        else if (port == "dhewm3")
            ListHelper::addItem(ui.tw_profiles, profile.baseName(), ":/dhewm3.svg");
    }
}

void MainWindow::on_btn_profiles_rename_clicked()
{
    QListWidgetItem *item = ui.tw_profiles->currentItem();
    QString profilesDir = settings->getProfilesDir();

    if (!item)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Rename profile '") + item->text() + "'",
                                             tr("New profile name:"), QLineEdit::Normal,
                                             item->text(), &ok);

    QFile file(profilesDir + text + ".ini");
    if (file.exists())
    {
        QMessageBox::warning(this, "Error", "Profile already exist.", QMessageBox::Ok);
        return;
    }

    if (ok && !text.isEmpty())
    {
        if (settings->getDefaultProfileName() == item->text())
            settings->setCurrentProfile(text);

        QFile::rename(profilesDir + item->text() + ".ini", profilesDir + text + ".ini");
        item->setText(text);
    }
}

void MainWindow::on_btn_profiles_delete_clicked()
{
    QListWidgetItem *item = ui.tw_profiles->currentItem();

    if (!item)
        return;

    QMessageBox message;
    message.setText("Warning!");
    message.setInformativeText("Are you sure you want to delete " + item->text() + " profile?");
    message.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    message.setDefaultButton(QMessageBox::Cancel);
    int ok = message.exec();

    if (ok == QMessageBox::Ok)
    {
        QFile file(settings->getProfilesDir() + item->text() + ".ini");
        file.remove();
        settings->setCurrentProfile(ui.tw_profiles->currentItem()->text());

        delete item;
    }
}

void MainWindow::on_btn_profiles_clone_clicked()
{
    QListWidgetItem *item = ui.tw_profiles->currentItem();

    if (!item)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Copy profile '") + item->text() + "'",
                                             tr("New profile name:"), QLineEdit::Normal,
                                             item->text(), &ok);

    QFile file(settings->getProfilesDir() + text + ".ini");
    if (file.exists())
    {
        QMessageBox::warning(this, "Error", "Profile already exist.", QMessageBox::Ok);
        return;
    }

    if (ok && !text.isEmpty())
    {
        QString profilesDir = settings->getProfilesDir();

        QFile::copy(profilesDir + item->text() + ".ini", profilesDir + text + ".ini");

        ListHelper::addItem(ui.tw_profiles, ui.tw_profiles->currentItem()->text(), ":/gzdoom.png");
        ListHelper::selectItem(ui.tw_profiles, text);
        settings->setCurrentProfile(ui.tw_profiles->currentItem()->text());
    }
}

void MainWindow::on_btn_profiles_load_clicked()
{
    writeSettings();

    QListWidgetItem *lwitem = ui.tw_profiles->currentItem();

    settings->setCurrentProfile(lwitem->text());

    ui.lw_iwad->clear();
    ui.lw_pwad->clear();
    ui.le_iwaddir->clear();
    ui.le_pwaddir->clear();

    for (int i = 0; i < ui.tw_profiles->count(); ++i)
    {
        QListWidgetItem *item = ui.tw_profiles->item(i);

        QFont font;
        font.setBold(false);

        item->setFont(font);
    }

    QFont font;
    font.setBold(true);
    lwitem->setFont(font);

    this->setWindowTitle("ChickenLauncher - " + lwitem->text());

    readSettings();
}
