#include "ObstacleMovementComponent.h"
#include "GameEngine/GameEngineMain.h"

using namespace GameEngine;

ObstacleMovementComponent::ObstacleMovementComponent():m_velocityFactor(0.f), m_moving(true)
{
    
}

ObstacleMovementComponent::~ObstacleMovementComponent()
{
    
}

void ObstacleMovementComponent::Update()
{
    Component::Update();
    if (!m_moving) return;
    float speed = GameEngine::GameEngineMain::GetInstance() -> GetGameSpeed();
    float velocity = 100.0f*speed*m_velocityFactor; // changes as the game progresses
    float dt = GameEngine::GameEngineMain::GetInstance() -> GetTimeDelta();
    
    sf::Vector2f displace = sf::Vector2f(0.0f, velocity*dt);
    GetEntity() -> SetPos(GetEntity() -> GetPos() + displace);
}

bool ObstacleMovementComponent::IsOutOfBound()
{
    GameEngine::GameEngineMain* mainEngine = GameEngine::GameEngineMain::GetInstance();
    sf::RenderWindow* window = mainEngine -> GetRenderWindow();
    sf::Vector2u size = window -> getSize();
    sf::Vector2f currpos = GetEntity() -> GetPos();
    return (size.y <= currpos.y);
}

void ObstacleMovementComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}

void ObstacleMovementComponent::SetVelocityFactor(float velocityFactor)
{
    m_velocityFactor = velocityFactor;
}

float ObstacleMovementComponent::GetVelocityFactor()
{
    return m_velocityFactor;
}

void ObstacleMovementComponent::StopMove()
{
    m_moving = false;
}

void ObstacleMovementComponent::StartMove()
{
    m_moving = true;
}
