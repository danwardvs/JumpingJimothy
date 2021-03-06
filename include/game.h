/**
 * GAME
 * A.D.S. Games
 * 05/05/2017
**/
#ifndef GAME_H
#define GAME_H

#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <Box2D/Box2D.h>

#include <mouseListener.h>
#include <keyListener.h>
#include <joystickListener.h>

#include "state.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

#include <Box.h>
#include <StaticBox.h>
#include <tools.h>
#include <Character.h>
#include <Goat.h>
#include <CollisionBox.h>
#include <DynamicBox.h>
#include <Explosive.h>
#include <button.h>
#include <LevelSelect.h>
#include "Sound.h"
#include "MusicManager.h"

class game : public state{
  public:
    // Construct / destruct
    game();
    ~game();

    // Override parent
    void update();
    void draw();
    bool level_complete();

    // Test mode
    static bool testing;
    static const char *testing_file_name;
    static int level_to_start;

  private:
    // Functions
    void load_world(int);
    void b2_setup();
    void load_sprites();
    void reset();

    // Creation code
    Box *create_dynamic_box(float newX, float newY, float newWidth, float newHeight,float newVelX,float newVelY,BITMAP*,  bool newBodyType, bool newIsSensor);
    Box *create_explosive_box(float,float,int,bool);
    Box *create_static_box(float newX, float newY,BITMAP*,BITMAP*, BITMAP*, BITMAP*);
    Box *create_collision_box(float newX, float newY,float,float);

    Goat *create_goat(float,float);
    Character *create_character(float newX, float newY);

    // Our character and goat
    Goat *gameGoat = nullptr;
    Character *gameCharacter = nullptr;

    // Game variables
    std::vector<Box*> gameBoxes;
    Box *newBox;
    Box *rootBox;
    b2Body* groundBody;

    int level;
    bool first_play;
    bool static_mode;

    ALLEGRO_FONT *game_font;
    ALLEGRO_FONT *help_font;
    ALLEGRO_FONT *edit_font;

    // Bitmaps
    ALLEGRO_BITMAP *box;
    ALLEGRO_BITMAP *box_repel;
    ALLEGRO_BITMAP *box_repel_direction;
    ALLEGRO_BITMAP *character;
    ALLEGRO_BITMAP *goat_sprite;
    ALLEGRO_BITMAP *goat_map;
    ALLEGRO_BITMAP *static_tileset;
    ALLEGRO_BITMAP *tiles[4][48];
    ALLEGRO_BITMAP *play;
    ALLEGRO_BITMAP *pause;
    ALLEGRO_BITMAP *help;

    ALLEGRO_BITMAP *new_dynamic_tile[100];
    //TODO FIX WHEN NOT DEAD INSIDE

    // Samples

    Sound toggle_off;
    Sound toggle_on;
    Sound death;

    Button testing_back_button;


    // Box2D world parameters
    b2Vec2 gravity;
    float32 timeStep;
    int32 velocityIterations;
    int32 positionIterations;
    b2World *gameWorld;
    bool doSleep;
};

#endif // GAME_H
