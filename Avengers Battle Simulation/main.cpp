#include "Battle.cpp"

int main()
{
    Battle B;
    int k,n,m;      // k -> no of suits, n -> no of heroes, m -> no of enemies
    std::cin >> k >> n >> m;
    assert( k > 0 && n > 0 && m > 0 );
    int p,d,e,h;
    for (int i = 0 ; i < k ; i++ )
    {
        std::cin >> p >> d >> e >> h;
        QNS suit(p,d,e,h);
        B.addSuit(suit);
    }
    std::string name;
    int attackstrength;
    for (int i = 0 ; i < n + m ; i++ )
    {
        std::cin >> name >> attackstrength;
        if (i >= k)
        {
            std::cout << name << " is out of fight \n";         // as no of suits are less 
        }
        else 
        {   
            Avenger avenger(name,B.getSuit(i),attackstrength);
            if (i < n)
                B.addHero(name);
            else B.addEnemy(name);
            B.addAvenger(name, avenger);
        }
    }
    std::string s;
    std::cin >> s;
    if(s == "BattleBegin")
        B.startBattle(); 
}