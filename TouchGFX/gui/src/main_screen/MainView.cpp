#include <gui/main_screen/MainView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include "BitmapDatabase.hpp"

MainView::MainView() : 
      count(MAX_Y_VALUE/2)
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

int MainView::map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;
}

void MainView::setupScreen()
{   
    int graphXOffset = 40;
    int graphYOffset = 0;
    
    /* Calculate Graph dimensions based on container's dimensions */
    int graphWidth = graphContainer.getWidth() - graphXOffset - 10;
    int graphHeight = graphContainer.getHeight() - graphYOffset;

    /* Setup Graph area and dimensions */
    primaryGraph.setXY(graphXOffset, graphYOffset);
    primaryGraph.setup(graphWidth, graphHeight, Color::getColorFrom24BitRGB(0xF1, 0xC6, 0x1A), Color::getColorFrom24BitRGB(0x89, 0x70, 0x0E));
    primaryGraph.setDotShape(0, 30, 5);
    primaryGraph.setDotBackgroundShape(0, 30, 8);
    primaryGraph.graphLine.setLineWidth(3);
    
    // primaryGraph.setDotsVisible(false);
    // primaryGraph.setDotsBackgroundVisible(false);
    // primaryGraph.setAreaVisible(false);
    
    DrawGraphGridLines(Color::getColorFrom24BitRGB(0xB1, 0xB1, 0xB1));
    
    /* Add graph to container after drawing lines to respect the Z-axis order */
    graphContainer.add(primaryGraph);
    
    // Initialize count
    setCount(count);
}

void MainView::tearDownScreen()
{
}

void MainView::DrawGraphGridLines(colortype color)
{
    touchgfx_printf("GRID_NUM_LINES_Y = %d\r\n", GRID_NUM_LINES_Y);

    int graphLineY = 0;
    int expected = 0;
    
    for (int i = 0; i < GRID_NUM_LINES_Y; i++)
    {
      expected = GRID_MIN_VALUE_Y + (i * GRID_DIV_VALUE_Y);
      
      touchgfx_printf("map(%d,%d,%d,%d,%d)\r\n", expected, GRID_MIN_VALUE_Y, GRID_MAX_VALUE_Y, 0, primaryGraph.getHeight());
      
      graphLineY = map(expected, GRID_MIN_VALUE_Y, GRID_MAX_VALUE_Y, 0, primaryGraph.getHeight());
      
      touchgfx_printf("Grid Set Y[%d] (%d)\r\n", i, expected);
      touchgfx_printf("Grid Got Y[%d] (%d)\r\n", i, graphLineY);

      /* Draw line */
      graphGridLines[i].setColor(color);
      graphGridLines[i].setPosition(primaryGraph.getX(), graphLineY, primaryGraph.getWidth(), 1);

      touchgfx_printf("Actual Line[%d] (%d, %d)\r\n\r\n", i, graphGridLines[i].getX(), graphGridLines[i].getY());

      /* Create label */
      Unicode::snprintf(graphYValuesbuf[i], 5, "%d", MAX_Y_VALUE - i * MAX_Y_DELTA);
      graphYValues[i].setTypedText(TypedText(T_GRAPH_Y_VALUE));
      graphYValues[i].setWildcard(graphYValuesbuf[i]);
      graphYValues[i].setColor(color);
      graphYValues[i].resizeToCurrentText();
      graphYValues[i].setXY(graphGridLines[i].getX() - graphYValues[i].getWidth() - 6, graphGridLines[i].getY() - (graphYValues[i].getTypedText().getFont()->getFontHeight() / 2) - 2);

      /* Add line and label to container */
      graphContainer.add(graphGridLines[i]);
      graphContainer.add(graphYValues[i]);
    }
}


void MainView::increaseValue()
{
    if (count < MAX_Y_VALUE)
    {
      count++;
        setCount(count);
    }
}

void MainView::decreaseValue()
{
    if (count > MIN_Y_VALUE)
    {
      count--;
        setCount(count);
    }
}

void MainView::setCount(int countValue)
{   
    if (countValue >= MAX_Y_VALUE)
    {
      setLimitEffects(false, true);
    }
    else if (countValue <= MIN_Y_VALUE)
    {
      setLimitEffects(true, false);
    }
    else
    {
      count = countValue;
      setLimitEffects(true, true);
    }
    
    Unicode::snprintf(countTxtBuffer, COUNTTXT_SIZE, "%d", count);
    // Invalidate text area, which will result in it being redrawn in next tick.
    countTxt.invalidate();
    addGraphValue(count);
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
  static bool order = true;
  static const uint8_t delta = 10;
  
  if (order == true)
  {
    if ((count + delta) >= MAX_Y_VALUE)
    {
      order = false;
      setCount(count - delta);
    }
    else
    {
      setCount(count + delta);
    }
  }
  else
  {
    if ((count - delta) <= MIN_Y_VALUE)
    {
      order = true;
      setCount(count + delta);
    }
    else
    {
      setCount(count - delta);
    } 
  }
}

void MainView::handleTickEvent()
{

}

void MainView::addGraphValue(int value)
{
  primaryGraph.addValue(graphX, map(value, MIN_Y_VALUE, MAX_Y_VALUE, 30, 370));
  graphX += MAX_X_DELTA; 
}

