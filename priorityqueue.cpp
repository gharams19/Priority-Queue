//
// Created by Gharam Alsaedi on 2019-11-12.
//

#include "priorityqueue.h"
#include <iostream>
#include "json.hpp"


PriorityQueue::PriorityQueue(std::size_t max_size) :
        nodes_(max_size + 1, KeyValuePair()),
        max_size_(max_size),
        size_(0) {
}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
    size_++;
    nodes_[size_] = kv;
    heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
    return nodes_[ROOT];
}

KeyValuePair PriorityQueue::removeMin() {
    KeyValuePair min = nodes_[ROOT];
    removeNode(ROOT);

    return min;
}

bool PriorityQueue::isEmpty() const {
    return size_ == 0;
}

size_t PriorityQueue::size() const {
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
    nlohmann::json result;
    for (size_t i = 1; i <= size_; i++) {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(i / 2);
        }
        if (2 * i <= size_) {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_) {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    return result;
}

bool PriorityQueue::IsInBounds(size_t i) {
    return i <= size_;
}

size_t PriorityQueue::rightChild(size_t i) {
    return 2 * i + 1;
}

size_t PriorityQueue::leftChild(size_t i) {
    return 2 * i;
}

size_t PriorityQueue::Parent(size_t i) {
    return i / 2;
}

Key PriorityQueue::getKey(size_t i) {
    return nodes_[i].first;
}


void PriorityQueue::heapifyUp(size_t i) {
    while (i > 1 && nodes_[i].first < nodes_[Parent(i)].first) {
        std::swap(nodes_[i], nodes_[Parent(i)]);
        i = Parent(i);
    }
}

void PriorityQueue::heapifyDown(size_t i) {

    while (IsInBounds(leftChild(i))) {
        size_t child = leftChild(i);
        if (IsInBounds(rightChild(i)) && nodes_[rightChild(i)].first < nodes_[leftChild(i)].first)
            child = rightChild(i);
        if (nodes_[child].first < nodes_[i].first ||
            (nodes_[i].first == 0 && nodes_[i].second == std::make_pair(0, 0))) {
            std::swap(nodes_[child], nodes_[i]);
        } else {
            break;
        }
        i = child;
    }
}

void PriorityQueue::removeNode(size_t i) {
    std::swap(nodes_[i], nodes_[nodes_.size() - 1]);
    nodes_.pop_back();
    heapifyDown(i);
    size_--;
}



