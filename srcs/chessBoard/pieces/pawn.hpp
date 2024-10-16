#ifndef PAWN_HPP
# define PAWN_HPP

# include "chessPiece.hpp"

class Pawn : public chessPiece
{
    public:
    
        Pawn(const string color, const string pos) : chessPiece(color, pos)
        {
            _doubleMove = true;
            _enPassant = true;
        }

        ~Pawn() {};

        virtual const bool  checkMoveConsistency(const string move) const
        {
            int target_x = move[0] - 97;
            int target_y = atoi(move.c_str() + 1);

            if ((_x + 1 == target_x && _y + 1 == target_y) || (_x - 1 == target_x && _y + 1 == target_y))
                return (true);
            if (_x == target_x && _y + 1 == target_y)
                return (true);
            if (_x == target_x && _y + 2 == target_y)
            {
                if (getDoubleMove() == true && _moves == 0)
                    return (true);
            }
            
            return (false);
        }

        bool    getDoubleMove(void) const { return(_doubleMove); }
        bool    getEnPassant(void) const { return(_enPassant); }

        void    disableDoubleMove(void) { _doubleMove = false; }
        void    disableEnPassant(void) { _enPassant = false; }

    private:

        bool    _doubleMove;
        bool    _enPassant;
};

#endif