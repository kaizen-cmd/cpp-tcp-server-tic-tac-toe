# Release Notes - Version 1.0

## 🚀 New Features

### Server and Client Implementation

- **Server (game_tcp_server):**
  - TCP server implementation to handle two clients for playing Tic Tac Toe.
  - Listens for client connections and assigns 'X' and 'O' to connected clients.
  - Utilizes a multi-threaded approach for handling multiple client connections simultaneously.
  - Displays connection details of clients and welcomes them to the Tic Tac Toe game.

- **Client (game_client):**
  - Connects to the Tic Tac Toe server using a TCP connection.
  - Implements a simple console-based user interface for making moves in the Tic Tac Toe game.
  - Receives and displays messages and moves from the server.

### Tic Tac Toe Game Logic

- **Tic Tac Toe Game (TicTacToe.cpp, TicTacToe.h):**
  - Implements the core logic for the Tic Tac Toe game.
  - Allows two clients to play the game, making moves using a custom protocol.
  - Checks for a winner, validates moves, and updates the game board.
  - Communicates with the server and clients through the provided API.

## 🎮 Gameplay Enhancements

- **Move Format:**
  - Players can make moves using the format `MOVXY`, where `X` and `Y` are the coordinates (0-2).
  - Example: `MOV11` represents placing a symbol in the center of the Tic Tac Toe board.

- **Player Assignment:**
  - Clients are assigned 'X' and 'O' upon connection to the server.
  - The server announces the player's assigned symbol upon connection.

## 📝 Additional Notes

- **GitHub Actions:**
  - Automated build and test workflows using GitHub Actions.
  - Automatic release generation for binaries when code is merged into the main branch.
  - Tagged releases follow the format `v1.x`, where `x` is the GitHub Actions run number.

- **Clean Code Structure:**
  - Organized project structure into distinct folders (`src/tcp_server`, `src/client`, `src/boardGames`).
  - Clear separation of server, client, and game logic.

## 🛠️ Contribution

For information on building and running the project, please refer to the `README.md` file. Contributions are welcome!
