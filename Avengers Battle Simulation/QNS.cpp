class QNS              // Quantum Nanotech suit 
{
    private:
        int P,D,E,H;   // P -> PowerLevel, D -> Durability, E -> EnergyStorage, H -> HeatLevel 
    public:
        QNS()
        {
            P=1000;                    // Default QNS
            D=500;          
            E=300;
            H=0;
        }
        QNS (int powerLevel, int durability, int energyStorage, int heatLevel)         // custamisable QNS
        {
            P = powerLevel;   
            D = durability;
            E = energyStorage;
            H = heatLevel;
            if (P>5000)
            {                                                              // MaxPower Level =  5000  
                P=5000;
            }
            if (H < 0)
            {
                H = 0;
            }
        }
        QNS(const QNS& suit)           // copy constructor
        {
            P = suit.P;
            D = suit.D;
            E = suit.E;
            H = suit.H;
            if (P > 5000)
            {
                P = 5000;
            }
            if (H < 0)
            {
                H = 0;
            }
        }
        ~QNS(){}
        void operator + (QNS& suit);
        void operator - (int X);
        void operator * (int X);
        void operator / (int X);
        void boostPower (int factor);
        void boostPower(QNS& otherSuit);
        bool operator == (QNS& suit);
        bool operator < (QNS& suit);
        void print();
        int getD()         // Durability
        {
            return D;
        }
        int getH()         // HeatLevel
        {
            return H;
        }
        int getP()         // PowerLevel
        {
            return P;
        }
};

void QNS :: operator + (QNS& suit)
{
    P += suit.E;
    if (P > 5000)
        P = 5000;
    D += suit.D;
    E += suit.P;
    // return *this 
}

void QNS :: operator - (int X)
{
    D -= X;
    E += X;
    H += X;
    if (H < 0)
    {
        H = 0;
    }
    //return *this;
    //if d < 0 destroy suit
}

void QNS :: operator * (int X)
{
    P += (P*X)/100;
    if (P > 5000)
        P = 5000;
    E += 5*X;
    H += X;
    if (H < 0)
    {
        H=0;
    }
    //return *this;
    // if h>500 overheat
}

void QNS :: operator / (int X)
{
    D += X;
    H -= X;
    if (H < 0)
        H=0;
    //return *this;
}

void QNS :: boostPower (int factor)
{
    *this*factor;
    // if h>500 overheat
}

void QNS :: boostPower(QNS& otherSuit)
{
    *this + otherSuit;
}

bool QNS :: operator == (QNS& suit)
{
    return (P == suit.P && D == suit.D);
}  

bool QNS :: operator < (QNS& suit)
{
    return ((P + D) < (suit.P + suit.D));
}

void QNS :: print()
{
    std::cout << P << " " << D << " " << E << " " << H << "\n";
}