#include <gui/main_screen/MainView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "BitmapDatabase.hpp"

MainView::MainView()
{
    // Support of larger displays for this example
    // is handled by showing a black box in the
    // unused part of the display.
    if (HAL::DISPLAY_WIDTH > backgroundImage.getWidth() ||
            HAL::DISPLAY_HEIGHT > backgroundImage.getHeight())
    {
        backgroundBox.setVisible(true);
    }
}

void MainView::setupScreen()
{
  // Initialize count
    setCount(0);
    
    int graphXOffset = 44;
    int graphYOffset = 10;
    int graphWidth = 415;
    int graphHeight = 150;
    
    for (int i = 0; i < NUMBER_OF_GRID_LINES; i++)
    {
        graphGridLines[i].setColor(Color::getColorFrom24BitRGB(0xB1, 0xB1, 0xB1));
        graphGridLines[i].setPosition(graphXOffset, 38 + 40 * i, graphWidth, 1);
        add(graphGridLines[i]);

        Unicode::snprintf(graphYValuesbuf[i], 5, "%d", 40 - i * 20);
        graphYValues[i].setTypedText(TypedText(T_GRAPH_Y_VALUE));
        graphYValues[i].setWildcard(graphYValuesbuf[i]);
        graphYValues[i].setColor(graphGridLines[i].getColor());
        graphYValues[i].resizeToCurrentText();
        graphYValues[i].setXY(graphGridLines[i].getX() - graphYValues[i].getWidth() - 6, graphGridLines[i].getY() - (graphYValues[i].getTypedText().getFont()->getFontHeight() / 2) - 2);
        add(graphYValues[i]);
    }
   
    // graph.setup(440, 200, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC), Color::getColorFrom24BitRGB(0x24, 0x73, 0xAC));
    
    // Place the graph on the screen
    graph.setXY(20, 20);
    
    // Set the outer dimensions and color of the graph
    graph.setup(440, 200, Color::getColorFrom24BitRGB(0xFF, 0xFF, 0xAC), Color::getColorFrom24BitRGB(0x24, 0x73, 0xAC));
    
    // Set the range for the x and y axis of the graph. That is
    // the max and min x/y value that can be displayed inside the
    // dimension of the graph.
    graph.setRange(0, 50, 0, 200);
    
    graph.setDotShape(0, 30, 5);
    graph.setDotBackgroundShape(0, 30, 7);

    add(graph);
}

void MainView::tearDownScreen()
{
}

void MainView::increaseValue()
{
    if (count < 42)
    {
        count++;
        setCount(count);
    }
}

void MainView::decreaseValue()
{
    if (count > 0)
    {
        count--;
        setCount(count);
    }
}

void MainView::setCount(uint8_t countValue)
{
  
    if (countValue >= 42)
    {
      setLimitEffects(false, true);
    }
    else if (countValue == 0)
    {
      setLimitEffects(true, false);
    }
    else
    {
      setLimitEffects(true, true);
    }
    
    Unicode::snprintf(countTxtBuffer, 3, "%d", countValue);
    // Invalidate text area, which will result in it being redrawn in next tick.
    countTxt.invalidate();
}

void MainView::setLimitEffects(bool belowUpper, bool aboveLower)
{
    flexBtnUp.setTouchable(belowUpper);
    flexBtnDown.setTouchable(aboveLower);

    if (belowUpper)
    {
        flexBtnUp.setBitmaps(Bitmap(BITMAP_SMALL_BTN_ID), Bitmap(BITMAP_SMALL_BTN_PRESSED_ID));
    }
    else
    {
        flexBtnUp.setBitmaps(Bitmap(BITMAP_SMALL_BTN_DISABLE_ID), Bitmap(BITMAP_SMALL_BTN_DISABLE_ID));
    }

    if (aboveLower)
    {
        flexBtnDown.setBitmaps(Bitmap(BITMAP_SMALL_BTN_ID), Bitmap(BITMAP_SMALL_BTN_PRESSED_ID));
    }
    else
    {
        flexBtnDown.setBitmaps(Bitmap(BITMAP_SMALL_BTN_DISABLE_ID), Bitmap(BITMAP_SMALL_BTN_DISABLE_ID));
    }

    flexBtnUp.invalidate();
    flexBtnDown.invalidate();
}

void MainView::addValue()
{
  graph.addValue(graphX, count);
  graphX += 15; 
}

void MainView::handleTickEvent()
{

}
