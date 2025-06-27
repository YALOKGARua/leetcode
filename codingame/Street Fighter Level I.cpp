#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct ChampionStats {
    int life, punch, kick;
    string name;
};

class Fighter {
public:
    ChampionStats stats;
    int currentLife;
    int rage;
    int hitsMade;
    int damageReceived;
    
    Fighter(const string& name) : rage(0), hitsMade(0), damageReceived(0) {
        map<string, ChampionStats> champStats = {
            {"KEN", {25, 6, 5, "KEN"}},
            {"RYU", {25, 4, 5, "RYU"}},
            {"TANK", {50, 2, 2, "TANK"}},
            {"VLAD", {30, 3, 3, "VLAD"}},
            {"JADE", {20, 2, 7, "JADE"}},
            {"ANNA", {18, 9, 1, "ANNA"}},
            {"JUN", {60, 2, 1, "JUN"}}
        };
        
        stats = champStats[name];
        currentLife = stats.life;
    }
    
    int calculateSpecialDamage(Fighter& opponent) {
        if (stats.name == "KEN") return 3 * rage;
        if (stats.name == "RYU") return 4 * rage;
        if (stats.name == "TANK") return 2 * rage;
        if (stats.name == "VLAD") {
            int damage = 2 * (rage + opponent.rage);
            opponent.rage = 0;
            return damage;
        }
        if (stats.name == "JADE") return hitsMade * rage;
        if (stats.name == "ANNA") return damageReceived * rage;
        if (stats.name == "JUN") {
            int damage = rage;
            currentLife += rage;
            return damage;
        }
        return 0;
    }
    
    void attack(Fighter& opponent, const string& attackType) {
        int damage = 0;
        
        if (attackType == "PUNCH") {
            damage = stats.punch;
        } else if (attackType == "KICK") {
            damage = stats.kick;
        } else if (attackType == "SPECIAL") {
            damage = calculateSpecialDamage(opponent);
            rage = 0;
        }
        
        opponent.takeDamage(damage);
        hitsMade++;
    }
    
    void takeDamage(int damage) {
        currentLife -= damage;
        damageReceived += damage;
        rage++;
    }
    
    bool isAlive() const {
        return currentLife > 0;
    }
};

int main() {
    string champion1Name, champion2Name;
    cin >> champion1Name >> champion2Name;
    cin.ignore();
    
    int n;
    cin >> n;
    cin.ignore();
    
    Fighter fighter1(champion1Name);
    Fighter fighter2(champion2Name);
    
    for (int i = 0; i < n; i++) {
        string direction, attack;
        cin >> direction >> attack;
        cin.ignore();
        
        if (direction == ">") {
            fighter1.attack(fighter2, attack);
        } else {
            fighter2.attack(fighter1, attack);
        }
        
        if (!fighter1.isAlive() || !fighter2.isAlive()) {
            break;
        }
    }
    
    string winner, loser;
    int winnerHits;
    
    if (!fighter1.isAlive() || (fighter1.isAlive() && fighter2.isAlive() && fighter2.currentLife > fighter1.currentLife)) {
        winner = fighter2.stats.name;
        loser = fighter1.stats.name;
        winnerHits = fighter2.hitsMade;
    } else {
        winner = fighter1.stats.name;
        loser = fighter2.stats.name;
        winnerHits = fighter1.hitsMade;
    }
    
    cout << winner << " beats " << loser << " in " << winnerHits << " hits" << endl;
    
    return 0;
}
