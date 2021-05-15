#pragma once
#include <vector>

template <typename T>
struct randomized_deque{

    randomized_deque();
    ~randomized_deque()=default;

    bool empty()const;
    unsigned int size() const;

    void push_front(const T &first);
    void push_back(const T &last);

    const T &front() const;
    const T &back() const;

    void pop_front();
    void pop_back();

    struct iterator{
        using itDeq = typename std::vector <T>::iterator;

        iterator(const itDeq &beginItDeq,const int &sizeAllDeq,const int &indHeadDeq,const int &nowIndDeq);
        iterator (const iterator &nowIt)=default;
        iterator()=default;
        ~iterator()=default;

        T &operator*();

        iterator operator+ (int num);
        iterator operator- (int num);
        iterator operator++ (int);
        iterator operator-- (int);
        iterator &operator++ ();
        iterator &operator-- ();
        iterator &operator+= (int num);
        iterator &operator-= (int num);
        iterator &operator= (const iterator &nowIt)=default;
        bool operator==(const iterator &nowIt);
        bool operator!=(const iterator &nowIt);
    private:
        itDeq beginIt;
        unsigned int indHead;
        unsigned int nowInd;
        unsigned int sizeAll;
    };

    iterator begin();
    iterator end();
private:
    std::vector <T> deq;
    int headDeq;
    int tailDeq;
    void changeSize(unsigned int nowSize);
};

template <typename T>
randomized_deque <T>::randomized_deque(){
    deq.resize(10);
    headDeq=tailDeq=0;
}

template <typename T>
unsigned int randomized_deque <T>::size() const{
    if (headDeq <= tailDeq) return tailDeq-headDeq;
    else return tailDeq-headDeq+deq.size();
}
template <typename T>
bool randomized_deque <T>::empty() const{
    return size()==0;
}

template <typename T>
void randomized_deque <T>::push_front(const T &first){
    changeSize(size()+1);
    headDeq = (headDeq == 0) ? (deq.size() - 1) : headDeq - 1;
    deq[headDeq] = first;
}
template <typename T>
void randomized_deque <T>::push_back(const T &last){
    changeSize(size()+1);
    deq[tailDeq] = last;
    tailDeq = (tailDeq + 1)%deq.size();
}

template <typename T>
const T &randomized_deque <T>::front() const{
    if (empty()) throw std::runtime_error("Empty deque");
    return deq[headDeq];
}
template <typename T>
const T &randomized_deque <T>::back() const{
    if (empty()) throw std::runtime_error("Empty deque");
    return deq[(tailDeq == 0) ? (deq.size() - 1) : tailDeq - 1];
}

template <typename T>
void randomized_deque <T>::pop_front(){
    if (empty()) throw std::runtime_error("Empty deque");
    deq[headDeq].~T();
    new(&deq[headDeq]) T;
    headDeq = (headDeq + 1)%deq.size();
}
template <typename T>
void randomized_deque <T>::pop_back(){
    if (empty()) throw std::runtime_error("Empty deque");
    tailDeq = (tailDeq == 0) ? (deq.size() - 1) : tailDeq - 1;
    deq[tailDeq].~T();
    new(&deq[tailDeq]) T;
}


template <typename T>
randomized_deque <T>::iterator::iterator(const itDeq &beginItDeq,const int &sizeAllDeq,const int &indHeadDeq,const int &nowIndDeq):
    beginIt(beginItDeq), sizeAll(sizeAllDeq), indHead(indHeadDeq), nowInd(nowIndDeq){};

template <typename T>
T &randomized_deque <T>::iterator::operator*(){
    return *(beginIt + (indHead + nowInd)%sizeAll);
};

template <typename T>
typename randomized_deque <T>::iterator randomized_deque <T>::iterator::operator+ (int num){
    return *this +=num;
};
template <typename T>
typename randomized_deque <T>::iterator randomized_deque <T>::iterator::operator- (int num){
    return *this -=num;
};
template <typename T>
typename randomized_deque <T>::iterator randomized_deque <T>::iterator::operator++ (int){
    auto nowIt = *this;
    nowInd++;
    return nowIt;
};
template <typename T>
typename randomized_deque <T>::iterator randomized_deque <T>::iterator::operator-- (int){
    auto nowIt = *this;
    nowInd--;
    return nowIt;
};
template <typename T>
typename randomized_deque <T>::iterator &randomized_deque <T>::iterator::operator++ (){
    nowInd++;
    return *this;
};
template <typename T>
typename randomized_deque <T>::iterator &randomized_deque <T>::iterator::operator-- (){
    nowInd--;
    return *this;
};
template <typename T>
typename randomized_deque <T>::iterator &randomized_deque <T>::iterator::operator+= (int num){
    nowInd+=num;
    return *this;
};
template <typename T>
typename randomized_deque <T>::iterator &randomized_deque <T>::iterator::operator-= (int num){
    nowInd-=num;
    return *this;
};
template <typename T>
bool randomized_deque <T>::iterator::operator==(const iterator &nowIt){
    auto first=beginIt+(indHead+nowInd)%sizeAll;
    auto second=nowIt.beginIt+(nowIt.indHead+nowIt.nowInd)%nowIt.sizeAll;
    return first==second;
};
template <typename T>
bool randomized_deque <T>::iterator::operator!=(const iterator &nowIt){
    auto first=beginIt+(indHead+nowInd)%sizeAll;
    auto second=nowIt.beginIt+(nowIt.indHead+nowIt.nowInd)%nowIt.sizeAll;
    return first!=second;
};

template <typename T>
typename randomized_deque <T>::iterator randomized_deque <T>::begin(){
    iterator nowIt (deq.begin(), deq.size(), headDeq, 0);
    return nowIt;
};
template <typename T>
typename randomized_deque <T>::iterator randomized_deque <T>::end(){
    iterator nowIt (deq.begin(), deq.size(), headDeq, size());
    return nowIt;
};


template <typename T>
void randomized_deque <T>::changeSize(unsigned int nowSize){
    if (nowSize>=10){
        if (deq.size()<=nowSize){
            std::vector <T> newDeq=deq;
            deq.clear();
            deq.resize(2*nowSize);
            if (headDeq<=tailDeq){
                for (int i=headDeq; i<tailDeq; i++) deq[i-headDeq]=newDeq[i];
                tailDeq-=headDeq;
            } else{
                int nowIndex=0;
                for (int i=headDeq; i<newDeq.size(); i++) {
                    deq[nowIndex]=newDeq[i];
                    nowIndex++;
                }
                for (int i=0; i<tailDeq; i++){
                    deq[nowIndex]=newDeq[i];
                    nowIndex++;
                }
                tailDeq+=newDeq.size()-headDeq;
            }

        headDeq=0;
        }
    }
};
