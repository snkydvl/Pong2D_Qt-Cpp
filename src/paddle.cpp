#include "paddle.h"
#include "ball.h"
#include "game.h"
Paddle::Paddle(PaddleType type, QSize size)
    : m_type(type), m_baseSpeed(6.0f), m_minSpeed(1.0f), m_size(size),
      m_moveUp(false), m_moveDown(false)
{
    init();
}

QSize Paddle::size() const
{
    return m_size;
}

void Paddle::setSize(QSize newSize)
{
    if(newSize == m_size)
    {
        return;
    }
    m_size = newSize;
}

void Paddle::update(Ball &ball)
{
    //Axis-Aligned Bounding-Box
    if (
            m_position.x()                   < ball.position().x() + ball.diameter() &&
            m_position.x() + m_size.width()  > ball.position().x()                   &&
            m_position.y()                   < ball.position().y() + ball.diameter() &&
            m_position.y() + m_size.height() > ball.position().y()
            )
    {
        if ( m_position.y() + (m_size.height() * 0.33f) > ball.position().y())
        {
            ball.setYDir(Ball::Y_DIRECTION::UP);
        }
        else if ( (m_position.y() + m_size.height() * 0.66f) < ball.position().y())
        {
            ball.setYDir(Ball::Y_DIRECTION::DOWN);
        }

        switch (m_type)
        {
        case PaddleType::PLAYER1:
            ball.setXDir(Ball::X_DIRECTION::LEFT);
            break;
        case PaddleType::AI:
        case PaddleType::AI1:
        case PaddleType::PLAYER2:
            ball.setXDir(Ball::X_DIRECTION::RIGHT);
            break;
        }

        ball.increaseSpeed();
    }


    switch (m_type) {
    case PaddleType::PLAYER1:
    case PaddleType::PLAYER2:
    {
        if(m_moveUp)
        {
            setPosition(position() + QPointF(0, -m_baseSpeed));
        }
        else if(m_moveDown)
        {
            setPosition(position() + QPointF(0, +m_baseSpeed));
        }
    }
        break;
    case PaddleType::AI:
    case PaddleType::AI1:
    {
        if(ball.position().y() < m_position.y())
        {
            if(m_position.y() - ball.position().y() < 0.5f)
            {
                setPosition(position() + QPointF(0, -m_minSpeed));
            }
            else
            {
                setPosition(position() + QPointF(0, -m_baseSpeed));
            }
        }
        else if(ball.position().y() + ball.diameter() > m_position.y() + m_size.height())
        {
            if(ball.position().y() + ball.diameter() - m_position.y() + m_size.height() < 0.5f)
            {
                setPosition(position() + QPointF(0,  m_minSpeed));
            }
            else
            {
                setPosition(position() + QPointF(0,  m_baseSpeed));
            }
        }
    }
        break;
    }
    clampPaddle();
}

QPointF Paddle::position() const
{
    return m_position;
}

void Paddle::setPosition(QPointF newPoint)
{
    if(m_position == newPoint)
    {
        return;
    }
    m_position = newPoint;
}

void Paddle::setMoveUp(bool val)
{
    if(m_moveUp == val)
    {
        return;
    }
    m_moveUp = val;
}

void Paddle::setMoveDown(bool val)
{
    if(m_moveDown == val)
    {
        return;
    }
    m_moveDown = val;
}

Paddle::PaddleType Paddle::type() const
{
    return m_type;
}

void Paddle::setPaddleType(PaddleType type)
{
    if( m_type == type)
    {
        return;
    }
    m_type = type;
}

void Paddle::init()
{
    switch (m_type)
    {
    case Paddle::PaddleType::PLAYER1:
    case Paddle::PaddleType::AI1:
        setPosition(QPointF(0.95f*Game::RESOLUTION.width(), 0.5f*Game::RESOLUTION.height()));
        break;
    case Paddle::PaddleType::AI:
    case Paddle::PaddleType::PLAYER2:
        setPosition(QPointF(0.05f*Game::RESOLUTION.width(), 0.5f*Game::RESOLUTION.height()));
        break;
    }
}

void Paddle::clampPaddle()
{
    if(m_position.y() < 0.0f)
    {
        setPosition(QPointF(m_position.x(), 0.0f));
    }
    if(m_position.y() + m_size.height() > Game::RESOLUTION.height())
    {
        setPosition(QPointF(m_position.x(), Game::RESOLUTION.height() - m_size.height()));
    }
}
