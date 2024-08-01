#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <vector>

extern "C" {
    int FCFS(const int* requests, int n, int starting_head) {
        int total_distance = 0;
        int current_head = starting_head;

        for (int i = 0; i < n; ++i) {
            total_distance += std::abs(current_head - requests[i]);
            current_head = requests[i];
        }

        return total_distance;
    }

    int SSTF(const int* requests, int n, int starting_head) {
        std::map<int, int> req_map;
        for (int i = 0; i < n; ++i) {
            req_map[requests[i]] = i;
        }
        req_map[starting_head] = -1;

        int total_distance = 0;
        int current = starting_head;
        while (req_map.size() > 1) {
            auto current_head = req_map.find(current);
            if (current_head == req_map.begin()) {
                total_distance += std::abs(current_head->first - std::next(current_head)->first);
                current = std::next(current_head)->first;
            } else if (std::next(current_head) == req_map.end()) {
                total_distance += std::abs(current_head->first - std::prev(current_head)->first);
                current = std::prev(current_head)->first;
            } else {
                int dist_left = std::abs(current_head->first - std::prev(current_head)->first);
                int dist_right = std::abs(current_head->first - std::next(current_head)->first);

                if (dist_left < dist_right) {
                    total_distance += dist_left;
                    current = std::prev(current_head)->first;
                } else if (dist_right < dist_left) {
                    total_distance += dist_right;
                    current = std::next(current_head)->first;
                } else {
                    if (std::prev(current_head)->second < std::next(current_head)->second) {
                        total_distance += dist_left;
                        current = std::prev(current_head)->first;
                    } else {
                        total_distance += dist_right;
                        current = std::next(current_head)->first;
                    }
                }
            }
            req_map.erase(current_head);
        }
        return total_distance;
    }

    int SCAN(const int* requests, int n, int starting_head, int cylinders) {
        std::set<int> st(requests, requests + n);
        st.insert(cylinders - 1);
        st.insert(starting_head);

        int current = starting_head;
        int total_distance = 0;
        while (current != *st.rbegin()) {
            auto current_head = st.find(current);
            total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
        }

        current = *st.rbegin();
        while (st.size() > 1) {
            auto current_head = st.find(current);
            total_distance += current - *std::prev(current_head);
            current = *std::prev(current_head);
            st.erase(current_head);
        }
        return total_distance;
    }

    int LOOK(const int* requests, int n, int starting_head) {
        std::set<int> st(requests, requests + n);
        st.insert(starting_head);

        int current = starting_head;
        int total_distance = 0;
        while (current != *st.rbegin()) {
            auto current_head = st.find(current);
            total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
        }

        current = *st.rbegin();
        while (st.size() > 1) {
            auto current_head = st.find(current);
            total_distance += current - *std::prev(current_head);
            current = *std::prev(current_head);
            st.erase(current_head);
        }
        return total_distance;
    }

    int C_SCAN(const int* requests, int n, int starting_head, int cylinders) {
        std::set<int> st(requests, requests + n);
        st.insert(cylinders - 1);
        st.insert(0);
        st.insert(starting_head);

        int current = starting_head;
        int total_distance = 0;
        while (current != *st.rbegin()) {
            auto current_head = st.find(current);
            total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
        }

        total_distance += current - *st.begin();
        st.erase(current);

        current = *st.begin();
        while (st.size() > 1) {
            auto current_head = st.find(current);
            total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
        }
        return total_distance;
    }

    int C_LOOK(const int* requests, int n, int starting_head) {
        std::set<int> st(requests, requests + n);
        st.insert(starting_head);

        int current = starting_head;
        int total_distance = 0;
        while (current != *st.rbegin()) {
            auto current_head = st.find(current);
            total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
        }

        total_distance += current - *st.begin();
        st.erase(current);

        current = *st.begin();
        while (st.size() > 1) {
            auto current_head = st.find(current);
            total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
        }
        return total_distance;
    }
}

