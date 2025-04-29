# TetrisCPP

This project will use C++ and the SFML library to create a Desktop Tetris game for learning purposes.
I will use the Model-View-Controller Architecture just because. I dont know if its appropriate for game dev, but I will stick to it, because it gives some guidance on how to structure code, which is what I try to learn.

# MVC Architecture
The MVC architecture is a way of organizing your code in a modular and encapsulated way. Key principle is the separation of UI and Data / Logic.
By breaking up frontend and backend into separate components the production of a GUI-App becomes more managable and accessible to multiple developers.

The general principle behind this Architecture is SoC: Separation of Concerns.

# Model
The models concern is managing the data. This could happen via a database, an API or simply objects. It stores data ( or knows where its stored ) and provides methods for manipulating it in a controlled manner.

# View
Decides how data is rendered. Presents Model data and sends user actions to the controller.

# Controller
Links Model and View. Manipulates / Accesses data of Model and provides it to the View for rendering. Furthermore it processes events happening in views by e.g. manipulating model data.

# Implementation
- ensure each component operates independently
- interface view listener defines all functions an observer of a view should implement --> responses to all the necessary events
  - view stores collection of observers and calls the implemented methods of view listener according to the triggered events
  - controller implements view listener interface and is responsible for handling those events by pulling data from model, updating view, etc.
- controller registers view and model

https://harddrop.com/wiki/SRS
