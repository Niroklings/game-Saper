#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

const int GRAN = 100;
const int PUST = 0;
const int MINA = 10;

class Pole {

private:
    int size;


    std::vector <std::vector<int>> pole;
    std::vector <std::vector<int>> mask;
public:

    Pole() {
        size = 10;
    }
    int openCell(int x, int y) {
        int result = 1;
        mask[x][y] = 1;

        if (pole[x][y] == MINA) {
            result = MINA;
        }

        else if (pole[x][y] == PUST) {
            result = PUST;
        }
        show();
        return result;
    }

    bool isGran(int x, int y) {
        if (x < 0 || x >= size) {
            return false;
        }
        if (y < 0 || y >= size) {
            return false;
        }
        if (pole[x][y] == GRAN) {
            return true;
        }
        return false;

    }

    void initVec(std::vector <std::vector<int>>& vec) {
        for (int i = 0; i < size; i++) {
            std::vector <int> temp;
            for (int j = 0; j < size; j++) {
                if (i == size - 1 or j == size - 1 or i == 0 or j == 0) {
                    temp.push_back(GRAN);
                }
                else {
                    temp.push_back(PUST);
                }

            }
            vec.push_back(temp);
        }
    }

    void initPole() {
        initVec(pole);
    }
    void initMask() {
        initVec(mask);
    }

    void setMines(int numMines) {
        if (numMines >= (size - 2) * (size - 2)) {
            std::cout << "Too many mines" << std::endl;
            return;
        }
        for (int i = 0; i < numMines; i++) {
            int x, y;

            do {
                x = rand() % (size - 2) + 1;
                y = rand() % (size - 2) + 1;
            } while (pole[x][y] == MINA);
            pole[x][y] = MINA;
        }

    }

    bool win(int numMines) {
        int count = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (mask[i][j] == 0) {
                    count++;
                }
            }
        }
        if (count == numMines) return true;
        return false;
    }

    void setDigits() {
        int d = 0;
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                if (pole[j][i] == MINA)
                    continue;
                if (pole[j][i + 1] == MINA)
                    d++;
                if (pole[j][i - 1] == MINA)
                    d++;
                if (pole[j + 1][i + 1] == MINA)
                    d++;
                if (pole[j + 1][i - 1] == MINA)
                    d++;
                if (pole[j - 1][i + 1] == MINA)
                    d++;
                if (pole[j - 1][i - 1] == MINA)
                    d++;
                if (pole[j + 1][i] == MINA)
                    d++;
                if (pole[j - 1][i] == MINA)
                    d++;
                pole[j][i] = d;
                d = 0;

            }

        }

    }

    void show() {
        gotoxy(0, 0);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (mask[j][i] == PUST) {
                    std::cout << ".";
                    continue;
                }
                if (pole[j][i] == GRAN) std::cout << "+";
                else if (pole[j][i] == PUST) std::cout << " ";
                else if (pole[j][i] == MINA) std::cout << "*";
                else if (pole[j][i] >= 1 && pole[j][i] < 8) std::cout << pole[j][i];

            }
            std::cout << std::endl;;
        }
    }

    void fill(int px, int py) {
        std::stack <int> stk;
        stk.push(px);
        stk.push(py);

        int x = 0, y = 0;

        while (true) {

            y = stk.top();
            stk.pop();
            x = stk.top();
            stk.pop();

            if (pole[x][y + 1] == PUST && mask[x][y + 1] == 0) {
                stk.push(x);
                stk.push(y + 1);
            }
            mask[x][y + 1] = 1;

            if (pole[x][y - 1] == PUST && mask[x][y - 1] == 0) {
                stk.push(x);
                stk.push(y - 1);
            }
            mask[x][y - 1] = 1;

            if (pole[x - 1][y + 1] == PUST && mask[x - 1][y + 1] == 0) {
                stk.push(x - 1);
                stk.push(y + 1);
            }
            mask[x - 1][y + 1] = 1;

            if (pole[x - 1][y - 1] == PUST && mask[x - 1][y - 1] == 0) {
                stk.push(x - 1);
                stk.push(y - 1);
            }
            mask[x - 1][y - 1] = 1;

            if (pole[x + 1][y + 1] == PUST && mask[x + 1][y + 1] == 0) {
                stk.push(x + 1);
                stk.push(y + 1);
            }
            mask[x + 1][y + 1] = 1;

            if (pole[x + 1][y - 1] == PUST && mask[x + 1][y - 1] == 0) {
                stk.push(x + 1);
                stk.push(y - 1);
            }
            mask[x + 1][y - 1] = 1;


            if (pole[x + 1][y] == PUST && mask[x + 1][y] == 0) {
                stk.push(x + 1);
                stk.push(y);
            }
            mask[x + 1][y] = 1;

            if (pole[x + 1][y] == PUST && mask[x + 1][y] == 0) {
                stk.push(x + 1);
                stk.push(y);
            }
            mask[x + 1][y] = 1;

            if (stk.empty()) {
                break;
            }

        }

    }
};

class Keyboard {
private:
    int ch = 0;
public:
    Keyboard() {
        ch = 0;
    }

    void waitKey() {
        ch = _getch();

    }

    int getKey() {
        return ch;
    }
};

class Cursor {

private:
    int x = 1;
    int y = 1;
    int tx = 1;
    int ty = 1;

public:
    void save() {
        tx = x;
        ty = y;
    }
    void undo() {
        x = tx;
        y = ty;
    }

    void incX() {
        x++;
    }
    void decX() {
        x--;
    }
    void incY() {
        y++;
    }
    void decY() {
        y--;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void move() {
        gotoxy(x, y);
    }

};

class Game {
private:

public:
    void gameOver() {
        gotoxy(15, 4);
        std::cout << "Game over";
        Sleep(2000);
        gotoxy(0, 15);
        system("pause");

    }
    void run() {
        int numMines = 9;
        Pole pole;
        pole.initPole();
        pole.initMask();
        pole.setMines(numMines);
        pole.setDigits();
        pole.show();

        Keyboard kb;
        Cursor cs;

        cs.move();
        bool exit = false;

        while (!exit) {
            kb.waitKey();
            cs.save();

            switch (kb.getKey()) {
            case 77: cs.incX(); break; //вправо
            case 80: cs.incY(); break; //вниз
            case 75: cs.decX(); break; //влево
            case 72: cs.decY(); break; //вверх
            case 13:
                int result = pole.openCell(cs.getX(), cs.getY());
                if (result == MINA) {
                    gameOver();
                    exit = true;
                }

                else if (pole.win(numMines)) {
                    gotoxy(15, 4);
                    std::cout << "WIN!";
                    Sleep(2000);
                    gotoxy(0, 15);
                    system("pause");
                    exit = true;
                }

                if (result == PUST) {
                    pole.fill(cs.getX(), cs.getY());
                    pole.show();
                }

                break;
            }
            if (pole.isGran(cs.getX(), cs.getY())) {
                cs.undo();
            }
            cs.move();
        }
    }
};


int main()
{
    srand(time(0));
    Game game;
    game.run();
}

