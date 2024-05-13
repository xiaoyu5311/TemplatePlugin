﻿#include "TemplateEventRegister.h"

#include <mc/world/item/registry/ItemStack.h>
#include "ll/api/event/EventBus.h"
#include "ll/api/event/player/PlayerJoinEvent.h"
#include "ll/api/event/player/PlayerUseItemEvent.h"
#include "mc/server/commands/CommandContext.h"
#include "mc/server/commands/PlayerCommandOrigin.h"
#include "ll/api/service/Bedrock.h"

using ll::event::ListenerPtr;
using ll::event::player::PlayerJoinEvent;
using ll::event::player::PlayerUseItemEvent;

void TemplateEventRegister::EventRegister() {

    playerJoinEventListener = eventBus->emplaceListener<PlayerJoinEvent>(
        [](PlayerJoinEvent& event) {
            auto& player = event.self();

            const auto& uuid = player.getUuid();

            ItemStack itemStack("clock", 1);
            player.add(itemStack);

            player.refreshInventory();
        }
    );

    playerUseItemEventListener =
        eventBus->emplaceListener<PlayerUseItemEvent>([](PlayerUseItemEvent& event) {
            auto& player = event.self();
            auto& itemStack = event.item();
            if (itemStack.getRawNameId() == "clock") {
                CommandContext context = CommandContext(
                    "menu",
                    std::make_unique<PlayerCommandOrigin>(PlayerCommandOrigin(player))
                );
                // ll::service::getMinecraft()->getCommands().executeCommand(context);
            }
        });
}

void TemplateEventRegister::RemoveEventListener() {
    eventBus->removeListener(playerJoinEventListener);
    eventBus->removeListener(playerUseItemEventListener);
}
