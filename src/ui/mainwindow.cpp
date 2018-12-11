#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//,
    //ui(new Ui::MainWindow)
{
    ui.setupUi(this);

    settings = new Settings;

    populateProfilesTable();
    populateConfigList();
    setupWindow();
}

MainWindow::~MainWindow()
{  
    writeSettings();

    delete settings;
    //delete ui;
}

void MainWindow::setupWindow()
{
    QFileInfo title(settings->getDefaultProfileName());
    this->setWindowTitle("ChickenLauncher - " + title.baseName().remove(".ini"));

    ListHelper::selectItem(ui.tw_profiles, title.baseName().remove(".ini"));

    ui.le_search->hide();

    ui.tabWidget->setTabEnabled(5, false);

    readSettings();
}

void MainWindow::writeSettings()
{
    QListWidgetItem *iwaditem = ui.lw_iwad->currentItem();
    if (iwaditem != nullptr)
    {
        QFileInfo lastiwad(iwaditem->text());
        settings->setLastIwad(lastiwad.fileName());
    }

    QString lastpwad;
    const QStringList checkeditems = ListHelper::getCheckedItems(ui.lw_pwad);
    for (const QString &item : checkeditems)
        lastpwad.append(QFileInfo(item).fileName() + "#");
    settings->setLastPwad(lastpwad);

    settings->setIwadDir(ui.le_iwaddir->text());
    settings->setPwadDir(ui.le_pwaddir->text());
    settings->setExePath(ui.le_executablepath->text());

    QListWidgetItem *configitem = ui.lw_port_config->currentItem();
    if (configitem != nullptr && configitem->text() != "[default]")
        settings->setConfigFile(configitem->text());

    delete iwaditem;
    delete configitem;
}

void MainWindow::readSettings()
{
    ui.le_iwaddir->setText(settings->getIwadDir());
    ui.le_pwaddir->setText(settings->getPwadDir());
    ui.le_executablepath->setText(settings->getExePath());

    ListHelper::selectItem(ui.lw_iwad, settings->getLastIwad());

    const QString &config = settings->getConfigFile();
    if (config.isEmpty())
        ListHelper::selectItem(ui.lw_port_config, "[default]");
    else
        ListHelper::selectItem(ui.lw_port_config, config);
}

void MainWindow::on_btn_ripandtear_clicked()
{
    Gzdoom *gzdoom = new Gzdoom(this);
    gzdoom->setExe(ui.le_executablepath->text());
    gzdoom->setIwad(ui.lw_iwad->currentItem()->text());
    gzdoom->setPwads(ListHelper::getCheckedItems(ui.lw_pwad));
    gzdoom->setMap(ui.le_gz_map->text());

    if (ui.cb_gz_skill->isChecked())
        gzdoom->setSkill(ui.comb_gz_skill->currentIndex());

    if (ui.gb_gz_join->isChecked())
        gzdoom->setAddress(ui.le_gz_ip->text() + ":" + ui.le_gz_ipport->text());

    ui.btn_ripandtear->setEnabled(false);
    connect(gzdoom, &Gzdoom::isfinish, [&](){
        ui.btn_ripandtear->setEnabled(true);
        //delete gzdoom;
    });

    gzdoom->start();
}

void MainWindow::on_actionAbout_Chicken_Launcher_triggered()
{
    AboutDialog about;
    about.exec();
    about.done(0);
}
