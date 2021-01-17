#include "ThrowProjectileComponent.h"
#include <SFML/Window/Mouse.hpp>
#include "GameEngine/GameEngineMain.h"
#include "Game/GameControls/ObstacleShower.h"
#include "Game/Components/ProjectileMovementComponent.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "Game/GameBoard.h"
#include <stack>
#include <iostream>
using namespace GameEngine;

ThrowProjectileComponent::ThrowProjectileComponent():m_cooldown(0.f), m_projectiles()
{
    
}

ThrowProjectileComponent::~ThrowProjectileComponent()
{
    
}

void ThrowProjectileComponent::Update()
{
    Component::Update();
    CheckProjectileOutOfBound();
    if (GameEngineMain::GetInstance() -> isPaused || !(GameEngineMain::GetInstance() -> isRunning)) return;
    float dt = GameEngineMain::GetInstance() -> GetTimeDelta();
    m_cooldown -= dt;
    if (m_cooldown > 0.f) return;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Window* window = GameEngineMain::GetInstance() -> GetRenderWindow();
        sf::Vector2i position = sf::Mouse::getPosition(*window);
        sf::Vector2f positionf = sf::Vector2f((float)position.x, (float)position.y);
        sf::Vector2f dir = positionf - (GetEntity() -> GetPos());
        FireProjectile(dir);
    }
}

void ThrowProjectileComponent::CheckProjectileOutOfBound()
{
    std::stack<Entity*> todelete;
    for (Entity* proj : m_projectiles)
    {
        ProjectileMovementComponent* move = proj -> GetComponent<ProjectileMovementComponent>();
        if (move && move -> IsOutOfBound()) todelete.push(proj);
    }
    while (!todelete.empty())
    {
        Entity* ent = todelete.top();
        todelete.pop();
        m_projectiles.erase(ent);
        GameEngineMain::GetInstance() -> RemoveEntity(ent);
    }
}

void ThrowProjectileComponent::ClearProjectiles()
{
    std::stack<Entity*> s;
    for (Entity* proj: m_projectiles) s.push(proj);
    while (!s.empty())
    {
        Entity* ent = s.top();
        s.pop();
        GameEngineMain::GetInstance() -> RemoveEntity(ent);
    }
    m_projectiles.clear();
}

void ThrowProjectileComponent::FireProjectile(sf::Vector2f& dir)
{
    Entity* proj = new Entity();
    GameEngineMain::GetInstance() -> AddEntity(proj);
    proj -> SetPos(GetEntity() -> GetPos());
    proj -> SetSize(sf::Vector2f(40.f, 40.f));
    proj -> AddComponent<CollidableComponent>();
    
    ProjectileMovementComponent* move = proj -> AddComponent<ProjectileMovementComponent>();
    move -> SetVelocityFactor(3.f);
    float mag = sqrt(dir.x*dir.x + dir.y*dir.y);
    move -> SetDir(dir/mag);
    move -> SetPlayerEntity(GetEntity());
    
    SpriteRenderComponent* render = proj -> AddComponent<SpriteRenderComponent>();
    render -> SetTexture(eTexture::BlueFire);
    render -> SetZLevel(30);
    render -> SetFillColor(sf::Color::Transparent);
  
    m_cooldown = 1.0f;
    m_projectiles.insert(proj);
}

void ThrowProjectileComponent::ClearProjectile(Entity* ent)
{
    m_projectiles.erase(ent);
    GameEngineMain::GetInstance() -> RemoveEntity(ent);
}

void ThrowProjectileComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}

std::set<Entity*>& ThrowProjectileComponent::GetProjectiles()
{
    return m_projectiles;
}

