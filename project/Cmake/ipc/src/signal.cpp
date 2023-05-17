#include <signal.hpp>

void Signal::signalHandler(int signalID) {
    cout << "Handle SignalID : " << signalID <<endl;
}

void Signal::sendSignal(int signalID) {

}

pid_t Signal::getProcessID() {
    return getpid();
}

void Signal::registerSignal(int signalID) {

}

