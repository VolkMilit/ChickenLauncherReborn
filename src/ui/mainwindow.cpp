#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    populateProfilesTable();
    populateConfigList();
    setupWindow();
}

MainWindow::~MainWindow()
{
    writeSettings();
    checkedItems.clear();
    delete ui;
}

void MainWindow::on_btn_profiles_new_clicked()
{
    Settings settings;
    newProfileDialog dialog;
    bool ok = dialog.exec();

    QFile file(settings.getProfilesDir() + dialog.getName() + ".ini");
    if (file.exists())
    {
        QMessageBox::warning(this, "Error", "Profile already exist.", QMessageBox::Ok);
        return;
    }

    if (ok)
        TableHelper::addItem(ui->tw_profiles, dialog.getName(), dialog.getPort());

    dialog.done(0);
}

void MainWindow::populateProfilesTable()
{
    Settings settings;
    QVector<QString> scan = DirectoryList::scan(settings.getProfilesDir(), QStringList() << "*.ini");

    for (auto i = 0; i < scan.size(); i++)
    {
        QString port = settings.readSettings(scan.at(i), "Port", "GamePort");
        QString profileRow = scan.at(i);

        QFileInfo profile(profileRow.remove(".ini"));

        TableHelper::addItem(ui->tw_profiles, profile.baseName(), port);
    }
}

void MainWindow::setupWindow()
{
    Settings settings;
    QFileInfo title(settings.getDefaultProfileName());
    this->setWindowTitle("ChickenLauncher - " + title.baseName().remove(".ini"));

    TableHelper::selectItem(ui->tw_profiles, title.baseName().remove(".ini"));

    ui->le_search->hide();

    readSettings();
}

void MainWindow::on_btn_profiles_rename_clicked()
{
    Settings settings;
    QTableWidgetItem *item = ui->tw_profiles->currentItem();
    QString profilesDir = settings.getProfilesDir();

    if (item == nullptr)
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
        if (settings.getDefaultProfileName() == item->text())
            settings.setCurrentProfile(text);

        QFile::rename(profilesDir + item->text() + ".ini", profilesDir + text + ".ini");
        item->setText(text);
    }
}

void MainWindow::on_btn_profiles_delete_clicked()
{
    Settings settings;

    QTableWidgetItem *item = ui->tw_profiles->currentItem();

    if (item == nullptr)
        return;

    QMessageBox message;
    message.setText("Warning!");
    message.setInformativeText("Are you sure you want to delete " + item->text() + " profile?");
    message.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    message.setDefaultButton(QMessageBox::Cancel);
    int ok = message.exec();

    if (ok == QMessageBox::Ok)
    {
        QFile file(settings.getProfilesDir() + item->text() + ".ini");
        file.remove();

        ui->tw_profiles->removeRow(item->row());

        ui->tw_profiles->setCurrentCell(0, 0);
        QTableWidgetItem *item = ui->tw_profiles->currentItem();
        settings.setCurrentProfile(item->text());
    }
}

void MainWindow::on_btn_profiles_clone_clicked()
{
    Settings settings;
    QTableWidgetItem *item = ui->tw_profiles->currentItem();

    if (item == nullptr)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Copy profile '") + item->text() + "'",
                                             tr("New profile name:"), QLineEdit::Normal,
                                             item->text(), &ok);

    QFile file(settings.getProfilesDir() + text + ".ini");
    if (file.exists())
    {
        QMessageBox::warning(this, "Error", "Profile already exist.", QMessageBox::Ok);
        return;
    }

    if (ok && !text.isEmpty())
    {
        QString profilesDir = settings.getProfilesDir();

        QFile::copy(profilesDir + item->text() + ".ini", profilesDir + text + ".ini");

        TableHelper::addItem(ui->tw_profiles, text, ui->tw_profiles->item(item->row(), 1)->text());
        TableHelper::selectItem(ui->tw_profiles, text);
        QTableWidgetItem *item = ui->tw_profiles->currentItem();
        settings.setCurrentProfile(item->text());
    }
}

void MainWindow::on_btn_profiles_load_clicked()
{
    writeSettings();

    Settings settings;
    settings.setCurrentProfile(ui->tw_profiles->item(ui->tw_profiles->currentRow(), 0)->text());

    checkedItems.clear();
    ui->lw_iwad->clear();
    ui->lw_pwad->clear();
    ui->le_iwaddir->clear();
    ui->le_pwaddir->clear();

    setWindowTitle("ChickenLauncher - " + ui->tw_profiles->item(ui->tw_profiles->currentRow(), 0)->text());

    readSettings();
}

void MainWindow::populateIwadList()
{
    ui->lw_iwad->clear();

    QVector<QString> scan = DirectoryList::scan(ui->le_iwaddir->text(), QStringList() << "*.wad" << "*.pk3" << "*.zip");

    for (QString item : scan)
        ListHelper::addItem(ui->lw_iwad, item);
}

void MainWindow::populatePwadList()
{
    ui->lw_pwad->clear();

    QVector<QString> scan = DirectoryList::scan(ui->le_pwaddir->text(), QStringList() << "*.wad" << "*.pk3" << "*.zip");

    for (QString item : scan)
        ListHelper::addItem(ui->lw_pwad, item, Qt::Unchecked);
}

void MainWindow::on_lw_iwad_itemActivated(QListWidgetItem *item)
{
    Settings settings;
    settings.setLastIwad(item->text());
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
}

void MainWindow::populateConfigList()
{
    QVector<QString> scan = DirectoryList::scan(GamesPaths::getGzdoomDir(), QStringList() << "*.ini");

    ListHelper::addItem(ui->lw_port_config, "[default]");

    for (QString item : scan)
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

    if (item == nullptr)
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

    if (item == nullptr)
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
    Settings settings;

    /*int row = ui->tw_profiles->currentRow();
    QString currentProfile = ui->tw_profiles->item(row, 0)->text();
    if (currentProfile != nullptr)
        settings.setCurrentProfile(currentProfile);*/

    QListWidgetItem *iwaditem = ui->lw_iwad->currentItem();
    if (iwaditem != nullptr)
    {
        QFileInfo lastiwad(iwaditem->text());
        settings.setLastIwad(lastiwad.fileName());
    }

    QString lastpwad;
    for (QString item : checkedItems)
    {
        QFileInfo lastpwaditem(item);
        lastpwad.append(lastpwaditem.fileName() + "#");
    }
    settings.setLastPwad(lastpwad);

    settings.setIwadDir(ui->le_iwaddir->text());
    settings.setPwadDir(ui->le_pwaddir->text());
    settings.setExePath(ui->le_executablepath->text());

    QListWidgetItem *configitem = ui->lw_port_config->currentItem();
    if (configitem != nullptr)
        settings.setConfigFile(configitem->text());

    delete iwaditem;
    delete configitem;
}

void MainWindow::readSettings()
{
    Settings settings;

    ui->le_iwaddir->setText(settings.getIwadDir());
    ui->le_pwaddir->setText(settings.getPwadDir());
    ui->le_executablepath->setText(settings.getExePath());

    ListHelper::selectItem(ui->lw_iwad, settings.getLastIwad());

    QStringList pwads = settings.getLastPwad().split("#");
    for (QString item : pwads)
        ListHelper::selectItem(ui->lw_pwad, ui->le_pwaddir->text() + item, Qt::Checked);
}

void MainWindow::on_btn_ripandtear_clicked()
{
    Gzdoom gzdoom;
    gzdoom.setExe(ui->le_executablepath->text());
    gzdoom.setIwad(ui->lw_iwad->currentItem()->text());
    gzdoom.setPwads(checkedItems);
    gzdoom.start();
}