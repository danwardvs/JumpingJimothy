#include "button.h"


// Defaults
button::button(){
  this -> x = 0;
  this -> y = 0;
  this -> text = "";
  this -> image = nullptr;
  this -> button_font = nullptr;
  this -> hovering = false;

  padding_x = 10;
  padding_y = 10;
}

// Constructor
button::button( int x, int y, std::string text, ALLEGRO_FONT *button_font, int width, int height, int padding_x, int padding_y){

  this -> alpha = 255;
  // Literally this
  this -> x = x;
  this -> y = y;
  this -> text = text;
  this -> image = nullptr;
  this -> button_font = button_font;

  this -> visible = true;
  this -> active = true;

  this -> mouse_released=false;
  this -> old_mouse_down=false;
  this -> hovering = false;

  if( button_font != nullptr){
    this -> width = al_get_text_width( button_font, text.c_str());
    this -> height = al_get_font_line_height( button_font);
  }
  else{
    this -> width = width;
    this -> height = height;
  }

  this -> padding_x = padding_x;
  this -> padding_y = padding_y;
}

// Destruct
button::~button(){
  if( image != nullptr)
    al_destroy_bitmap( image);
}

// Sets an image
void button::setImage( ALLEGRO_BITMAP *image){
  this -> image = image;
  this -> width = al_get_bitmap_width( this -> image);
  this -> height = al_get_bitmap_height( this -> image);
}

// Set new font
void button::setFont( ALLEGRO_FONT *font){
  this -> button_font = font;
  if( button_font != nullptr){
    this -> width = al_get_text_width( button_font, text.c_str());
    this -> height = al_get_font_line_height( button_font);
  }
}
void button::toggleVisibility(){

  visible=!visible;
}


void button::toggleStatus(){

  visible=!visible;
  active=!active;
}

// Update
void button::update(){

  mouse_released = false;
  if(active){
    if( hovering && old_mouse_down && !mouseListener::mouse_button & 1){
      mouse_released = true;

        }
    old_mouse_down = hovering && mouseListener::mouse_button & 1;
    hovering = mouseListener::mouse_x > x && mouseListener::mouse_x < x + getWidth() &&
               mouseListener::mouse_y > y && mouseListener::mouse_y < y + getHeight();
  }else{
    hovering=false;
  }
}

// True if hovering
bool button::hover(){
  return hovering;
}

// True if clicked
bool button::clicked(){
  return hovering && mouseListener::mouse_pressed & 1;
}

bool button::mouseReleased(){
  return mouse_released;
}

// Draw
void button::draw(){
  if(visible){
    // Backdrop
    al_draw_filled_rectangle( x, y, x + width + padding_x * 2, y + height + padding_y * 2, al_map_rgba( 200 + 20 * hovering, 200 + 20 * hovering, 200 + 20 * hovering,alpha));
    al_draw_rectangle( x, y, x + width + padding_x * 2, y + height + padding_y * 2, al_map_rgba( 0, 0, 0,alpha), 2);

    // Text
    if( button_font != nullptr)
      al_draw_text( button_font, al_map_rgba( 0, 0, 0,alpha), x + padding_x, y + padding_y, 0, text.c_str());

    // Image if avail
    if( image != nullptr)
      al_draw_bitmap( image, x + padding_x, y + padding_y, 0);
  }
}
