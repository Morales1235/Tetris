#include "highscoreddialog.h"
#include "ui_highscoreddialog.h"

HighScoredDialog::HighScoredDialog(pHighscores highscores, QWidget *parent) :
    QDialog(parent),
    highscores(highscores),
    ui(new Ui::HighScoredDialog)
{
    ui->setupUi(this);


    buttonLayout = new QGridLayout;
    mainVBoxLayout = new QVBoxLayout;
    lVBoxLayout = new QVBoxLayout;
    rVBoxLayout = new QVBoxLayout;
    hBoxLayout = new QHBoxLayout;

    this->setLayout(mainVBoxLayout);

    mainVBoxLayout->addLayout(hBoxLayout);
    mainVBoxLayout->addLayout(buttonLayout);

    hBoxLayout->addLayout(lVBoxLayout);
    hBoxLayout->addLayout(rVBoxLayout);

    buttonLayout->addWidget(ui->buttonBox);


    mainVBoxLayout->addWidget(ui->buttonBox);
    initLabels();
}

HighScoredDialog::~HighScoredDialog()
{
    delete ui;
}


void HighScoredDialog::initLabels()
{
    for (QMultiMap<int, QString> :: iterator it = highscores->end() -1; it != highscores->end() - 6; it--)
    {
        lVBoxLayout->addWidget(new QLabel(QString::number(it.key())), 0, Qt::AlignRight);
        rVBoxLayout->addWidget(new QLabel(it.value()));
    }
}

