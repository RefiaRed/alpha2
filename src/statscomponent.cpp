#include "statscomponent.hpp"


StatsComponent::StatsComponent(int level, std::random_device& rd) {
    std::uniform_int_distribution<int> distLow(1,3);
    this->level = level;
    this->exp = 0;
    this->expNext = (this->level) * log10((this->level) + 10);
    this->heals = 3;

    this->health = distLow(rd);
    this->strength = distLow(rd);
    this->speed = distLow(rd);


    hpMax  = (this->health * 6) + this->health;
    hp = this->hpMax;
    atk    = this->strength + (this->strength /2);
    def    = this->strength;

}

StatsComponent::~StatsComponent() {


}

void StatsComponent::updateStats() {
    int newHealth;
    int newStrength;
    int newSpeed;

    newHealth = this->health + this->level;
    newStrength = this->strength + this->level;
    newSpeed = this->speed + this->level;

    this->health = newHealth;
    this->strength = newStrength;
    this->speed = newSpeed;

    this->hpMax  = (this->health * 6) + this->health;
    this->atk    = this->strength + (this->strength /2);
    this->def    = this->strength;

}

void StatsComponent::calculateExpNext() {
    this->expNext = (this->level) * log10((this->level) + 10);
}

void StatsComponent::levelUp() {
    while (this->exp >= this->expNext){
        ++this->level;
        this->exp -= this->expNext;
        this->calculateExpNext();
        this->updateStats();
    }
}

void StatsComponent::gainExp(const int xp) {
    this->exp = this->exp + xp;
    this->levelUp();
}

std::string StatsComponent::debugPrint() const {

    std::stringstream ss;
    ss << "Lv:" <<this->level <<"   " << "XP: " <<this->exp <<"\n"
            << "++++++++++++++++++++++++" <<"\n"
            << "HPMax: " <<this->hpMax <<"\n"
            << "HP: " <<this->hp <<"   "<< "Heals: " <<this->heals <<"\n"
            << "ATK: " <<this->atk <<"   "<< "DEF: " <<this->def <<"\n"
            << "++++++++++++++++++++++++" <<"\n"
            << "++++++++++++++++++++++++" <<"\n";

    return ss.str();
}

//Actions
void StatsComponent::attack(Entity* target) {
    if(target->statsComponent->def < this->atk){
    target->statsComponent->hp = target->statsComponent->hp + (target->statsComponent->def - this->atk);
    }
    else
        --target->statsComponent->hp;

    if(target->statsComponent->hp < 0)
        target->statsComponent->hp = 0;
}

void StatsComponent::heal() {
        this->hp = this->hpMax;
        --this->heals;


}

void StatsComponent::rollNewStats(std::random_device& rd){
    std::uniform_int_distribution<int> distLow(1,3);
    this->level = level;
    this->exp = 0;
    this->expNext = (this->level) * log10((this->level) + 10);
    this->heals = 3;

    this->health = 1;
    this->strength = 1;
    this->speed = 1;

    this->health = distLow(rd);
    this->strength = distLow(rd);
    this->speed = distLow(rd);


    hpMax  = (this->health * 6) + this->health;
    hp = this->hpMax;
    atk    = this->strength + (this->strength /2);
    def    = this->strength;
}



