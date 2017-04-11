//
// Created by wing on 17/04/05.
//

#include <sstream>

#include "catch.hpp"

#include "utils/StringUtil.h"

using namespace std;

TEST_CASE("StringUtils", "[stringutils]")
{
	ostringstream iss;

	SECTION("stream empty string")
	{
		streamf(iss, "");
		REQUIRE(iss.str() == "");
	}

	SECTION("stream constant string")
	{
		streamf(iss, "constant");
		REQUIRE(iss.str() == "constant");
	}

	SECTION("stream string formatted with int")
	{
		streamf(iss, "I am %d", 17);
		REQUIRE(iss.str() == "I am 17");
	}

	SECTION("stream string formatted with double")
	{
		streamf(iss, "Pi is around %.2f", 3.14159);
		REQUIRE(iss.str() == "Pi is around 3.14");
	}

	SECTION("stream string formatted with string")
	{
		streamf(iss, "My name is %s!", "Jacob");
		REQUIRE(iss.str() == "My name is Jacob!");
	}

	SECTION("stream string formatted with various arguments")
	{
		streamf(iss, "Buy %d %s, %d %s and %.2gL of %s, please.", 3, "eggs", 4, "batteries", 5.2, "water");
		REQUIRE(iss.str() == "Buy 3 eggs, 4 batteries and 5.2L of water, please.");
	}
}