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

class HighScoresDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoresDialog(pHighscores highscores, QWidget *parent = 0);
    ~HighScoresDialog();


private:
    Ui::HighScoredDialog *ui;

    void initLabels();      /// \brief declaration of labels
    void fillEmptyScores(); /// \brief fills highscores with empty scores if number of scores is less than displaying scores
    void addScoresToWindow(); /// \brief displays QLabels with scores

    QGridLayout * buttonLayout;         /// \param myLayout stores the button
    QVBoxLayout * mainVBoxLayout;   /// \param mainVBoxLayout is layout separating button from scores
    QHBoxLayout * hBoxLayout;       /// \param hBoxLayout separates points from names
    QVBoxLayout * lVBoxLayout;      /// \param lVBoxLayout stores points of scores
    QVBoxLayout * rVBoxLayout;      /// \param RVBoxLayout stores playre's name's

    pHighscores highscores;         /// \param highscores stores the high scores: points and names
};

#endif // HIGHSCOREDDIALOG_H
