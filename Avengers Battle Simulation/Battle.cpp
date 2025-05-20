#include "Avenger.cpp"

class Battle
{
    private:
        std::vector < std::string > heroes;        // hero names
        std::vector < std::string > enemies;         // enemy names
        std::vector < std::string > battleLog;
        std::vector < QNS > Q;
        std::map < std::string, Avenger > Name_Avenger;          // Name to avenger mapping
        int suit_avai;
        int k = 0;         // no of suits;
    public:
        Battle() {}
        ~Battle() {}
        void addSuit (QNS& suit);
        void addHero (std::string& name);
        void addEnemy (std::string& name);
        void addAvenger (std::string& name, Avenger& avenger);
        void startBattle();
        void Attack (std::string& avenger1, std::string& avenger2);
        void Repair (std::string& name, int x);
        void BoostPowerByFactor (std::string& name, int y);
        void BoostPower (std::string& name, QNS& suit);
        void Upgrade (std::string& name);
        void printBattleLog();
        int Result();
        QNS& getSuit(int i)
        {
            return Q[i];
        }
};

void Battle :: addSuit (QNS& suit)
{
    Q.push_back(suit);
    k++;
}

void Battle :: addHero (std::string& name)
{
    heroes.push_back(name);
}

void Battle :: addEnemy (std::string& name)
{
    enemies.push_back(name);
}       

void Battle :: addAvenger (std::string& name, Avenger& avenger)
{
    Name_Avenger[name] = avenger;
}

void Battle :: startBattle()
{   
    suit_avai = heroes.size() + enemies.size();          // no of suits given already
    std::string s;
    while (true)
    {
        std::cin >> s;
        if (s == "End")
        {
            return;
        }
        else if (s == "Attack")
        {
            std::string avenger1,avenger2;
            std::cin >> avenger1 >> avenger2;
            Attack(avenger1, avenger2);
        }
        else if (s == "Repair")
        {
            std::string name;
            int x;
            std::cin >> name >> x;
            Repair(name,x);
        }
        else if (s == "BoostPowerByFactor")
        {
            std::string name;
            int y;
            std::cin >> name >> y;
            BoostPowerByFactor(name,y);
        }
        else if (s == "BoostPower")
        {
            std::string name;
            int p,d,e,h;
            std::cin >> p >> d >> e >> h;
            QNS suit(p,d,e,h);
            BoostPower(name, suit);
        }
        else if (s == "AvengerStatus")
        {
            std::string name;
            std::cin >> name;
            auto ptr = Name_Avenger.find(name);
            if(ptr != Name_Avenger.end())
            {
                ptr -> second.printStatus();
            }
        }
        else if (s == "Upgrade")
        {
            std::string name;
            std::cin >> name;
            Upgrade(name);
        }
        else if (s == "PrintBattleLog")
        {
            printBattleLog();
        }
        else if (s == "BattleStatus")
        {
            if (Result() == 1)
            {
                std::cout << "heroes are winning \n";
            }
            else if (Result() == -1)
            {
                std::cout << "enemies are winning \n";
            }
            else if (Result() == 0)
            {
                std::cout << "tie \n";
            }
        }
    }
}

void Battle :: Attack (std::string& avenger1, std::string& avenger2)
{
    auto ptr1 = Name_Avenger.find(avenger1);
    auto ptr2 = Name_Avenger.find(avenger2);
    if (ptr1 != Name_Avenger.end() && ptr2 != Name_Avenger.end())
    {    
        if (ptr1 -> second.getSuit().getD() > 0 && ptr1 -> second.getSuit().getH() <= 500)
        {
            if (ptr2 -> second.getSuit().getD() > 0)
            {
                ptr1 -> second.attack(ptr2 -> second);
                battleLog.push_back(avenger1 + " attacks " + avenger2);
                if(ptr2->second.getSuit().getD() <= 0)
                {
                    battleLog.push_back(avenger2 + " suit destroyed");
                    //if(suit_avai<k)                 // if there is an available suit we can give the suit to avenger
                    //ptr2->second.upgradeSuit(Q[suit_avai]);
                }
                else if (ptr2 -> second.getSuit().getH() > 500)
                {
                    battleLog.push_back(avenger2 + " suit overheated");
                }
            }
        }
    }
}

void Battle :: Repair (std::string& name, int x)
{
    auto ptr = Name_Avenger.find(name);
    if (ptr != Name_Avenger.end() && ptr -> second.getSuit().getD() > 0)
    {
        ptr -> second.repair(x);
        battleLog.push_back(name + " repaired");
    }
}

void Battle :: BoostPowerByFactor (std::string& name, int y)
{
    auto ptr = Name_Avenger.find(name);
    if (ptr != Name_Avenger.end() && ptr -> second.getSuit().getD() > 0){
        ptr -> second.avengersuitboost(y);
        battleLog.push_back(name + " boosted");
        if (ptr->second.getSuit().getH() > 500)
        {
            battleLog.push_back(name + " suit overheated");
        }
    }
}

void Battle :: BoostPower (std::string& name, QNS& suit)
{
    auto ptr = Name_Avenger.find(name);
    if (ptr != Name_Avenger.end() && ptr -> second.getSuit().getD() > 0)
    {
        ptr -> second.avengersuitboost(suit);
        battleLog.push_back(name + " boosted");
        if (ptr -> second.getSuit().getH() > 500)
        {
            battleLog.push_back(name + " suit overheated");
        }
    }
}

void Battle :: Upgrade (std::string& name)
{
    auto ptr = Name_Avenger.find(name);
    if (ptr != Name_Avenger.end() && ptr -> second.getSuit().getD() > 0)
    {
        if (suit_avai < k)
        {
            ptr -> second.upgradeSuit(Q[suit_avai]);
            suit_avai++;
            battleLog.push_back(name + " upgraded");
        }
        else battleLog.push_back(name + " upgrade Fail");
    }
}

void Battle :: printBattleLog()
{
    for (auto v: battleLog)
    {
        std::cout << v << "\n";
    }
}

int Battle :: Result()
{
    int hero = 0, enemy = 0;
    for (auto x: heroes){
        auto ptr = Name_Avenger.find(x);
        if (ptr != Name_Avenger.end() && ptr -> second.getSuit().getD() > 0)
            hero += ptr -> second.getSuit().getP() + ptr -> second.getSuit().getD();
    }
    for (auto y: enemies)
    {
        auto ptr = Name_Avenger.find(y);
        if (ptr != Name_Avenger.end() && ptr -> second.getSuit().getD() > 0)
            enemy += ptr -> second.getSuit().getP() + ptr -> second.getSuit().getD();
    }
    if (hero > enemy)
    {
        return 1;
    }
    else if (hero < enemy)
    {
        return -1;
    }
    else return 0;
}