# Crane Project
![crane](https://user-images.githubusercontent.com/106777205/190901745-06755e2f-5526-48b1-a9c8-74d3dbfcb38f.PNG)
Crane in this project can attract objcects (square, circle, triangle) and put them on the top of each other.
- #### Space - attract or loose objects
- #### WASD  - standart buttons to manipulate the chain of the crane
- #### Esc   - Make disappear all objects
- #### By clicking left mouse on objects, you make them spawn

One of the main goal of this project was to realise that using buffer for animation
![image](https://user-images.githubusercontent.com/106777205/190902083-1f253357-e569-451b-a396-fe8863215e0a.png)

## Problems
The problem of this project was drawing. Firstly I wanted to used GDI+ to draw shapes, but then memDC doesn't worked correctly, so I used to find another function to draw lines. After that I have the problems with buttons, I can't see them, so I draw the shapes and using WndProc make their area clickable.

## Using techologies
* C++
* Winapi
* GDI
* Buffering


###### This code was written by Aliaksandr Karpovich, the student of Gdansk Technical University.
