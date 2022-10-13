#include <string>
#include "req.cpp"
#include "webserv.cpp"
#include "loadbalancer.cpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;


int main(){
    ofstream out("logtest5.txt");
    int clockcycles = 0;
    int webservers = 0;
    cout << "Input # of webservers: ";
    cin >> webservers;
    cout << "Input # of clock cycles: ";
    cin >> clockcycles;
    cout << endl;
    srand(time(0));
    loadbalancer lb;
    for(int i = 0; i<700; i++){
        request r;
        r.source = to_string(rand() % 256) +"." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256);
        r.destination = to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256);
        r.processTime = rand() % 200;
        lb.addRequest(r);
    }
    out << "Left in queue:" << lb.requestQueue.size() << endl;
    webserver webarr[webservers];
    for(int i = 0; i<webservers; i++){
        webserver w((char)(i+'A'));
        webarr[i] = w;
        if(!lb.requestQueue.empty()){

            webarr[i].addR(lb.getRequest(), lb.systemTime);
        }
    }

    while (lb.systemTime < clockcycles){
        int curr = lb.systemTime;
        if((webarr[curr % webservers].start + webarr[curr % webservers].r.processTime) - curr < 0){
            request r = webarr[curr % webservers].r;
            out << "At " << curr << ", " << webarr[curr % webservers].name << " processed request from " << r.source << " to " << r.destination << endl;
             if(!lb.requestQueue.empty()){
                webarr[curr % webservers].addR(lb.getRequest(), curr);

             }
        }
        if (rand() % 10 == 0){
            request r;
            r.source = to_string(rand() % 256) +"." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256);
            r.destination = to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256) + "." + to_string(rand() % 256);
            r.processTime = rand() % 200;
            lb.addRequest(r);
        }
        lb.systemTime++;
    }

    out << "Left in queue:" << lb.requestQueue.size() << endl;
    return 0;

}