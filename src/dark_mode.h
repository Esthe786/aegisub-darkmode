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

/// @file dark_mode.h
/// @brief Dark mode support
/// @ingroup main

#pragma once

/// The three possible values of the "App/Dark Mode" option.
enum class DarkModeSetting {
	System = 0, ///< Follow the OS-wide light/dark setting
	Light  = 1, ///< Always use the light theme
	Dark   = 2  ///< Always use the dark theme
};

/// @brief Should Aegisub currently render itself using a dark theme?
///
/// Resolves the "App/Dark Mode" option, querying the OS appearance when the
/// option is set to "System".
bool ShouldUseDarkMode();

/// @brief Apply the bundled dark colour palette to the custom-drawn widgets.
///
/// Only colour options the user has not customised are touched, and the values
/// are not flushed to disk so switching back to the light theme restores the
/// defaults. Call once at startup, after the configuration has been loaded.
void ApplyDarkModeColors();
