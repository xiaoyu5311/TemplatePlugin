#pragma once
#include "EventRegisterBase.h"
#include "Core/IEventRegister.h"
#include "ll/api/event/Listener.h"

using ll::event::ListenerPtr;

class TemplateEventRegister : public EventRegisterBase {

private:
    ListenerPtr playerJoinEventListener;
    ListenerPtr playerUseItemEventListener;

public:
    TemplateEventRegister() { }

    void EventRegister() override;
    void RemoveEventListener() override;

};
