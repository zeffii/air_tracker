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