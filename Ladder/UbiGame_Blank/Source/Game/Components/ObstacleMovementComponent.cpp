#include "ObstacleMovementComponent.h"
#include "GameEngine/GameEngineMain.h"

using namespace GameEngine;

ObstacleMovementComponent::ObstacleMovementComponent():m_velocityFactor(0.f)
{
    
}

ObstacleMovementComponent::~ObstacleMovementComponent()
{
    
}

void ObstacleMovementComponent::Update()
{
    Component::Update();
    float multi = GameEngine::GameEngineMain::GetInstance() -> GetGameSpeed();
    float velocity = 100.0f*multi*m_velocityFactor; // changes as the game progresses
    float dt = GameEngine::GameEngineMain::GetInstance() -> GetTimeDelta();
    
    sf::Vector2f displace = sf::Vector2f(0.0f, velocity*dt);
    GetEntity() -> SetPos(GetEntity() -> GetPos() + displace);
    
    //check if out of bound
    GameEngine::GameEngineMain* mainEngine = GameEngine::GameEngineMain::GetInstance();
    sf::RenderWindow* window = mainEngine -> GetRenderWindow();
    sf::Vector2u size = window -> getSize();
    sf::Vector2f currpos = GetEntity() -> GetPos();
    if (size.y <= currpos.y) GameEngine::GameEngineMain::GetInstance() -> RemoveEntity(GetEntity());
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
