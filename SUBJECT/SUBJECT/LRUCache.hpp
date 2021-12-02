//
//  LRUCache.hpp
//  SUBJECT
//
//  Created by 晏榆 on 2021/12/2.
//

#ifndef LRUCache_hpp
#define LRUCache_hpp

#include <stdio.h>
#include <unordered_map>

class Node {
public:
    int key;
    int value;
    Node* previous;
    Node* next;
    Node() :key(0), value(0), previous(nullptr), next(nullptr){

    };
};

class LRUCache {
private:
    std::unordered_map<int, Node*> map;
    int max_num;
    int size;
    Node* head;
    Node* tail;

public:
    LRUCache(int capacity) {
        max_num = capacity;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->previous = head;
    }
    
    int get(int key) {
        if (map.find(key) != map.end()) {
            Node* node = map[key];
            // 移动该node到头部
            moveNodeToHead(node);
            return node->value;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            // 复写
            Node* node = map[key];
            node->value = value;
            // 移动该node到头部
            moveNodeToHead(node);
        } else {
            if (size == max_num) {
            // 淘汰尾部
            Node* last = removeTail();
            map.erase(last->key);
            delete last;
            size -- ;
            }

            Node* node = new Node();
            node->key = key;
            node->value = value;
            map[key] = node;
            // 加入node到头部
            addNodeToHead(node);
            size ++;
        }
    }

    // 把已存在的node移动到头部
    void moveNodeToHead(Node* node) {
        // 干掉当前节点
        node->previous->next = node->next;
        node->next->previous = node->previous;
        // 加到头部
        node->next = head->next;
        node->next->previous = node;
        node->previous = head;
        head->next = node;
    }

    // 干掉尾部节点
    Node* removeTail() {
        Node *last = tail->previous;
        last->previous->next = tail;
        tail->previous = last->previous;
        return last;
    }

    // 把新节点加到头部
    void addNodeToHead(Node *node) {
        node->next = head->next;
        node->next->previous = node;
        node->previous = head;
        head->next = node;
    }
};


#endif /* LRUCache_hpp */
