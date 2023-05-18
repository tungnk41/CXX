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
       void registerSignal(int signalID, __sighandler_t callback);
       void run();
    };
#endif