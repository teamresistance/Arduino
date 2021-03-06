#include "Arduino.h"
#include "Menu.h"

static int DEFAULT_KEY_PIN = 0; 
static int DEFAULT_THRESHOLD = 5;

Menu::Menu(){
  _menuMode = MAINMENU;     //Used to determine how to handle Sel & Esc
  _subMenuPtr = 0;          //Update Pointer to subMenu choice
  _actMenuPtr = 0;          //Active Pointer to subMenu choice

}

void Menu::SetMaxItems(int maxItems){
  _maxItems = maxItems;     //Set the max # of items in the Menu
}

void Menu::SetNames(String * p_names){
  _p_names = p_names;     //Save pointer to menu names
}

int Menu::GetMenuMode() {
  return _menuMode;
}

int Menu::GetActPtr() {
  return _actMenuPtr;
}

String Menu::GetActName() {
  return *(_p_names + _actMenuPtr);
}

int Menu::GetSubPtr() {
  return _subMenuPtr;
}

String Menu::GetSubName() {
  return *(_p_names + _subMenuPtr);
}

void Menu::UpdateMenu(int keyVal){   //Update submenu pointer or action
  
  if (keyVal > NO_KEY && keyVal <= ESC_KEY) {
    switch (keyVal) {
      case 1:               //--Next Prim
        _subMenuPtr = _actMenuPtr;              //Cancel Update
        _menuMode = 0;
        break;
      case 2:               //--Select (Left)
        switch (_menuMode) {
          case MAINMENU:              //MainMenu(0) Mode
            _subMenuPtr = _actMenuPtr;  //Set to prv choice
            _menuMode = SUBMENU;        //and set mode to SubMenu(1)
            break;
          case SUBMENU:               //SubMenu(1) Mode
            _menuMode = CONFMENU;     //Set to Confirm(2) mode
            break;
          case CONFMENU:              //Confirm(2) Mode
            _actMenuPtr = _subMenuPtr;  //Set actMenuPtr to subMenuPtr
            _menuMode = MAINMENU;       //and mode to Main(0) Mode
            break;
          default:
            break;
        }
        break;
      case 3:             //--Up
        _subMenuPtr-- ;             //Decrement subMenuPtr
        if (_subMenuPtr < 0) _subMenuPtr = _maxItems - 1;  //Rap-around
        break;
      case 4:             //--Dn
        _subMenuPtr++;              //Increment subMenuPtr
        if (_subMenuPtr >= _maxItems) _subMenuPtr = 0;          //Rap-around
        break;
      case 5:             //--Esc (Right)
        switch (_menuMode) {
          case MAINMENU:            //Main(0) Mode
            // do nothing.  Should be handled in main code
            break;
          case SUBMENU:             //SubMenu(1)
            _menuMode = MAINMENU;     //Set back to Main(0) Mode
            break;
          case CONFMENU:            //Confirm(2) Mode
            _menuMode = SUBMENU;      //Set back to SubMenu(1) Mode
            break;
          default:
            break;
        }
        break;
      default:        //--Default
        break;
    }
  }
}

