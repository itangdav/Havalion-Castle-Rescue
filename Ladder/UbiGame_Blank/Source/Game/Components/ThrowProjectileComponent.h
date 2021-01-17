#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine/EntitySystem/Entity.h"
#include <set>

namespace GameEngine
{
    class ThrowProjectileComponent : public GameEngine::Component
    {
    public:
        ThrowProjectileComponent();
        ~ThrowProjectileComponent();

        virtual void Update() override;
        virtual void OnAddToWorld() override;
        
        void ClearProjectiles();
        void ClearProjectile(Entity* ent);
        std::set<Entity*>& GetProjectiles();

    private:
        float m_cooldown;
        void FireProjectile (sf::Vector2f& dir);
        std::set<Entity*> m_projectiles;
        
        void CheckProjectileOutOfBound();
    };

}
