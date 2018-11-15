#include "newprofiledialog.h"
#include "ui_newprofiledialog.h"

#include <QDebug>
#include <QMessageBox>

newProfileDialog::newProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProfileDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add new profile");
}

newProfileDialog::~newProfileDialog()
{
    delete ui;
}

QString newProfileDialog::getName()
{
    return ui->le_name->text();
}

QString newProfileDialog::getPort()
{
    return ui->comb_game->currentText();
}

void newProfileDialog::accept()
{
    if (ui->le_name->text().isEmpty())
    {
        wrongStyle(ui->le_name);
        return;
    }

    Settings settings;

    QFile file(settings.getProfilesDir() + ui->le_name->text() + ".ini");
    if (file.exists())
    {
        QMessageBox::warning(this, "Error", "Profile already exist.", QMessageBox::Ok);
        return;
    }

    settings.setCurrentProfile(ui->le_name->text());
    settings.setGamePort(ui->comb_game->currentText());

    QDialog::accept();

    this->close();
}

void newProfileDialog::wrongStyle(QWidget *widget)
{
    widget->style()->unpolish(widget);
    widget->setStyleSheet("QLineEdit{background-color: yellow;}");
}

void newProfileDialog::standartStyle(QWidget *widget)
{
    widget->style()->unpolish(widget);
    widget->setStyleSheet("");
}

void newProfileDialog::on_le_name_textChanged()
{
    standartStyle(ui->le_name);
}
