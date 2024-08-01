#include <iostream>
#include <queue>
#include <set>
#include <map>

void init() {
#ifdef BARAA
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

int FCFS(std::queue<int> q, const int &STARTING_HEAD) { // Time Complexity: O(n)
    int total_distance = 0;
    int current_head = STARTING_HEAD;

    while (!q.empty()) {
        total_distance += abs(current_head - q.front());
        current_head = q.front();
        q.pop();
    }

    return total_distance;
}

int SSTF(std::map<int, int> req, const int &STARTING_HEAD) { // Time Complexity: O(n * log(n))
    req[STARTING_HEAD] = -1;

    int total_distance = 0;
    int current = STARTING_HEAD;
    while (req.size() > 1) {
        auto current_head = req.find(current);
        if (current_head == req.begin()) {
            total_distance += abs(current_head->first - next(current_head)->first);
            current = next(current_head)->first;
        } else if (next(current_head) == req.end()) {
            total_distance += abs(current_head->first - prev(current_head)->first);
            current = prev(current_head)->first;
        } else {
            int dist_left = abs(current_head->first - prev(current_head)->first);
            int dist_right = abs(current_head->first - next(current_head)->first);

            if (dist_left < dist_right) {
                total_distance += dist_left;
                current = prev(current_head)->first;
            } else if (dist_right < dist_left) {
                total_distance += dist_right;
                current = next(current_head)->first;
            } else {
                if (prev(current_head)->second < next(current_head)->second) {
                    total_distance += dist_left;
                    current = prev(current_head)->first;
                } else {
                    total_distance += dist_right;
                    current = next(current_head)->first;
                }
            }
        }
        req.erase(current_head);
    }
    return total_distance;
}

int SCAN(std::set<int> st, const int &STARTING_HEAD, const int &CYLINDERS) { // Time Complexity: O(n * log(n))
    st.insert(CYLINDERS - 1);
    st.insert(STARTING_HEAD);

    int current = STARTING_HEAD;
    int total_distance = 0;
    while (current != *st.rbegin()) {
        auto current_head = st.find(current);
        total_distance += *next(current_head) - current;
        current = *next(current_head);
        st.erase(current_head);
    }

    current = *st.rbegin();
    while (st.size() > 1) {
        auto current_head = st.find(current);
        total_distance += current - *prev(current_head);
        current = *prev(current_head);
        st.erase(current_head);
    }
    return total_distance;
}

int LOOK(std::set<int> st, const int &STARTING_HEAD) { // Time Complexity: O(n * log(n))
    st.insert(STARTING_HEAD);

    int current = STARTING_HEAD;
    int total_distance = 0;
    while (current != *st.rbegin()) {
        auto current_head = st.find(current);
        total_distance += *next(current_head) - current;
        current = *next(current_head);
        st.erase(current_head);
    }

    current = *st.rbegin();
    while (st.size() > 1) {
        auto current_head = st.find(current);
        total_distance += current - *prev(current_head);
        current = *prev(current_head);
        st.erase(current_head);
    }
    return total_distance;
}

int C_SCAN(std::set<int> st, const int &STARTING_HEAD, const int &CYLINDERS) { // Time Complexity: O(n * log(n))
    st.insert(CYLINDERS - 1);
    st.insert(0);
    st.insert(STARTING_HEAD);

    int current = STARTING_HEAD;
    int total_distance = 0;
    while (current != *st.rbegin()) {
        auto current_head = st.find(current);
        total_distance += *next(current_head) - current;
        current = *next(current_head);
        st.erase(current_head);
    }

    total_distance += current - *st.begin();
    st.erase(current);

    current = *st.begin();
    while (st.size() > 1) {
        auto current_head = st.find(current);
        total_distance += *next(current_head) - current;
        current = *next(current_head);
        st.erase(current_head);
    }
    return total_distance;
}

int C_LOOK(std::set<int> st, const int &STARTING_HEAD) { // Time Complexity: O(n * log(n))
    st.insert(STARTING_HEAD);

    int current = STARTING_HEAD;
    int total_distance = 0;
    while (current != *st.rbegin()) {
        auto current_head = st.find(current);
        total_distance += *next(current_head) - current;
        current = *next(current_head);
        st.erase(current_head);
    }

    total_distance += current - *st.begin();
    st.erase(current);

    current = *st.begin();
    while (st.size() > 1) {
        auto current_head = st.find(current);
        total_distance += *next(current_head) - current;
        current = *next(current_head);
        st.erase(current_head);
    }
    return total_distance;
}

signed main() {
    init();
    std::queue<int> q;
    std::set<int> st;
    std::map<int, int> requests;

    int n;
    std::cout << "Enter the number of requests: ";
    std::cin >> n;
    std::cout << "Enter the requests: ";
    for (int order = 1; order <= n; order++) {
        int x;
        std::cin >> x;
        q.push(x);
        st.insert(x);
        requests[x] = order;
    }

    int STARTING_HEAD, CYLINDERS;
    std::cout << "Enter the starting head: ";
    std::cin >> STARTING_HEAD;
    std::cout << "Enter the number of cylinders: ";
    std::cin >> CYLINDERS;


    std::cout << "FCFS: " << FCFS(q, STARTING_HEAD) << std::endl;
    std::cout << "SSTF: " << SSTF(requests, STARTING_HEAD) << std::endl;
    std::cout << "SCAN: " << SCAN(st, STARTING_HEAD, CYLINDERS) << std::endl;
    std::cout << "LOOK: " << LOOK(st, STARTING_HEAD) << std::endl;
    std::cout << "C-SCAN: " << C_SCAN(st, STARTING_HEAD, CYLINDERS) << std::endl;
    std::cout << "C-LOOK: " << C_LOOK(st, STARTING_HEAD) << std::endl;

    /*
        FCFS: 7081
        SSTF: 1745
        SCAN: 9769
        LOOK: 3319
        C-SCAN: 9985
        C-LOOK: 3363
    */
}

