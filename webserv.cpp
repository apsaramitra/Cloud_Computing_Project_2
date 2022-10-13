



#include "req.cpp"

#ifndef WEBSERVER_H
#define WEBSERVER_H


class webserver{
    public:
        request r;
        int start;
        char name;
        webserver(){
            start = 0;
            name = ' ';
        }
        webserver(char c){
            start = 0;
            name = c;
        }
        void addR(request req, int curr){
            r = req;
            start = curr;
        }
        
};

#endif