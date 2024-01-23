
typedef struct {
    bool left;
    bool far_left;
    bool right;
    bool far_right;
} LS_data_t;

void LS_setup();

LS_data_t LS_read();
