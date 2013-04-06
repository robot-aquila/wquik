========================================================================
    STATIC LIBRARY : xltable Project Overview
========================================================================

xltable.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

/////////////////////////////////////////////////////////////////////////////

xltable - библиотека классов для чтения таблиц формата XlTable (Fast Table
Format). Работает на уровне потока байт, преобразовывая его в объект доступа
к области таблицы. 

Для получения таблицы достаточно
1. Создать объект доступа к потоку байт
2. Передать поток конструктору таблицы
3. Освободить поток
4. Обработать ячейки таблицы и освободить таблицу

