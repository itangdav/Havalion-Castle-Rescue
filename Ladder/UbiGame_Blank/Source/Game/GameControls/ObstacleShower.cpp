#include "ObstacleShower.h"
#include <iostream>

using namespace GameEngine;

ObstacleShower::ObstacleShower():m_spawntimer(0.f), m_showering(false), m_g1((unsigned int)time(0))
{

}

ObstacleShower::~ObstacleShower()
{
    
}

void ObstacleShower::CreateObstacle(GameEngine::eObstacle::ladderType type, sf::Vector2f& pos)
{
    using namespace GameEngine;
    ObstacleEntity* obstacle = new ObstacleEntity();
    GameEngineMain::GetInstance() -> AddEntity(obstacle);
    obstacle -> SetPos (pos);
    obstacle -> SetSize (ObstacleManager::GetInstance() -> GetObstacleSize(type));
    SpriteRenderComponent* render = obstacle -> GetComponent<SpriteRenderComponent>();
    if (render)
    {
        render -> SetTexture(ObstacleManager::GetInstance() -> GetObstacleTexture(type));
        render -> SetTileIndex(sf::Vector2i(0, 0));
        render -> SetZLevel(10);
    }
    obstacle -> SetVelocityFactor(ObstacleManager::GetInstance() -> GetObstacleVelocityFactor(type));
    AnimationComponent* anim = obstacle -> GetComponent<AnimationComponent>();
    if (anim)
    {
        anim -> SetIsLooping(true);
        anim -> PlayAnim(ObstacleManager::GetInstance() -> GetObstacleAnimation(type));
    }
}

void ObstacleShower::CreateObstacle(GameEngine::eObstacle::nonLadderType type, sf::Vector2f& pos)
{
    using namespace GameEngine;
    ObstacleEntity* obstacle = new ObstacleEntity();
    GameEngineMain::GetInstance() -> AddEntity(obstacle);
    obstacle -> SetPos(pos);
    obstacle -> SetSize(ObstacleManager::GetInstance() -> GetObstacleSize(type));
    SpriteRenderComponent* render = obstacle -> GetComponent<SpriteRenderComponent>();
    if (render)
    {
        render -> SetTexture(ObstacleManager::GetInstance() -> GetObstacleTexture(type));
        render -> SetTileIndex(sf::Vector2i(0, 0));
        render -> SetZLevel(10);
    }
    obstacle -> SetVelocityFactor(ObstacleManager::GetInstance() -> GetObstacleVelocityFactor(type));
    AnimationComponent* anim = obstacle -> GetComponent<AnimationComponent>();
    if (anim)
    {
        anim -> SetIsLooping(true);
        anim -> PlayAnim(ObstacleManager::GetInstance() -> GetObstacleAnimation(type));
    }
}

void ObstacleShower::SpawnObstacle(bool onladder)
{
    sf::RenderWindow* window = GameEngine::GameEngineMain::GetInstance() -> GetRenderWindow();
    float screenWidth = (window -> getSize()).x;
    static int ladderCount = 5;
    sf::Vector2f pos = sf::Vector2f(0.f, 0.f);
    int ladderNum = RandInt(0, ladderCount - 1);
    float laddersX[5] = { 0.14, 0.31, 0.5, 0.61, 0.84 };
    pos.x = onladder ? laddersX[ladderNum]*screenWidth : RandFloat(0.f, screenWidth);
    if (onladder)
    {
        int cnt = (int)GameEngine::eObstacle::ladderType::Count;
        if (cnt <= 0) return;
        GameEngine::eObstacle::ladderType type = static_cast<GameEngine::eObstacle::ladderType>(RandInt(0, cnt - 1));
        CreateObstacle(type, pos);
    }
    else
    {
        int cnt = (int)GameEngine::eObstacle::nonLadderType::Count;
        if (cnt <= 0) return;
        GameEngine::eObstacle::nonLadderType type = static_cast<GameEngine::eObstacle::nonLadderType>(RandInt(0, (int)GameEngine::eObstacle::nonLadderType::Count - 1));
        CreateObstacle(type, pos);
    }
}

void ObstacleShower::SpawnNewRandomObstacles()
{
    float speed = GameEngine::GameEngineMain::GetInstance() -> GetGameSpeed();
    float minNextTime = 0.2f/speed;
    float maxNextTime = 1.5f/speed;
    float dice = RandFloat(0.f, 1.f);
    
    SpawnObstacle(dice <= 0.2f);
    m_spawntimer = RandFloat(minNextTime, maxNextTime);
}

void ObstacleShower::Update()
{
    if (!m_showering) return;
    float dt = GameEngine::GameEngineMain::GetInstance() -> GetTimeDelta();
    m_spawntimer -= dt;
    if (m_spawntimer <= 0.f) SpawnNewRandomObstacles();
}

void ObstacleShower::EnableShower()
{
    m_showering = true;
}

void ObstacleShower::DisableShower()
{
    m_showering = false;
}

float ObstacleShower::RandFloat (float a, float b)
{
    return std::uniform_real_distribution<float>(a, b)(m_g1);
}

int ObstacleShower::RandInt(int a, int b)
{
    return std::uniform_int_distribution<int>(a, b)(m_g1);
}
