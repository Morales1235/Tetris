#ifndef HIGHSCOREDDIALOG_H
#define HIGHSCOREDDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLayout>
#include <QLabel>
#include <QMultiMap>
#include <memory>

typedef std::shared_ptr<QMultiMap<int, QString> > pHighscores;

namespace Ui {
class HighScoredDialog;
}

class HighScoredDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoredDialog(pHighscores highscores, QWidget *parent = 0);
    ~HighScoredDialog();


private:
    Ui::HighScoredDialog *ui;

    void initLabels();      /// \brief declaration of labels

    QGridLayout * myLayout;

    QVBoxLayout * mainVBoxLayout;
    QVBoxLayout * lVBoxLayout;
    QVBoxLayout * rVBoxLayout;
    QHBoxLayout * hBoxLayout;

    pHighscores highscores;
};

#endif // HIGHSCOREDDIALOG_H
