//
// Created by rick on 2025/4/28.
//

#pragma once

#include <map>
#include "flutter/encodable_value.h"


namespace flutter_inappwebview_plugin {
	struct ContextMenuItem {
		std::string id;
		std::string title;
	};

	class ContextMenuSettings {
	public:
		explicit ContextMenuSettings(const flutter::EncodableMap &contextMenuMap);

		[[nodiscard]] bool isHideDefaultSystemContextMenuItems() const { return myHideDefaultSystemContextMenuItems; }

		[[nodiscard]] const std::vector<ContextMenuItem> & getContextMenuItems() const {
			return myContextMenuItems;
		}

	private:
		bool myHideDefaultSystemContextMenuItems;
		std::vector<ContextMenuItem> myContextMenuItems;

	};
}
