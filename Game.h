#ifndef GAME_H
#define GAME_H

class Human;
class DefaultComputer;

class Game { // Visitor abstract base class
    // current turn #; 0 to 3
    // turnNum=n means its Player<n+1>s turn
    unsigned int turnNum;

    public:
        void nextTurn(); // updates turnNum
        int getTurnNum(); // getter
        void virtual visit(Human *human) = 0;
        void virtual visit(DefaultComputer *comp) = 0;

        explicit Game(unsigned int turnNum); // ctor
        ~Game(); // dtor
};


#endif