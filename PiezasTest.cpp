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

TEST(PiezasTest, constructorCheck)
{
  Piezas p;
  for (int i = 0; i < BOARD_ROWS; i++)
  {
    for (int j = 0; j < BOARD_COLS; j++)
    {
      ASSERT_EQ(p.pieceAt(i, j), Blank);
    }
  }
}

TEST(PiezasTest, peiceAtTest)
{
  Piezas p;
  ASSERT_EQ(p.pieceAt(-1, -1), Invalid);
  ASSERT_EQ(p.pieceAt(3, 4), Invalid);
  ASSERT_EQ(p.pieceAt(3, 0), Invalid);
  ASSERT_EQ(p.pieceAt(0, 4), Invalid);
}

TEST(PiezasTest, fullBoard_pieceAtTest)
{
  Piezas p;
  for (int i = 0; i < BOARD_ROWS; i++)
  {
    for (int j = 0; j < BOARD_COLS; j++)
    {
      p.dropPiece(j);
      ASSERT_NE(p.pieceAt(i, j), Blank);
      ASSERT_NE(p.pieceAt(i, j), Invalid);
      if (j % 2)
      {
        ASSERT_EQ(p.pieceAt(i, j), O);
      }
      else
      {
        ASSERT_EQ(p.pieceAt(i, j), X);
      }
    }
  }
}

TEST(PiezasTest, tieTest)
{
  Piezas p;
  for (int i = 0; i < BOARD_ROWS; i++)
  {
    for (int j = 0; j < BOARD_COLS; j++)
    {
      p.dropPiece(j);
      ASSERT_EQ(p.gameState(), Invalid);
    }
  }
  ASSERT_EQ(p.gameState(), Blank);
  ASSERT_EQ(p.gameState(), Invalid);
  p.reset();
  ASSERT_EQ(p.gameState(), Invalid);
  for (int j = 0; j < BOARD_COLS; j++)
  {
    p.dropPiece(j);
    ASSERT_EQ(p.gameState(), Invalid);
  }
  for (int j = 3; j >= 0; j--)
  {
    p.dropPiece(j);
    ASSERT_EQ(p.gameState(), Invalid);
  }
  for (int j = 0; j < BOARD_COLS; j++)
  {
    p.dropPiece(j);
    ASSERT_EQ(p.gameState(), Invalid);
  }
  ASSERT_EQ(p.gameState(), Blank);
}

TEST(PiezasTest, winnerTest)
{
  Piezas p;
  p.dropPiece(0);
  p.dropPiece(0);
  p.dropPiece(1);
  p.dropPiece(1);
  p.dropPiece(2);
  p.dropPiece(2);
  p.dropPiece(3);
  p.dropPiece(0);
  p.dropPiece(3);
  p.dropPiece(3);
  p.dropPiece(2);
  p.dropPiece(1);
  ASSERT_EQ(p.gameState(), X);
  p.reset();
  p.dropPiece(0);
  p.dropPiece(0);
  p.dropPiece(1);
  p.dropPiece(1);
  p.dropPiece(2);
  p.dropPiece(2);
  p.dropPiece(0);
  p.dropPiece(3);
  p.dropPiece(1);
  p.dropPiece(3);
  p.dropPiece(2);
  p.dropPiece(3);
  ASSERT_EQ(p.gameState(), O);
}
