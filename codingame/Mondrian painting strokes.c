#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** grid;
    int width;
    int height;
} MondrianGrid;

typedef struct {
    int* positions;
    int count;
    int capacity;
} BoundarySegments;

static BoundarySegments* create_boundary_segments(int capacity) {
    BoundarySegments* segments = malloc(sizeof(BoundarySegments));
    segments->positions = malloc(capacity * sizeof(int));
    segments->count = 0;
    segments->capacity = capacity;
    return segments;
}

static void destroy_boundary_segments(BoundarySegments* segments) {
    if (segments) {
        free(segments->positions);
        free(segments);
    }
}

static void add_boundary_position(BoundarySegments* segments, int position) {
    if (segments->count < segments->capacity) {
        segments->positions[segments->count++] = position;
    }
}

static int count_continuous_segments(const BoundarySegments* segments) {
    if (segments->count == 0) return 0;
    
    int segment_count = 1;
    
    for (int i = 1; i < segments->count; i++) {
        if (segments->positions[i] != segments->positions[i - 1] + 1) {
            segment_count++;
        }
    }
    
    return segment_count;
}

static BoundarySegments* extract_horizontal_boundary_segments(const MondrianGrid* grid, int row) {
    BoundarySegments* segments = create_boundary_segments(grid->width);
    
    for (int col = 0; col < grid->width; col++) {
        if (grid->grid[row][col] != grid->grid[row + 1][col]) {
            add_boundary_position(segments, col);
        }
    }
    
    return segments;
}

static BoundarySegments* extract_vertical_boundary_segments(const MondrianGrid* grid, int col) {
    BoundarySegments* segments = create_boundary_segments(grid->height);
    
    for (int row = 0; row < grid->height; row++) {
        if (grid->grid[row][col] != grid->grid[row][col + 1]) {
            add_boundary_position(segments, row);
        }
    }
    
    return segments;
}

static int count_horizontal_strokes(const MondrianGrid* grid) {
    int total_strokes = 0;
    
    for (int row = 0; row < grid->height - 1; row++) {
        BoundarySegments* segments = extract_horizontal_boundary_segments(grid, row);
        total_strokes += count_continuous_segments(segments);
        destroy_boundary_segments(segments);
    }
    
    return total_strokes;
}

static int count_vertical_strokes(const MondrianGrid* grid) {
    int total_strokes = 0;
    
    for (int col = 0; col < grid->width - 1; col++) {
        BoundarySegments* segments = extract_vertical_boundary_segments(grid, col);
        total_strokes += count_continuous_segments(segments);
        destroy_boundary_segments(segments);
    }
    
    return total_strokes;
}

static int calculate_minimum_strokes(const MondrianGrid* grid) {
    int horizontal_strokes = count_horizontal_strokes(grid);
    int vertical_strokes = count_vertical_strokes(grid);
    
    return horizontal_strokes + vertical_strokes;
}

static MondrianGrid* create_mondrian_grid(int width, int height) {
    MondrianGrid* grid = malloc(sizeof(MondrianGrid));
    grid->width = width;
    grid->height = height;
    grid->grid = malloc(height * sizeof(char*));
    
    for (int i = 0; i < height; i++) {
        grid->grid[i] = malloc((width + 1) * sizeof(char));
    }
    
    return grid;
}

static void destroy_mondrian_grid(MondrianGrid* grid) {
    if (grid) {
        for (int i = 0; i < grid->height; i++) {
            free(grid->grid[i]);
        }
        free(grid->grid);
        free(grid);
    }
}

static MondrianGrid* parse_input() {
    int width, height;
    scanf("%d %d", &width, &height);
    
    MondrianGrid* grid = create_mondrian_grid(width, height);
    
    for (int i = 0; i < height; i++) {
        scanf("%s", grid->grid[i]);
    }
    
    return grid;
}

int main() {
    MondrianGrid* grid = parse_input();
    int result = calculate_minimum_strokes(grid);
    
    printf("%d\n", result);
    
    destroy_mondrian_grid(grid);
    
    return 0;
}
