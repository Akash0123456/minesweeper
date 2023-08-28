    #include <SFML/Graphics.hpp>
#include"TextureManager.h"
#include"Board.h"
#include <iostream>
using namespace std;



int main()
{
    Board board;

    bool debugMode = false; // If true, then debug mode is on.
    //cout << board.mines << endl;

    board.numTiles = board.rows * board.columns;

    sf::Sprite unrevealedTile(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite revealedTile(TextureManager::GetTexture("tile_revealed"));

    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite happyFace(TextureManager::GetTexture("face_happy"));
    sf::Sprite loseFace(TextureManager::GetTexture("face_lose"));
    sf::Sprite winFace(TextureManager::GetTexture("face_win"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));

    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));

    sf::Sprite num1(TextureManager::GetTexture("number_1"));
    sf::Sprite num2(TextureManager::GetTexture("number_2"));
    sf::Sprite num3(TextureManager::GetTexture("number_3"));
    sf::Sprite num4(TextureManager::GetTexture("number_4"));
    sf::Sprite num5(TextureManager::GetTexture("number_5"));
    sf::Sprite num6(TextureManager::GetTexture("number_6"));
    sf::Sprite num7(TextureManager::GetTexture("number_7"));
    sf::Sprite num8(TextureManager::GetTexture("number_8"));

    sf::Sprite digit0(TextureManager::GetTexture("digits"));
    sf::Sprite digit1(TextureManager::GetTexture("digits"));
    sf::Sprite digit2(TextureManager::GetTexture("digits"));
    sf::Sprite digit3(TextureManager::GetTexture("digits"));
    sf::Sprite digit4(TextureManager::GetTexture("digits"));
    sf::Sprite digit5(TextureManager::GetTexture("digits"));
    sf::Sprite digit6(TextureManager::GetTexture("digits"));
    sf::Sprite digit7(TextureManager::GetTexture("digits"));
    sf::Sprite digit8(TextureManager::GetTexture("digits"));
    sf::Sprite digit9(TextureManager::GetTexture("digits"));
    sf::Sprite negativeSign(TextureManager::GetTexture("digits"));


    digit0.setTextureRect(sf::IntRect(0, 0, 21, 32));
    digit1.setTextureRect(sf::IntRect(21, 0, 21, 32));
    digit2.setTextureRect(sf::IntRect(42, 0, 21, 32));
    digit3.setTextureRect(sf::IntRect(63, 0, 21, 32));
    digit4.setTextureRect(sf::IntRect(84, 0, 21, 32));
    digit5.setTextureRect(sf::IntRect(105, 0, 21, 32));
    digit6.setTextureRect(sf::IntRect(126, 0, 21, 32));
    digit7.setTextureRect(sf::IntRect(147, 0, 21, 32));
    digit8.setTextureRect(sf::IntRect(168, 0, 21, 32));
    digit9.setTextureRect(sf::IntRect(189, 0, 21, 32));
    negativeSign.setTextureRect(sf::IntRect(210, 0, 21, 32));

    map<int, sf::Sprite> numbers;
    numbers[1] = num1;
    numbers[2] = num2;
    numbers[3] = num3;
    numbers[4] = num4;
    numbers[5] = num5;
    numbers[6] = num6;
    numbers[7] = num7;
    numbers[8] = num8;

    map<int, sf::Sprite> digitNumbers;
    digitNumbers[0] = digit0;
    digitNumbers[1] = digit1;
    digitNumbers[2] = digit2;
    digitNumbers[3] = digit3;
    digitNumbers[4] = digit4;
    digitNumbers[5] = digit5;
    digitNumbers[6] = digit6;
    digitNumbers[7] = digit7;
    digitNumbers[8] = digit8;
    digitNumbers[9] = digit9;
    digitNumbers[10] = negativeSign;


    bool clicked = false;
    bool hasWon = false;
    bool hasLost = false;

    int tileWidth = unrevealedTile.getGlobalBounds().width; // 32
    int tileHeight = unrevealedTile.getGlobalBounds().height; // 32

    int interfaceTileWidth = happyFace.getGlobalBounds().width; // 64
    int interfaceTileHeight = happyFace.getGlobalBounds().height; // 64  


    int flagCount = board.mines;

    int clearedTileNum = 0;


    sf::RenderWindow window(sf::VideoMode(board.columns * 32, (board.rows * 32 + 100)), "Minesweeper");


    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        int columnClicked = mousePosition.x / tileWidth;
        int rowClicked = mousePosition.y / tileHeight;
        int cellClicked = rowClicked * board.columns + columnClicked;

        //cout << "Column is: " << columnClicked << " Row is: " << rowClicked << " Cell Clicked: " << cellClicked << endl;
        //cout << mousePosition.x << " " << mousePosition.y << endl;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (hasLost == 0 && hasWon == 0)
                    {
                        // If you are clicking the left Mouse button on the BOARD
                        if (columnClicked < board.columns && rowClicked < board.rows && cellClicked < board.tiles.size())
                        {
                            if (board.tiles[cellClicked].isFlagged == 0)
                            {
                                board.tiles[cellClicked].isRevealed = true;

                                if (board.tiles[cellClicked].numberOnTile == 0 && board.tiles[cellClicked].isFlagged == 0)
                                {
                                    for (int i = 0; i < board.tiles[cellClicked].adjacentTiles.size(); i++)
                                    {
                                        if (board.tiles[cellClicked].adjacentTiles[i]->isFlagged == false)
                                        {
                                            board.tiles[cellClicked].adjacentTiles[i]->isRevealed = true;
                                        }                                        
                                    }
                                }
                            }
                        }
                    }


                    // IF YOU ARE CLICKING THE FACE BUTTON

                    sf::Vector2f facePosition = happyFace.getPosition();

                    if ((mousePosition.x >= facePosition.x) && (mousePosition.x <= facePosition.x + interfaceTileWidth) && (mousePosition.y >= facePosition.y) && (mousePosition.x <= facePosition.x + interfaceTileWidth))
                    {
                        if (hasLost == true)
                            hasLost = false;

                        board.LoadNewBoard("random");
                        //cout << "Mouse click worked!!!" << endl;
                        flagCount = board.mines;
                    }

                    // IF YOU ARE CLICKING DEBUG BUTTON

                    sf::Vector2f debugPosition = debug.getPosition();

                    //cout << debugPosition.x << " " << debugPosition.y << endl;

                    if ((mousePosition.x >= debugPosition.x) && (mousePosition.x <= debugPosition.x + interfaceTileWidth) && (mousePosition.y >= debugPosition.y) && (mousePosition.x <= debugPosition.x + interfaceTileWidth))
                    {
                        debugMode = !debugMode;
                        //cout << "Mouse click worked!!!" << endl;
                    }

                    // IF YOU ARE CLICKING TEST#1 ICON

                    sf::Vector2f test1Position = test1.getPosition();

                    if ((mousePosition.x >= test1Position.x) && (mousePosition.x <= test1Position.x + interfaceTileWidth) && (mousePosition.y >= test1Position.y) && (mousePosition.x <= test1Position.x + interfaceTileWidth))
                    {
                        board.LoadNewBoard("test1");
                        //cout << "Mouse click worked!!!  1" << endl;
                        flagCount = board.mines;
                    }


                    // IF YOU ARE CLICKING THE TEST#2 ICON

                    sf::Vector2f test2Position = test2.getPosition();

                    if ((mousePosition.x >= test2Position.x) && (mousePosition.x <= test2Position.x + interfaceTileWidth) && (mousePosition.y >= test2Position.y) && (mousePosition.x <= test2Position.x + interfaceTileWidth))
                    {
                        board.LoadNewBoard("test2");
                        //cout << "Mouse click worked!!!  2" << endl;
                        flagCount = board.mines;
                    }

                    // IF YOU ARE CLICKING THE TEST#3 ICON


                    sf::Vector2f test3Position = test3.getPosition();

                    if ((mousePosition.x >= test3Position.x) && (mousePosition.x <= test3Position.x + interfaceTileWidth) && (mousePosition.y >= test3Position.y) && (mousePosition.x <= test3Position.x + interfaceTileWidth))
                    {
                        board.LoadNewBoard("test3");
                        //cout << "Mouse click worked!!!  3" << endl;
                        flagCount = board.mines;
                    }


                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if (columnClicked < board.columns && rowClicked < board.rows && cellClicked < board.numTiles)
                    {
                        if (board.tiles[cellClicked].isFlagged == true)
                        {
                            board.tiles[cellClicked].isFlagged = false;
                            flagCount++;
                        }
                        else
                        {
                            board.tiles[cellClicked].isFlagged = true;
                            flagCount--;

                        }
                    }
                }
            }
        }


        window.clear();

        float posX;
        float posY;

        int x = 0;
        int y = 0;

        for (int i = 0; i < board.rows * board.columns; i++)
        {
            x = i % board.columns; // Rows
            y = i / board.columns; // Columns

            board.tiles[i].xPosition = (x * tileWidth);
            board.tiles[i].yPosition = (y * tileHeight);



            if (board.tiles[i].isRevealed == false)
            {
                unrevealedTile.setPosition(board.tiles[i].xPosition, board.tiles[i].yPosition);
                window.draw(unrevealedTile);

                if (board.tiles[i].isFlagged == true)
                {
                    flag.setPosition(board.tiles[i].xPosition, board.tiles[i].yPosition);
                    window.draw(flag);
                }

                if (debugMode == true && board.tiles[i].hasMine == true)
                {
                    mine.setPosition(board.tiles[i].xPosition, board.tiles[i].yPosition);
                    window.draw(mine);
                }

            }

            if (board.tiles[i].isRevealed == true)
            {
                revealedTile.setPosition(board.tiles[i].xPosition, board.tiles[i].yPosition);
                window.draw(revealedTile);

                if (board.tiles[i].hasMine == true)
                {
                    mine.setPosition(board.tiles[i].xPosition, board.tiles[i].yPosition);
                    window.draw(mine);
                }
                else
                {
                    int tileNum = board.tiles[i].numberOnTile;
                    numbers[tileNum].setPosition(board.tiles[i].xPosition, board.tiles[i].yPosition);
                    window.draw(numbers[tileNum]);

                }
            }
        }

        clearedTileNum = 0;

        for (int i = 0; i < board.tiles.size(); i++)
        {
            if (board.tiles[i].hasMine == 0 && board.tiles[i].isRevealed == 1)
            {
                clearedTileNum++;
            }

        }

        if (clearedTileNum == (board.tiles.size() - board.mines))
        {
            hasWon = true;
        }

        if (hasWon == true)
        {
            for (int i = 0; i < board.tiles.size(); i++)
            {
                if (board.tiles[i].hasMine == true)
                {
                    flag.setPosition(board.tiles[i].xPosition, board.tiles[i].yPosition);
                    window.draw(flag);

                    flagCount = 0;
                }
            }
        }

        if (hasLost == true)
        {
            for (int i = 0; i < board.tiles.size(); i++)
            {
                if (board.tiles[i].hasMine == true)
                    mine.setPosition(board.tiles[i].xPosition, board.tiles[i].yPosition);
                    window.draw(mine);
            }
        }



        // FLAG COUNTER

        posX = 0;
        posY = unrevealedTile.getGlobalBounds().height * board.rows;

        //cout << flagCount << " " << board.mines << endl;

        int leftMostSprite = abs(flagCount % 10);
        int middleSprite = abs(flagCount / 10);
        if (middleSprite == 10)
            middleSprite = 0;

        int rightMostSprite = abs(flagCount) / 100;


        if (flagCount < 0)
        {
            digitNumbers[10].setPosition(posX, posY);
            window.draw(digitNumbers[10]);
        }
        else
        {
            digitNumbers[rightMostSprite].setPosition(posX, posY);
            window.draw(digitNumbers[rightMostSprite]);
        }
        posX = (float)digitNumbers[leftMostSprite].getGlobalBounds().width;
        digitNumbers[middleSprite].setPosition(posX, posY);
        window.draw(digitNumbers[middleSprite]);
        posX *= 2;
        digitNumbers[leftMostSprite].setPosition(posX, posY);
        window.draw(digitNumbers[leftMostSprite]);


        // DRAWING THE FACE

        posX = ((board.columns * tileWidth) - (interfaceTileWidth)) / 2.0f;
        posY = board.rows * tileHeight;

        for (int i = 0; i < board.tiles.size(); i++)
        {
            if (board.tiles[i].hasMine && board.tiles[i].isRevealed)
                hasLost = true;
        }

            if (hasLost == true)
            {
                loseFace.setPosition(posX, posY);
                window.draw(loseFace);
            }
            else if (hasWon == true)
            {
                winFace.setPosition(posX, posY);
                window.draw(winFace);
            }
            else
            {
                happyFace.setPosition(posX, posY);
                window.draw(happyFace);
            }


        // Drawing Test#3 sprite
        posX = (board.columns * tileWidth) - interfaceTileWidth;
        test3.setPosition(posX, posY);
        window.draw(test3);

        // Drawing Test#2 sprite
        posX -= interfaceTileWidth;
        test2.setPosition(posX, posY);
        window.draw(test2);

        // Drawing Test#1 sprite
        posX -= interfaceTileWidth;
        test1.setPosition(posX, posY);
        window.draw(test1);

        // Drawing Debug toggle
        posX -= interfaceTileWidth;
        debug.setPosition(posX, posY);
        window.draw(debug);

        window.display();
    }

    TextureManager::Clear();

    return 0;
}