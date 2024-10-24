#include "pile.h"

UnstableSlots::UnstableSlots() {
    key = nullptr;
}

UnstableSlots::~UnstableSlots() {
    while (key != nullptr) {
        Pop();
    }
}

void UnstableSlots::Push(uint16_t x, uint16_t y) {
    Node* new_node = new Node;
    new_node->x = x;
    new_node->y = y;
    new_node->prev = key;
    key = new_node;
}

void UnstableSlots::Pop() {
    Node* temp = key;
    key = key->prev;
    delete temp;
}

void Field::GetStartSize(Arguments &arguments) {
    std::ifstream input_file(arguments.input_path);
    char* line = new char[kInputStringLength];

    if (!input_file.is_open()) {
        ShowError(ErrorCode::CanNotOpenTheFile);
        EXIT_FAILURE;
    }

    while (input_file.getline(line, kInputStringLength)) {
        int16_t x;
        int16_t y;
        uint64_t sand;

        if (sscanf(line, "%hd\t%hd\t%llu\n", &x, &y, &sand) == 3) {
            max_x = std::max(max_x, x);
            min_x = std::min(min_x, x);
            max_y = std::max(max_y, y);
            min_y = std::min(min_y, y);
        }
    }

    width = std::abs(min_x) + std::abs(max_x) + 1;
    height = std::abs(min_y) + std::abs(max_y) + 1;

    input_file.close();
    delete[] line;
}

void Field::InitField(Arguments &arguments) {
    field = new uint64_t*[width];
    for (int i = 0; i < width; ++i) {
        field[i] = new uint64_t[height] {0};
    }

    std::ifstream input_file(arguments.input_path);
    char* line = new char[kInputStringLength];

    if (!input_file.is_open()) {
        ShowError(ErrorCode::CanNotOpenTheFile);
        EXIT_FAILURE;
    }

    while (input_file.getline(line, kInputStringLength)) {
        int16_t x;
        int16_t y;
        uint64_t sand;

        if (sscanf(line, "%hd\t%hd\t%llu\n", &x, &y, &sand) == 3) {
            field[x - min_x][y - min_y] = sand;
        }
    }

    input_file.close();
    delete[] line;
}

bool Field::IsStable() const {
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            if (field[i][j] > 3) {
                return false;
            }
        }
    }

    return true;
}

bool Field::NeedResize() {
    upper = false;
    right = false;
    lower = false;
    left = false;

    for (int y = 0; y < height; ++y) {
        if (field[0][y] > 3) {
            left = true;
        }

        if (field[width - 1][y] > 3) {
            right = true;
        }
    }

    for (int x = 0; x < width; ++x) {
        if (field[x][0] > 3) {
            lower = true;
        }

        if (field[x][height - 1] > 3) {
            upper = true;
        }
    }

    return upper || lower || left || right;
}

void Field::Resize() {

    if (upper) {
        uint64_t** new_field = new uint64_t*[width];
        for (int i = 0; i < width; ++i) {
            new_field[i] = new uint64_t[height * 2] {0};
        }

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                new_field[i][j] = field[i][j];
            }
        }

        for (int i = 0; i < width; ++i) {
            delete[] field[i];
        }
        delete[] field;

        height *= 2;
        field = new_field;
    }

    if (lower) {
        uint64_t** new_field = new uint64_t*[width];
        for (int i = 0; i < width; ++i) {
            new_field[i] = new uint64_t[height * 2] {0};
        }

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                new_field[i][j + height] = field[i][j];
            }
        }

        for (int i = 0; i < width; ++i) {
            delete[] field[i];
        }
        delete[] field;

        height *= 2;
        field = new_field;
    }

    if (right) {
        uint64_t** new_field = new uint64_t*[width * 2];
        for (int i = 0; i < width * 2; ++i) {
            new_field[i] = new uint64_t[height] {0};
        }

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                new_field[i][j] = field[i][j];
            }
        }

        for (int i = 0; i < width; ++i) {
            delete[] field[i];
        }
        delete[] field;

        width *= 2;
        field = new_field;
    }

    if (left) {
        uint64_t** new_field = new uint64_t*[width * 2];
        for (int i = 0; i < width * 2; ++i) {
            new_field[i] = new uint64_t[height] {0};
        }

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                new_field[i + width][j] = field[i][j];
            }
        }

        for (int i = 0; i < width; ++i) {
            delete[] field[i];
        }
        delete[] field;

        width *= 2;
        field = new_field;
    }
}

void Field::Iteration() {

    if (NeedResize()) {
        Resize();
    }

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            if (field[i][j] > 3) {
                unstable_slots.Push(i, j);
            }
        }
    }

    bool iter_finished = (unstable_slots.key == nullptr);

    while (!iter_finished) {
        field[unstable_slots.key->x][unstable_slots.key->y] -= 4;
        field[unstable_slots.key->x + 1][unstable_slots.key->y] += 1;
        field[unstable_slots.key->x][unstable_slots.key->y + 1] += 1;
        field[unstable_slots.key->x - 1][unstable_slots.key->y] += 1;
        field[unstable_slots.key->x][unstable_slots.key->y - 1] += 1;

        unstable_slots.Pop();
        iter_finished = (unstable_slots.key == nullptr);
    }

    unstable_slots.~UnstableSlots();
}
