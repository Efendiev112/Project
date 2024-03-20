#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;

const int HEIGHT = 28;
const int WIDTH = 19;

char field[HEIGHT][WIDTH];

int currentPieceX = WIDTH / 2;
int currentPieceY = 28;

char currentPiece[4][4];
int score = 0;

char tetrominoes[7][4][4] = {

    {
        {' ', ' ', ' ', ' '},
        {' ', '0', '0', '0'},
        {' ', ' ', '0', ' '},
        {' ', ' ', ' ', ' '}
    },

    {
        {' ', ' ', ' ', ' '},
        {' ', '0', '0', ' '},
        {' ', '0', '0', ' '},
        {' ', ' ', ' ', ' '}
    },

    {
        {' ', ' ', ' ', ' '},
        {'0', '0', ' ',' '},
        {' ', '0', '0', ' '},
        {' ', ' ', ' ', ' '}
    },

    {
        {' ', ' ', ' ', ' '},
        {'0', '0', '0', '0'},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },

    {
        {' ', ' ', ' ', ' '},
        {'0', '0', '0', ' '},
        {'0', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    },

    {
        {' ', ' ', ' ', ' '},
        {'0', '0', '0', ' '},
        {' ', ' ', '0', ' '},
        {' ', ' ', ' ', ' '}
    },

    {
        {' ', ' ', ' ', ' '},
        {' ', ' ', '0', '0'},
        {' ', '0', '0', ' '},
        {' ', ' ', ' ', ' '}
    }
};

void Init() { 
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = ' ';
        }
    }
}

void Draw() { 

    system("cls");
    
    cout << "=======================" << endl;
    for (int i = 0; i < HEIGHT; i++) {
        cout << "||";
        for (int j = 0; j < WIDTH; j++) {
            if (i >= currentPieceY && i < currentPieceY + 4 && j >= currentPieceX && j < currentPieceX + 4 &&
                currentPiece[i - currentPieceY][j - currentPieceX] != ' ') {
                cout << currentPiece[i - currentPieceY][j - currentPieceX];
            }
            else {
                cout << field[i][j];
            }
        }
        cout << "||";

        cout << endl;
    }
    cout << "=======================" << endl;
    cout <<"Счет:" << score << endl;
}
void RotatePiece() {

    
    char tempPiece[4][4];

    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tempPiece[i][j] = currentPiece[i][j];
        }
    }

    // Поворачиваем фигуру
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            currentPiece[i][j] = tempPiece[3 - j][i]; 
        }
    }
}

bool CheckCollision(int X, int Y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece[i][j] != ' ') {
                int newX = currentPieceX + X + j;
                int newY = currentPieceY + Y + i;
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || field[newY][newX] != ' ') {
                    return true;
                }
            }
        }
    }
    return false;

}

void Update() {

    if (!CheckCollision(0, 1)) {
        currentPieceY++;
    }
    else {
        // Фиксация фигуры на поле
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (currentPiece[i][j] != ' ') {
                    field[currentPieceY + i][currentPieceX + j] = currentPiece[i][j];
                }
            }
        }

        // заполняные ряды
        int linesCleared = 0;
        for (int i = HEIGHT - 1; i >= 0; i--) {
            bool rowFilled = true;
            for (int j = 0; j < WIDTH; j++) {
                if (field[i][j] == ' ') {
                    rowFilled = false;
                    break;
                }
            }
            if (rowFilled) {
                linesCleared++;
                // все строки на 1 вниз
                for (int k = i; k > 0; k--) {
                    for (int j = 0; j < WIDTH; j++) {
                        field[k][j] = field[k - 1][j];
                    }
                }
                // заполняем верхнюю строку пустыми символами
                for (int j = 0; j < WIDTH; j++) {
                    field[0][j] = ' ';
                }
            }
        }

        
        score += linesCleared * 10;

        // ссброс текущей позиции фигуры
        currentPieceX = WIDTH / 2 - 2; 
        currentPieceY = 0;

        
        srand(time(NULL));
        int randomIndex = rand() % 7;

        // Копирование выбранной фигуры в текущую фигуру
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentPiece[i][j] = tetrominoes[randomIndex][i][j];
            }
        }
    }
}

void MovePiece(char direction) {

    switch (direction) {
    case 'a':
        if (!CheckCollision(-1, 0)) {
            currentPieceX--;
        }
        break;
    case 'd':
        if (!CheckCollision(1, 0)) {
            currentPieceX++;
        }
        break;

    case 's':
        if (!CheckCollision(0, 1)) {
            currentPieceY++;
        }
        break;
    }
}

void gameOver() {
    cout << endl << "Игра Закончена  !";
    exit(0);
}

void MainMenu() { 
    system("cls");
    cout << "=================================================" << endl;
    cout << "||         Тетрис                              ||" << endl;
    cout << "=================================================" << endl;
    cout << "|| Для управление используйте клавиши W A S D  ||" << endl;
    cout << "|| Для завершения игры нажмите O               ||" << endl;
    cout << "=================================================" << endl;
    _getch(); 
}

int main() {
    setlocale(LC_ALL, "");
    system("color 3F");
    Init();
    MainMenu(); 
    while (true) {
        Draw();
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' || key == 'd' || key == 'w') {
                MovePiece(key);
            }
            if (key == 'w') {
                RotatePiece();
            }
            if (key == 's') {
                MovePiece(key);
            }
            if (key == 'o') {
                gameOver();
            }
        }

        Update();
        Sleep(50);
    }
    return 0;

}
