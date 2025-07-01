#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

using namespace std;

enum class ScoringMethod {
    SINGLE_PIN,
    MULTIPLE_PINS
};

struct ScoringOption {
    int points;
    ScoringMethod method;
    
    ScoringOption(int p, ScoringMethod m) : points(p), method(m) {}
};

class MolkkyScoring {
private:
    static constexpr int MIN_SCORE_PER_ROUND = 1;
    static constexpr int MAX_SCORE_PER_ROUND = 12;
    static constexpr int TARGET_SCORE = 50;
    static constexpr int MAX_ROUNDS = 4;

public:
    static vector<ScoringOption> generateScoringOptions() {
        vector<ScoringOption> options;
        options.reserve(23);
        
        options.emplace_back(1, ScoringMethod::SINGLE_PIN);
        
        for (int points = 2; points <= MAX_SCORE_PER_ROUND; points++) {
            options.emplace_back(points, ScoringMethod::SINGLE_PIN);
            options.emplace_back(points, ScoringMethod::MULTIPLE_PINS);
        }
        
        return options;
    }
    
    static bool isValidScore(int score) {
        return score >= MIN_SCORE_PER_ROUND && score <= MAX_SCORE_PER_ROUND;
    }
    
    static int getTargetScore() { return TARGET_SCORE; }
    static int getMaxRounds() { return MAX_ROUNDS; }
};

class GameState {
private:
    int currentScore;
    int remainingRounds;
    
public:
    GameState(int score, int rounds) : currentScore(score), remainingRounds(rounds) {}
    
    int getCurrentScore() const { return currentScore; }
    int getRemainingRounds() const { return remainingRounds; }
    
    bool isTargetReached() const {
        return currentScore == MolkkyScoring::getTargetScore();
    }
    
    bool isGameOver() const {
        return currentScore > MolkkyScoring::getTargetScore() || remainingRounds == 0;
    }
    
    GameState makeMove(const ScoringOption& option) const {
        return GameState(currentScore + option.points, remainingRounds - 1);
    }
    
    long long getStateHash() const {
        return static_cast<long long>(currentScore) * 100 + remainingRounds;
    }
};

class MemoizationCache {
private:
    unordered_map<long long, long long> cache;
    
public:
    bool hasResult(const GameState& state) const {
        return cache.find(state.getStateHash()) != cache.end();
    }
    
    long long getResult(const GameState& state) const {
        auto it = cache.find(state.getStateHash());
        return (it != cache.end()) ? it->second : 0;
    }
    
    void storeResult(const GameState& state, long long result) {
        cache[state.getStateHash()] = result;
    }
    
    void clear() {
        cache.clear();
    }
    
    size_t size() const {
        return cache.size();
    }
};

class CombinationCounter {
private:
    MemoizationCache cache;
    vector<ScoringOption> scoringOptions;
    
    long long countWaysRecursive(const GameState& state) {
        if (state.isTargetReached()) {
            return 1;
        }
        
        if (state.isGameOver()) {
            return 0;
        }
        
        if (cache.hasResult(state)) {
            return cache.getResult(state);
        }
        
        long long totalWays = 0;
        for (const ScoringOption& option : scoringOptions) {
            GameState nextState = state.makeMove(option);
            totalWays += countWaysRecursive(nextState);
        }
        
        cache.storeResult(state, totalWays);
        return totalWays;
    }
    
public:
    CombinationCounter() : scoringOptions(MolkkyScoring::generateScoringOptions()) {}
    
    long long calculateWaysToWin(int initialScore) {
        cache.clear();
        GameState initialState(initialScore, MolkkyScoring::getMaxRounds());
        return countWaysRecursive(initialState);
    }
    
    size_t getCacheSize() const {
        return cache.size();
    }
};

class MolkkyGameAnalyzer {
private:
    unique_ptr<CombinationCounter> counter;
    
public:
    MolkkyGameAnalyzer() : counter(make_unique<CombinationCounter>()) {}
    
    long long analyzeWinningPossibilities(int startingScore) {
        validateInput(startingScore);
        return counter->calculateWaysToWin(startingScore);
    }
    
private:
    void validateInput(int score) const {
        if (score < 0 || score >= MolkkyScoring::getTargetScore()) {
            throw invalid_argument("Invalid starting score");
        }
    }
};

class InputOutputProcessor {
public:
    static int readInitialScore() {
        int score;
        cin >> score;
        return score;
    }
    
    static void outputResult(long long result) {
        cout << result << endl;
    }
};

class MolkkyApplication {
private:
    MolkkyGameAnalyzer analyzer;
    
public:
    void run() {
        try {
            int initialScore = InputOutputProcessor::readInitialScore();
            long long possibilities = analyzer.analyzeWinningPossibilities(initialScore);
            InputOutputProcessor::outputResult(possibilities);
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};

int main() {
    MolkkyApplication app;
    app.run();
    
    return 0;
}
