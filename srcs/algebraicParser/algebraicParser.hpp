#ifndef ALGEBRAICPARSER_HPP
# define ALGEBRAICPARSER_HPP

# include <iostream>

using namespace std;

class algebraicParser
{
    public:

        algebraicParser(void);
        ~algebraicParser(void);

        void    operator=(const string move);

        string  getParsedMove(void) const;
        bool    fail(void) const;

    private:

        bool    isValid(void);
        void    printInvalid(void) const;
        
        bool    isGoodLength(void) const;
        bool    isValidComplexSequence(void) const;
        bool    isValidSimpleSequence(void) const;
        bool    isValidSequence(void) const;
        bool    isValidChar(void) const;

        void    parseUniqueSequence(void);
        void    parseDoubleSequence(void);
        void    parseMove(void);

        bool    _fail;
        string  _move;
        string  _newMove;
};

bool            isChessDigit(const char c);
bool            isChessPiece(const char c);
bool            isChessCoord(const char c);

vector<string>  getKingSequence(const string move);
vector<string>  getQueenSequence(const string move);

vector<string>  getRookSequence(const string move);
vector<string>  getBishopSequence(const string move);
vector<string>  getKnightSequence(const string move);

vector<string>  getPawnSequence(const string move);

#endif