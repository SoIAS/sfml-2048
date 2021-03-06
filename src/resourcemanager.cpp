#include "resourcemanager.h"

ResourceManager& ResourceManager::instance()
{
	static ResourceManager resource_manager{};
	return resource_manager;
}

const sf::Texture* ResourceManager::load_texture(const std::string& file, const std::string& id)
{
	// todo, do I remove the old texture and reload or simply return as it is now?
	if (const auto result = get_texture(id))
	{
		// todo, log that the texture already exist(or the id rather)
		return result;
	}
	
	auto texture = std::make_unique<sf::Texture>();
	if (texture->loadFromFile(file))
	{
		textures_[id] = std::move(texture);
		return textures_[id].get();
	}

	return nullptr;
}

const sf::Texture* ResourceManager::get_texture(const std::string& id)
{
	if (const auto result = textures_.find(id);
		result != textures_.end())
	{
		return result->second.get();
	}

	return nullptr;
}

const sf::Font* ResourceManager::load_font(const std::string& file, const std::string& id)
{
	// todo, do I remove the old font and reload or simply return as it is now?
	if (const auto result = get_font(id))
	{
		// todo, log that the font already exist(or the id rather)
		return result;
	}
	
	auto font = std::make_unique<sf::Font>();
	if (font->loadFromFile(file))
	{
		fonts_[id] = std::move(font);
		return fonts_[id].get();
	}

	return nullptr;
}

const sf::Font* ResourceManager::get_font(const std::string& id)
{
	if (const auto result = fonts_.find(id);
		result != fonts_.end())
	{
		return result->second.get();
	}

	return nullptr;
}