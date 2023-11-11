#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QKeyEvent>
#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
private:
    Ui::Game *ui;
    GameManager* gManager;
    void keyPressEvent(QKeyEvent *event);
    /*
     * O -> Game menu
     * 1 -> Level 1
     * 2 -> Level 2
    */
    int currentPage = 0;
private slots:
    void onBtnLevel1Clicked();
    void onBtnLevel2Clicked();
    void onBtnExitGameClicked();
    void onBtnGoBackClicked();
    void onBtnContinueClicked();
};
#endif // GAME_H