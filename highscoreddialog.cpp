#include "highscoreddialog.h"
#include "ui_highscoreddialog.h"

HighScoredDialog::HighScoredDialog(std::shared_ptr<QMultiMap<unsigned int, QString> > highscores, QWidget *parent) :
    QDialog(parent),
    parent(parent),
    scores(highscores),
    ui(new Ui::HighScoredDialog)
{
    ui->setupUi(this);

    //myLayout = new QGridLayout(parent);
    //this->setLayout(myLayout);

    //initLabels();

}

HighScoredDialog::~HighScoredDialog()
{
    delete ui;
}


void HighScoredDialog::initLabels()
{
    //myLayout->addWidget((new QLabel(scores->end().value())), 0, 0, Qt::AlignRight);
    std::unique_ptr<QLabel> score1 (new QLabel("Hi", parent));
    //QLabel * score1 = (new QLabel("Hi"));
    score1->setObjectName("score1");
    myLayout->addWidget(score1.get(), 0, 0, Qt::AlignRight);
    score1->show();
}

