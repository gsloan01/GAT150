#pragma once
#include "Color.h"
#include <vector>
#include "core.h"
#include "graphics.h"
#include <string>
#include "Transform.h"

namespace nc
{
	class Shape
	{
	public:
		Shape(){}
		Shape(const std::vector<nc::Vector2>& points, const Color& color) : m_points{ points }, m_color{ color }{}

		void Draw(Core::Graphics& graphics, nc::Vector2 position, float scale = 1, float angle = 0);
		void Draw(Core::Graphics& graphics, const Transform& transform);

		bool Load(const std::string& filename);

		void SetColor(Color color){ m_color = color; }
		const Color& GetColor() const{ return m_color; }
		float GetRadius() { return m_radius; }

	private:
		std::vector<nc::Vector2> m_points;
		Color m_color;
		float m_radius{ 1 };
	};

	

}
