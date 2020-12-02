#include <string>

//struct Selection_Params;

struct Selection_Params {
    string first_hex;
    string last_hex;
    int numrows;
    int first_row_idx;
    int selection_start;
    int selection_length;
};

struct Sparse_Selection {
    int start_idx;
    string hex_value;
};

struct Selection_Range {
    int first_col_idx;
    int last_col_idx;
    int first_row_idx;
    int last_row_idx;
};

struct Cell_Range {
    int cell_start, cell_length;
    string cell_replacement;
};