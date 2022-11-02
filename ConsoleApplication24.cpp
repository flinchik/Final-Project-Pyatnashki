#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;

class Boolean {
public:
    bool stop = true, play = false, peremeshka = false, pause = false;
    int puskgame = 1000;
};

Boolean boolean;

RenderWindow window(VideoMode(750, 512), "Pyatnashki by Klopotar Alexander");

class Game {
public:
    Sprite s[17];
    // Розмір квадрата та поля
    int w = 128;
    int grid[6][6] = { 0 };
    int n = 0;

    int b = 1, x = 0, y = 0; // b - де знаходиться пусте місце, x та y - координати

    Game(Texture& image) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                n++;
                s[n].setTexture(image);
                s[n].setTextureRect(IntRect(i * w, j * w, w, w));
                grid[i + 1][j + 1] = n;
            }
    }

    void update() {
        int dx = 0;
        int dy = 0;

        if (grid[x + 1][y] == b) {
            dx = 1;
            dy = 0;
        }
        if (grid[x - 1][y] == b) {
            dx = -1;
            dy = 0;
        }
        if (grid[x][y - 1] == b) {
            dx = 0;
            dy = -1;
        }
        if (grid[x][y + 1] == b) {
            dx = 0;
            dy = 1;
        }
        // Зміна квадрата з пустим місцем
        n = grid[x][y];
        grid[x][y] = b;
        grid[x + dx][y + dy] = n;
        // Анімація
        s[b].move(-dx * w, -dy * w);
        float speed = 16;
        for (int i = 0; i < w; i += speed) {
            s[n].move(speed * dx, speed * dy);
            window.draw(s[b]);
            window.draw(s[n]);
            window.display();
        }

        if (boolean.play) {
            if (grid[1][1] == 1 && grid[1][2] == 2 && grid[1][3] == 3 && grid[1][4] == 4 &&
                grid[2][1] == 5 && grid[2][2] == 6 && grid[2][3] == 7 && grid[2][4] == 8 &&
                grid[3][1] == 9 && grid[3][2] == 10 && grid[3][3] == 11 && grid[3][4] == 12 &&
                grid[4][1] == 13 && grid[4][2] == 14 && grid[4][3] == 15 && grid[4][4] == 16) {
                boolean.play = false;
                boolean.stop = true;

                boolean.puskgame = 1000;

                window.setFramerateLimit(0);

 
            }
        }
    }
};

class Button {
public:
    Texture t, s;
    Sprite start, prod, naczap;

    Button() {
        t.loadFromFile("C:/Game/Paint/startt.png");
        s.loadFromFile("C:/Game/Paint/sett.png");

        start.setTexture(t);
        start.setPosition(540, 400);
        start.setTextureRect(IntRect(0, 0, 196, 65));

        prod.setTexture(s);
        prod.setPosition(540, 150);
        prod.setTextureRect(IntRect(0, 0, 196, 65));

        naczap.setTexture(s);
        naczap.setPosition(540, 300);
        naczap.setTextureRect(IntRect(0, 65, 196, 65));
    }
};

class Stopwatch {
public:
    Sprite min[2], sec[2], toc;
    int m[2], s[2], ms;

    Stopwatch(Texture& image) {
        for (int i = 0; i < 2; i++) {
            min[i].setTexture(image);
            sec[i].setTexture(image);

            min[i].setPosition(570 + 30 * i, 25);
            sec[i].setPosition(654 + 30 * i, 25);

            min[i].setTextureRect(IntRect(0, 0, 24, 38));
            sec[i].setTextureRect(IntRect(0, 0, 24, 38));

            m[i] = 0;
            s[i] = 0;
        }

        toc.setTexture(image);
        toc.setPosition(627, 25);
        toc.setTextureRect(IntRect(240, 0, 24, 38));

        ms = 0;
    }

    void update() {
        if (boolean.play)
            ms++;

        if (ms >= 7) {
            s[1]++;
            ms = 0;
        }

        if (s[1] == 10) {
            s[0]++;
            s[1] = 0;
        }

        if (s[0] == 6) {
            m[1]++;
            s[0] = 0;
        }

        if (m[1] == 10) {
            m[0]++;
            m[1] = 0;
        }

        for (int i = 0; i < 2; i++) {
            sec[i].setTextureRect(IntRect(24 * s[i], 0, 24, 38));
            min[i].setTextureRect(IntRect(24 * m[i], 0, 24, 38));
        }
    }
};

int main()
{
    srand(time(0));

    Texture t;
    t.loadFromFile("C:/Game/Paint/Northern lights.png");
    Game game(t);

    Sprite picture(t);
    picture.setScale(0.4, 0.4);
    picture.setPosition(530, 130);

    Button button;

    Texture ti;
    ti.loadFromFile("C:/Game/Paint/time.png");
    Stopwatch watch(ti);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
                if (event.key.code == Mouse::Left) {
                    Vector2i pos = Mouse::getPosition(window);

                    if (boolean.play) {
                        if (pos.x <= 512) {
                            game.x = pos.x / game.w + 1;
                            game.y = pos.y / game.w + 1;

                        }

                        else if (button.start.getGlobalBounds().contains(pos.x, pos.y)) {
                            boolean.pause = true;
                            boolean.play = false;

                        }
                    }
                    else if (boolean.stop) {
                        if (button.start.getGlobalBounds().contains(pos.x, pos.y)) {
                            boolean.stop = false;
                            boolean.peremeshka = true;

                            window.setFramerateLimit(0);

                            for (int i = 0; i < 2; i++) {
                                watch.m[i] = 0;
                                watch.s[i] = 0;
                            }
                            watch.ms = 0;

                            button.start.setTextureRect(IntRect(0, 65, 196, 65));
                        }
                    }
                    else if (boolean.pause) {
                        if (button.prod.getGlobalBounds().contains(pos.x, pos.y)) {
                            boolean.pause = false;
                            boolean.play = true;

                        }

                        if (button.naczap.getGlobalBounds().contains(pos.x, pos.y)) {
                            game.grid[1][1] = 1; game.grid[1][2] = 2; game.grid[1][3] = 3; game.grid[1][4] = 4;
                            game.grid[2][1] = 5; game.grid[2][2] = 6; game.grid[2][3] = 7; game.grid[2][4] = 8;
                            game.grid[3][1] = 9; game.grid[3][2] = 10; game.grid[3][3] = 11; game.grid[3][4] = 12;
                            game.grid[4][1] = 13; game.grid[4][2] = 14; game.grid[4][3] = 15; game.grid[4][4] = 16;

                            boolean.pause = false;
                            boolean.peremeshka = true;

                            boolean.puskgame = 1000;


                            for (int i = 0; i < 2; i++) {
                                watch.m[i] = 0;
                                watch.s[i] = 0;
                            }
                            watch.ms = 0;

                            window.setFramerateLimit(0);
                        }
                    }
                }
        }

        if (boolean.peremeshka) {
            game.x = rand() % 4 + 1;
            game.y = rand() % 4 + 1;

            boolean.puskgame--;

            if (boolean.puskgame == 0) {
                boolean.peremeshka = false;
                boolean.play = true;
            }
        }
        else if (boolean.play) {
            window.setFramerateLimit(60);
        }
        else if (boolean.stop)
            button.start.setTextureRect(IntRect(0, 0, 196, 65));

        game.update();
        watch.update();
        window.clear(Color::White);
        window.draw(picture);
        if (boolean.stop || boolean.play)
            window.draw(button.start);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                game.n = game.grid[i + 1][j + 1];
                game.s[game.n].setPosition(i * game.w, j * game.w);
                window.draw(game.s[game.n]);
            }
        for (int i = 0; i < 2; i++) {
            window.draw(watch.min[i]);
            window.draw(watch.sec[i]);
        }
        window.draw(watch.toc);
        if (boolean.pause) {
            window.draw(button.prod);
            window.draw(button.naczap);
        }
        window.display();
    }

    return 0;
}