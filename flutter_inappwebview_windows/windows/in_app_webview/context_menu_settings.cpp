//
// Created by rick on 2025/4/28.
//

#include "context_menu_settings.h"
#include "../utils/flutter.h"

// helper type for the visitor
template <class... Ts>
struct overloads : Ts... {
  using Ts::operator()...;
  // work around for msvc ebo bug
  // https://developercommunity.visualstudio.com/t/runtime-stack-corruption-using-stdvisit/346200
  int dummy = 0;
};
template <class... Ts>
overloads(Ts...) -> overloads<Ts...>;

namespace flutter_inappwebview_plugin {
ContextMenuSettings::ContextMenuSettings(
    const flutter::EncodableMap& contextMenuMap) {
  auto settingsValue = get_optional_fl_map_value<flutter::EncodableMap>(
      contextMenuMap, "settings");
  if (settingsValue.has_value()) {
    myHideDefaultSystemContextMenuItems =
        get_optional_fl_map_value<bool>(settingsValue.value(),
                                        "hideDefaultSystemContextMenuItems")
            .value_or(false);
  } else {
    myHideDefaultSystemContextMenuItems = false;
  }

  auto menuItemsValue = get_optional_fl_map_value<flutter::EncodableList>(
      contextMenuMap, "menuItems");
  if (menuItemsValue.has_value()) {
    std::for_each(
        menuItemsValue.value().begin(), menuItemsValue.value().end(),
        [this](const flutter::EncodableValue& item) {
          auto visitor = overloads{
              [&](const flutter::EncodableMap& itemMap) {
                auto id = get_fl_map_value<std::string>(itemMap, "id");
                auto title = get_fl_map_value<std::string>(itemMap, "title");
                myContextMenuItems.emplace_back(ContextMenuItem{id, title});
              },
              [](const auto& value) {}};
          std::visit(visitor, item);
        });
  }
}
}  // namespace flutter_inappwebview_plugin