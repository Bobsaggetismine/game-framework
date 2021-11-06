#pragma once

namespace bq {

	class float_rect {
	protected:
		float m_x, m_y, m_w, m_h;
		float_rect(float x,float y,float w, float h);
	public:
		bool intersects(const float_rect& other);
	};
	class int_rect {
		int m_x, m_y, m_w, m_h;
		int_rect(int x, int y, int w, int h);
	};
}