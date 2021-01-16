#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player,
			Ladder,
			Wall,
            Rock,
			Fog,
            Fireball,
			Count,
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
        switch (texture)
        {
            case eTexture::Player: return "character.png";
			case eTexture::Ladder: return "ladder-realistic.png";
			case eTexture::Wall: return "brick-wall-v1.1.png";
            case eTexture::Rock: return "Rock.png";
			case eTexture::Fog: return "fog-overlay.png";
            case eTexture::Fireball: return "Fireball.png";
            default: return "UnknownTextType";
        }
		return "UnknownTexType";
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture);
}

