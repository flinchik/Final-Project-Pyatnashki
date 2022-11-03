
# Final Project 15-Game

## Мова програмування: **C++**
------
### Створено [K.A](https://github.com/flinchik) для Компьютерної Академії ШАГ
----
#### Тема гри: **15-Game (П'ятнашки)**
----
# Коротко о самій грі

Складається з 15 однакових квадратних пластинок з нанесеними числами від 1 до 15. Пластинки поміщаються в квадратну коробку, довжина сторони якої в чотири рази більша довжини сторони пластинок, відповідно в коробці залишається незаповненим одне квадратне поле. Мета гри — переміщаючи пластинки по коробці добитися впорядковування їх по номерах (як зображено на рисунку), бажано зробивши якомога менше переміщень.

## Використані бібліотеки

- [iostream](https://uk.wikipedia.org/wiki/Iostream) — бібліотека і відповідний заголовний файл, які використовується для організації введення-виведення в мові програмування C++
- [SFML](https://www.sfml-dev.org/) - вільна кросплатформова мультимедійна бібліотека. SFML містить ряд модулів для простого програмування ігор та мультимедіа додатків

---
## Демо гри:
![DEMO](https://cdn.discordapp.com/attachments/1036007615379017779/1037755764716085289/demka.gif)

---


***Опис коду:***

---

**Створення классу для кнопок "Старт", "Пауза", "Продовжити" та "Почати заново"**

-----
```
class Knopki {
public:
    bool stop = true, play = false, peremeshka = false, pause = false;
    int puskgame = 1000;
};

Knopki knopki;
```
**Створення вікна для гри**

-----
```
RenderWindow window(VideoMode(750, 512), "Pyatnashki");
```
Створення классу самої гри (створення спрайта, ігрового поля та текстури для плиток)

```
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
```
Створення анімації для плиток, механіки для гри та саме ігрове поле

```
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

        if (knopki.play) {
            if (grid[1][1] == 1 && grid[1][2] == 2 && grid[1][3] == 3 && grid[1][4] == 4 &&
                grid[2][1] == 5 && grid[2][2] == 6 && grid[2][3] == 7 && grid[2][4] == 8 &&
                grid[3][1] == 9 && grid[3][2] == 10 && grid[3][3] == 11 && grid[3][4] == 12 &&
                grid[4][1] == 13 && grid[4][2] == 14 && grid[4][3] == 15 && grid[4][4] == 16) {
                knopki.play = false;
                knopki.stop = true;

                knopki.puskgame = 1000;

                window.setFramerateLimit(0);

 
            }
        }
    }
};
```
Створення классу для кнопок та їх розташування
```
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
```

# **Детальніше в .cpp файлі! Дякую за увагу!**


