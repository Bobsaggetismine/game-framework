#include <bq/util/vec.h>

bq::v2i bq::operator+(const v2i& first, const v2i& second)
{
	return { first.x + second.x, first.y + second.y };
}