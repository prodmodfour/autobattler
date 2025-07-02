#pragma once

#include "GridDimensions.h"

class PlayerGridDimensions : public GridDimensions {
public:
    PlayerGridDimensions()
    {
        this->rows = 7;
        this->columns = 8;
    }
    
    int32 GetRows() const override { return rows; }
    int32 GetColumns() const override { return columns; }

private:
    int32 rows;
    int32 columns;
};
