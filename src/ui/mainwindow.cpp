#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    settings = new Settings;

    populateProfilesTable();
    populateConfigList();
    setupWindow();
}

MainWindow::~MainWindow()
{  
    writeSettings();

    delete settings;
    //checkedItems.clear();
    delete ui;
}

void MainWindow::on_btn_profiles_new_clicked()
{
    newProfileDialog dialog;
    bool ok = dialog.exec();

    if (ok)
        TableHelper::addItem(ui->tw_profiles, ":/doom.png", dialog.getName(), dialog.getPort());

    dialog.done(0);
}

void MainWindow::populateProfilesTable()
{
    ui->tw_profiles->setIconSize(QSize(50, 25));

    const QStringList &scan = DirectoryList::scan(settings->getProfilesDir(), QStringList() << "*.ini");

    for (auto i = 0; i < scan.size(); ++i)
    {
        const QString &port = settings->readSettings(scan.at(i), "Port", "GamePort");
        QString profileRow = scan.at(i);

        QFileInfo profile(profileRow.remove(".ini"));

        TableHelper::addItem(ui->tw_profiles, ":/doom.png", profile.baseName(), port);
    }
}

void MainWindow::setupWindow()
{
    QFileInfo title(settings->getDefaultProfileName());
    this->setWindowTitle("ChickenLauncher - " + title.baseName().remove(".ini"));

    TableHelper::selectItem(ui->tw_profiles, title.baseName().remove(".ini"));

    ui->le_search->hide();

    ui->tabWidget->setTabEnabled(5, false);

    readSettings();
}

void MainWindow::on_btn_profiles_rename_clicked()
{
    QTableWidgetItem *item = ui->tw_profiles->currentItem();
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
    QTableWidgetItem *item = ui->tw_profiles->currentItem();

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

        ui->tw_profiles->removeRow(item->row());

        ui->tw_profiles->setCurrentCell(0, 0);
        QTableWidgetItem *item = ui->tw_profiles->currentItem();
        settings->setCurrentProfile(item->text());
    }
}

void MainWindow::on_btn_profiles_clone_clicked()
{
    QTableWidgetItem *item = ui->tw_profiles->currentItem();

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

        TableHelper::addItem(ui->tw_profiles, ":/doom.png", text, ui->tw_profiles->item(item->row(), 1)->text());
        TableHelper::selectItem(ui->tw_profiles, text);
        QTableWidgetItem *item = ui->tw_profiles->currentItem();
        settings->setCurrentProfile(item->text());
    }
}

void MainWindow::on_btn_profiles_load_clicked()
{
    TableHelper::setStandartFont(ui->tw_profiles);

    writeSettings();

    QFont font;
    font.setBold(true);
    int row = ui->tw_profiles->currentRow();

    settings->setCurrentProfile(ui->tw_profiles->item(row, 0)->text());
    ui->tw_profiles->item(row, 0)->setFont(font);
    ui->tw_profiles->item(row, 1)->setFont(font);

    checkedItems.clear();
    ui->lw_iwad->clear();
    ui->lw_pwad->clear();
    ui->le_iwaddir->clear();
    ui->le_pwaddir->clear();

    this->setWindowTitle("ChickenLauncher - " + ui->tw_profiles->item(ui->tw_profiles->currentRow(), 0)->text());

    readSettings();
}

void MainWindow::populateIwadList()
{
    ui->lw_iwad->clear();
    ui->lw_iwad->setIconSize(QSize(50, 25));

    const QStringList &scan = DirectoryList::scan(ui->le_iwaddir->text(), QStringList() << "*.wad" << "*.pk3" << "*.zip");

    for (const QString &item : scan)
    {
        QFileInfo fi(item);

        if (!fi.baseName().compare("doom2", Qt::CaseInsensitive))
            ListHelper::addItem(ui->lw_iwad, item, ":/doom2.png");
        else if (!fi.baseName().compare("doom", Qt::CaseInsensitive))
            ListHelper::addItem(ui->lw_iwad, item, ":/doom.png");
    }
}

void MainWindow::populatePwadList()
{
    ui->lw_pwad->clear();

    const QStringList &scan = DirectoryList::scan(ui->le_pwaddir->text(), QStringList() << "*.wad" << "*.pk3" << "*.zip");

    for (const QString &item : scan)
        ListHelper::addItem(ui->lw_pwad, item, Qt::Unchecked);
}

void MainWindow::on_lw_iwad_itemActivated(QListWidgetItem *item)
{
    settings->setLastIwad(item->text());
}

void MainWindow::on_lw_pwad_itemChanged()
{
    checkedItems = ListHelper::getCheckedItems(ui->lw_pwad);
}

void MainWindow::on_btn_pwad_up_clicked()
{
    ListHelper::moveUp(ui->lw_pwad);
}

void MainWindow::on_btn_pwad_down_clicked()
{
    ListHelper::moveDown(ui->lw_pwad);
}

void MainWindow::on_btn_refresh_clicked()
{
    populatePwadList();

    foreach (const QString &item, checkedItems) // DO NOT use std foreach here, it will segfault
       ListHelper::selectItem(ui->lw_pwad, item, Qt::Checked);
}

void MainWindow::populateConfigList()
{
    const QStringList &scan = DirectoryList::scan(GamesPaths::getGzdoomDir(), QStringList() << "*.ini");

    ListHelper::addItem(ui->lw_port_config, "[default]");

    for (const QString &item : scan)
    {
        QFileInfo file(item);

        if (file.baseName() == "zdoom" || file.baseName() == "gzdoom")
            continue;

        ListHelper::addItem(ui->lw_port_config, file.baseName());
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
        ListHelper::addItem(ui->lw_port_config, text);
    }
}

void MainWindow::on_btn_config_rename_clicked()
{
    QListWidgetItem *item = ui->lw_port_config->currentItem();

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
    QListWidgetItem *item = ui->lw_port_config->currentItem();

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

void MainWindow::writeSettings()
{
    QListWidgetItem *iwaditem = ui->lw_iwad->currentItem();
    if (iwaditem != nullptr)
    {
        QFileInfo lastiwad(iwaditem->text());
        settings->setLastIwad(lastiwad.fileName());
    }

    QString lastpwad;
    for (const QString &item : checkedItems)
    {
        QFileInfo lastpwaditem(item);
        lastpwad.append(lastpwaditem.fileName() + "#");
    }
    settings->setLastPwad(lastpwad);

    settings->setIwadDir(ui->le_iwaddir->text());
    settings->setPwadDir(ui->le_pwaddir->text());
    settings->setExePath(ui->le_executablepath->text());

    QListWidgetItem *configitem = ui->lw_port_config->currentItem();
    if (configitem != nullptr && configitem->text() != "[default]")
        settings->setConfigFile(configitem->text());

    delete iwaditem;
    delete configitem;
}

void MainWindow::readSettings()
{
    ui->le_iwaddir->setText(settings->getIwadDir());
    ui->le_pwaddir->setText(settings->getPwadDir());
    ui->le_executablepath->setText(settings->getExePath());

    ListHelper::selectItem(ui->lw_iwad, settings->getLastIwad());

    const QString &config = settings->getConfigFile();
    if (config.isEmpty())
        ListHelper::selectItem(ui->lw_port_config, "[default]");
    else
        ListHelper::selectItem(ui->lw_port_config, config);

    const QStringList &pwads = settings->getLastPwad().split("#");
    for (const QString &item : pwads)
        ListHelper::selectItem(ui->lw_pwad, ui->le_pwaddir->text() + item, Qt::Checked);
}

void MainWindow::on_btn_ripandtear_clicked()
{
    Gzdoom *gzdoom = new Gzdoom;
    gzdoom->setExe(ui->le_executablepath->text());
    gzdoom->setIwad(ui->lw_iwad->currentItem()->text());
    gzdoom->setPwads(checkedItems);
    gzdoom->setMap(ui->le_gz_map->text());

    if (ui->cb_gz_skill->isChecked())
        gzdoom->setSkill(ui->comb_gz_skill->currentIndex());

    if (ui->gb_gz_join->isChecked())
        gzdoom->setAddress(ui->le_gz_ip->text() + ":" + ui->le_gz_ipport->text());

    ui->btn_ripandtear->setEnabled(false);
    connect(gzdoom, &Gzdoom::isfinish, [&](){
        ui->btn_ripandtear->setEnabled(true);
        //delete gzdoom;
    });

    gzdoom->start();
}

void MainWindow::on_lw_pwad_itemChanged(QListWidgetItem *item)
{
    QFont font;

    if (item->checkState() == Qt::Checked)
        font.setBold(true);
    else
        font.setBold(false);

    item->setFont(font);
}

void MainWindow::on_lw_iwad_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
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

        ui->btn_ripandtear->setIcon(current->icon());
        QFileInfo fi(current->text());
        ui->btn_ripandtear->setText("Play " + fi.completeBaseName());
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

void MainWindow::on_le_gz_map_textChanged(const QString &arg1)
{
    const QString &last_iwad = ui->lw_iwad->currentItem()->text();
    if (last_iwad.contains("DOOM.WAD", Qt::CaseInsensitive) \
            || last_iwad.contains("heretic", Qt::CaseInsensitive) \
            || last_iwad.contains("wolf", Qt::CaseInsensitive))
    {
        if (!arg1.isEmpty())
        {
            if (arg1.at(0).isDigit())
                ui->le_gz_map->setText("E" + QString(arg1.at(0)).toUtf8());

            if (arg1.length() >= 3)
                if (arg1.at(2).isDigit())
                    ui->le_gz_map->setText("E" + QString(arg1.at(1)).toUtf8() + "M" + QString(arg1.at(2)).toUtf8());
        }
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

    ui->le_iwaddir->setText(dir);
}

void MainWindow::on_btn_pwad_chooser_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,\
                                                    tr("Choose pwad directory"),\
                                                    QDir::homePath(),\
                                                    QFileDialog::ShowDirsOnly);
    if (dir.isEmpty())
        return;

    ui->le_pwaddir->setText(dir);
}

void MainWindow::on_btn_exe_chooser_clicked()
{
    QString dir = QFileDialog::getOpenFileName(this,\
                                                    tr("Choose exe directory"),\
                                                    QDir::homePath(),\
                                                    tr("Executable Files (*.* *.exe)"));
    if (dir.isEmpty())
        return;

    ui->le_executablepath->setText(dir);
}

void MainWindow::on_actionAbout_Chicken_Launcher_triggered()
{
    AboutDialog about;
    about.exec();
    about.done(0);
}
