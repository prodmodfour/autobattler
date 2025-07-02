#pragma once

class GridDimensions {
public:
    virtual int32 GetRows() const { return rows; }
    virtual int32 GetColumns() const { return columns; }
private:
    int32 rows;
    int32 columns;
};