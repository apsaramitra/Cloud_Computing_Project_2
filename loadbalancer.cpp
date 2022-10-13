


#include "webserv.cpp"
#include "req.cpp"
#ifndef LOAD_H
#define LOAD_H

#include <queue>

class loadbalancer{
    public:
        std::queue<request> requestQueue;
        int systemTime;
        loadbalancer(){
            systemTime = 0;
        }
        void addRequest (request r){
            requestQueue.push(r);
            systemTime++;
        }
        request getRequest(){
            systemTime++;
            request r = requestQueue.front();
            requestQueue.pop();
            return r;
            
        }
};

#endif

