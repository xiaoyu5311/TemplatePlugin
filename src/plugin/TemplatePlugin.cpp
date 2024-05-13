#include "plugin/TemplatePlugin.h"

#include <memory>

#include "Command/TemplateCommandRegister.h"
#include "Event/TemplateEventRegister.h"
#include "ll/api/plugin/NativePlugin.h"
#include "ll/api/plugin/RegisterHelper.h"
#include "plugin/Log/Log.h"

namespace TemplatePlugin {

static std::unique_ptr<TemplatePlugin> instance;

TemplatePlugin& TemplatePlugin::getInstance() { return *instance; }

bool TemplatePlugin::load() {
    Log::Init(&getSelf().getLogger());
    Log::Info("插件加载中...Loading...");
    
    return true;
}

bool TemplatePlugin::enable() {
    command_register = new TemplateCommandRegister();
    event_register = new TemplateEventRegister();

    command_register->CommandRegister();
    event_register->EventRegister();

    
    return true;
}

bool TemplatePlugin::disable() {
    Log::Info("插件关闭中...Disabling...");
    
    event_register->RemoveEventListener();
    return true;
}

} 

LL_REGISTER_PLUGIN(TemplatePlugin::TemplatePlugin, TemplatePlugin::instance);
