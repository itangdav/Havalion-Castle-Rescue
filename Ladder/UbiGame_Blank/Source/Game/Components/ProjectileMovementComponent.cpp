//
//  ProjectileMovementComponent.cpp
//  Ladder
//
//  Created by Jacky He on 2021-01-16.
//
#include "ProjectileMovementComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "Game/GameControls/ObstacleShower.h"
#include "Game/Components/ThrowProjectileComponent.h"
#include <vector>
#include <iostream>

using namespace GameEngine;

ProjectileMovementComponent::ProjectileMovementComponent(): m_velocityFactor(1.5f), m_moving(true), m_dir(sf::Vector2f(0.f, 0.f)), m_player(nullptr)
{
    
}

ProjectileMovementComponent::~ProjectileMovementComponent()
{
    
}

void ProjectileMovementComponent::SetVelocityFactor(float velocityFactor)
{
    m_velocityFactor = velocityFactor;
}

void ProjectileMovementComponent::SetDir(sf::Vector2f dir)
{
    m_dir = dir;
}

sf::Vector2f ProjectileMovementComponent::GetDir()
{
    return m_dir;
}

float ProjectileMovementComponent::GetVelocityFactor()
{
    return m_velocityFactor;
}

void ProjectileMovementComponent::StopMove()
{
    m_moving = false;
}

void ProjectileMovementComponent::StartMove()
{
    m_moving = true;
}

void ProjectileMovementComponent::Update()
{
    Component::Update();
    CheckCollision();
    if (!(GameEngineMain::GetInstance() -> isRunning) || GameEngineMain::GetInstance() -> isPaused) StopMove();
    else StartMove();
    if (!m_moving) return;
    float speed = GameEngine::GameEngineMain::GetInstance() -> GetGameSpeed();
    float velocity = 0.7f*speed*m_velocityFactor; // changes as the game progresses
    float dt = GameEngine::GameEngineMain::GetInstance() -> GetTimeDelta();
    sf::Vector2f displace = m_dir*velocity*dt;
    GetEntity() -> SetPos(GetEntity() -> GetPos() + displace);
}

void ProjectileMovementComponent::CheckCollision()
{
    std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance() -> GetCollidables();
    CollidableComponent* thiscol = GetEntity() -> GetComponent<CollidableComponent>();
    CollidableComponent* playercol = m_player -> GetComponent<CollidableComponent>();
    
    for (int a = 0; a < collidables.size(); ++a)
    {
        CollidableComponent* colComponent = collidables[a];
        if (colComponent == thiscol || colComponent == playercol) continue;
        AABBRect intersection;
        AABBRect myBox = thiscol -> GetWorldAABB();
        AABBRect colideBox = colComponent -> GetWorldAABB();
        if (myBox.intersects(colideBox, intersection))
        {
            ObstacleEntity* obstacle = static_cast<ObstacleEntity*>(colComponent -> GetEntity());
            GameEngineMain::GetInstance() -> GetGameBoard() -> GetShower() -> ClearObstacle(obstacle);
            ThrowProjectileComponent* proj = m_player -> GetComponent<ThrowProjectileComponent>();
            proj -> ClearProjectile(GetEntity());
            break;
        }
    }
}

        
        
void ProjectileMovementComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}

void ProjectileMovementComponent::SetPlayerEntity(Entity *player)
{
    m_player = player;
}

bool ProjectileMovementComponent::IsOutOfBound()
{
    GameEngine::GameEngineMain* mainEngine = GameEngine::GameEngineMain::GetInstance();
    sf::RenderWindow* window = mainEngine -> GetRenderWindow();
    sf::Vector2u size = window -> getSize();
    sf::Vector2f currpos = GetEntity() -> GetPos();
    return (size.y + 50.f <= currpos.y + 50.f) || (currpos.y < -50.f) || (currpos.x < -50.f) || (currpos.x >= size.x + 50.f);
}
