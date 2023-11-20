#include "firstlevelscene.h"

FirstLevelScene::FirstLevelScene()
{
    s = new QGraphicsScene;
    p = new Player(100, 10, 10, 10, 3, playerSprites[0], 1000);
    pScoreEnemies = new PlayerScore(QString("Enemies: "), 20, 0, 600, 30);
    pScoreLife = new PlayerScore(QString("Life: "), 100, 100, 600, 10);
    enemyTimer = new QTimer;
    connect(enemyTimer, &QTimer::timeout, this, &FirstLevelScene::generateEnemy);
    connect(p, &Player::changePlayerLife, pScoreLife, &PlayerScore::decreaseCurrentPlayerLife);
}

FirstLevelScene::~FirstLevelScene()
{
    delete s;
    delete g;
    delete p;
    delete enemyTimer;
    delete pScoreEnemies;
    delete pScoreLife;
}

void FirstLevelScene::setGraphicsScene(QGraphicsView *g)
{
    this->g = g;
    s->setSceneRect(0, 0, g->width() - 2, g->height() - 2);
    s->addItem(p);
    s->addItem(pScoreEnemies);
    s->addItem(pScoreLife);
    g->setScene(s);
}

void FirstLevelScene::movePlayer()
{
    p->movePlayer();
    p->setIsMoving(true);
}

void FirstLevelScene::noMovePlayer()
{
    p->setIsMoving(false);
}

void FirstLevelScene::modifyPositionDir(int pos)
{
    p->modifyPositionVector(pos);
}

int FirstLevelScene::getXPlayerPos()
{
    return p->getXPos();
}

int FirstLevelScene::getYPlayerPos()
{
    return p->getYPos();
}

void FirstLevelScene::clearScene()
{
    s->clear();
}

void FirstLevelScene::generateBullet(int x, int y)
{
    Bullet *newBullet = new Bullet(1, playerSprites[2], 1000);
    newBullet->setPos(p->getXPos() + (CHARACTER_WEIGHT / 4), p->getYPos() + (CHARACTER_HEIGHT / 4));
    int dir = p->getDir(); // 0 -> UP/1 -> DOWN/2 -> LEFT/3 -> RIGHT
    newBullet->targetDirection(dir);
    s->addItem(newBullet);
}

void FirstLevelScene::startLevel()
{
    enemyTimer->start(1000);
}

int FirstLevelScene::getDeadEnemies() const
{
    return deadEnemies;
}

void FirstLevelScene::generateEnemy()
{
    if (amountOfEnemies < 5) {
        int distanceGeneration = 200;
        int angleOfGeneration = rand() % 360;

        int xPos = p->getXPos() + distanceGeneration * std::cos(angleOfGeneration * M_PI / 180);
        int yPos = p->getYPos() + distanceGeneration * std::sin(angleOfGeneration * M_PI / 180);

        xPos = qBound(0, xPos, static_cast<int>(s->width()));
        yPos = qBound(0, yPos, static_cast<int>(s->height()));

        Enemy *newEnemy = new Enemy(p->getXPos(), p->getYPos(), 100, 10, 10, 10, 3, playerSprites[1], 1000);
        newEnemy->setPos(xPos, yPos);
        amountOfEnemies++;

        connect(p, &Player::changeEnemyPos, newEnemy, &Enemy::changePosition);
        connect(newEnemy, &Enemy::enemyIsDeath, this, &FirstLevelScene::amountOfEnemiesDecrement);
        connect(newEnemy, &Enemy::enemyIsDeath, pScoreEnemies, &PlayerScore::increaseCurrentDeadEnemies);
        s->addItem(newEnemy);
    }
}

void FirstLevelScene::amountOfEnemiesDecrement()
{
    amountOfEnemies--;
    deadEnemies++;
}
