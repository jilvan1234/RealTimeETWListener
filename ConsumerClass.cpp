#include "ConsumerClass.h"

using namespace System;
using namespace System::Threading;

ConsumerClass::ConsumerClass(RealTimeEWTListener* handle) :
    _handle(handle)
{

}

static ConsumerClass::ConsumerClass() {
    pin_ptr<UInt64> frequency = &PerformanceCounterFrequency;
    QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(frequency));
}

void ConsumerClass::StartProcessThread(RealTimeEWTListener* handle)
{
    auto tmp = gcnew ConsumerClass(handle);
    Thread^ processThread = gcnew Thread(gcnew ThreadStart(tmp, &ConsumerClass::ProcessTrace));

    processThread->Start();

}


void ConsumerClass::ProcessTrace() {
    _handle->ProcessTraceThread();
}


void ConsumerClass::FireEvent(CallbackData data) {
    EventReceived(data);
}

void ConsumerClass::ShowConsole() {
    //Open a console!
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "w", stdin);
}