#include "ObstacleEntity.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "Game/Components/ObstacleMovementComponent.h"
#include <SFML/Graphics.hpp>

using namespace GameEngine;

ObstacleEntity::ObstacleEntity()
{
    m_EAnim = EAnimationId::None;
    m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
    m_renderComponent -> SetFillColor(sf::Color::Transparent);
    AddComponent<GameEngine::CollidableComponent>();
    AddComponent<GameEngine::ObstacleMovementComponent>();
    AddComponent<GameEngine::AnimationComponent>();
}

ObstacleEntity::~ObstacleEntity()
{

}

void ObstacleEntity::OnAddToWorld()
{
    Entity::OnAddToWorld();
}

void ObstacleEntity::OnRemoveFromWorld()
{
    Entity::OnRemoveFromWorld();
}

void ObstacleEntity::SetVelocityFactor(float velocityFactor)
{
    GetComponent<GameEngine::ObstacleMovementComponent>() -> SetVelocityFactor(velocityFactor);
}

float ObstacleEntity::GetVelocityFactor()
{
    return GetComponent<GameEngine::ObstacleMovementComponent>() -> GetVelocityFactor();
}

void ObstacleEntity::SetAnim(EAnimationId::type anim)
{
    m_EAnim = anim;
}

void ObstacleEntity::Update()
{
    Entity::Update();
    AnimationComponent* anim = GetComponent<AnimationComponent>();
    ObstacleMovementComponent* move = GetComponent<ObstacleMovementComponent>();
    if (!(GameEngineMain::GetInstance() -> isRunning) || GameEngineMain::GetInstance() -> isPaused)
    {
        if (anim) anim -> StopAnim();
        if (move) move -> StopMove();
    }
    else
    {
        if (anim && !(anim -> IsAnimPlaying())) anim -> PlayAnim(m_EAnim);
        if (move) move -> StartMove();
    }
}
