#include "ItemTracker.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <limits>

/**
 * Constructor: Initializes the tracker by loading purchase records
 * and immediately generating the required frequency.dat backup file.
 */
ItemTracker::ItemTracker()
{
    loadData();
    createBackupFile();
}

/**
 * Reads CS210_Project_Three_Input_File.txt line-by-line and stores word counts in a std::map.
 */
void ItemTracker::loadData()
{
    std::ifstream inFile(m_inputFileName);

    if (!inFile.is_open())
    {
        std::cerr << "[Error] Could not open input file: " << m_inputFileName << std::endl;
        std::cerr << "Please ensure the file is located in the working directory." << std::endl;
        return;
    }

    std::string word;
    while (inFile >> word)
    {
        // Standardize input casing (Title Case) so "apples" and "Apples" match
        word = toTitleCase(word);
        m_itemFrequencies[word]++;
    }

    inFile.close();
}

/**
 * Creates the frequency.dat backup file containing item names paired with their frequencies.
 * Executed at program launch without user intervention.
 */
void ItemTracker::createBackupFile() const
{
    std::ofstream outFile(m_backupFileName);

    if (!outFile.is_open())
    {
        std::cerr << "[Error] Could not create backup file: " << m_backupFileName << std::endl;
        return;
    }

    for (const auto &pair : m_itemFrequencies)
    {
        outFile << pair.first << " " << pair.second << "\n";
    }

    outFile.close();
}

/**
 * Converts a string to Title Case (e.g., "apples" -> "Apples").
 */
std::string ItemTracker::toTitleCase(const std::string &str) const
{
    if (str.empty())
        return str;
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    result[0] = static_cast<char>(::toupper(result[0]));
    return result;
}

/**
 * Menu Option 1: Searches for a specific item and returns its frequency.
 */
int ItemTracker::getItemFrequency(const std::string &item) const
{
    std::string formattedItem = toTitleCase(item);
    auto iter = m_itemFrequencies.find(formattedItem);

    if (iter != m_itemFrequencies.end())
    {
        return iter->second;
    }
    return 0; // Item not found in records
}

/**
 * Menu Option 2: Prints all items and their numerical frequencies.
 */
void ItemTracker::printAllFrequencies() const
{
    std::cout << "\n=====================================\n";
    std::cout << "      ITEM PURCHASE FREQUENCIES      \n";
    std::cout << "=====================================\n";

    for (const auto &pair : m_itemFrequencies)
    {
        std::cout << std::left << std::setw(15) << pair.first
                  << " " << pair.second << "\n";
    }
    std::cout << "=====================================\n";
}

/**
 * Menu Option 3: Prints items with a visual histogram using asterisks (*).
 */
void ItemTracker::printHistogram() const
{
    std::cout << "\n=====================================\n";
    std::cout << "       ITEM PURCHASE HISTOGRAM       \n";
    std::cout << "=====================================\n";

    for (const auto &pair : m_itemFrequencies)
    {
        std::cout << std::left << std::setw(15) << pair.first << " ";
        // Print asterisks equal to the frequency count
        for (int i = 0; i < pair.second; ++i)
        {
            std::cout << "*";
        }
        std::cout << "\n";
    }
    std::cout << "=====================================\n";
}

/**
 * Displays the formatted main menu options.
 */
void ItemTracker::displayMenu() const
{
    std::cout << "\n=====================================\n";
    std::cout << "      CORNER GROCER ITEM TRACKER     \n";
    std::cout << "=====================================\n";
    std::cout << "1. Search for Item Frequency\n";
    std::cout << "2. Display All Item Frequencies\n";
    std::cout << "3. Display Item Histogram\n";
    std::cout << "4. Exit Program\n";
    std::cout << "=====================================\n";
    std::cout << "Enter your choice (1-4): ";
}

/**
 * Main application execution loop with robust input validation.
 */
void ItemTracker::run()
{
    int userChoice = 0;

    while (userChoice != 4)
    {
        displayMenu();

        // Optional Challenge: Input Validation and Error Handling
        if (!(std::cin >> userChoice))
        {
            std::cout << "\n[Invalid Input] Please enter a valid integer between 1 and 4.\n";
            std::cin.clear();                                                   // Clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
            continue;
        }

        switch (userChoice)
        {
        case 1:
        {
            std::string searchItem;
            std::cout << "\nEnter the item name to search for: ";
            std::cin >> searchItem;
            int count = getItemFrequency(searchItem);
            std::cout << "\nResult: " << toTitleCase(searchItem)
                      << " was purchased " << count << " time(s).\n";
            break;
        }
        case 2:
            printAllFrequencies();
            break;
        case 3:
            printHistogram();
            break;
        case 4:
            std::cout << "\nThank you for using the Corner Grocer Item-Tracking System. Goodbye!\n";
            break;
        default:
            std::cout << "\n[Invalid Option] Selection must be between 1 and 4.\n";
            break;
        }
    }
}