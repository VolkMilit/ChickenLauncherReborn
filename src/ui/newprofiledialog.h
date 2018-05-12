#ifndef NEWPROFILEDIALOG_H
#define NEWPROFILEDIALOG_H

#include <QDialog>
#include <QDir>

#include "core/settings.h"

namespace Ui {class newProfileDialog;}

class newProfileDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit newProfileDialog(QWidget *parent = 0);
        ~newProfileDialog();

        QString getName();
        QString getPort();

    protected slots:
        void accept();

    private slots:
        void on_le_name_textChanged();

    private:
        Ui::newProfileDialog *ui;

        void wrongStyle(QWidget *widget);
        void standartStyle(QWidget *widget);
};

#endif // NEWPROFILEDIALOG_H
