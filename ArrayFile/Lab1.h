#pragma once

#include "Console.h"
#include "InputManager.h"

#include <iostream>
#include <fstream>
#include <ios>
#include <vector>

#include <time.h>

class Lab1
{

    enum class TASK : int
    {
        NONE,
        T1,
        T2,
        T3
    };

    enum class TASK_ARROW : int
    {
        T1,
        T2,
        T3,
        ESC
    };

    TASK_ARROW ArrTask;

    TASK ThisTask;

    bool OpenLab;

    std::string MenuContent;

public:

    // Singlton pattern:

    static Lab1& GetInstance();

    Lab1(const  Lab1& other) = delete;

    Lab1& operator=(const  Lab1& other) = delete;

    bool IsOpen() const;

    void HendleInput();

    void Update();

    void Render() const;

    ~Lab1();

private:

    Lab1();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void HendleInputMenuTask();
    bool UpdateMenuTask();
    void RenderMenuTask() const;
    void RemoveArrowFromSelectedElement(std::string& element);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int *A, *B;

    void Task1();

    void replacePositiveElements() const;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Task2();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Task3();
};

