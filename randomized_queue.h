#pragma once

#include <vector>
#include <random>
#include <algorithm>

template <typename T>

struct randomized_queue{
    randomized_queue()=default;
    ~randomized_queue()=default;

    bool empty() const;
    unsigned int size() const;

    struct iterator{
        using itQue = typename std::vector <T>::iterator;

        iterator(const itQue &beginItQue,const int &sizeAllQue,const int &nowIndQue);
        iterator (const iterator &nowIt);
        iterator()=default;
        ~iterator()=default;

        T &operator*();

        iterator operator++ (int);
        iterator operator-- (int);
        iterator &operator++ ();
        iterator &operator-- ();
        iterator &operator= (const iterator &nowIt);
        bool operator==(const iterator &nowIt);
        bool operator!=(const iterator &nowIt);
    private:
        std::vector <int> randShuffle;
        void makeShuffle();

        itQue beginIt;
        unsigned int nowInd;
        unsigned int sizeAll;
    };
    iterator begin();
    iterator end();

    void enqueue(const T &now);
    T sample();
    T dequeue();

private:
    std::vector <T> que;

    static std::mt19937_64 initRand();
    std::mt19937_64 nowRand = initRand();
    std::uniform_int_distribution <int> maxRand;

    void changeMaxRand();
};

template <typename T>
bool randomized_queue <T>::empty() const{
    return size()==0;
};

template <typename T>
unsigned int randomized_queue <T>::size() const{
    return que.size();
};

template <typename T>
randomized_queue <T>::iterator::iterator(const itQue &beginItQue,const int &sizeAllQue,const int &nowIndQue):
    beginIt(beginItQue), sizeAll(sizeAllQue), nowInd(nowIndQue){
        makeShuffle();
    };

template <typename T>
randomized_queue <T>::iterator::iterator (const iterator &nowIt):
    beginIt(nowIt.beginIt), sizeAll(nowIt.sizeAll), nowInd(nowIt.nowInd), randShuffle(std::move(nowIt.randShuffle)) {};;

template <typename T>
T &randomized_queue <T>::iterator::operator*(){
    return *(beginIt+randShuffle[nowInd]);
};

template <typename T>
typename randomized_queue <T>::iterator randomized_queue <T>::iterator::operator++ (int){
    auto nowIt = *this;
    nowInd++;
    return nowIt;
};
template <typename T>
typename randomized_queue <T>::iterator randomized_queue <T>::iterator::operator-- (int){
    auto nowIt = *this;
    nowInd--;
    return nowIt;
};
template <typename T>
typename randomized_queue <T>::iterator &randomized_queue <T>::iterator::operator++ (){
    nowInd++;
    return *this;
};
template <typename T>
typename randomized_queue <T>::iterator &randomized_queue <T>::iterator::operator-- (){
    nowInd--;
    return *this;
};

template <typename T>
typename randomized_queue <T>::iterator &randomized_queue <T>::iterator::operator= (const randomized_queue <T>::iterator &nowIt){
    beginIt=nowIt.beginIt;
    sizeAll=nowIt.sizeAll;
    nowInd=nowIt.nowInd;
    randShuffle=std::move(nowIt.randShuffle);
};
template <typename T>
bool randomized_queue <T>::iterator::operator==(const randomized_queue <T>::iterator &nowIt){
    auto first=beginIt+randShuffle[nowInd];
    auto second=nowIt.beginIt+nowIt.randShuffle[nowIt.nowInd];
    return first==second;
};
template <typename T>
bool randomized_queue <T>::iterator::operator!=(const randomized_queue <T>::iterator &nowIt){
    auto first=beginIt+randShuffle[nowInd];
    auto second=nowIt.beginIt+nowIt.randShuffle[nowIt.nowInd];
    return first!=second;
};

template <typename T>
void randomized_queue <T>::iterator::makeShuffle(){
    randShuffle.resize(sizeAll+1);
    for (int i=0; i<sizeAll+1; i++) randShuffle[i]=i;
    std::shuffle(randShuffle.begin(), randShuffle.end()-1, std::mt19937_64(std::random_device()()));
};

template <typename T>
typename randomized_queue <T>::iterator randomized_queue <T>::begin(){
    randomized_queue <T>::iterator ans(que.begin(), size(), 0);
    return ans;
};
template <typename T>
typename randomized_queue <T>::iterator randomized_queue <T>::end(){
    randomized_queue <T>::iterator ans(que.begin(), size(), size());
    return ans;
};

template <typename T>
void randomized_queue <T>::enqueue(const T &now){
    que.push_back(now);
    changeMaxRand();
};

template <typename T>
T randomized_queue <T>::sample(){
    if (empty()){
        std::cout<<"Empty queue"<<std::endl;
        exit(0);
    } else return que[maxRand(nowRand)];
};

template <typename T>
T randomized_queue <T>::dequeue(){
    if (empty()){
        std::cout<<"Empty queue"<<std::endl;
        exit(0);
    } else{
        int indAns = maxRand(nowRand);
        T ans=que[indAns];
        std::swap(que[indAns], que[que.size()-1]);
        que.pop_back();
        changeMaxRand();
        return ans;
    }
};

template <typename T>
std::mt19937_64 randomized_queue <T>::initRand(){
    std::random_device newRand;
    return std::mt19937_64(newRand());
};

template <typename T>
void randomized_queue <T>::changeMaxRand(){
    maxRand=std::uniform_int_distribution <int> (0, size()-1);
}
