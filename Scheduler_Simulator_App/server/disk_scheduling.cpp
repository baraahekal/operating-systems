#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <vector>
#include <cstring> 

extern "C" {
    struct Result {
        int total_distance;
        int* seek_sequence;
        int sequence_length;
    };

    void free_result(Result result) {
        delete[] result.seek_sequence;
    }

    Result FCFS(const int* requests, int num_requests, int starting_head) {
        Result result;
        result.total_distance = 0;
        int current_head = starting_head;
        std::vector<int> sequence;
        sequence.push_back(current_head);

        for (int i = 0; i < num_requests; ++i) {
            result.total_distance += std::abs(current_head - requests[i]);
            current_head = requests[i];
            sequence.push_back(current_head);
        }

        result.sequence_length = sequence.size();
        result.seek_sequence = new int[result.sequence_length];
        std::memcpy(result.seek_sequence, sequence.data(), result.sequence_length * sizeof(int));

        return result;
    }

    Result SSTF(const int* requests, int num_requests, int starting_head) {
        std::map<int, int> req_map;
        for (int i = 0; i < num_requests; ++i) {
            req_map[requests[i]] = i;
        }
        req_map[starting_head] = -1;

        Result result;
        result.total_distance = 0;
        int current = starting_head;
        std::vector<int> sequence;
        sequence.push_back(current);

        while (req_map.size() > 1) {
            std::map<int, int>::iterator current_head = req_map.find(current);
            if (current_head == req_map.begin()) {
                result.total_distance += std::abs(current_head->first - std::next(current_head)->first);
                current = std::next(current_head)->first;
            } else if (std::next(current_head) == req_map.end()) {
                result.total_distance += std::abs(current_head->first - std::prev(current_head)->first);
                current = std::prev(current_head)->first;
            } else {
                int dist_left = std::abs(current_head->first - std::prev(current_head)->first);
                int dist_right = std::abs(current_head->first - std::next(current_head)->first);

                if (dist_left < dist_right) {
                    result.total_distance += dist_left;
                    current = std::prev(current_head)->first;
                } else {
                    result.total_distance += dist_right;
                    current = std::next(current_head)->first;
                }
            }
            req_map.erase(current_head);
            sequence.push_back(current);
        }

        result.sequence_length = sequence.size();
        result.seek_sequence = new int[result.sequence_length];
        std::memcpy(result.seek_sequence, sequence.data(), result.sequence_length * sizeof(int));

        return result;
    }

    Result SCAN(const int* requests, int num_requests, int starting_head, int cylinders) {
        std::set<int> st(requests, requests + num_requests);
        st.insert(cylinders - 1);
        st.insert(starting_head);

        Result result;
        result.total_distance = 0;
        int current = starting_head;
        std::vector<int> sequence;
        sequence.push_back(current);

        while (current != *st.rbegin()) {
            std::set<int>::iterator current_head = st.find(current);
            result.total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
            sequence.push_back(current);
        }

        current = *st.rbegin();
        while (st.size() > 1) {
            std::set<int>::iterator current_head = st.find(current);
            result.total_distance += current - *std::prev(current_head);
            current = *std::prev(current_head);
            st.erase(current_head);
            sequence.push_back(current);
        }

        result.sequence_length = sequence.size();
        result.seek_sequence = new int[result.sequence_length];
        std::memcpy(result.seek_sequence, sequence.data(), result.sequence_length * sizeof(int));

        return result;
    }

    Result LOOK(const int* requests, int num_requests, int starting_head) {
        std::set<int> st(requests, requests + num_requests);
        st.insert(starting_head);

        Result result;
        result.total_distance = 0;
        int current = starting_head;
        std::vector<int> sequence;
        sequence.push_back(current);

        while (current != *st.rbegin()) {
            std::set<int>::iterator current_head = st.find(current);
            result.total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
            sequence.push_back(current);
        }

        current = *st.rbegin();
        while (st.size() > 1) {
            std::set<int>::iterator current_head = st.find(current);
            result.total_distance += current - *std::prev(current_head);
            current = *std::prev(current_head);
            st.erase(current_head);
            sequence.push_back(current);
        }

        result.sequence_length = sequence.size();
        result.seek_sequence = new int[result.sequence_length];
        std::memcpy(result.seek_sequence, sequence.data(), result.sequence_length * sizeof(int));

        return result;
    }

    Result C_SCAN(const int* requests, int num_requests, int starting_head, int cylinders) {
        std::set<int> st(requests, requests + num_requests);
        st.insert(cylinders - 1);
        st.insert(0);
        st.insert(starting_head);

        Result result;
        result.total_distance = 0;
        int current = starting_head;
        std::vector<int> sequence;
        sequence.push_back(current);

        while (current != *st.rbegin()) {
            std::set<int>::iterator current_head = st.find(current);
            result.total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
            sequence.push_back(current);
        }

        result.total_distance += current - *st.begin();
        st.erase(current);

        current = *st.begin();
        sequence.push_back(current);

        while (st.size() > 1) {
            std::set<int>::iterator current_head = st.find(current);
            result.total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
            sequence.push_back(current);
        }

        result.sequence_length = sequence.size();
        result.seek_sequence = new int[result.sequence_length];
        std::memcpy(result.seek_sequence, sequence.data(), result.sequence_length * sizeof(int));

        return result;
    }

    Result C_LOOK(const int* requests, int num_requests, int starting_head) {
        std::set<int> st(requests, requests + num_requests);
        st.insert(starting_head);

        Result result;
        result.total_distance = 0;
        int current = starting_head;
        std::vector<int> sequence;
        sequence.push_back(current);

        while (current != *st.rbegin()) {
            std::set<int>::iterator current_head = st.find(current);
            result.total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
            sequence.push_back(current);
        }

        result.total_distance += current - *st.begin();
        st.erase(current);

        current = *st.begin();
        sequence.push_back(current);

        while (st.size() > 1) {
            std::set<int>::iterator current_head = st.find(current);
            result.total_distance += *std::next(current_head) - current;
            current = *std::next(current_head);
            st.erase(current_head);
            sequence.push_back(current);
        }

        result.sequence_length = sequence.size();
        result.seek_sequence = new int[result.sequence_length];
        std::memcpy(result.seek_sequence, sequence.data(), result.sequence_length * sizeof(int));

        return result;
    }
}
