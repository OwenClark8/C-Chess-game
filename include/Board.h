#ifndef BOARDDEF
#define BOARDDEF

#include <iostream>
#include "Component.h"
#include "ObserverMapper.h"
#include "Square.h"
#include "Key.h"

class GameBuilder;
class Game;
class LossBoard;

/* Needs to be able to restore enpassant links */
struct Move{
	Move(const std::pair<Location, Location>& m, const std::pair<bool, PieceType>& lp):
		m_move(m), m_lostPiece(lp)
	{};
	Move(void) = default;
	std::pair<Location, Location> m_move;
	std::pair<bool, PieceType>    m_lostPiece;
};


class Board : public Component, private ObserverMapper<Location>
{
protected:
	 std::map<Location, std::unique_ptr<Square>> m_board;
	 //Move m_currentMove;
	 Game* mp_game;
	 LossBoard * mp_lossBoard;

public: 
	Board(Game* game, LossBoard* lb, PrintImpl* pi) : Component(pi), mp_game(game), mp_lossBoard(lb)
	{};

	//Board(const Board& otherboard);
	Board(Board&& otherboard)       = delete;

	Board&  operator=(const Board&) = delete;
	Board&& operator=(Board&&)      = delete;

	~Board() = default;
	
	PieceType getPiece(const Location& i) const;

	void selectSquare(const Location& i);

	bool checkMove(const Location& movefrom, const Location& moveto) const;

	void unselectAll();

	void updateBoard(const Location& movefrom, const Location& moveto);

	void doMove(const Move& mov, const GameBuilder& b, Key<Game>);

	void undoMove(const Move& mov, const GameBuilder& b, Key<Game>);

	void addSquare(Location loc, std::unique_ptr<Square> sqr);
	void removeSquare(const Location& loc);

	void draw() const override;

	void pawnAttach(const Location& loc1, const Location& loc2);

	void pawnDetach(const Location& loc1, const Location& loc2);

	//void checkCastle(Colour c) const;

	
};





#endif