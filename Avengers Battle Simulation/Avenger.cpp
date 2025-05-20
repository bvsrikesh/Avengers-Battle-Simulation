#include "QNS.cpp"

class Avenger
{
    private:
        std::string name;
        QNS suit;                         
        int attackStrength;
    public:
        Avenger(){}
        Avenger (std::string avName, QNS& avSuit, int strength)
        {
            name = avName;
            suit = avSuit;
            attackStrength = strength;
        }
        ~Avenger(){}
        void attack (Avenger& enemy);
        void upgradeSuit (QNS& Suit);
        void repair (int x);
        void printStatus();
        void avengersuitboost (int factor);
        void avengersuitboost (QNS& otherSuit);
        QNS& getSuit()
        {
            return suit;
        }
};  

void Avenger :: attack (Avenger& enemy)
{
    enemy.suit - attackStrength;
}

void Avenger :: upgradeSuit (QNS& Suit)
{
    suit + Suit;
    //destroy Suit second
}

void Avenger :: repair (int x)
{
    suit/x;
}

void Avenger :: printStatus()
{
    std::cout << name << " " ;
    suit.print();
}

void Avenger :: avengersuitboost (int factor)
{
    suit.boostPower(factor);
}

void Avenger :: avengersuitboost (QNS& otherSuit)
{
    suit.boostPower(otherSuit);
}