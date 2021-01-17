#include "ObstacleManager.h"

using namespace GameEngine;

ObstacleManager* ObstacleManager::sm_instance = nullptr;

ObstacleManager::ObstacleManager()
{
    
}

ObstacleManager::~ObstacleManager()
{
    
}

sf::Vector2f ObstacleManager::GetObstacleSize (eObstacle::ladderType type)
{
    switch (type)
    {
        case eObstacle::ladderType::Rock: return sf::Vector2f(60.f, 60.f);
        case eObstacle::ladderType::Fireball: return sf::Vector2f(30.f, 60.f);
        case eObstacle::ladderType::Arrow: return sf::Vector2f(30.f, 97.5f);
        default: return sf::Vector2f(0.f, 0.f);
    }
    return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f ObstacleManager::GetObstacleSize (eObstacle::nonLadderType type)
{
    switch (type)
    {
        case eObstacle::nonLadderType::Rock: return sf::Vector2f(60.f, 60.f);
        case eObstacle::nonLadderType::Fireball: return sf::Vector2f(30.f, 60.f);
        default: return sf::Vector2f(0.f, 0.f);
    }
    return sf::Vector2f(0.f, 0.f);
}

eTexture::type ObstacleManager::GetObstacleTexture (eObstacle::ladderType type)
{
    switch (type)
    {
        case eObstacle::ladderType::Rock: return eTexture::Rock;
        case eObstacle::ladderType::Fireball: return eTexture::Fireball;
        case eObstacle::ladderType::Arrow: return eTexture::Arrow;
        default: return eTexture::None;
    }
    return eTexture::None;
}

eTexture::type ObstacleManager::GetObstacleTexture (eObstacle::nonLadderType type)
{
    switch (type)
    {
        case eObstacle::nonLadderType::Rock: return eTexture::Rock;
        case eObstacle::nonLadderType::Fireball: return eTexture::Fireball;
        default: return eTexture::None;
    }
    return eTexture::None;
}

EAnimationId::type ObstacleManager::GetObstacleAnimation (eObstacle::ladderType type)
{
    switch (type)
    {
        case eObstacle::ladderType::Rock: return EAnimationId::RollingRock;
        case eObstacle::ladderType::Fireball: return EAnimationId::FiryBall;
        case eObstacle::ladderType::Arrow: return EAnimationId::ShootingArrow;
        default: return EAnimationId::None;
    }
    return EAnimationId::None;
}

EAnimationId::type ObstacleManager::GetObstacleAnimation (eObstacle::nonLadderType type)
{
    switch (type)
    {
        case eObstacle::nonLadderType::Rock: return EAnimationId::RollingRock;
        case eObstacle::nonLadderType::Fireball: return EAnimationId::FiryBall;
        default: return EAnimationId::None;
    }
    return EAnimationId::None;
}

float ObstacleManager::GetObstacleVelocityFactor (eObstacle::ladderType type)
{
    switch (type)
    {
        case eObstacle::ladderType::Rock: return 4.f;
        case eObstacle::ladderType::Fireball: return 3.f;
        case eObstacle::ladderType::Arrow: return 5.f;
        default: return 0.f;
    }
    return 0.f;
}

float ObstacleManager::GetObstacleVelocityFactor (eObstacle::nonLadderType type)
{
    switch (type)
    {
        case eObstacle::nonLadderType::Rock: return 4.f;
        case eObstacle::nonLadderType::Fireball: return 3.f;
        default: return 0.f;
    }
    return 0.f;
}
