#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QWidget>

namespace Ui {
class outputWindow;
}

class outputWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit outputWindow(QWidget *parent = 0);
        ~outputWindow();

        void appendOut(QString text);

    private:
        Ui::outputWindow *ui;
};

#endif // OUTPUTWINDOW_H
