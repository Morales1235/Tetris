#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <QDialog>
#include <QInputDialog>

namespace Ui {
class NameDialog;
}

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NameDialog(QWidget *parent = 0);
    ~NameDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NameDialog *ui;
    QString getPlayerName();
};

#endif // NAMEDIALOG_H
