#include "game.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "resource_manager.h"

Game::Game(unsigned int width, unsigned int height)
    : width(width), height(height), keys() {}

Game::~Game() {}

void Game::init() {
  ResourceManager::LoadShader("assets/shaders/line.vs",
                              "assets/shaders/line.frag", NULL, "line");

  glm::mat4 projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("line").use().setMat4("projection", projection);
}

void Game::update(float dt) {}

void Game::processInput(float dt) {}

void Game::render() {}
