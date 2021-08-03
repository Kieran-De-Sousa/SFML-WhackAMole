
#ifndef WHACKAMOLESFML_GAME_H
#define WHACKAMOLESFML_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  bool collisionCheck(sf::Vector2i click, sf::Sprite parrot, sf::Sprite chick);
  void spawn();
  int RandomPositionX();
  int RandomPositionY();
  int RandomSpeedX();
  int RandomSpeedY();
  bool Reverse();

  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Sprite parrot;
  sf::Texture parrot_texture;
  sf::Sprite chick;
  sf::Texture chick_texture;
  sf::Font font;
  sf::Text title_text;

  bool in_menu;
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Text score_text;
  bool play_selected = true;

  bool parrot_reverse_x = false;
  bool parrot_reverse_y = false;
  bool chick_reverse_x = false;
  bool chick_reverse_y = false;
  float speed_x = rand() % 250 + 100;
  float speed_y = rand() % 250 + 100;


  int window_width = 1080;
  int window_height = 720;

  int score = 0;


};

#endif // WHACKAMOLESFML_GAME_H
