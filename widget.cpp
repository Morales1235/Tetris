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

    //for (int i = 0; i < floorMatrix.size(); i++)
    //    floorMatrix[i].fill(0);


    movingTimer = std::move(std::unique_ptr<QTimer> (new QTimer(this)));
    connect(movingTimer.get(), SIGNAL(timeout()), this, SLOT(movingDown()));

}

Widget::~Widget()
{
    delete ui;
}



void Widget::keyPressEvent(QKeyEvent * event)
{
        switch (event->key()) {
        case 0x41:      //key A
            if (isPossibleMove(0, -1)) currentTetromino->move<int>(-blockSize.width(), 0);
            break;
        case 0x44:      //key D
            if (isPossibleMove(0, 1)) currentTetromino->move<int>(blockSize.width(), 0);
            break;
        case 0x45:      //key E
            if (currentTetromino->getShapeNumber() != 4) { //!Fourth tetromino is O, it should't be rotating in 5x5 matrix
                currentTetromino->transponse();
                if (!isPossibleMove(0, 0))
                {
                    currentTetromino->transponse();
                    break;
                }
                if (currentTetromino->getShapeNumber() != 1)
                {
                    currentTetromino->verticalReflection(); //!Don't know why I tetromino is breaking every second rotate. Transponse is enough for that block
                    if (!isPossibleMove(0, 0)) currentTetromino->verticalReflection();
                }
            }
            break;
        case 0x51:      //key Q
            if (currentTetromino->getShapeNumber() != 4) {
                currentTetromino->transponse();
                if (!isPossibleMove(0, 0))
                {
                    currentTetromino->transponse();
                    break;
                }
                if (currentTetromino->getShapeNumber() != 1)
                {
                    currentTetromino->horizontalReflection();
                    if (!isPossibleMove(0, 0)) currentTetromino->horizontalReflection();
                }
            }
            break;
        default:
            break;
    }
}

void Widget::setCurrentTetromino()
{
    /*
    currentBlock = std::move(tetrominos.last());
    currentBlock->setPosition(startPoint);
    nextBlock = std::move(std::shared_ptr<Block> (new Block(this, nextBlockPoint)));
    tetrominos.push_back(nextBlock);
    */
    ///Without qvector of tetrominos
    currentTetromino = std::move(nextTetromino);
    currentTetromino->setPosition(startPoint);
    nextTetromino = std::move(std::unique_ptr<Tetromino> (new Tetromino(this, nextPoint, loss(1, 7))));
}

void Widget::on_pushButton_clicked()
{
    currentTetromino->move<int>(0, 40);
}

void Widget::startGame()
{
    /*
    tetrominos.clear();
    nextBlock = std::move(std::shared_ptr<Block> (new Block(this, nextBlockPoint)));
    tetrominos.push_back(nextBlock);
    setCurrentBlock();
    movingTimer->start(moveInterval);
    */
    /////Without vector: tetrominos:
    myFloor->resetMatrix();
    nextTetromino = std::move(std::unique_ptr<Tetromino> (new Tetromino(this, nextPoint, loss(1, 7))));
    setCurrentTetromino();
    movingTimer->start(*moveInterval);
}

void Widget::movingDown()
{
    if (isPossibleMove(1, 0)) currentTetromino->move(0, blockSize.height());
    else if (currentTetromino->getPos().y() == -10) gameOver();
    else
    {
        addTetrominoToFloor();
        setCurrentTetromino();
    }
}

void Widget::touchFloor()
{

}


bool Widget::isPossibleMove(int di, int dj)
{
    bool check = true;
    int _i, _j;
    for (unsigned int i = 0; i < currentTetromino->getMatrix().size(); i++)
    {
        for (unsigned int j = 0; j < currentTetromino->getMatrix()[i].size(); j++)
        {
            _j = (currentTetromino->getPos().x() - 10) / blockSize.width() + j + dj;
            _i = (currentTetromino->getPos().y() - 30) / blockSize.height() + i + di + 1;
            if ((currentTetromino->getMatrix()[i][j]) && (_i >= myFloor->getMatrix().size() || _j >= myFloor->getMatrix()[_i].size() || _j < 0))   //!Checks if tetromino wants move outside the playground
            {
                check = false;
                break;
            }
            else if (currentTetromino->getMatrix()[i][j] && myFloor->getMatrix()[_i][_j])     //!Checks if tetromino will be on the other tetromino
            {
                check = false;
                break;
            }
        }
    }
    return check;
}

void Widget::addTetrominoToFloor()
{
    for (unsigned int i = 0; i < currentTetromino->getMatrix().size(); i++)
    {
        for (unsigned int j = 0; j < currentTetromino->getMatrix()[i].size(); j++)
        {
            if (currentTetromino->getMatrix()[i][j])
            {
                myFloor->addItemToMatrix((currentTetromino->getPos().y() - 30)/blockSize.height()+ i+ 1, (currentTetromino->getPos().x() - 10) / blockSize.width() + j); //!Position of block and i means in what point on floor matrix is tetromino
            }
        }
    }
}

void Widget::gameOver()
{
    movingTimer->stop();
    QMessageBox::information(this, "Game over", "You finished the game with: ", QDialogButtonBox::Close);
}

void Widget::on_addButton_clicked()
{
    if (isPossibleMove(0, 0)) addTetrominoToFloor();
    for (int i = 0; i < myFloor->getMatrix().size(); i++)
    {
        for (int j = 0; j < myFloor->getMatrix()[i].size(); j++)
        {
            std::cout << bool(myFloor->getMatrix()[i][j]) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    setCurrentTetromino();
}

void Widget::on_startButton_clicked()
{
    startGame();
}


