#ifndef _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#endif // !_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include "pch.h"
#include "Position.cpp"
#include <gtest/gtest.h>

class PositionFixture : public ::testing::Test
{
public:
	PositionFixture() : x(-2), y(-2), dir("dir") {}
	~PositionFixture() {}

	std::shared_ptr<Position> sut = std::make_shared<Position>();
	int x, y;
	std::string dir;
};

TEST_F(PositionFixture, ShouldGetInitialPosition)
{
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, -1);
	ASSERT_EQ(y, -1);
	ASSERT_EQ(dir, "");
}

TEST_F(PositionFixture, ShouldPlaceNorth)
{
	sut->setPosition(0, 0, "north");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
	ASSERT_EQ(dir, "north");
}

TEST_F(PositionFixture, ShouldPlaceEast)
{
	sut->setPosition(0, 0, "east");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
	ASSERT_EQ(dir, "east");
}

TEST_F(PositionFixture, ShouldPlaceSouth)
{
	sut->setPosition(0, 0, "south");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
	ASSERT_EQ(dir, "south");
}

TEST_F(PositionFixture, ShouldPlaceWest)
{
	sut->setPosition(0, 0, "west");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
	ASSERT_EQ(dir, "west");
}

TEST_F(PositionFixture, ShouldNotMovePositionWhenInvalidMoveCommand)
{
	sut->setPosition(0, 0, "west");
	sut->move();
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
	ASSERT_EQ(dir, "west");
}

TEST_F(PositionFixture, ShouldNotAcceptInvalidPosition)
{
	sut->setPosition(-3, -3, "north");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, -1);
	ASSERT_EQ(y, -1);
	ASSERT_EQ(dir, "");
}

TEST_F(PositionFixture, ShouldNotAcceptInvalidDirection)
{
	sut->setPosition(0, 0, "northeast");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, -1);
	ASSERT_EQ(y, -1);
	ASSERT_EQ(dir, "");
}

TEST_F(PositionFixture, ShouldAcceptUppercaseDirection)
{
	sut->setPosition(0, 0, "NORTH");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
	ASSERT_EQ(dir, "north");
}

TEST_F(PositionFixture, ShouldChangeDirectionWithLeftCommand)
{
	sut->setPosition(0, 0, "north");

	sut->rotate(ERotation::left);
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(dir, "west");

	sut->rotate(ERotation::left);
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(dir, "south");

	sut->rotate(ERotation::left);
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(dir, "east");

	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
}

TEST_F(PositionFixture, ShouldChangeDirectionWithRightCommand)
{
	sut->setPosition(0, 0, "north");

	sut->rotate(ERotation::right);
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(dir, "east");

	sut->rotate(ERotation::right);
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(dir, "south");

	sut->rotate(ERotation::right);
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(dir, "west");

	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
}

TEST_F(PositionFixture, ShouldMoveOneStepNorth)
{
	sut->setPosition(5, 5, "north");
	sut->move();
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 5);
	ASSERT_EQ(y, 6);
	ASSERT_EQ(dir, "north");
}

TEST_F(PositionFixture, ShouldMoveOneStepWest)
{
	sut->setPosition(5, 5, "west");
	sut->move();
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 4);
	ASSERT_EQ(y, 5);
	ASSERT_EQ(dir, "west");
}

TEST_F(PositionFixture, ShouldMoveOneStepSouth)
{
	sut->setPosition(5, 5, "south");
	sut->move();
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 5);
	ASSERT_EQ(y, 4);
	ASSERT_EQ(dir, "south");
}

TEST_F(PositionFixture, ShouldMoveOneStepEast)
{
	sut->setPosition(5, 5, "east");
	sut->move();
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 6);
	ASSERT_EQ(y, 5);
	ASSERT_EQ(dir, "east");
}

TEST_F(PositionFixture, ShouldPlaceInANewPositionWhenSetAgain)
{
	sut->setPosition(5, 5, "west");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 5);
	ASSERT_EQ(y, 5);
	ASSERT_EQ(dir, "west");

	sut->setPosition(0, 0, "east");
	std::tie(x, y, dir) = sut->getPosition();
	ASSERT_EQ(x, 0);
	ASSERT_EQ(y, 0);
	ASSERT_EQ(dir, "east");
}