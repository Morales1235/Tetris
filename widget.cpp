#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //setting the background image
    QPixmap background("./graphics/background.jpg");
    ui->backgroundLabel->setPixmap(background);

    scoresFile = new QFile("highscores");

    shapes = Shapes::getInstance();
    movingTimer = std::unique_ptr<QTimer> (new QTimer(this));
    connect(movingTimer.get(), SIGNAL(timeout()), this, SLOT(movingDownLogic()));
    connect(ui->highscoresButton, SIGNAL(clicked(bool)), movingTimer.get(), SLOT(stop()));
}

Widget::~Widget()
{
    delete ui;
}



void Widget::keyPressEvent(QKeyEvent * event)
{
        switch (event->key()) {
        case Qt::Key_A:
            if (isPossibleMove(0, -1)) currentTetromino->move(-blockSize.width(), 0);
            break;
        case Qt::Key_D:
            if (isPossibleMove(0, 1)) currentTetromino->move(blockSize.width(), 0);
            break;
        case Qt::Key_E:
            if (currentTetromino->getShapeNumber() != YELLOW) { //!Fourth tetromino is O, it should't be rotating in 5x5 matrix
                rotateRight();
            }
            break;
        case Qt::Key_Q:
            if (currentTetromino->getShapeNumber() != YELLOW) {
                rotateLeft();
            }
            break;
        case Qt::Key_S:
            movingDownLogic();
            break;
        case Qt::Key_Z:
            hardDrop();
            break;
        default:
            break;
    }
}

void Widget::startGame()
{
    setInitValues();
    myFloor->resetMatrix();
    setNextTetromino();
    setCurrentTetromino();
    movingTimer->start(moveInterval);
}

void Widget::setInitValues()
{
    setPlayerName();
    moveInterval = 1000;
    gameFinished = false;
    ui->scorePointsLabel->setText(QString::number(score = 0));
}

void Widget::setPlayerName()
{
    playerName = std::unique_ptr<QString> (new QString(QInputDialog::getText(this, "Introduce yourself", "Your Name: ")));
    if (playerName->length() <= 0)
        playerName = std::unique_ptr<QString> (new QString("Unnamed"));
}

void Widget::setNextTetromino()
{
    nextTetromino = std::unique_ptr<Tetromino> (new Tetromino(this, nextPoint, shapes));
}

void Widget::setCurrentTetromino()
{
    currentTetromino = std::move(nextTetromino);
    currentTetromino->setPosition(startPoint);
    setNextTetromino();
}

bool Widget::isPossibleMove(int di, int dj)
{
    int _i, _j;
    for (unsigned int i = 0; i < currentTetromino->getMatrix().size(); i++)
    {
        for (unsigned int j = 0; j < currentTetromino->getMatrix()[i].size(); j++)
        {
            _i = currentTetromino->getPosAtMatrix().y() + i + di + 1;  //!Plus one is because floormatrix begins at -1, because tetromino matrix is over the playground when its begin to move
            _j = currentTetromino->getPosAtMatrix().x() + j + dj;
            if ((currentTetromino->getMatrix()[i][j]) && (_i >= myFloor->getMatrix().size() || _j >= myFloor->getMatrix()[_i].size() || _j < 0))   //!Checks if tetromino wants move outside the playground
                return false;
            else if (currentTetromino->getMatrix()[i][j] && myFloor->getMatrix()[_i][_j])     //!Checks if tetromino will be on the other tetromino
                return false;
        }
    }
    return true;
}

void Widget::rotateRight()
{
    currentTetromino->rotateRight();
    if (!isPossibleMove(0, 0))
        currentTetromino->rotateLeft();
}

void Widget::rotateLeft()
{
    currentTetromino->rotateLeft();
    if (!isPossibleMove(0, 0))
        currentTetromino->rotateRight();
}

void Widget::movingDownLogic()
{
    if (!isPossibleMove(0, 0))
        gameOver();
    else if (isPossibleMove(1, 0))
        moveTetrominoDown();
    else
    {
        addTetrominoToFloor();
        removeFullRows();
        setCurrentTetromino();
    }
}

void Widget::moveTetrominoDown()
{
    currentTetromino->move(0, blockSize.height());
}

void Widget::hardDrop()
{
    while (isPossibleMove(1, 0))
        movingDownLogic();
    movingDownLogic();      //!It makes add tetromino to floor when is fallen
}

void Widget::addTetrominoToFloor()
{
    int _i = currentTetromino->getPosAtMatrix().y() + 1; //!Plus one is because floormatrix begins at -1, because tetromino matrix is over the playground when its begin to move
    int _j = currentTetromino->getPosAtMatrix().x();

    for (unsigned int i = 0; i < currentTetromino->getMatrix().size(); i++)
        for (unsigned int j = 0; j < currentTetromino->getMatrix()[i].size(); j++)
            if (currentTetromino->getMatrix()[i][j])
                myFloor->addBlockToMatrix(i + _i, j + _j, currentTetromino->getPixmap()); //!Position of block and 'i' means in what point on floor matrix is tetromino
}

void Widget::removeFullRows()
{
    int begin = currentTetromino->getPosAtMatrix().y() + 1;
    for (int i = begin; (i < (begin + 4)) && (i < myFloor->getMatrix().size()); i++)
    {
        if (myFloor->isRowFull(i))
        {
            myFloor->resetMatrixRow(i);
            myFloor->moveDownBlocks(i);
            addPointToScore();
        }
    }
}

void Widget::addPointToScore()
{
    score += 1;
    ui->scorePointsLabel->setText(QString::number(score));
}

void Widget::gameOver()
{
    saveScore();
    gameFinished = true;
    movingTimer->stop();
    QMessageBox::information(this, "Game over", "You finished the game with: " + QString::number(score) + " points", QDialogButtonBox::Close);
}

void Widget::saveScore()
{
    if (scoresFile->open(QIODevice::Append | QFile::WriteOnly))
    {
        QTextStream outStream(scoresFile);
        outStream << "\n" << score;
        outStream << QString(";");
        outStream << *playerName;
    }
    else std::cout << "Could not write the score." << std::endl;
    scoresFile->close();
}

void Widget::on_startButton_clicked()
{
    startGame();
}

void Widget::on_highscoresButton_clicked()
{

    if (scoresFile->open(QFile::ReadOnly))
    {
        highScoresDialog = new HighScoresDialog(readHighscores(), this);
        startTimerAfterCloseHighScores();
        highScoresDialog->show();
    } else QMessageBox::information(this, "Highscores", "No scores");
    scoresFile->close();
}


pHighscores Widget::readHighscores()
{
    QStringList line;
    QString _score;
    QTextStream inStream(scoresFile);
    pHighscores highscores (new QMultiMap<int, QString>);

    while (!inStream.atEnd())
    {
        _score = inStream.readLine();
        if (!_score.isEmpty())
        {
            line = _score.split(';');
            highscores->insert(line.first().toInt(), line.last());
        }
    }
    return highscores;
}

void Widget::startTimerAfterCloseHighScores()
{
    if (!gameFinished)
        connect(highScoresDialog, SIGNAL(rejected()), movingTimer.get(), SLOT(start()));
}

void Widget::on_exitButton_clicked()
{
    QCoreApplication::exit();
}
