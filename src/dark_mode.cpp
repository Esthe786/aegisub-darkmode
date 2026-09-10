// Copyright (c) 2026, Aegisub Project
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// Aegisub Project http://www.aegisub.org/

/// @file dark_mode.cpp
/// @brief Dark mode support
/// @ingroup main

#include "dark_mode.h"

#include "options.h"

#include <libaegisub/color.h>
#include <libaegisub/log.h>

#include <string_view>

#include <wx/settings.h>

namespace {
struct ColorOverride {
	const char *option;
	std::string_view dark;
};

/// Dark equivalents of the light-theme defaults from default_config.json. These
/// are only applied to options which the user has left at their default value.
constexpr ColorOverride dark_palette[] = {
	// Subtitle grid
	{"Colour/Subtitle Grid/Standard",                       "rgb(222, 222, 222)"},
	{"Colour/Subtitle Grid/Selection",                      "rgb(255, 255, 255)"},
	{"Colour/Subtitle Grid/Collision",                      "rgb(255, 105, 105)"},
	{"Colour/Subtitle Grid/Header",                         "rgb(45, 45, 48)"},
	{"Colour/Subtitle Grid/Left Column",                    "rgb(40, 48, 40)"},
	{"Colour/Subtitle Grid/Lines",                          "rgb(72, 72, 72)"},
	{"Colour/Subtitle Grid/Active Border",                  "rgb(255, 91, 239)"},
	{"Colour/Subtitle Grid/CPS Error",                      "rgb(112, 40, 40)"},
	{"Colour/Subtitle Grid/Background/Background",          "rgb(30, 30, 30)"},
	{"Colour/Subtitle Grid/Background/Selection",           "rgb(18, 78, 56)"},
	{"Colour/Subtitle Grid/Background/Comment",             "rgb(70, 54, 34)"},
	{"Colour/Subtitle Grid/Background/Inframe",             "rgb(58, 58, 28)"},
	{"Colour/Subtitle Grid/Background/Selected Comment",    "rgb(28, 66, 66)"},

	// Edit box / syntax highlighting
	{"Colour/Subtitle/Background",                          "rgb(30, 30, 30)"},
	{"Colour/Subtitle/Syntax/Normal",                       "rgb(220, 220, 220)"},
	{"Colour/Subtitle/Syntax/Comment",                      "rgb(120, 120, 120)"},
	{"Colour/Subtitle/Syntax/Drawing Command",              "rgb(210, 210, 210)"},
	{"Colour/Subtitle/Syntax/Drawing X",                    "rgb(210, 140, 140)"},
	{"Colour/Subtitle/Syntax/Drawing Y",                    "rgb(140, 210, 140)"},
	{"Colour/Subtitle/Syntax/Brackets",                     "rgb(120, 160, 255)"},
	{"Colour/Subtitle/Syntax/Slashes",                      "rgb(255, 120, 220)"},
	{"Colour/Subtitle/Syntax/Tags",                         "rgb(165, 165, 165)"},
	{"Colour/Subtitle/Syntax/Parameters",                   "rgb(140, 210, 140)"},
	{"Colour/Subtitle/Syntax/Error",                        "rgb(255, 120, 120)"},
	{"Colour/Subtitle/Syntax/Background/Error",             "rgb(96, 40, 40)"},
	{"Colour/Subtitle/Syntax/Line Break",                   "rgb(150, 150, 150)"},
	{"Colour/Subtitle/Syntax/Karaoke Template",             "rgb(200, 130, 240)"},
	{"Colour/Subtitle/Syntax/Karaoke Variable",             "rgb(200, 130, 240)"},

	// Audio display
	{"Colour/Audio Display/Line Boundary Inactive Line",    "rgb(130, 130, 130)"},

	// Style editor preview backdrop
	{"Colour/Style Editor/Background/Preview",              "rgb(48, 52, 58)"},
};
}

bool ShouldUseDarkMode() {
	switch (static_cast<DarkModeSetting>(OPT_GET("App/Dark Mode")->GetInt())) {
		case DarkModeSetting::Light: return false;
		case DarkModeSetting::Dark:  return true;
		case DarkModeSetting::System:
		default:
			return wxSystemSettings::GetAppearance().IsDark();
	}
}

void ApplyDarkModeColors() {
	if (!ShouldUseDarkMode()) return;

	LOG_D("darkmode") << "applying dark colour palette";
	for (auto const& entry : dark_palette) {
		agi::OptionValue *opt = OPT_SET(entry.option);
		if (opt->IsDefault())
			opt->SetColor(agi::Color(entry.dark));
	}
}
