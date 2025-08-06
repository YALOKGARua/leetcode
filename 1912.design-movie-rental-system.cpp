class MovieRentingSystem {
private:
    struct pair_hash {
        template <class T1, class T2>
        size_t operator () (const pair<T1, T2>& p) const {
            auto h1 = hash<T1>{}(p.first);
            auto h2 = hash<T2>{}(p.second);
            return h1 ^ h2;
        }
    };
    
    unordered_map<int, set<pair<int, int>>> unrented;
    set<tuple<int, int, int>> rented;
    unordered_map<pair<int, int>, int, pair_hash> prices;

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto& entry : entries) {
            int shop = entry[0], movie = entry[1], price = entry[2];
            unrented[movie].insert({price, shop});
            prices[{shop, movie}] = price;
        }
    }
    
    vector<int> search(int movie) {
        vector<int> result;
        auto it = unrented[movie].begin();
        for (int i = 0; i < 5 && it != unrented[movie].end(); ++i, ++it) {
            result.push_back(it->second);
        }
        return result;
    }
    
    void rent(int shop, int movie) {
        int price = prices[{shop, movie}];
        unrented[movie].erase({price, shop});
        rented.insert({price, shop, movie});
    }
    
    void drop(int shop, int movie) {
        int price = prices[{shop, movie}];
        rented.erase({price, shop, movie});
        unrented[movie].insert({price, shop});
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> result;
        auto it = rented.begin();
        for (int i = 0; i < 5 && it != rented.end(); ++i, ++it) {
            result.push_back({get<1>(*it), get<2>(*it)});
        }
        return result;
    }
}; 