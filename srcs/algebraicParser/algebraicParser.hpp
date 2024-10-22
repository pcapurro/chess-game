#ifndef ALGEBRAICPARSER_HPP
# define ALGEBRAICPARSER_HPP

# include <iostream>

using namespace std;

typedef struct s_move
{
    string  move;
    char    action;
    
    char    obj;
    string  src;
    string  dest;

}   t_move;

class algebraicParser
{
    public:

        algebraicParser(void) { _turn = 0; };
        ~algebraicParser(void) {};

        void            operator=(const string move);
        bool            fail(void) const;

        void            setTurn(const int turn) { _turn = turn; };
        t_move          getParsedMove(void) const { return (_move); };

    private:

        bool    isValid(void);
        
        bool    isGoodLength(void) const;
        bool    isValidComplexSequence(void) const;
        bool    isValidSimpleSequence(void) const;
        bool    isValidSequence(void) const;
        bool    isValidChar(void) const;

        string  getLeftSequence(void) const;
        string  getRightSequence(void) const;

        void    parseUniqueSequence(void);
        void    parseDoubleSequence(void);
        void    parseMove(void);

        bool    _fail;

        int     _turn;
        t_move  _move;
};

bool            isChessDigit(const char c);
bool            isChessPiece(const char c);
bool            isChessCoord(const char c);

vector<string>  getKingSequence(const string move, const char sign);
vector<string>  getQueenSequence(const string move, const char sign);

vector<string>  getRookSequence(const string move, const char sign);
vector<string>  getBishopSequence(const string move, const char sign);
vector<string>  getKnightSequence(const string move, const char sign);

vector<string>  getPawnSequence(const string move, const int turn, const char sign);

#endif