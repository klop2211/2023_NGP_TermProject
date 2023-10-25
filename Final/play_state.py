import time

import Banshee_object
import Chaindemon_object
import Item_object
import Niflheim_object
import game_framework
import Camera
import Map_object
import UI_object
import Hero_object
import game_world
import Map_bb

import Biggrayskel_object
from pico2d import *

map = None
minimap = None
hero = None
back_ground = None
wall_data = [[(0, 6, 1, 18), (29, 6, 30, 18)],
             [(0, 6, 1, 18), (29, 13, 30, 18), (29, 2, 30, 9)],
             [(0, 6, 1, 18), (29, 2, 30, 11), (29, 15, 30, 18)],
             [(0, 6, 1, 18), (29, 2, 30, 18)]]
block_data = [[(0, 0, 29, 2), (5, 5, 9, 5), (10, 8, 14, 8), (7, 12, 11, 12), (11, 16, 15, 16), (16, 13, 18, 13), (19, 11, 21, 11), (21, 8, 25, 8)],
              [(0, 0, 29, 2), (3, 10, 4, 10), (5, 13, 9, 13), (7, 9, 11, 9), (9, 16, 12, 16), (12, 5, 16, 5), (14, 11, 17, 11), (16, 8, 20, 8), (18, 14, 21, 14), (23, 11, 26, 11)],
              [(0, 0, 29, 2), (4, 5, 7, 5), (5, 8, 8, 8), (3, 11, 6, 11), (6, 14, 9, 14), (11, 16, 14, 16), (14, 12, 16, 12), (19, 16, 22, 16), (22, 13, 26, 13), (20, 10, 22, 10), (22, 7, 24, 7), (20, 4, 22, 4)],
              [(0, 0, 29, 2), (4, 7, 7, 7), (4, 11, 7, 11), (4, 15, 7, 15), (9, 5, 13, 5), (9, 9, 13, 9), (9, 13, 13, 13), (15, 7, 16, 7), (15, 11, 16, 11), (15, 15, 16, 15), (18, 5, 22, 5), (18, 9, 22, 9), (18, 13, 22, 13), (24, 7, 27, 7), (24, 11, 27, 11), (24, 15, 27, 15)]]
door_data = [[(0, 2, 1, 6), (29, 2, 30, 6)], [(0, 2, 1, 6), (29, 9, 30, 13)], [(0, 2, 1, 6), (29, 11, 30, 15)], [(0, 2, 1, 6)]]
walls = []
blocks = []
doors = []
check_col = None
biggrayskels = []
banshees = []
chaindemons = []
spawn_timer = None
ice_pillars = []
niflheim = None
items = []

def set_map():
    global map, walls, doors, blocks, check_col, minimap, biggrayskels, spawn_timer, items
    for o in items:
        if o.state == 'drop':
            game_world.remove_object(o)
    if map.map_num == 1:
        items.append(Item_object.Item('colt', 100, 100, 'drop', 10, 0, 0, 0.3))
    elif map.map_num == 2:
        items.append(Item_object.Item('saber', 600, 500, 'drop', 15, 0, 0, 0.15))
    elif map.map_num == 3:
        items.append(Item_object.Item('shotgun', 200, 200, 'drop', 5, 0, 0, 0.6))
    game_world.add_objects(items, 2)
    minimap.num = map.map_num
    for o in walls:
        game_world.remove_collision_object(o)
    for o in blocks:
        game_world.remove_collision_object(o)
    for o in doors:
        game_world.remove_collision_object(o)
    walls = [Map_bb.Wall(*l) for l in wall_data[map.map_num]]
    blocks = [Map_bb.Block(*l) for l in block_data[map.map_num]]
    doors = [Map_bb.Door(*l) for l in door_data[map.map_num]]
    game_world.add_collision_pairs(hero, walls, 'hero:wall')
    game_world.add_collision_pairs(hero, blocks, 'hero:block')
    game_world.add_collision_pairs(hero, doors, 'hero:door')
    game_world.add_collision_pairs(hero, items, 'hero:item')
    spawn_timer = time.time()
    if map.map_num == 3:
        map.boss_bgm.set_volume(32)
        map.boss_bgm.repeat_play()
    elif map.map_num == 0:
        map.normal_bgm.set_volume(32)
        map.normal_bgm.repeat_play()

    for o in biggrayskels:
        game_world.remove_object(o)
    for o in banshees:
        game_world.remove_object(o)
    for o in chaindemons:
        game_world.remove_object(o)


def enter():
    global map, minimap, hero, back_ground, walls, doors, blocks, biggrayskels, banshees, niflheim
    back_ground = load_image('./Resource\ice_tile\BGLayer_0 #218364.png')
    map = Map_object.Map()
    minimap = UI_object.Minimap(map.map_num)
    hero = Hero_object.Hero()
    biggrayskels.append(Biggrayskel_object.Biggrayskel(16 * 40, 2 * 40, 5, 100, 0))
    biggrayskels.append(Biggrayskel_object.Biggrayskel(7 * 40, 5 * 40, 5, 100, 0))
    biggrayskels.append(Biggrayskel_object.Biggrayskel(24 * 40, 8 * 40, 5, 100, 0))
    biggrayskels.append(Biggrayskel_object.Biggrayskel(17 * 40, 13 * 40, 5, 100, 0))
    biggrayskels.append(Biggrayskel_object.Biggrayskel(10 * 40, 12 * 40, 5, 100, 0))
    banshees.append(Banshee_object.Banshee(6 * 40, 2 * 40, 4, 100, 5))
    banshees.append(Banshee_object.Banshee(4 * 40, 10 * 40, 4, 100, 5))
    banshees.append(Banshee_object.Banshee(10 * 40, 16 * 40, 4, 100, 5))
    banshees.append(Banshee_object.Banshee(14 * 40, 5 * 40, 4, 100, 5))
    banshees.append(Banshee_object.Banshee(14 * 40, 11 * 40, 4, 100, 5))
    banshees.append(Banshee_object.Banshee(19 * 40, 14 * 40, 4, 100, 5))
    banshees.append(Banshee_object.Banshee(20 * 40, 8 * 40, 4, 100, 5))
    chaindemons.append(Chaindemon_object.Chaindemon(20 * 40, 4 * 40, 7, 100, 7))
    chaindemons.append(Chaindemon_object.Chaindemon(25 * 40, 9 * 40, 7, 100, 7))
    chaindemons.append(Chaindemon_object.Chaindemon(20 * 40, 16 * 40, 7, 100, 7))
    chaindemons.append(Chaindemon_object.Chaindemon(14 * 40, 8 * 40, 7, 100, 7))
    chaindemons.append(Chaindemon_object.Chaindemon(8 * 40, 15 * 40, 7, 100, 7))
    chaindemons.append(Chaindemon_object.Chaindemon(4 * 40, 11 * 40, 7, 100, 7))
    niflheim = Niflheim_object.Niflheim(600, 440, 20, 100, 10)
    set_map()
    # walls = [Map_bb.Wall(*l) for l in wall_data[map.map_num]]
    # blocks = [Map_bb.Block(*l) for l in block_data[map.map_num]]
    # doors = [Map_bb.Door(*l) for l in door_data[map.map_num]]
    game_world.add_objects(walls, 0)
    game_world.add_object(map, 0)
    game_world.add_object(hero, 1)
    game_world.add_object(minimap, 2)
    # game_world.add_collision_pairs(hero, walls, 'hero:wall')
    # game_world.add_collision_pairs(hero, blocks, 'hero:block')
    # game_world.add_collision_pairs(hero, doors, 'hero:door')


def collide(a, b):
    left_a, bottom_a, right_a, top_a = a.get_bb()
    left_b, bottom_b, right_b, top_b = b.get_bb()
    if left_a > right_b: return False
    if right_a < left_b: return False
    if top_a < bottom_b: return False
    if bottom_a > top_b: return False

    return True

def monster_spawn():
    if map.map_num == 0 and map.state < 3:
        game_world.add_objects(biggrayskels, 1)
        game_world.add_collision_pairs(hero, biggrayskels, 'hero:monster')
        game_world.add_collision_pairs(biggrayskels, blocks, 'biggrayskel:block')
    if map.map_num == 1 and map.state < 3:
        game_world.add_objects(banshees, 1)
        game_world.add_collision_pairs(hero, banshees, 'hero:monster')
    if map.map_num == 2 and map.state < 3:
        game_world.add_objects(chaindemons, 1)
        game_world.add_collision_pairs(hero, chaindemons, 'hero:monster')
    if map.map_num == 3 and map.state < 3:
        game_world.add_object(niflheim, 1)
        game_world.add_collision_pairs(hero, niflheim, 'hero:monster')

def check_monster():
    if map.map_num == 0:
        if not biggrayskels:
            return False
    if map.map_num == 1:
        if not banshees:
            return False
    if map.map_num == 2:
        if not chaindemons:
            return False
    return True


def update():
    # hero.update(camera.x)
    Camera.camera.update(hero)
    if time.time() - spawn_timer > 2 and map.state == 0:
        monster_spawn()
        map.state = 1
    if not check_monster():
        map.state = 2
    if hero.mouse_x > hero.x + Camera.camera.x:
        hero.face_dir = 1
    else:
        hero.face_dir = -1
    for object in game_world.all_object():
        object.update()
    for a, b, group in game_world.all_collision_pairs():
        if collide(a, b):
            a.handle_collision(b, group)
            b.handle_collision(a, group)


def draw_world():
    global map, camera, minimap
    back_ground.clip_draw(0, 0, back_ground.w, back_ground.h, Camera.camera.x + 1200 // 2, Camera.camera.y + 800 // 2, 1200, 800)
    for object in game_world.all_object():
        object.draw(Camera.camera.x, Camera.camera.y)


def draw():
    clear_canvas()
    draw_world()
    update_canvas()
    pass

def handle_events():
    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            game_framework.quit()
        elif (event.type, event.key) == (SDL_KEYDOWN, SDLK_ESCAPE):
            game_framework.quit()
        elif (event.type, event.key) == (SDL_KEYDOWN, SDLK_m):
            hero.invincible_mode = not hero.invincible_mode
        else:
            hero.handle_event(event)
    # events = get_events()
    # for event in events:
    #     if event.type == SDL_QUIT:
    #         game_framework.quit()
    #     elif event.type == SDL_KEYDOWN:
    #         match event.key:
    #             # 맵 이동을 위한 임시 문장
    #             case pico2d.SDLK_1:
    #                 map.map_num = 0
    #             case pico2d.SDLK_2:
    #                 map.map_num = 1
    #             case pico2d.SDLK_3:
    #                 map.map_num = 2
    #             case pico2d.SDLK_4:
    #                 map.map_num = 3
    #             # 주인공 좌우이동
    #             case pico2d.SDLK_a:
    #                 hero.dir = -1
    #                 hero.state['run'] = True
    #             case pico2d.SDLK_d:
    #                 hero.dir = 1
    #                 hero.state['run'] = True
    #             # 점프
    #             case pico2d.SDLK_SPACE:
    #                 if collision_hero_map():
    #                     hero.state['jump'] = 7
    #             case pico2d.SDLK_LSHIFT:
    #                 if hero.state['dash'] == 0:
    #                     hero.state['dash'] = 7
    #     elif event.type == SDL_KEYUP:
    #         hero.frame = 0
    #         match event.key:
    #             case pico2d.SDLK_a:
    #                 if hero.dir == -1:
    #                     hero.state['run'] = False
    #             case pico2d.SDLK_d:
    #                 if hero.dir == 1:
    #                     hero.state['run'] = False





def exit():
    pass

def pause():
    pass

def resume():
    pass



if __name__ == '__main__':
    open_canvas()
    game_framework.run(__name__)
    close_canvas()