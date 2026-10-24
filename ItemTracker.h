#ifndef ITEM_TRACKER_H
#define ITEM_TRACKER_H

#include <string>
#include <map>

/**
 * @class ItemTracker
 * @brief Manages item purchase frequencies loaded from an input file,
 *        handles backing up data to frequency.dat, and provides menu operations.
 */
class ItemTracker
{
private:
    std::map<std::string, int> m_itemFrequencies;
    const std::string m_inputFileName = "CS210_Project_Three_Input_File.txt";
    const std::string m_backupFileName = "frequency.dat";

    // Private helper methods
    void loadData();
    void createBackupFile() const;
    std::string toTitleCase(const std::string &str) const;

public:
    // Constructor initializes data and creates backup file automatically
    ItemTracker();

    // Core functionality
    int getItemFrequency(const std::string &item) const;
    void printAllFrequencies() const;
    void printHistogram() const;
    void displayMenu() const;
    void run();
};

#endif // ITEM_TRACKER_H