Puzzle Piece Edge Detection

Author:     Tom Cariello
Created:    1/31/2019

The Goal:
    Create a process to identify, isolate & process jigsaw puzzle pieces to seperate "Edge" (outside) pieces from all other pieces.

The Tech:
    This project is written in C++ (ISO C++ 17 Standard) and using openCV 4.0.1 (https://docs.opencv.org/4.0.1/) to handle image processing. I am using Visual Studio 2017 on a Windows 10 64-bit PC.

The Sorting Lifecycle:
    Dump all puzzle pieces into a common area. This could be on a table, in a box, in a hopper, etc. These are not sorted at all.
    Using a camera & image processing, determine if there are any pieces in the hopper.
        If there are pieces, identify & select a single piece.
        If there are no pieces end the process.
    Move the individual piece to a platform(?) for additional checking.
    Take image (or frame from video) of piece. 
    Process image through Edge detection algorithm.
    Determine the likelihood that the piece is an Edge piece.
    Sort edge pieces into a seperate bucket from the rest of the pieces.

The Roadmap:
    [ ] = Status. [X] indicates that step is completed.
    [X]   Using a Windows PC, process pre-rendered JPG images through Edge detection algorithm
    [ ]   Determine the likelihood that a given piece is an Edge piece.
    [ ]   Install & interface with webcam (or similar) instead of pre-rendered images.
    [ ]   Create physical interface to sort edge pieces into a seperate bucket from the rest of the pieces.
    [ ]   Create physical interface to "load" puzzle pieces into position of the webcam.
    [ ]   Port code to Arduino/RaspPi hardware

How to use (Note: This WILL change as development continues):
    Clone the repository.
    Download & extract openCV & configure the application to use it (https://www.youtube.com/watch?v=l4372qtZ4dc&t=819s).
    Create a /data folderin the root directory.
    Copy your JPG files into this directory.
    When you run the program each of the images will be run through the edge detector. Press any button to advance through the image(s).
