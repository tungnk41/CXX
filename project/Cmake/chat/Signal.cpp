#include <signal.hpp>

void signalHandler(int signalID) {
    cout << "Handle SignalID : " << signalID <<endl;
}

void Signal::sendSignal(pid_t pid, int signalID) {
    // Send a signal to the process
    kill(pid, SIGUSR1);
}

pid_t Signal::getProcessID() {
    return getpid();
}

void Signal::registerSignal(pid_t pid,int signalID, std::function<void(int)> callback) {
    signal(signalID, signalHandler);
}

void Signal::run() {
    pid_t processID = getProcessID();
    registerSignal(processID,SIGINT, signalHandler);

    //Send to specific process
    // sendSignal(processID,SIGUSR1);

    //Send to current process
    // raise(SIGUSR1);
}

