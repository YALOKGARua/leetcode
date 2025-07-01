#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LOGO_SIZE 1000
#define MAX_LINE_LENGTH 11

typedef struct {
    char grid[MAX_LOGO_SIZE][MAX_LOGO_SIZE];
    int height;
    int width;
} Canvas;

typedef struct {
    char layout[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int rows;
    int maxCols;
} LogoLayout;

void initializeCanvas(Canvas* canvas) {
    canvas->height = 0;
    canvas->width = 0;
    
    for (int i = 0; i < MAX_LOGO_SIZE; i++) {
        for (int j = 0; j < MAX_LOGO_SIZE; j++) {
            canvas->grid[i][j] = ' ';
        }
    }
}

void drawPlusOutline(Canvas* canvas, int startRow, int startCol, int size, int thickness) {
    int center = size / 2;
    int halfThickness = thickness / 2;
    
    int vertStart = center - halfThickness;
    int vertEnd = center - halfThickness + thickness - 1;
    int horizStart = center - halfThickness;
    int horizEnd = center - halfThickness + thickness - 1;
    
    for (int row = 0; row < size; row++) {
        canvas->grid[startRow + row][startCol + vertStart] = '+';
        canvas->grid[startRow + row][startCol + vertEnd] = '+';
    }
    
    for (int col = 0; col < size; col++) {
        canvas->grid[startRow + horizStart][startCol + col] = '+';
        canvas->grid[startRow + horizEnd][startCol + col] = '+';
    }
}

void connectAdjacentPluses(Canvas* canvas, LogoLayout* layout, int size, int thickness) {
    for (int layoutRow = 0; layoutRow < layout->rows; layoutRow++) {
        for (int layoutCol = 0; layoutCol < layout->maxCols; layoutCol++) {
            if (layout->layout[layoutRow][layoutCol] != '+') continue;
            
            int baseRow = layoutRow * size;
            int baseCol = layoutCol * size;
            
            if (layoutCol + 1 < layout->maxCols && 
                layout->layout[layoutRow][layoutCol + 1] == '+') {
                
                int center = size / 2;
                int halfThickness = thickness / 2;
                int horizStart = center - halfThickness;
                int horizEnd = center - halfThickness + thickness - 1;
                
                for (int row = horizStart; row <= horizEnd; row++) {
                    canvas->grid[baseRow + row][baseCol + size] = '+';
                }
            }
            
            if (layoutRow + 1 < layout->rows && 
                layoutCol < strlen(layout->layout[layoutRow + 1]) &&
                layout->layout[layoutRow + 1][layoutCol] == '+') {
                
                int center = size / 2;
                int halfThickness = thickness / 2;
                int vertStart = center - halfThickness;
                int vertEnd = center - halfThickness + thickness - 1;
                
                for (int col = vertStart; col <= vertEnd; col++) {
                    canvas->grid[baseRow + size][baseCol + col] = '+';
                }
            }
        }
    }
}

void trimRightSpaces(char* line) {
    int len = strlen(line);
    while (len > 0 && line[len - 1] == ' ') {
        line[len - 1] = '\0';
        len--;
    }
}

void calculateCanvasDimensions(Canvas* canvas, LogoLayout* layout, int size) {
    canvas->height = layout->rows * size;
    canvas->width = layout->maxCols * size;
}

void printCanvas(Canvas* canvas) {
    for (int row = 0; row < canvas->height; row++) {
        char line[MAX_LOGO_SIZE + 1];
        
        for (int col = 0; col < canvas->width; col++) {
            line[col] = canvas->grid[row][col];
        }
        line[canvas->width] = '\0';
        
        trimRightSpaces(line);
        printf("%s\n", line);
    }
}

void parseLogoLayout(LogoLayout* layout, int N) {
    layout->rows = N;
    layout->maxCols = 0;
    
    for (int i = 0; i < N; i++) {
        char logoLine[MAX_LINE_LENGTH];
        scanf("%[^\n]", logoLine);
        fgetc(stdin);
        
        strcpy(layout->layout[i], logoLine);
        
        int lineLength = strlen(logoLine);
        if (lineLength > layout->maxCols) {
            layout->maxCols = lineLength;
        }
    }
}

bool belongsToPlus(LogoLayout* layout, int globalRow, int globalCol, int size, int thickness) {
    int layoutRow = globalRow / size;
    int layoutCol = globalCol / size;
    
    if (layoutRow >= layout->rows || layoutCol >= strlen(layout->layout[layoutRow]) || 
        layout->layout[layoutRow][layoutCol] != '+') {
        return false;
    }
    
    int localRow = globalRow % size;
    int localCol = globalCol % size;
    
    int center = size / 2;
    int halfThickness = thickness / 2;
    int vertStart = center - halfThickness;
    int vertEnd = center - halfThickness + thickness - 1;
    int horizStart = center - halfThickness;
    int horizEnd = center - halfThickness + thickness - 1;
    
    bool inVerticalBar = (localCol >= vertStart && localCol <= vertEnd);
    bool inHorizontalBar = (localRow >= horizStart && localRow <= horizEnd);
    
    return inVerticalBar || inHorizontalBar;
}

void generateLogo(Canvas* canvas, LogoLayout* layout, int size, int thickness) {
    initializeCanvas(canvas);
    calculateCanvasDimensions(canvas, layout, size);
    
    for (int row = 0; row < canvas->height; row++) {
        for (int col = 0; col < canvas->width; col++) {
            if (belongsToPlus(layout, row, col, size, thickness)) {
                bool isBorder = false;
                
                int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
                for (int d = 0; d < 4; d++) {
                    int newRow = row + directions[d][0];
                    int newCol = col + directions[d][1];
                    
                    if (newRow < 0 || newRow >= canvas->height || 
                        newCol < 0 || newCol >= canvas->width ||
                        !belongsToPlus(layout, newRow, newCol, size, thickness)) {
                        isBorder = true;
                        break;
                    }
                }
                
                if (isBorder) {
                    canvas->grid[row][col] = '+';
                }
            }
        }
    }
}

int main() {
    int size, thickness, N;
    Canvas canvas;
    LogoLayout layout;
    
    scanf("%d", &size);
    scanf("%d", &thickness);
    scanf("%d", &N);
    fgetc(stdin);
    
    parseLogoLayout(&layout, N);
    generateLogo(&canvas, &layout, size, thickness);
    printCanvas(&canvas);
    
    return 0;
}
