//
// Created by acro_ on 2016/06/24.
//

#include "catch.hpp"

#include "include/core/math/Vector2.h"

TEST_CASE( "Test Vec2f comparison", "[geometry]" )
{
	Vector2 a(1, 2);
	Vector2 b(1, 2);
	Vector2 c(2, 3);

	SECTION("Equality")
	{
		CHECK( a == b );
	}
	SECTION("Inequality")
	{
		CHECK( a != c );
	}
}