# Who wants to be a millionaire?

https://user-images.githubusercontent.com/60004480/187656479-72b1472f-b9c5-412f-8721-4895dce74ada.mp4

(**Refresh page if you have problem with the video**)

# About the Game

This game was created in c++ made with Simple DirectMedia Layer (SDL).

The program contains more than 5,000 questions in English, German and Hungarian.

In conclusion the game has a full version of English, German and Hungarian.

# Important to know before start

- The game was designed for `hungarian` play. 
- The original questions are hungarian so the `english and german versions are translated` with google translater -> There can be a LOT OF anomaly.
- There is `no memory leak` according to the CrtDumpMemoryLeaks().
- The **"Windows.h"** include was used in the program -> Game `can be run only on WINDOWS`.

# How to compile and run the project form TERMINAL
1. Download the `Only Source Files` project form my github.
2. Extract the project and open the `Only Source Files` directory (You should be where the .cpp files are) then create a new directory named as src
3. In the src directory create two new directories named as include and lib
4. Download SDL, SDL_image, SDL_mixer, SDL_ttf libraries. <br>

<div align="center">

| SDL libraries  | Description |
| :----------- | :----------- |
| SDL         | https://www.libsdl.org/release/SDL2-devel-2.0.22-VC.zip       |
| SDL_image   | https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.6.2-VC.zip      |
| SDL_mixer   | https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.6.2-VC.zip        |
| SDL_ttf     | https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.20.1-VC.zip        |

</div>

5. Extract the downloaded libraries. Every library will contain an include and lib directories.
6. From the SDL include directories move all the .h files to our project's src/include directory.
7. From the SDL x64/lib directories move all the .lib files to our project's src/lib directiory.
8. From the SDL x64/lib directories move the `SDL2.dll | SDL2_image.dll | SDL2_mixer.dll | SDL2_ttf.dll` libraries to our project's directiory. (These files should be where the .cpp and .h files are.)
9. At this point you should see this.

<div align="center">

| Main Directory  | Src Directory  | Include Directory   | Lib Directory  |
| :----------- | :----------- | :----------- | :----------- |
| ![image](https://user-images.githubusercontent.com/60004480/201665505-dd66f3e2-1c8e-4312-9469-6cfff5bcbeb1.png)        | ![image](https://user-images.githubusercontent.com/60004480/201665902-51259978-84eb-4d12-ab7a-d88ea5ebd3e4.png)      | ![image](https://user-images.githubusercontent.com/60004480/201665829-4d58dcec-15f0-4164-83ce-b612329bc374.png) | ![image](https://user-images.githubusercontent.com/60004480/201665782-eed52d14-8d5a-4ae9-938f-5062bb6d5d6f.png) |

</div>

10. Open a terminal in the directory and compile the files with this command: <br>
`g++ -Isrc/include -Lsrc/lib *.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wall -Wextra`

11. Run the a.exe file and you are ready to go.

# Problem with Threads while compiling the project.

`At the 10. step you might get an error like this.`

![image](https://user-images.githubusercontent.com/60004480/201669180-c6f7f548-552f-4216-bb55-50e6c02f2245.png)

## Try this first

```
Compile the project with -pthread and -std=c++17. <br>
```

## Problem

```
If the above advice did not worked then it is likely that your version of the c++ compiler does not support threads by default. 
I used to have the same problem with this version of g++. 
```

![image](https://user-images.githubusercontent.com/60004480/201670167-c9e3fc38-14da-46a4-afdd-918547f45503.png)

## Solution

```
The solution was to download another g++ compiler with the posix version.
I downloaded the `prebuild MinGW-w64 x86 posix` version and everything works fine with it.
(With this version you don't need to use the -pthread and -std=c++17 operators.)

https://www.mingw-w64.org/downloads/#mingw-builds
```

![image](https://user-images.githubusercontent.com/60004480/201671907-66c4ac2d-74fe-4136-b632-28e1f6a5ed8f.png)

# How to run Project from Visual Studio 2022

1. Download the `Visual Studio 2022 Version` from my Github
2. Create an directory named as SDL2 recommended in C:\
3. Create an `include`, `lib`, `bin` direcory inside of the SDL2 directory.
3. Download SDL, SDL_image, SDL_mixer, SDL_ttf libraries. <br>

<div align="center">

| SDL libraries  | Description |
| :----------- | :----------- |
| SDL         | https://www.libsdl.org/release/SDL2-devel-2.0.22-VC.zip       |
| SDL_image   | https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.6.2-VC.zip      |
| SDL_mixer   | https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.6.2-VC.zip        |
| SDL_ttf     | https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.20.1-VC.zip        |

</div>

4. Extract the downloaded libraries and move all their .h files from include directory to our SDL2\include directory. (C:\SDL2\include)
5. Move all their .lib files from lib\x64 to our SDL2\lib directory. (C:\SDL2\lib)
6. Move all their .dll files from lib\x64 to our SDL2\bin directory. (C:\SDL2\bin)
7. At this point you should see this.

| SDL2 Directory  | Bin Directory  | Include Directory   | Lib Directory  |
| :----------- | :----------- | :----------- | :----------- |
| ![image](https://user-images.githubusercontent.com/60004480/201678187-71700633-50b2-48da-945b-4dcea1da44f9.png)       | ![image](https://user-images.githubusercontent.com/60004480/201679014-a5d311d9-c9b1-4a82-b097-4ceecf789f8d.png)      | ![image](https://user-images.githubusercontent.com/60004480/201679046-7bbddc3c-f4be-49f3-9249-32e7478151d4.png) | ![image](https://user-images.githubusercontent.com/60004480/201678503-d0fdf704-627f-48fb-b187-2cbab45158da.png) |

8. Open a terminal and create a virutal disk using this command: <br>
   `subst T: C:\`
9. Open the Visual Studio 2022 project and you are ready to go.

# Start Display

![kép](https://user-images.githubusercontent.com/60004480/187660290-f437689b-7ad6-41a7-8059-af8374041509.png)

On the start display there are 3 buttons. <br>
- The first will load the `Select display`. If you want to create a new game then click on this. <br>
- The second button will load the `LeaderBoard display`. If you want to check the top 10 player of all time then click on this.<br>
- The third button will load the `Results display`. If you are curious about your results then click on this button.<br>

# LeaderBoard display

![kép](https://user-images.githubusercontent.com/60004480/187661297-a085d424-c0fe-41cf-87e6-1423b8fc3c79.png)

- On this display you can check the top 10 player by the different game modes. <br>
- After you played a game your game state will **saved in a file**. <br>
- If you did well you will be shown on the leaderboards. <br>

# Results display

![kép](https://user-images.githubusercontent.com/60004480/187662756-cc8980b3-2fda-4ec3-8da9-d1bd0428f2ee.png)

On the Results display you can check the game results of a given player. 
- Click on the `input text field` and start to type your or somebody else's name.
- For capital letter use the `CAPS LOCK` key.
- After you typed a name click on the `green check mark`, and **all the results will be shown**.

# Select display

![kép](https://user-images.githubusercontent.com/60004480/187666659-ba9023bd-b9f6-4bac-9b9b-03d286933b2c.png)

- You must choose a `game mode` and a `name`. <br>
- If you didn't choose any of them you **can't start the game**. <br>
- The chosen game mode will be green. <br>
- After you click on start game button the INGAME button will be displayed.

# InGame display

![kép](https://user-images.githubusercontent.com/60004480/187667306-c8592872-bab9-4b2b-94c9-247220e0d907.png)

At the left side you can find the helps.
- `50 / 50` -> This help deletes 2 answers
- `Phone` -> You have 30 seconds to "phone" a friend
- `Ask the Audience` -> The audience votes and you can decide to belive them or not.
- The used helps are rendered with a red X and they are unavailable.

At the right side you can find the values you can win.
- The **current winnable prize** is marked as `yellow`.
- The **completed prizes** are marked as `green`.
- Language is **hungarian** the prizes are in `HUF`, otherwise they are in `DOLLAR`

# Option display

![kép](https://user-images.githubusercontent.com/60004480/187668807-0f2922fd-eb03-47e5-9e7f-a71fb15ceed6.png)

Available game languages: 
- `English`
- `German`
- `Hungarian`
- You can set the language while being on `any of the displays`. After you set it every text will be displayed according to the language.

Available game font types:
- `Times New Roman`
- `Minecraft`
- `IndieFlower Regular`

Music Volume `(0 - 10)` <br>
Chunk Volume `(0 - 10)`

# About the Game Sounds
The full sound track: https://www.youtube.com/watch?v=MForOVuA6hs <br>
Click sound: https://www.youtube.com/watch?v=h6_8SlZZwvQ <br>
Hover sound: https://www.youtube.com/watch?v=caezQznghGE <br>
Error sound: https://www.youtube.com/watch?v=FwVRkhy5G04 <br>

