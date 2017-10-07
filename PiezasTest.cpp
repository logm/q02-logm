/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}
//Testing for reset()
TEST(PiezasTest, reset) {
	Piezas pi;
	pi.dropPiece(0);//X
	pi.dropPiece(1);//O
	pi.dropPiece(0);//X
	pi.dropPiece(1);//O
	pi.dropPiece(2);//X
	pi.dropPiece(1);//O
	pi.dropPiece(3);//X
	pi.dropPiece(0);//O
	pi.dropPiece(3);//X
	pi.dropPiece(2);//O
	pi.dropPiece(2);//X
	pi.reset();
	ASSERT_EQ(Blank, pi.pieceAt(1,1));
}


//Testing for dropPiece()
TEST(PiezasTest, correctDropX) {
	Piezas pi;
	ASSERT_EQ(X, pi.dropPiece(1));
}

TEST(PiezasTest, correctDropO) {
	Piezas pi;
	pi.dropPiece(0);
	ASSERT_EQ(O, pi.dropPiece(1));
}

TEST(PiezasTest, outOfBoundsDrop) {
	Piezas pi;
	ASSERT_EQ(Invalid, pi.dropPiece(-1));
}

TEST(PiezasTest, fullColDrop) {
	Piezas pi;
	pi.dropPiece(0);
	pi.dropPiece(0);
	pi.dropPiece(0);
	ASSERT_EQ(Blank, pi.dropPiece(0));
}

//Testing for pieceAt()
TEST(PiezasTest, outOfBoundsPieceAt) {
	Piezas pi;
	ASSERT_EQ(Invalid, pi.pieceAt(5,5));
}

TEST(PiezasTest, correctPieceAt) {
	Piezas pi;
	pi.dropPiece(0);
	pi.dropPiece(0);
	ASSERT_EQ(O, pi.pieceAt(1,0));
}

TEST(PiezasTest, blankPieceAt) {
	Piezas pi;
	ASSERT_EQ(Blank, pi.pieceAt(1,0));
}

//Testing for gameState()
TEST(PiezasTest, gameNotDone) {
	Piezas pi;
	pi.dropPiece(0);//X
	pi.dropPiece(0);//O
	pi.dropPiece(1);//X
	pi.dropPiece(1);//O
	pi.dropPiece(2);//X
	pi.dropPiece(0);//O
	pi.dropPiece(3);//X
	pi.dropPiece(1);//O
	ASSERT_EQ(Invalid, pi.gameState());
}

TEST(PiezasTest, fourStreakWinnerRows) {
	Piezas pi;
	pi.dropPiece(0);//X
	pi.dropPiece(0);//O
	pi.dropPiece(1);//X
	pi.dropPiece(0);//O
	pi.dropPiece(2);//X
	pi.dropPiece(2);//O
	pi.dropPiece(3);//X
	pi.dropPiece(3);//O
	pi.dropPiece(1);//X
	pi.dropPiece(2);//O
	pi.dropPiece(1);//X
	pi.dropPiece(3);//O
	ASSERT_EQ(X, pi.gameState());
}

TEST(PiezasTest, tie) {
	Piezas pi;
	pi.dropPiece(0);//X
	pi.dropPiece(0);//O
	pi.dropPiece(0);//X
	pi.dropPiece(1);//O
	pi.dropPiece(2);//X
	pi.dropPiece(2);//O
	pi.dropPiece(3);//X
	pi.dropPiece(3);//O
	pi.dropPiece(1);//X
	pi.dropPiece(2);//O
	pi.dropPiece(1);//X
	pi.dropPiece(3);//O
	ASSERT_EQ(Blank, pi.gameState());
}

TEST(PiezasTest, threeStreakWinnerCOl) {
	Piezas pi;
	pi.dropPiece(0);//X
	pi.dropPiece(1);//O
	pi.dropPiece(0);//X
	pi.dropPiece(1);//O
	pi.dropPiece(2);//X
	pi.dropPiece(1);//O
	pi.dropPiece(3);//X
	pi.dropPiece(0);//O
	pi.dropPiece(3);//X
	pi.dropPiece(2);//O
	pi.dropPiece(2);//X
	pi.dropPiece(3);//O
	ASSERT_EQ(O, pi.gameState());
}