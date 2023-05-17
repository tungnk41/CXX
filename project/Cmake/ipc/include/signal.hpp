#ifndef _SIGNAL_HPP_
#define _SIGNAL_HPP_
    #include <iostream>
    #include <csignal>
    #include <unistd.h>

    using std::cout;
    using std::endl;

    class Signal {
    private:
        
    public:
       void signalHandler(int signalID);
       void sendSignal(int signalID);
       pid_t getProcessID();
       void registerSignal(int signalID);
    };
#endif