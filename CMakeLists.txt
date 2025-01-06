cmake_minimum_required(VERSION 3.10)
project(pbl2)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create lists of source files
set(CONTROLLER_SOURCES
    src/Controller/Account_Management.cpp
    src/Controller/Admin.cpp
    src/Controller/Controller.cpp
    src/Controller/DB_Helper.cpp
    src/Controller/Messages.cpp
    src/Controller/Movie_Management.cpp
    src/Controller/Room_Management.cpp
    src/Controller/Seat_Management.cpp
    src/Controller/Showtime_Management.cpp
    src/Controller/Ticket_Management.cpp
)

set(MODEL_SOURCES
    src/Model/Account.cpp
    src/Model/Comparable.cpp
    src/Model/Movie.cpp
    src/Model/Room.cpp
    src/Model/Seat.cpp
    src/Model/Showtime.cpp
    src/Model/Ticket.cpp
    src/Model/DateTime.cpp
)

set(VIEW_SOURCES
    src/View/DisplayManager.cpp
)

# Add the main executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
    ${CONTROLLER_SOURCES}
    ${MODEL_SOURCES}
    ${VIEW_SOURCES}
)

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/Controller
    src/Model
    src/View
)