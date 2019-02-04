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
    
    virtual void addGraphValue(int value);
    
    int map(int x, int in_min, int in_max, int out_min, int out_max);

    void setCount(int countValue);
    void setLimitEffects(bool belowUpper, bool aboveLower);

    void handleTickEvent();
    
    static const int MAX_Y_VALUE = 80;
    static const int MIN_Y_VALUE = -20;
    static const int MAX_Y_DELTA = 20;
    
    static const int GRID_MAX_VALUE_Y = MAX_Y_VALUE;
    static const int GRID_MIN_VALUE_Y = MIN_Y_VALUE;
    static const int GRID_DIV_VALUE_Y = MAX_Y_DELTA;
    static const int GRID_NUM_LINES_Y = ((MAX_Y_VALUE - MIN_Y_VALUE) / MAX_Y_DELTA);
    
    static const int MAX_Y_VALUE_VALID =  60;
    static const int MIN_Y_VALUE_VALID = -10;
    
    static const int MAX_X_VALUE = 228;
    static const int MAX_X_DELTA = MAX_X_VALUE / Graph::NUMBER_OF_POINTS;


protected:
    Box graphGridLines[GRID_NUM_LINES_Y];
    Box graphLimitsLines[2];
    
    TextAreaWithOneWildcard graphYValues[GRID_NUM_LINES_Y];
    Unicode::UnicodeChar graphYValuesbuf[GRID_NUM_LINES_Y][5];

    Graph primaryGraph;
    
    void DrawGraphGridLines(colortype color);
    
    int count = 0;
    uint8_t graphX = 0;

private:

};

#endif // MAIN_VIEW_HPP
