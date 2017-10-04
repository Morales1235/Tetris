#ifndef HIGHSCOREDDIALOG_H
#define HIGHSCOREDDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMultiMap>
#include <memory>

namespace Ui {
class HighScoredDialog;
}

class HighScoredDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoredDialog(std::shared_ptr<QMultiMap<unsigned int, QString> > highscores, QWidget *parent = 0);
    ~HighScoredDialog();


private:
    Ui::HighScoredDialog *ui;

    void initLabels();      /// \brief declaration of labels

    QWidget * parent;
    QGridLayout * myLayout;
    std::shared_ptr<QMultiMap<unsigned int, QString> > scores;
};

#endif // HIGHSCOREDDIALOG_H
