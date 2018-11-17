#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTableWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

#include "ui/newprofiledialog.h"
#include "ui/aboutdialog.h"
#include "core/directorylist.h"
#include "core/settings.h"
#include "core/tablehelper.h"
#include "core/listhelper.h"
#include "games/common.h"
#include "games/gzdoom.h"

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void on_btn_profiles_new_clicked();
        void on_btn_profiles_rename_clicked();
        void on_btn_profiles_delete_clicked();
        void on_btn_profiles_clone_clicked();
        void on_lw_iwad_itemActivated(QListWidgetItem *item);
        void on_lw_pwad_itemChanged();
        void on_le_iwaddir_textChanged();
        void on_le_pwaddir_textChanged();
        void on_btn_pwad_up_clicked();
        void on_btn_pwad_down_clicked();
        void on_btn_refresh_clicked();
        void on_btn_config_new_clicked();
        void on_btn_config_rename_clicked();
        void on_btn_config_delete_clicked();
        void on_btn_profiles_load_clicked();
        void on_btn_ripandtear_clicked();
        void on_lw_pwad_itemChanged(QListWidgetItem *item);
        void on_lw_iwad_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
        void on_lw_port_config_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
        void on_le_gz_map_textChanged(const QString &arg1);
        void on_btn_iwad_chooser_clicked();
        void on_btn_pwad_chooser_clicked();
        void on_btn_exe_chooser_clicked();
        void on_actionAbout_Chicken_Launcher_triggered();

private:
        Ui::MainWindow *ui;

        void setupWindow();
        void populateProfilesTable();
        void populateIwadList();
        void populatePwadList();
        void populateConfigList();

        void writeSettings();
        void readSettings();

        Settings *settings;

        QStringList checkedItems;
};

#endif // MAINWINDOW_H
