# BasicDBMS 
[Polska Wersja](https://github.com/KrzysztofMarciniak/basicDBMS/wiki/readmePL)

BasicDBMS is a simple and minimalistic database management system written in C++ with an object-oriented approach. It allows users to create databases, tables, manage rows within those tables, and includes user authentication features. Check out [wiki](https://github.com/KrzysztofMarciniak/basicDBMS/wiki) for more information.

## Features:

- **User Authentication**: The system supports user authentication, allowing users to securely log in and manage their data.
- **Basic Database Usage**: BasicDBMS allows for the creation of databases, tables, rows, and records.
- **System Logs**: Implemented a logging system for tracking system activities and events.

## Usage:

1. **Compile**: Compile the source code of BasicDBMS using a C++ compiler. (use `make`)
2. **Run**: Execute the compiled program to start using BasicDBMS. 
3. **Commands**: Use the command-line interface to interact with BasicDBMS. Below are some sample commands:
   - `help`: Displays available commands.
   - `createDatabase`: Create a new database.
   - `createTable`: Create a new table within a database.
   - `addRow`: Add a new row to a table.
   - `login`: Log in to the system.
   - `createAccount`: Create a new user account.

## Folder Structure:

- **Database Folder**: Each database is stored in a separate folder for organization.
- **Table Folder**: Within each database folder, tables are stored in separate folders.
- **Row Files**: Rows within tables are represented as files within the corresponding table folder.
- **Records Storage**: Records are stored inside row files.

## Implementation:

BasicDBMS is implemented in C++ with a focus on simplicity and minimalism. Object-oriented programming principles are used to structure the codebase, making it easy to understand and extend. For example, `user.h` and `user.cpp` handle user management functionalities.

## Contributions:

Contributions to BasicDBMS are welcome! If you have any ideas for improvements or new features, feel free to submit a pull request or open an issue on GitHub.

## License:

This project is licensed under the GPL-3.0 License - see the [LICENSE](LICENSE) file for details.

---

**Note:** BasicDBMS is intended for educational purposes and may not be suitable for production environments requiring advanced database management features.
