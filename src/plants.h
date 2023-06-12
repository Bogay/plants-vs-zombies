#ifndef PLANTS_H
#define PLANTS_H


#include <string>
#include <iostream>
class Game;
class Player;
class Zombie;

class Info{

    public:
        void set_info(std::string n,int m_hp,int p);

        std::string get_name()const{return name;}
        int get_max_hp()const{return max_hp;}
        int get_price()const{return price;}

    private:
        std::string name="plant";
        int max_hp=0;
        int price=0;
};




class Plants{
    friend std::ostream &operator<<(std::ostream &os,const Plants &p);
    public:

        static void set_game_ref(Game &game);

        virtual std::string get_name() const = 0;
        virtual void player_visit(Player &p){};
        virtual bool zombie_visit(Zombie &z) = 0;// return true represent this plant dead
        virtual void healed(int i){};

        int get_cur_hp()const{return cur_hp;}


    protected:
        int cur_hp=0;
        static Game *g;
    private:
};


class CoinPlant: public Plants{
    friend std::ostream &operator<<(std::ostream &os,const CoinPlant &c);
    public:
        CoinPlant();
        static void set_info(std::string name,int max_hp,int price);

        static Info get_info() ;

        virtual std::string get_name() const override;
        virtual void player_visit(Player &p) override;
        virtual bool zombie_visit(Zombie &z) override;
        virtual void healed(int i) override;

        static void set_each_round(int i);
        static void set_earn_money(int i);
        static void print_intro();


    private:
        static int each_round_visit;
        static int earn_money;
        static Info info;

        int cur_visit=0;
};


class HornPlant: public Plants{

    public:
        HornPlant();
        static void set_info(std::string name,int max_hp,int price);

        static Info get_info() ;

        virtual std::string get_name() const override;
        virtual void player_visit(Player &p) override;
        virtual bool zombie_visit(Zombie &z) override;
        virtual void healed(int i) override;

        static void set_atk(int i);
        static void print_intro();

    private:
        static int atk;
        static Info info;
};


class BombPlant: public Plants{

    public:
        BombPlant();
        static void set_info(std::string name,int max_hp,int price);

        static Info get_info() ;

        virtual std::string get_name() const override;
        virtual void player_visit(Player &p) override;
        virtual bool zombie_visit(Zombie &z) override;
        virtual void healed(int i) override;
        static void set_atk(int i);
        static void print_intro();

    private:
        static int atk;
        static Info info;
};


class HealPlant: public Plants{

    public:
        HealPlant();
        static void set_info(std::string name,int max_hp,int price);

        static Info get_info() ;

        virtual std::string get_name() const override;
        virtual void player_visit(Player &p) override;
        virtual bool zombie_visit(Zombie &z) override;
        virtual void healed(int i) override;

        static void set_heal_point(int i);
        
        static void print_intro();

    private:
        static int heal_point;
        static Info info;
};

std::ostream &operator<<(std::ostream &os,const CoinPlant &c);
std::ostream &operator<<(std::ostream &os, const Plants &p);

#endif // PLANTS_H