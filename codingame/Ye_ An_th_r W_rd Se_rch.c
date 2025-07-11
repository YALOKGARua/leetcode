#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 50
#define MAX_WORDS 20
#define MAX_WORD_LEN 20
#define MAX_PLACEMENTS 1000

typedef struct {
    int word_idx;
    int x, y, dir;
    int cells[MAX_WORD_LEN][2];
    int length;
} Placement;

typedef struct {
    char grid[MAX_SIZE][MAX_SIZE + 1];
    char solution[MAX_SIZE][MAX_SIZE + 1];
    char words[MAX_WORDS][MAX_WORD_LEN];
    Placement placements[MAX_PLACEMENTS];
    int placement_count;
    bool used_cells[MAX_SIZE][MAX_SIZE];
    bool word_placed[MAX_WORDS];
    int height, width, word_count;
} WordSearch;

static const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
static const int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};

static bool is_valid(int x, int y, int height, int width) {
    return x >= 0 && x < height && y >= 0 && y < width;
}

static bool can_place_word_at(WordSearch* ws, const char* word, int x, int y, int dir) {
    int len = strlen(word);
    
    for (int i = 0; i < len; i++) {
        int nx = x + i * dx[dir];
        int ny = y + i * dy[dir];
        
        if (!is_valid(nx, ny, ws->height, ws->width)) {
            return false;
        }
        
        char grid_char = ws->grid[nx][ny];
        if (grid_char != '.' && grid_char != word[i]) {
            return false;
        }
    }
    
    return true;
}

static void generate_all_placements(WordSearch* ws) {
    ws->placement_count = 0;
    
    for (int word_idx = 0; word_idx < ws->word_count; word_idx++) {
        const char* word = ws->words[word_idx];
        int len = strlen(word);
        
        for (int x = 0; x < ws->height && ws->placement_count < MAX_PLACEMENTS; x++) {
            for (int y = 0; y < ws->width && ws->placement_count < MAX_PLACEMENTS; y++) {
                for (int dir = 0; dir < 8 && ws->placement_count < MAX_PLACEMENTS; dir++) {
                    if (can_place_word_at(ws, word, x, y, dir)) {
                        Placement* p = &ws->placements[ws->placement_count++];
                        p->word_idx = word_idx;
                        p->x = x;
                        p->y = y;
                        p->dir = dir;
                        p->length = len;
                        
                        for (int i = 0; i < len; i++) {
                            p->cells[i][0] = x + i * dx[dir];
                            p->cells[i][1] = y + i * dy[dir];
                        }
                    }
                }
            }
        }
    }
}

static bool placement_conflicts(WordSearch* ws, const Placement* p) {
    for (int i = 0; i < p->length; i++) {
        if (ws->used_cells[p->cells[i][0]][p->cells[i][1]]) {
            return true;
        }
    }
    return false;
}

static void apply_placement(WordSearch* ws, const Placement* p) {
    const char* word = ws->words[p->word_idx];
    for (int i = 0; i < p->length; i++) {
        int x = p->cells[i][0];
        int y = p->cells[i][1];
        ws->solution[x][y] = word[i];
        ws->used_cells[x][y] = true;
    }
    ws->word_placed[p->word_idx] = true;
}

static void remove_placement(WordSearch* ws, const Placement* p) {
    for (int i = 0; i < p->length; i++) {
        int x = p->cells[i][0];
        int y = p->cells[i][1];
        ws->solution[x][y] = ' ';
        ws->used_cells[x][y] = false;
    }
    ws->word_placed[p->word_idx] = false;
}

static int count_placed_words(WordSearch* ws) {
    int count = 0;
    for (int i = 0; i < ws->word_count; i++) {
        if (ws->word_placed[i]) count++;
    }
    return count;
}

static bool solve_placements(WordSearch* ws, int placement_idx) {
    if (count_placed_words(ws) == ws->word_count) {
        return true;
    }
    
    if (placement_idx >= ws->placement_count) {
        return false;
    }
    
    const Placement* p = &ws->placements[placement_idx];
    
    if (!ws->word_placed[p->word_idx] && !placement_conflicts(ws, p)) {
        apply_placement(ws, p);
        
        if (solve_placements(ws, placement_idx + 1)) {
            return true;
        }
        
        remove_placement(ws, p);
    }
    
    return solve_placements(ws, placement_idx + 1);
}

int main() {
    WordSearch ws = {0};
    
    scanf("%d%d", &ws.height, &ws.width);
    fgetc(stdin);
    
    for (int i = 0; i < ws.height; i++) {
        scanf("%[^\n]", ws.grid[i]);
        fgetc(stdin);
    }
    
    char words_line[251];
    scanf("%[^\n]", words_line);
    
    char* token = strtok(words_line, " ");
    while (token != NULL && ws.word_count < MAX_WORDS) {
        strcpy(ws.words[ws.word_count], token);
        ws.word_count++;
        token = strtok(NULL, " ");
    }
    
    for (int i = 0; i < ws.height; i++) {
        for (int j = 0; j < ws.width; j++) {
            ws.solution[i][j] = ' ';
            ws.used_cells[i][j] = false;
        }
        ws.solution[i][ws.width] = '\0';
    }
    
    for (int i = 0; i < ws.word_count; i++) {
        ws.word_placed[i] = false;
    }
    
    generate_all_placements(&ws);
    
    if (solve_placements(&ws, 0)) {
        for (int i = 0; i < ws.height; i++) {
            printf("%s\n", ws.solution[i]);
        }
    } else {
        for (int i = 0; i < ws.height; i++) {
            for (int j = 0; j < ws.width; j++) {
                printf(" ");
            }
            printf("\n");
        }
    }
    
    return 0;
}
