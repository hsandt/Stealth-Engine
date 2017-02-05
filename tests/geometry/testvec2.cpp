//
// Created by acro_ on 2016/06/24.
//

#include "catch.hpp"

#include "geometry/Vec2.h"

TEST_CASE( "Test Vec2f comparison", "[geometry]" )
{
	Vec2f a(1, 2);
	Vec2f b(1, 2);
	Vec2f c(2, 3);

	SECTION("Equality")
	{
		CHECK( a == b );
	}
	SECTION("Inequality")
	{
		CHECK( a != c );
	}
}