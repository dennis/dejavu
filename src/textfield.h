#ifndef TEXTFIELD_H__
#define TEXTFIELD_H__

// This file originates from from Gosu (examples/TextInput.cpp), but have been slightly modified
//
#include <Gosu/Gosu.hpp>
#include <boost/scoped_ptr.hpp>

class TextField : public Gosu::TextInput {
private:
  Gosu::Window& window;
  Gosu::Font& font;
  double x, y;
    
public:
  // Some constants that define our appearance.
  // (Can't use Gosu::Color that easily as a class constant, thanks to C++.)
  static const unsigned long INACTIVE_COLOR  = 0xcc666666;
  static const unsigned long ACTIVE_COLOR    = 0xccff6666;
  static const unsigned long SELECTION_COLOR = 0xcc0000ff;
  static const unsigned long CARET_COLOR     = 0xffffffff;
  static const int PADDING = 5;
  
  TextField(Gosu::Window& window_, Gosu::Font& font_, double x_, double y_)
  : window(window_), font(font_), x(x_), y(y_) {
    // Start with a self-explanatory text in each field.
  }
  
  void draw() const {
    // Depending on whether this is the currently selected input or not, change the
    // background's color.
    Gosu::Color backgroundColor;
    if (window.input().textInput() == this)
      backgroundColor = ACTIVE_COLOR;
    else
      backgroundColor = INACTIVE_COLOR;

    window.graphics().drawQuad(
      x - PADDING,           y - PADDING,            backgroundColor,
      x + width() + PADDING, y - PADDING,            backgroundColor,
      x - PADDING,           y + height() + PADDING, backgroundColor,
      x + width() + PADDING, y + height() + PADDING, backgroundColor, 0);
  
    // Calculate the position of the caret and the selection start.
    double posX = x + font.textWidth(text().substr(0, caretPos()));
    double selX = x + font.textWidth(text().substr(0, selectionStart()));

    // Draw the selection background, if any; if not, sel_x and pos_x will be
    // the same value, making this quad empty.
    window.graphics().drawQuad(
      selX, y,            SELECTION_COLOR,
      posX, y,            SELECTION_COLOR,
      selX, y + height(), SELECTION_COLOR,
      posX, y + height(), SELECTION_COLOR, 0);

    // Draw the caret; again, only if this is the currently selected field.
    if (window.input().textInput() == this)
      window.graphics().drawLine(
        posX, y,            CARET_COLOR,
        posX, y + height(), CARET_COLOR, 0);

    // Finally, draw the text itself!
    font.draw(text(), x, y, 0);
  }
  
  // This text field grows with the text that's being entered.
  // (Without clipping, one has to be a bit creative about this ;) )
  double width() const {
    return font.textWidth(text());
  }
  
  double height() const {
    return font.height();
  }
  
  bool isUnderPoint(double mouseX, double mouseY) {
    return mouseX > x - PADDING && mouseX < x + width() + PADDING &&
          mouseY > y - PADDING and mouseY < y + height() + PADDING;
  }
};

// Helper magic to get size of static array, MUCH safer than sizeof hackery.
template<typename T, std::size_t Len>
std::size_t lengthof(const T(&) [Len]) {
  return Len;
}

#endif
// ex: ts=2 sw=2 et sr
