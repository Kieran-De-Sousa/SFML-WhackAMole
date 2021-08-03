
#include "Game.h"
#include <iostream>
#include <random>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  // Initialisation of sprites and checks if they are correctly opened.
  if(!background_texture.loadFromFile("Data/Images/background.png"))
  {
    std::cout << "Background texture did not load \n";
  }
  background.setTexture(background_texture);

  // Creation of parrot entity
  if(!parrot_texture.loadFromFile("Data/Images/parrot.png"))
  {
    std::cout << "Parrot texture did not load \n";
  }
  parrot.setTexture(parrot_texture);
  parrot.setScale(0.5f, 0.5f);
  parrot.setPosition(RandomPositionX()/1.5, RandomPositionY()/1.5);
  Reverse();

  // Creation of chick entity
  if(!chick_texture.loadFromFile("Data/Images/chick.png"))
  {
    std::cout << "Chick texture did not load \n";
  }
  chick.setTexture(chick_texture);
  chick.setScale(1.0f, 1.0f);
  chick.setPosition(RandomPositionX()/1.5, RandomPositionY()/1.5);
  Reverse();

  // Initialisation of text and checks if they are correctly opened.
  if(!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font did not load \n";
  }
  title_text.setString("thwack-a-para(keet)");
  title_text.setFont(font);
  title_text.setCharacterSize(35);
  title_text.setFillColor(sf::Color(22,44,25,210));
  title_text.setPosition(
    window.getSize().x/2 - title_text.getGlobalBounds().width/2,
    window.getSize().y/2 - title_text.getGlobalBounds().height/2);

  //Scoreboard text
  score_text.setString(std::to_string(score));
  score_text.setFont(font);
  score_text.setCharacterSize(35);
  score_text.setFillColor(sf::Color(22,44,25,210));
  score_text.setPosition(
    window.getSize().x/10 - title_text.getGlobalBounds().width/10,
    window.getSize().y/10 - title_text.getGlobalBounds().height/10);

  // Menu screen text
  in_menu = true;
  menu_text.setString("Welcome to thwack-a-para(keet) [PATENT PENDING]\n"
                      "                           Please select an option: \n");
  menu_text.setFont(font);
  menu_text.setCharacterSize((20));
  menu_text.setFillColor(sf::Color(0, 255, 55, 255));
  menu_text.setPosition(
    window.getSize().x/2 - menu_text.getGlobalBounds().width/2,
    window.getSize().y/4 - menu_text.getGlobalBounds().height/4);

  // Play option text
  play_option.setString("Play");
  play_option.setFont(font);
  play_option.setCharacterSize(20);
  play_option.setFillColor(sf::Color(0, 255, 55, 255));
  play_option.setPosition(
    window.getSize().x/4 - play_option.getGlobalBounds().width/4,
    window.getSize().y/2 - play_option.getGlobalBounds().height/4);

  // Quit option text
  quit_option.setString("Quit");
  quit_option.setFont(font);
  quit_option.setCharacterSize(20);
  quit_option.setFillColor(sf::Color(0, 255, 55, 255));
  quit_option.setPosition(
    window.getSize().x/4*3 - quit_option.getGlobalBounds().width/4*3,
    window.getSize().y/2 - quit_option.getGlobalBounds().height/4);

  return true;
}

void Game::update(float dt)
{
  // Parrot checks if its position is offscreen and adjusts its trajectory
  if ((parrot.getPosition().x > (window.getSize().x - parrot.getGlobalBounds().width))
  || (parrot.getPosition().x < 0))
  {
    parrot_reverse_x = !parrot_reverse_x;
  }
  if ((parrot.getPosition().y > (window.getSize().y - parrot.getGlobalBounds().height))
  || (parrot.getPosition().y < 0))
  {
    parrot_reverse_y = !parrot_reverse_y;
  }

  // Chick checks if its position is offscreen and adjusts its trajectory
  if ((chick.getPosition().x > (window.getSize().x - chick.getGlobalBounds().width))
      || (chick.getPosition().x < 0))
  {
    chick_reverse_x = !chick_reverse_x;
  }
  if ((chick.getPosition().y > (window.getSize().y - chick.getGlobalBounds().height))
      || (chick.getPosition().y < 0))
  {
    chick_reverse_y = !chick_reverse_y;
  }

  // Checks for the parrots X and Y positions
  if (parrot_reverse_x == true and parrot_reverse_y == true)
  {
    parrot.move(1.0f * speed_x * dt, 1.0f * speed_y * dt);
  }
  else if (parrot_reverse_x == true and parrot_reverse_y == false)
  {
    parrot.move(1.0f * speed_x * dt, -1.0f * speed_y * dt);
  }
  else if (parrot_reverse_x == false and parrot_reverse_y == true)
  {
    parrot.move(-1.0f * speed_x * dt, 1.0f * speed_y * dt);
  }
  else
  {
    parrot.move(-1.0f * speed_x * dt, -1.0f * speed_y * dt);
  }

  // Checks for the chick X and Y positions
  if (chick_reverse_x == true and chick_reverse_y == true)
  {
    chick.move(1.0f * speed_x * dt, 1.0f * speed_y * dt);
  }
  else if (chick_reverse_x == true and chick_reverse_y == false)
  {
    chick.move(1.0f * speed_x * dt, -1.0f * speed_y * dt);
  }
  else if (chick_reverse_x == false and chick_reverse_y == true)
  {
    chick.move(-1.0f * speed_x * dt, 1.0f * speed_y * dt);
  }
  else
  {
    chick.move(-1.0f * speed_x * dt, -1.0f * speed_y * dt);
  }

  score_text.setString(std::to_string(score));
}

void Game::render()
{
  if (in_menu == true)
  {
    window.draw(menu_text);
    window.draw(play_option);
    window.draw(quit_option);
  }
  else
  {
    window.draw(background);
    window.draw(title_text);
    window.draw(score_text);
    window.draw(parrot);
    window.draw(chick);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  // check if in bounds of parrot Sprite
  if (collisionCheck(click, parrot, chick))
  {
    score = score + 1;
    spawn();
  }
}

void Game::keyPressed(sf::Event event)
{
  if ((event.key.code == sf::Keyboard::Left) ||
  (event.key.code == sf::Keyboard::Right))
  {
    play_selected =! play_selected;
    if(play_selected)
    {
      play_option.setString(">>Play<<");
      quit_option.setString("Quit");
    }
    else
    {
      play_option.setString("Play");
      quit_option.setString(">>Quit<<");
    }
  }
  else if (event.key.code == sf::Keyboard::Enter)
  {
    if(play_selected)
    {
      in_menu = false;
    }
    else
    {
      window.close();
    }
  }
}


bool Game::collisionCheck(sf::Vector2i click, sf::Sprite parrot, sf::Sprite chick)
{
  // Checks if the click location was within the bounding box of the parrot
  if (click.x > parrot.getPosition().x && click.y > parrot.getPosition().y
      && click.x > parrot.getGlobalBounds().width && click.y >
      parrot.getGlobalBounds().height)
  {
    std::cout << "\nNice shootin' tex!";
    return true;
  }
  // Checks if the click location was within the bounding box of the chick
  else if (click.x > chick.getPosition().x && click.y >
           chick.getPosition().y && click.x > chick.getGlobalBounds().width
           && click.y > chick.getGlobalBounds().height)
  {
    std::cout << "\nDON'T SHOOT THE CHICK YOU FOOL!!!";
    score -= 5;
    return false;
  }
  else
  {
    std::cout << "\nYou missed!!!";
    score -= 1;
    return false;
  }
}

void Game::spawn()
{
  parrot.setPosition(RandomPositionX()/1.5, RandomPositionY()/1.5);
  chick.setPosition(RandomPositionX()/1.5, RandomPositionY()/1.5);
  speed_x = RandomSpeedX();
  speed_y = RandomSpeedY();
  Reverse();
}

int Game::RandomPositionX()
{
  int random_number = rand() % window_width + 1;
  return random_number;
}

int Game::RandomPositionY()
{
  int random_number = rand() % window_height + 1;
  return random_number;
}

int Game::RandomSpeedX()
{
  return rand() % 250 + 100;
}

int Game::RandomSpeedY()
{
  return rand() % 250 + 100;
}

bool Game::Reverse()
{
  int decision = rand() % 4 + 1;
  if (decision == 1)
  {
    parrot_reverse_x = parrot_reverse_y = true;
    chick_reverse_x = true;
    chick_reverse_y = false;
  }
  else if (decision == 2)
  {
    parrot_reverse_x = true;
    parrot_reverse_y = false;
    chick_reverse_x = chick_reverse_y = true;
  }
  else if (decision == 3)
  {
    parrot_reverse_x = false;
    parrot_reverse_y = true;
    chick_reverse_x = chick_reverse_y = false;

  }
  else if (decision == 4)
  {
    parrot_reverse_x = parrot_reverse_y = false;
    chick_reverse_x = false;
    chick_reverse_y = true;
  }
}
