#include <iostream>
#include "randomized_queue.h"
#include "randomized_deque.h"
void queTest(){
    std::cout<<"RANDOMIZED INT QUEUE:"<<std::endl;
    randomized_queue <int> que;
    for (int i=0; i<10; i++){
        que.enqueue(i);
    }
    std::cout<<"Size: "<<que.size()<<std::endl;
    std::cout<<"Sample: "<<que.sample()<<std::endl;
    std::cout<<"First iterator go: "<<std::endl;
    for (auto i:que){
        std::cout<<i<<" ";
    }
    std::cout<<std::endl<<"Second iterator go: "<<std::endl;
    for (auto i:que){
        std::cout<<i<<" ";
    }
    std::cout<<std::endl<<"Dequeue: "<<std::endl;
    while(!que.empty()){
        std::cout<<que.dequeue()<<" ";
    }
    std::cout<<std::endl<<"===================================="<<std::endl;
    std::cout<<"RANDOMIZED STRING QUEUE:"<<std::endl;
    randomized_queue <std::string> queString;
    queString.enqueue("first");
    queString.enqueue("second");
    queString.enqueue("third");
    queString.enqueue("fourth");
    while(!queString.empty()){
        std::cout<<queString.dequeue()<<" ";
    }
    std::cout<<std::endl;
}
void deqTest(){
    std::cout<<"INT DEQUE:"<<std::endl;
    randomized_deque <int> deq;
    for (int i=0; i<10; i++){
        deq.push_back(i);
    }
    std::cout<<"Do push Back [0;10)"<<std::endl;
    for (int i=0; i<10; i++){
        deq.push_front(i+10);
    }
    std::cout<<"Do push Front [10;20)"<<std::endl;

    std::cout<<"Front: "<<deq.front()<<std::endl;
    std::cout<<"Back: "<<deq.back()<<std::endl;
    std::cout<<"Size: "<<deq.size()<<std::endl;
    std::cout<<"Deque with iterator:"<<std::endl;
    for (auto i:deq){
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Deque with empty and pop_front:"<<std::endl;
    while(!deq.empty()){
        std::cout<<deq.front()<<" ";
        deq.pop_front();
    }
    std::cout<<std::endl<<"===================================="<<std::endl;
    std::cout<<"STRING DEQUE:"<<std::endl;
    randomized_deque <std::string> deqString;
    deqString.push_back("first");
    deqString.push_back("second");
    deqString.push_back("third");
    deqString.push_back("fourth");
    while(!deqString.empty()){
        std::cout<<deqString.back()<<" ";
        deqString.pop_back();
    }
    std::cout<<std::endl;
}

int main() {
    queTest();
    std::cout<<std::endl<<"===================================="<<std::endl;
    std::cout<<std::endl<<"===================================="<<std::endl;
    deqTest();
}
