#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <cctype>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SQUARE_SIZE = SCREEN_WIDTH / 8;

ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
ALLEGRO_FONT* font = nullptr;

struct Position {
    int row, col;
};

Position selectedPiece = { -1, -1 };
bool isWhiteTurn = true;

void initialize_allegro() {
    if (!al_init()) {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        exit(-1);
    }

    if (!al_init_primitives_addon()) {
        std::cerr << "Failed to initialize primitives addon!" << std::endl;
        exit(-1);
    }

    if (!al_install_mouse()) {
        std::cerr << "Failed to install mouse!" << std::endl;
        exit(-1);
    }

    if (!al_init_font_addon()) {
        std::cerr << "Failed to initialize font addon!" << std::endl;
        exit(-1);
    }

    if (!al_init_ttf_addon()) {
        std::cerr << "Failed to initialize TTF addon!" << std::endl;
        exit(-1);
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        std::cerr << "Failed to create display!" << std::endl;
        exit(-1);
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        std::cerr << "Failed to create event queue!" << std::endl;
        exit(-1);
    }

    font = al_load_ttf_font("arial.ttf", 36, 0);
    if (!font) {
        std::cerr << "Failed to load font!" << std::endl;
        exit(-1);
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

void draw_chessboard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ALLEGRO_COLOR color = ((i + j) % 2 == 0) ? al_map_rgb(255, 206, 158) : al_map_rgb(209, 139, 71);
            al_draw_filled_rectangle(j * SQUARE_SIZE, i * SQUARE_SIZE, (j + 1) * SQUARE_SIZE, (i + 1) * SQUARE_SIZE, color);
        }
    }
}

void draw_pieces(char board[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != ' ') {
                std::string piece(1, board[i][j]);
                al_draw_text(font, al_map_rgb(0, 0, 0), j * SQUARE_SIZE + SQUARE_SIZE / 2, i * SQUARE_SIZE + SQUARE_SIZE / 2 - 12, ALLEGRO_ALIGN_CENTER, piece.c_str());
            }
        }
    }
}

bool isValidMove(char board[8][8], Position from, Position to) {
    char piece = board[from.row][from.col];
    if (piece == ' ') return false;

    int direction = (piece == 'P') ? -1 : 1;
    if (tolower(piece) == 'p') {
        if (to.col == from.col && to.row == from.row + direction && board[to.row][to.col] == ' ') {
            return true;
        }
    }
    return false;
}

void handleMouseClick(int x, int y, char board[8][8]) {
    int col = x / SQUARE_SIZE;
    int row = y / SQUARE_SIZE;

    if (selectedPiece.row == -1) {
        if (board[row][col] != ' ') {
            bool isWhitePiece = isupper(board[row][col]);
            if ((isWhiteTurn && isWhitePiece) || (!isWhiteTurn && !isWhitePiece)) {
                selectedPiece = { row, col };
            }
        }
    }
    else {
        if (isValidMove(board, selectedPiece, { row, col })) {
            board[row][col] = board[selectedPiece.row][selectedPiece.col];
            board[selectedPiece.row][selectedPiece.col] = ' ';
            isWhiteTurn = !isWhiteTurn;
        }
        selectedPiece = { -1, -1 };
    }
}

int main() {
    initialize_allegro();

    char board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            handleMouseClick(event.mouse.x, event.mouse.y, board);
        }

        draw_chessboard();
        draw_pieces(board);
        al_flip_display();
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);

    return 0;
}
