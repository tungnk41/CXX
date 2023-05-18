#ifndef _SIGNAL_HPP_
#define _SIGNAL_HPP_
    #include <iostream>
    #include <signal.h>
    #include <unistd.h>
    #include <functional>

    using std::cout;
    using std::endl;

    class Signal {
    private:
        
    public:
       void sendSignal(pid_t pid, int signalID);
       pid_t getProcessID();
       void registerSignal(pid_t pid,int signalID, std::function<void(int)> callback);
       void run();
    };
#endif