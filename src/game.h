/*
 * game.h - Gameplay related functions
 *
 * Copyright (C) 2013  Jon Lund Steffensen <jonlst@gmail.com>
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

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include <vector>

#include "src/player.h"
#include "src/flag.h"
#include "src/serf.h"
#include "src/map.h"
#include "src/random.h"
#include "src/objects.h"

#define DEFAULT_GAME_SPEED  2

#define GAME_MAX_PLAYER_COUNT  4


typedef void game_update_map_height_func(map_pos_t pos, void *data);

typedef collection_t<flag_t> flags_t;
typedef collection_t<inventory_t> inventories_t;
typedef collection_t<building_t> buildings_t;
typedef collection_t<serf_t> serfs_t;
typedef collection_t<player_t> players_t;

typedef struct {
  map_t *map; /* ADDITION */
  /* 0 */
  /* MOVED to map_t
  uint32_t map_index_mask;
  uint32_t map_dirs[8];
  map_1_t *map_mem2_ptr;
  uint32_t map_col_size;
  uint32_t map_elms; */
  /* 30 */
  /*
  uint16_t map_row_shift;
  uint16_t map_col_mask;
  uint16_t map_row_mask;
  uint32_t map_data_offset;
  uint16_t map_shifted_col_mask;
  uint32_t map_shifted_row_mask; */
  /* 40 */
  /*
  uint16_t map_col_pairs;
  uint16_t map_row_pairs; */
  int16_t map_water_level;
  int16_t map_max_lake_area;
  /*uint16_t map_max_serfs_left;*/
  uint32_t map_gold_deposit;
  /* 50 */
  uint16_t map_size;
  /* 58 */
  int map_gold_morale_factor;
  /* 5E */
  int winning_player;
  /* 60 */
  /* uint16_t map_move_left_2; MOVED to map_t */
  /* 64 */
  players_t players;
  /* 78 */
  /*interface_t *interface;*/
  /* 80 */
  /*void *player_map_rows[2];*/ /* OBSOLETE */
  /* 90 */
  /*int **map_serf_rows_left;*/ /* OBSOLETE */
  /*int **map_serf_rows_right;*/ /* OBSOLETE */
  /* 98 */
  flags_t flags;
  inventories_t inventories;
  buildings_t buildings;
  serfs_t serfs;
  /* OBSOLETE
  flag_t **flag_queue_black;
  flag_t **flag_queue_white; */
  /* C4 */
  /* F0 */
  /* 108 */
  /*frame_t *frame;*/
  /* 1C2 */
  /* MOVED to map_t 
  uint16_t map_cols;
  uint16_t map_rows; */
  /* 1C8 */
  uint8_t svga; /* flags */
  /* 1D6 */
  /*player_init_t pl_init[4];*/
  /* 1EE */
  random_state_t init_map_rnd;
  /* 1FA */
  unsigned int game_speed_save;
  unsigned int game_speed;
  /* Increased according to the currect game speed. */
  unsigned int tick;
  unsigned int last_tick;
  /* Increased by one no matter the game speed. */
  unsigned int const_tick;
  /* 20E */
  unsigned int game_stats_counter;
  unsigned int history_counter;
  random_state_t rnd;
  /*uint8_t field_218[4];*/
  uint16_t map_regions;
  /* OBSOLETE by local vars */
  /*uint8_t init_map_old_type;
  uint8_t init_map_seed_type;
  uint8_t init_map_new_type;
  uint8_t init_map_saved_types[9];
  uint16_t field_22A;
  int16_t field_22C;
  uint16_t init_map_tries;*/
  /* 230 */
  /*uint16_t field_230;
  uint16_t field_232;
  uint8_t init_map_type_min;
  uint8_t init_map_type_max;
  uint8_t init_map_rnd_offset;
  uint8_t init_map_rnd_mask;*/
  /* 248 */
  /* OBSOLETE by local vars*/
  /*uint16_t build_road_source_flag;
  uint16_t build_road_out_dir;
  uint16_t build_road_in_dir;
  uint16_t field_24E;*/
  /* 250 */
  /* OBSOLETE by local vars */
  /*uint16_t short_row_length;
  uint16_t long_row_length;*/
  /* 258 */
  /* 260 */
  /* 26C */
  uint16_t next_index;
  uint16_t flag_search_counter;
  uint16_t flag_queue_select;
  /* 276 */
  int16_t flags_in_queue;
  /* 27A */
  building_type_t building_type;
  uint16_t update_map_last_tick;
  int16_t update_map_counter;
  /* 280 */
  map_pos_t update_map_initial_pos;
  int tick_diff;
  /* 286 */
  uint16_t max_next_index;
  /* 28C*/
  int16_t update_map_16_loop;
  /* 2F8 */
  /*map_1_t *map_tiles; MOVED to map_t */
  /*uint8_t *map_minimap;*/
  /* 320 */
  int player_history_index[4];
  int player_history_counter[3];
  /* 32E */
  int resource_history_index;
  /* 340 */
  uint16_t field_340;
  uint16_t field_342;
  inventory_t *field_344;
  /* 352 */
  int game_type;
  int tutorial_level;
  int mission_level;
  int map_generator; /* ADDITION */
  int map_preserve_bugs; /* ADDITION */
  /* 37C */
  uint8_t split;
  /* 380 */
  int player_score_leader;
  /* ... */

  /* Callback for map height changes */
  game_update_map_height_func *update_map_height_cb;
  void *update_map_height_data;

  int knight_morale_counter;
  int inventory_schedule_counter;
} game_t;

/* Global game object */
extern game_t game;


/* External interface */
void game_init();
int game_add_player(unsigned int face, unsigned int color,
                    unsigned int supplies, unsigned int reproduction,
                    unsigned int intelligence);
int game_load_mission_map(int m);
int game_load_random_map(int size, const random_state_t &rnd);
int game_load_save_game(const char *path);
void game_allocate_objects();

void game_update();
void game_pause(int enable);

void game_prepare_ground_analysis(map_pos_t pos, int estimates[5]);
int game_send_geologist(flag_t *dest);

int game_get_leveling_height(map_pos_t pos);

int game_can_build_military(map_pos_t pos);
int game_can_build_small(map_pos_t pos);
int game_can_build_mine(map_pos_t pos);
int game_can_build_large(map_pos_t pos);
int game_can_build_building(map_pos_t pos, building_type_t type,
          const player_t *player);
int game_can_build_castle(map_pos_t pos, const player_t *player);
int game_can_build_flag(map_pos_t pos, const player_t *player);
int game_can_player_build(map_pos_t pos, const player_t *player);

int game_can_build_road(map_pos_t source, const dir_t dirs[],
                        unsigned int length, const player_t *player,
                        map_pos_t *dest, int *water);

bool game_can_demolish_flag(map_pos_t pos, const player_t *player);
int game_can_demolish_road(map_pos_t pos, const player_t *player);

int game_build_road(map_pos_t source, const dir_t dirs[],
                    unsigned int length, const player_t *player);

int game_build_flag(map_pos_t pos, player_t *player);
int game_build_building(map_pos_t pos, building_type_t type, player_t *player);
int game_build_castle(map_pos_t pos, player_t *player);

int game_demolish_road(map_pos_t pos, player_t *player);
int game_demolish_flag(map_pos_t pos, player_t *player);
int game_demolish_building(map_pos_t pos, player_t *player);

void game_set_inventory_resource_mode(inventory_t *inventory, int mode);
void game_set_inventory_serf_mode(inventory_t *inventory, int mode);


/* Internal interface */
void game_calculate_military_flag_state(building_t *building);
void game_init_land_ownership();
void game_update_land_ownership(map_pos_t pos);
void game_occupy_enemy_building(building_t *building, int player);

void game_cancel_transported_resource(resource_type_t type, unsigned int dest);
void game_lose_resource(resource_type_t type);

uint16_t game_random_int();

int game_send_serf_to_flag(flag_t *dest, serf_type_t type, resource_type_t res1,
                           resource_type_t res2);

void game_deinit();

#endif  // SRC_GAME_H_
