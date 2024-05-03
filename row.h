    #ifndef ROW_H
    #define ROW_H

    #include <string>

    class Globals; 

    class Row {
    public:
        Row(Globals* globalsInstance);
        void addRowView();
        void addRow(const std::string& tableName, const std::string& columnName, const std::string& columnType);
        bool isValidColumnType(const std::string& columnType);

    private:
        Globals* globalsInstance; // Pointer to Globals instance
    };

    #endif // ROW_H
