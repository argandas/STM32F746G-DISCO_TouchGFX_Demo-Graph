#include <gui/main_screen/MainView.hpp>
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
    setCount(0);
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
