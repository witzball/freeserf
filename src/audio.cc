/*
 * audio.cc - Music and sound effects playback base.
 *
 * Copyright (C) 2015  Wicked_Digger <wicked_digger@mail.ru>
 *
 * This file is part of freeserf.
 *
 * freeserf is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * freeserf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with freeserf.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "src/audio.h"

#include <algorithm>

#include "src/log.h"

Audio *
Audio::instance = NULL;

Audio::Player::Player() {
  enabled = true;
}

Audio::Player::~Player() {
  while (track_cache.size()) {
    Audio::Track *track = track_cache.begin()->second;
    track_cache.erase(track_cache.begin());
    delete track;
  }
}

void
Audio::Player::play_track(int track_id) {
  if (!is_enabled()) {
    return;
  }

  Audio::Track *track = NULL;
  TrackCache::iterator it = track_cache.find(track_id);
  if (it == track_cache.end()) {
    track = create_track(track_id);
    if (track != NULL) {
      track_cache[track_id] = track;
    }
  } else {
    track = it->second;
  }

  if (track != NULL) {
    track->play();
  }
}
