#ifndef COMMAND_REGISTRATION_H
#define COMMAND_REGISTRATION_H

#include "interface.h"
#include "user.h"
#include "help.h"
#include "database.h"
#include "table.h"
#include "records.h"
#include "row.h"

void registerCommands(Interface& interface) {
    interface.registerCommand("help", Help::help);

    //user:
    interface.registerCommand("createUser", User::createView);
    interface.registerCommand("viewUser", User::readView);
    interface.registerCommand("deleteUser", User::delView);
    interface.registerCommand("updateUser", User::updateView);
    interface.registerCommand("login", User::loginView);
    interface.registerCommand("lsu", User::listAll);
    interface.registerCommand("whoami", User::whoami);
    interface.registerCommand("logout", User::logout);

    //db:
    interface.registerCommand("createDatabase", Database::createDatabaseView);
    interface.registerCommand("createTable", Table::createTableView); 
    interface.registerCommand("deleteTable", Table::deleteTableView); 
    interface.registerCommand("lst", Table::listTables); 
    interface.registerCommand("addRecord", Records::addRecordView); 
    interface.registerCommand("lsr",Records::printTableView);
    interface.registerCommand("addRow",Row::addRowView);
    
}

#endif
