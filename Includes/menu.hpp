#ifndef MENU_HPP
#define MENU_HPP

#include "config.hpp"
#include "font.h"

#include <vector>
#include <string>


class MenuNode;
class Menu;

class MenuItem {
public:
  MenuItem(std::string const& label);
  MenuItem(MenuNode *parent, std::string const& label);
  virtual ~MenuItem();
  virtual void execute(Menu *) = 0;
  MenuNode *getParent() const;
  std::string_view getLabel() const;

  void setParent(MenuNode* parent);
protected:
  MenuNode *parentNode;
  const std::string label;
};

class MenuNode : public MenuItem {
public:
  MenuNode(std::string const& label);
  MenuNode(MenuNode *parent, std::string const& label);
  ~MenuNode();
  void execute(Menu *);
  size_t getSelected();
  std::vector<MenuItem*> *getChildNodes();
  void addNode(MenuItem *node);

  void up();
  void down();
protected:
  size_t selected = 0;
  std::vector<MenuItem*> childNodes;
};

class MenuXbe : public MenuNode {
public:
  MenuXbe(std::string const& label, std::string const& path);
  MenuXbe(MenuNode *parent, std::string const& label, std::string const& path);
  ~MenuXbe();
  void execute(Menu *menu);
protected:
  std::string path;
};

class MenuLaunch : public MenuItem {
public:
  MenuLaunch(std::string const& label, std::string const& path);
  ~MenuLaunch();
  void execute(Menu *);
protected:
  std::string path;
};

class Menu {
public:
  Menu(const Config &config, Renderer &renderer);
  void render(Font &font);
  MenuNode *getCurrentMenu();
  void setCurrentMenu(MenuNode *);

  void up();
  void down();
  void back();
  void execute();
protected:
  Renderer &renderer;
  MenuNode rootNode;
  MenuNode *currentMenu;
};

#endif
