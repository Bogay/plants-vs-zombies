#include "plants.h"
#include "player.h"
#include "zombie.h"
//#include "game.h"

Game* Plants::g = nullptr;
int   CoinPlant::each_round_visit=0;
int   CoinPlant::earn_money=0;
Info  CoinPlant::info;
int   HornPlant::atk=0;
Info  HornPlant::info;
Info  BombPlant::info;
int   HealPlant::heal_point=0;
Info  HealPlant::info;

void Plants::set_game_ref(Game &game){
    g= &game;
}

void Info::set_info(std::string n, int m_hp, int p){
    name=n;
    max_hp=m_hp;
    price=p;
}

CoinPlant::CoinPlant(){
    cur_hp=CoinPlant::info.get_max_hp();
}

void CoinPlant::set_info(std::string name, int max_hp, int price){
    CoinPlant::info.set_info(name,max_hp,price);
}

Info CoinPlant::get_info()
{
    return CoinPlant::info;
}

std::string CoinPlant::get_name()const{
    return CoinPlant::info.get_name();
}

void CoinPlant::player_visit(Player &p){
    ++cur_visit;
    if(cur_visit==CoinPlant::each_round_visit){
        cur_visit=0;
        std::cout<<"You have earned $"<<CoinPlant::earn_money<<"! Now you have $"<<p.money()<<"."<<std::endl;
    }
    else{
        std::cout<<"You still need "<<CoinPlant::each_round_visit-cur_visit<<" visits to earn money."<<std::endl;
    }
}

bool CoinPlant::zombie_visit(Zombie &z){
    std::cout<<"Zombie eats plant "<<CoinPlant::info.get_name()<<" and causes damage "<<z.attack()<<"."<<std::endl;
    cur_hp-=z.attack();
    if(cur_hp<=0){
        std::cout<<"Plant "<<CoinPlant::info.get_name()<<" is dead!"<<std::endl;
        return true;
    }
    return false;
}

void CoinPlant::healed(int i){
    cur_hp+=i;
    if(cur_hp>=CoinPlant::info.get_max_hp()){
        cur_hp=CoinPlant::info.get_max_hp();
    }
}

void CoinPlant::set_each_round(int i){
    CoinPlant::each_round_visit=i;
}

void CoinPlant::set_earn_money(int i){
    CoinPlant::earn_money=i;
}

void CoinPlant::print_intro(){
    std::cout<<CoinPlant::info.get_name()<<" $"<<CoinPlant::info.get_price()<<" HP: "<<CoinPlant::info.get_max_hp()
            <<" - gives $"<<CoinPlant::earn_money<<" every "<<CoinPlant::each_round_visit<<" rounds"<<std::endl;
}

HornPlant::HornPlant(){
    cur_hp=HornPlant::info.get_max_hp();
}

void HornPlant::set_info(std::string name, int max_hp, int price){
    HornPlant::info.set_info(name,max_hp,price);
}

Info HornPlant::get_info(){
    return HornPlant::info;
}

std::string HornPlant::get_name()const{
    return HornPlant::info.get_name();
}

void HornPlant::player_visit(Player &p){
    std::cout<<"Your "<<HornPlant::info.get_name()<<" is guarding your land."<<std::endl;
}

bool HornPlant::zombie_visit(Zombie &z){
    std::cout<<HornPlant::info.get_name()<<" gives "<<HornPlant::atk<<" damage to the zombie!"<<std::endl;
    z.hurt(HornPlant::atk);
    if(z.hp()<=0){
        std::cout<<"Zombie is killed!"<<std::endl;
    }
    else{
        std::cout<<"Zombie eats plant "<<HornPlant::info.get_name()<<" and causes damage "<<z.attack()<<"."<<std::endl;
        cur_hp-=z.attack();
        if(cur_hp<=0){
            std::cout<<"Plant "<<HornPlant::info.get_name()<<" is dead!"<<std::endl;
            return true;
        }
        return false;
    }
    return false;
}

void HornPlant::healed(int i){
    cur_hp+=i;
    if(cur_hp>=HornPlant::info.get_max_hp()){
        cur_hp=HornPlant::info.get_max_hp();
    }
}

void HornPlant::set_atk(int i){
    HornPlant::atk=i;
}

void HornPlant::print_intro(){
    std::cout<<HornPlant::info.get_name()<<" $"<<HornPlant::info.get_price()<<" HP: "<<HornPlant::info.get_max_hp()
            <<" - gives $"<<HornPlant::atk<<" damage points"<<std::endl;
}

BombPlant::BombPlant(){
    cur_hp=BombPlant::info.get_max_hp();
}

void BombPlant::set_info(std::string name, int max_hp, int price){
    BombPlant::info.set_info(name,max_hp,price);
}

Info BombPlant::get_info(){
    return BombPlant::info;
}

std::string BombPlant::get_name()const{
    return BombPlant::info.get_name();
}

void BombPlant::player_visit(Player &p){
    std::cout<<"Your "<<BombPlant::info.get_name()<<" is guarding your land."<<std::endl;
}

bool BombPlant::zombie_visit(Zombie &z){
    std::cout<<BombPlant::info.get_name()<<" gives "<<BombPlant::info.get_max_hp()<<" damage to the zombie!"<<std::endl;
    z.hurt(BombPlant::info.get_max_hp());
    if(z.hp()<=0){
        std::cout<<"Zombie is killed!"<<std::endl;
    }
    std::cout<<"Plant "<<BombPlant::info.get_name()<<" is dead!"<<std::endl;
    return true;
}

void BombPlant::healed(int i){
    cur_hp+=i;
    if(cur_hp>=BombPlant::info.get_max_hp()){
        cur_hp=BombPlant::info.get_max_hp();
    }
}

void BombPlant::print_intro(){
    std::cout<<BombPlant::info.get_name()<<" $"<<BombPlant::info.get_price()<<" HP: "<<BombPlant::info.get_max_hp()
            <<" - gives $"<<BombPlant::info.get_max_hp()<<" damage points"<<std::endl;
}


HealPlant::HealPlant(){
    cur_hp=HealPlant::info.get_max_hp();
}

void HealPlant::set_info(std::string name, int max_hp, int price){
    HealPlant::info.set_info(name,max_hp,price);
}

Info HealPlant::get_info(){
    return HealPlant::info;
}

std::string HealPlant::get_name()const{
    return HealPlant::info.get_name();
}

//undone(I need to know how to store each plant in the class Game)
void HealPlant::player_visit(Player &p){
    std::cout<<"All your plants have recovered "<<HealPlant::heal_point<<" HP!"<<std::endl;
    
}

bool HealPlant::zombie_visit(Zombie &z){
    std::cout<<"Zombie eats plant "<<HealPlant::info.get_name()<<" and causes damage "<<z.attack()<<"."<<std::endl;
    cur_hp-=z.attack();
    if(cur_hp<=0){
        std::cout<<"Plant "<<HealPlant::info.get_name()<<" is dead!"<<std::endl;
        return true;
    }
    return false;
}

void HealPlant::healed(int i){
    cur_hp+=i;
    if(cur_hp>=HealPlant::info.get_max_hp()){
        cur_hp=HealPlant::info.get_max_hp();
    }
}

void HealPlant::set_heal_point(int i){
    HealPlant::heal_point=i;
}

void HealPlant::print_intro(){
    std::cout<<HealPlant::info.get_name()<<" $"<<HealPlant::info.get_price()<<" HP: "<<HealPlant::info.get_max_hp()
            <<" - gives all your plants "<<HealPlant::heal_point<<" HP back."<<std::endl;
}


std::ostream &operator<<(std::ostream &os,const CoinPlant &c){
    os<<c.get_name()<<" HP: "<<c.cur_hp<<" ("<<CoinPlant::each_round_visit-c.cur_visit<<" more visits)"<<std::endl;
    return os;
}
std::ostream &operator<<(std::ostream &os, const Plants &p){
    os<<p.get_name()<<" HP: "<<p.cur_hp<<std::endl;
    return os;
}