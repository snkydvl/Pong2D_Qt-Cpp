#include <QString>
#include "game.h"

const QSize Game::RESOLUTION = QSize(800, 600);
const float Game::ITERATION_VALUE = 1000.0f/60.0f;
const QString Game::PATH_TO_PADDLE_PIXMAP = ":/res/paddle.png";
const QString Game::PATH_TO_BALL_PIXMAP = ":/res/ball.png";
const QString Game::PATH_TO_CURSOR_PIXMAP = ":/res/cursor.png";

int Game::SCORE_1 = 0;
int Game::SCORE_2 = 0;

Game::Game()
    : m_isPause(false)
{

}
