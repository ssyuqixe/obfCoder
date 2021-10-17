
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char isEnded;
    char move;
    char map[9];
    char moves;

}gameInformation;



void Draw(gameInformation* memseg, char player) {
    system("clear");
    if (player == 0)
    {
        std::cout << "Host - krzyk" << std::endl;
    }
    else
    {
        std::cout << "User - kolko" << std::endl;
    }
    for (int i = 1; i <= 9; i++)
    {
        std::cout << memseg->map[i - 1];
        if (i % 3 == 0)
        {
            std::cout << std::endl;
        }
    }

}


void DoMove(gameInformation* memseg, char player) {
    int move = 0;
    char _char = '0';
    std::cout << "Wykonaj ruch [1-9]: " << std::endl;
    while (1) {
        if (scanf("%d", &move) == 0)
        {
            do {
                _char = getchar();
            } while (!isdigit(_char));
            ungetc(_char, stdin);
        }

        if (move >= 1 && move <= 9 && memseg->map[move - 1] == '#')
        {
            break;
        }
        else if (memseg->map[move - 1] != '#')
        {
            std::cout << "Wybrales zajete pole! Wybierz jeszcze raz: [1-9]" << std::endl;
        }
        else
        {
            std::cout << "Wybrales zle pole! Wybierz jeszcze raz: [1-9]" << std::endl;
        }
    }
    if (player)
    {
        memseg->map[move - 1] = 'O';
        memseg->move = 0;
    }
    else
    {
        memseg->map[move - 1] = 'X';
        memseg->move = 1;
    }
    Draw(memseg, player);

    std::cout << "Trwa ruch przeciwnika..." << std::endl;
}

void WaitForMove(gameInformation* memseg, char player) {
    while (memseg->move != player)
    {
        Sleep(1);
    }
    Draw(memseg, player);
}

void checkEnd(gameInformation* memseg) {
    char test = '#';
    if (memseg->map[0] != '#')
    {
        if ((memseg->map[0] == memseg->map[1]) && (memseg->map[1] == memseg->map[2]))
        {
            test = memseg->map[0];
        }
        else if ((memseg->map[0] == memseg->map[4]) && (memseg->map[4] == memseg->map[8]))
        {
            test = memseg->map[0];
        }
        else if ((memseg->map[0] == memseg->map[3]) && (memseg->map[3] == memseg->map[6]))
        {
            test = memseg->map[0];
        }
    }

    if (memseg->map[1] != '#' && (memseg->map[1] == memseg->map[4]) && (memseg->map[4] == memseg->map[7]))
    {
        test = memseg->map[1];
    }


    if (memseg->map[2] != '#')
    {
        if ((memseg->map[2] == memseg->map[5]) && (memseg->map[5] == memseg->map[8]))
        {
            test = memseg->map[2];
        }
        else if ((memseg->map[2] == memseg->map[4]) && (memseg->map[4] == memseg->map[6]))
        {
            test = memseg->map[2];
        }

    }

    if (memseg->map[3] != '#' && (memseg->map[3] == memseg->map[4]) && (memseg->map[4] == memseg->map[5]))
    {
        test = memseg->map[3];
    }

    if (memseg->map[6] != '#' && (memseg->map[6] == memseg->map[7]) && (memseg->map[7] == memseg->map[8]))
    {
        test = memseg->map[6];
    }
    if (test != '#') {
        if (test == 'X')
        {
            memseg->isEnded = 1;
        }
        else
        {
            memseg->isEnded = 2;
        }
    }


}



int main(int argc, wchar_t** argv) {
    if (argc != 2)
    {
        if (argc > 2)
        {
            std::cout << strerror(errno) << " uzyto za duzo argumentow" << std::endl;
        }
        std::cout << strerror(errno) << " uzyj " << *argv[0] << " <nazwa pliku> \n np. " << * argv[0] << " abc123" << std::endl;
        return 1;
    }

    HANDLE MapFile;

    char player = 1;
    MapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, argv[1]);
    if (MapFile == NULL)
    {
        MapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(gameInformation), argv[1]);
        player = 0;
        if (MapFile == NULL)
        {
            std::cout << strerror(errno) << "Could not create file mapping object" << std::endl;
            return 2;
        }
    }

    gameInformation* memseg = (gameInformation*)MapViewOfFile(MapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(gameInformation));

    if (memseg == NULL)
    {
        std::cout << strerror(errno) << "Could not map view of file" << std::endl;
        CloseHandle(MapFile);
        return 3;
    }

    //game

    if (!player)
    {
        memseg->isEnded = 0;
        memseg->move = 0;
        memseg->map[9];
        memseg->moves = 0;
        for (int i = 0; i < 9; i++)
        {
            memseg->map[i] = '#';
        }

    }
    else
    {
        Draw(memseg, player);
    }


    while (memseg->isEnded == 0 && memseg->moves < 9)
    {
        if (player == memseg->move)
        {
            Draw(memseg, player);
            DoMove(memseg, player);
            memseg->moves++;
            checkEnd(memseg);
        }
        else
            WaitForMove(memseg, player);
    }
    if (memseg->isEnded == 0 && memseg->moves == 9)
    {
        std::cout << "Remis!" << std::endl;
    }
    else
    {
        if (memseg->isEnded == player + 1)
        {
            std::cout << "Wygrales!" << std::endl;
        }
        else
        {
            std::cout << "Przegrales!" << std::endl;
        }
    }


    if (!UnmapViewOfFile(memseg))
    {
        std::cout << strerror(errno) << "Could not unmap view of file" << std::endl;
        CloseHandle(MapFile);
        return 4;
    }
    CloseHandle(MapFile);
    return 0;
}
