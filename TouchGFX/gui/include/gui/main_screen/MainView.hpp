#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/main_screen/graph_widget/Graph.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void increaseValue();
    virtual void decreaseValue();

    virtual void addValue();

    void setCount(uint8_t countValue);
    void setLimitEffects(bool belowUpper, bool aboveLower);

    void handleTickEvent();
    


protected:
    static const int NUMBER_OF_GRID_LINES = 4;

    Box graphGridLines[NUMBER_OF_GRID_LINES];
    
    TextAreaWithOneWildcard graphYValues[NUMBER_OF_GRID_LINES];
    Unicode::UnicodeChar graphYValuesbuf[NUMBER_OF_GRID_LINES][5];

    Graph graph;
    
    uint8_t count = 0;
    uint8_t graphX = 0;

private:

};

#endif // MAIN_VIEW_HPP
