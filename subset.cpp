#include <iostream>
#include "randomized_queue.h"

int main (int argc, char **argv){
    randomized_queue <std::string> now;
    std::string s;
    while (std::getline(std::cin, s)){
        now.enqueue(s);
    }
    char *last;
    int n = std::strtol(argv[1], &last, 10);
    for (int i = 0; i < n; i++){
        std::cout<<now.dequeue()<<" ";
    }
}
