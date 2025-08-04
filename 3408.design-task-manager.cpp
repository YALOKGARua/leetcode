class TaskManager {
private:
    struct Task {
        int userId;
        int taskId;
        int priority;
        
        Task(int u, int t, int p) : userId(u), taskId(t), priority(p) {}
        
        bool operator<(const Task& other) const {
            if (priority != other.priority) {
                return priority < other.priority;
            }
            return taskId < other.taskId;
        }
    };
    
    priority_queue<Task> pq;
    unordered_map<int, pair<int, int>> taskMap; // taskId -> {userId, priority}
    
public:
    TaskManager(vector<vector<int>>& tasks) {
        for (const auto& task : tasks) {
            int userId = task[0];
            int taskId = task[1];
            int priority = task[2];
            
            taskMap[taskId] = {userId, priority};
            pq.push(Task(userId, taskId, priority));
        }
    }
    
    void add(int userId, int taskId, int priority) {
        taskMap[taskId] = {userId, priority};
        pq.push(Task(userId, taskId, priority));
    }
    
    void edit(int taskId, int newPriority) {
        taskMap[taskId].second = newPriority;
        pq.push(Task(taskMap[taskId].first, taskId, newPriority));
    }
    
    void rmv(int taskId) {
        taskMap.erase(taskId);
    }
    
    int execTop() {
        while (!pq.empty()) {
            Task top = pq.top();
            pq.pop();
            
            auto it = taskMap.find(top.taskId);
            if (it != taskMap.end() && it->second.second == top.priority) {
                int userId = it->second.first;
                taskMap.erase(it);
                return userId;
            }
        }
        return -1;
    }
}; 