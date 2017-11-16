#include "highscoresdialog.h"
#include "ui_highscoreddialog.h"

HighScoresDialog::HighScoresDialog(pHighscores highscores, QWidget *parent) :
    QDialog(parent),
    highscores(highscores),
    ui(new Ui::HighScoredDialog)
{
    ui->setupUi(this);


    buttonLayout = std::unique_ptr <QGridLayout> (new QGridLayout);
    mainVBoxLayout = std::unique_ptr <QVBoxLayout> (new QVBoxLayout);
    lVBoxLayout = std::unique_ptr <QVBoxLayout> (new QVBoxLayout);
    rVBoxLayout = std::unique_ptr <QVBoxLayout> (new QVBoxLayout);
    hBoxLayout = std::unique_ptr <QHBoxLayout> (new QHBoxLayout);

    this->setLayout(mainVBoxLayout.get());

    mainVBoxLayout->addLayout(hBoxLayout.get());
    mainVBoxLayout->addLayout(buttonLayout.get());

    hBoxLayout->addLayout(lVBoxLayout.get());
    hBoxLayout->addLayout(rVBoxLayout.get());

    buttonLayout->addWidget(ui->buttonBox);


    mainVBoxLayout->addWidget(ui->buttonBox);
    initLabels();
}

HighScoresDialog::~HighScoresDialog()
{
    delete ui;
}


void HighScoresDialog::initLabels()
{
    lVBoxLayout->addWidget(new QLabel("Points"), 0, Qt::AlignRight);
    rVBoxLayout->addWidget(new QLabel("Name"));
    if (highscores->size() < 6)
        fillEmptyScores();
    addScoresToWindow();
}

void HighScoresDialog::fillEmptyScores()
{
    for (int i = highscores->size(); i < 6; i++)
        highscores->insert(0, "Nobody");
}

void HighScoresDialog::addScoresToWindow()
{
    for (QMultiMap<int, QString> :: iterator it = highscores->end() -1; it != highscores->end() - 6; it--)
    {
        lVBoxLayout->addWidget(new QLabel(QString::number(it.key())), 0, Qt::AlignRight);
        rVBoxLayout->addWidget(new QLabel(it.value()));
    }
}

