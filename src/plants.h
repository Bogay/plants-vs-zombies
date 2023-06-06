#ifndef PLANTS_H
#define PLANTS_H


#include <string>
#include <iostream>
class Game;

class Plants{

    public:

        static void set_gameref(Game &g);

    	virtual void set_name(string s){};
    	virtual void set_max_hp(int i){};
        virtual void set_price(int i){};

    	virtual string get_name()const{};
    	virtual int get_max_hp()const{};
        virtual int get_price()const{};

        virtual void player_visit(Player &p){};
        virtual bool zombie_visit(Zombie &z){};// return true represent this plant dead
        virtual void healed(){};

        int get_cur_hp()const{return cur_hp;}
		
		
    protected:
        int cur_hp=0;
        static Game *g;
    private:
};


class CoinPlant: public Plants{
    CoinPlant():cur_hp(max_hp){};
    public:
        virtual void set_name(string s) override;
    	virtual void set_max_hp(int i) override;
        virtual void set_price(int i) override;

    	virtual string get_name()const override;
    	virtual int get_max_hp()const override;
        virtual int get_price()const override;

        virtual void player_visit(Player &p) override;
        virtual bool zombie_visit(Zombie &z) override;
        virtual void healed() override;

        void set_each_round(int i);
        void set_earn_money(int i);


    private:
        static int each_round_visit;
        static int earn_money;
    	static string name;
    	static int max_hp;
    	static int price;

    	int cur_visit=0;
};


class HornPlant: public Plants{

    HornPlant():cur_hp(max_hp){};
    public:
        virtual void set_name(string s) override;
    	virtual void set_max_hp(int i) override;
        virtual void set_price(int i) override;

    	virtual string get_name()const override;
    	virtual int get_max_hp()const override;
        virtual int get_price()const override;

        virtual void player_visit(Player &p) override;
        virtual bool zombie_visit(Zombie &z) override;
        virtual void healed() override;

        void set_atk(int i);


    private:
        static int atk;
    	static string name;
    	static int max_hp;
    	static int price;
};


class BombPlant: public Plants{

    BombPlant():cur_hp(max_hp){};
    public:
        virtual void set_name(string s) override;
    	virtual void set_max_hp(int i) override;
        virtual void set_price(int i) override;

    	virtual string get_name()const override;
    	virtual int get_max_hp()const override;
        virtual int get_price()const override;

        virtual void player_visit(Player &p) override;
        virtual bool zombie_visit(Zombie &z) override;
        virtual void healed() override;

    private:
    	static string name;
    	static int max_hp;
    	static int price;

};


class HealPlant: public Plants{

    HealPlant():cur_hp(max_hp){};
    public:
        virtual void set_name(string s) override;
    	virtual void set_max_hp(int i) override;
        virtual void set_price(int i) override;

    	virtual string get_name()const override;
    	virtual int get_max_hp()const override;
        virtual int get_price()const override;

        virtual void player_visit(Player &p) override;
        virtual bool zombie_visit(Zombie &z) override;
        virtual void healed() override;

        void set_heal_point(int i);

    private:
        static int heal_point;
    	static string name;
    	static int max_hp;
    	static int price;
};

std::ostream &operator << (std::ostream,const Plants&);

#endif // PLANTS_H
