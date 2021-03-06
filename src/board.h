#pragma once

#include "scene.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Drawable.hpp"

#include <optional>


// tmp
#include "SFML/Graphics.hpp"

struct Tile
{
	sf::Sprite sprite{};
	unsigned value{};
};


class Board : public sf::Drawable, public sf::Transformable
{
public:
	enum class e_direction
	{
		NORTH,
		SOUTH,
		WEST,
		EAST
	};

	Board(unsigned size, const sf::Vector2f& render_size, unsigned max_value);
	~Board() override = default;

	[[nodiscard]] unsigned size() const noexcept;
	[[nodiscard]] unsigned max_value() const noexcept;
	[[nodiscard]] unsigned score() const noexcept;

	void set_render_size(const sf::Vector2f& render_size);

	bool spawn_new_tile();
	[[nodiscard]] std::vector<size_t> get_empty_tiles();

	bool move(e_direction direction);
	[[nodiscard]] bool any_moves_available() const;

	[[nodiscard]] bool contains_value(unsigned value) const;

	void clear();
	
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Tile& tile(size_t x, size_t y) noexcept;
	const Tile& tile(size_t x, size_t y) const noexcept;
	Tile& tile(size_t index) noexcept;
	const Tile& tile(size_t index) const noexcept;
	void init_background_tiles();

	[[nodiscard]] sf::Vector2f get_tile_size(const sf::Vector2f& render_size) const noexcept;
	[[nodiscard]] sf::Vector2f get_tile_position(unsigned x, unsigned y) const noexcept;
	[[nodiscard]] size_t xy_to_index(size_t x, size_t y) const noexcept;
	[[nodiscard]] sf::Vector2i index_to_xy(size_t index) const noexcept;

	[[nodiscard]] sf::Vector2i get_direction_vector(e_direction direction) const;
	[[nodiscard]] std::optional<sf::Vector2i> get_next_position(sf::Vector2i position, sf::Vector2i direction_vector) const;
	[[nodiscard]] std::optional<sf::Vector2i> get_next_non_empty_position(sf::Vector2i position, sf::Vector2i direction_vector) const;
	[[nodiscard]] std::pair<std::vector<size_t>, std::vector<size_t>> get_sequence_vectors(sf::Vector2i direction_vector) const;

	[[nodiscard]] bool has_empty_tile() const;
	[[nodiscard]] bool any_merge_available() const;

	Tile new_tile(sf::Vector2i position, unsigned value) const;
	
	bool merge_tiles(sf::Vector2i direction_vector);
	bool move_tiles(sf::Vector2i direction_vector);
	
private:
	const unsigned size_;
	std::vector<Tile> board_;
	const unsigned max_value_;
	// the merge/move functions should be in the mainscene not in the board itself<?>
	// it'd be easier to maintain score in mainscene, but for now... let's put it int he board itself
	unsigned score_{};

	// TODO
	float tile_padding_{ 10 };
	sf::Vector2f tile_size_{};
	sf::RectangleShape background_;
	std::vector<sf::RectangleShape> background_tiles_;
};
