#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "DateUtility.h"

// Invoice Class
class Invoice
{
private:
    int id;
    std::string customerName;
    std::string issueDate;
    double totalValue;

public:
    Invoice(int id, const std::string &customerName, const std::string &issueDate, double totalValue)
        : id(id), customerName(customerName), issueDate(issueDate), totalValue(totalValue) {}

    // Getters
    int getId() const { return id; }
    std::string getCustomerName() const { return customerName; }
    std::string getIssueDate() const { return issueDate; }
    double getTotalValue() const { return totalValue; }

    // Setters
    void setId(int newId) { id = newId; }
    void setCustomerName(const std::string &newName) { customerName = newName; }
    void setIssueDate(const std::string &newDate) { issueDate = newDate; }
    void setTotalValue(double newValue) { totalValue = newValue; }

    // display methods
    void display() const
    {
        std::cout << "\nID: " << id << ", Customer: " << customerName << ", Date: " << issueDate << ", Total Value: " << totalValue;
    }
};

class InvoiceManager
{
private:
    std::vector<Invoice> invoices;

public:
    int getMaxId()
    {
        int maxId = 0;
        for (const auto &invoice : invoices)
        {
            if (invoice.getId() > maxId)
            {
                maxId = invoice.getId();
            }
        }
        return maxId;
    }

    Invoice enterInvoiceData()
    {
        std::string customerName;
        std::string issueDate;
        double totalValue;

        std::cout << "Enter customer name: ";
        std::getline(std::cin >> std::ws, customerName);

        std::cout << "Enter issue date (DD/MM/YYYY): ";
        std::cin >> issueDate;
        while (!DateUtility::isValidDate(issueDate))
        {
            std::cout << "The date format is invalid or the date is later than the current date.\nEnter issue date (DD/MM/YYYY): ";
            std::cin >> issueDate;
        }

        std::cout << "Enter total value: ";
        std::cin >> totalValue;

        return Invoice(this->getMaxId() + 1, customerName, issueDate, totalValue);
    }

    void displayAll()
    {
        for (const auto &invoice : invoices)
        {
            invoice.display();
        }
    }

    void displayInvoiceByIndex(int index)
    {
        if (index < 0 || index >= invoices.size())
        {
            std::cerr << "\nInvalid index.";
            return;
        }
        invoices[index].display();
    }

    void addInvoice(const Invoice &invoice)
    {
        invoices.push_back(invoice);
    }

    void addInvoiceAtStart(const Invoice &invoice)
    {
        invoices.insert(invoices.begin(), invoice);
    }

    void addInvoiceAtPosition(const Invoice &invoice, int position)
    {
        if (position < 0 || position > invoices.size())
        {
            std::cerr << "\nInvalid position.";
            return;
        }
        invoices.insert(invoices.begin() + position, invoice);
    }

    void editInvoiceById(int id)
    {
        for (auto &invoice : invoices)
        {
            if (invoice.getId() == id)
            {
                invoice = enterInvoiceData();
                return;
            }
        }
        std::cerr << "\nInvoice with ID " << id << " not found.";
    }

    void changeInvoicePosition(int id, int newPosition)
    {
        if (newPosition < 0 || newPosition > invoices.size())
        {
            std::cerr << "\nInvalid position.";
            return;
        }
        for (auto it = invoices.begin(); it != invoices.end(); ++it)
        {
            if (it->getId() == id)
            {
                Invoice invoice = *it;
                invoices.erase(it);
                invoices.insert(invoices.begin() + newPosition, invoice);
                return;
            }
        }
        std::cerr << "\nInvoice with ID " << id << " not found.";
    }

    void deleteInvoiceById(int id)
    {
        for (auto it = invoices.begin(); it != invoices.end(); ++it)
        {
            if (it->getId() == id)
            {
                invoices.erase(it);
                return;
            }
        }
        std::cerr << "\nInvoice with ID " << id << " not found.";
    }

    void deleteInvoiceByCustomerName(const std::string &customerName)
    {
        for (auto it = invoices.begin(); it != invoices.end(); ++it)
        {
            if (it->getCustomerName() == customerName)
            {
                invoices.erase(it);
                return;
            }
        }
        std::cerr << "\nInvoice with customer name " << customerName << " not found.";
    }

    void deleteInvoiceAtPosition(int position)
    {
        if (position < 0 || position > invoices.size())
        {
            std::cerr << "\nInvalid position.";
            return;
        }
        invoices.erase(invoices.begin() + position);
    }

    int searchInvoicePositionById(int id)
    {
        for (int i = 0; i < invoices.size(); ++i)
        {
            if (invoices[i].getId() == id)
            {
                return i;
            }
        }
        return -1;
    }

    int searchInvoicePositionByCustomerName(const std::string &customerName)
    {
        for (int i = 0; i < invoices.size(); ++i)
        {
            if (invoices[i].getCustomerName() == customerName)
            {
                return i;
            }
        }
        return -1;
    }

    std::vector<Invoice> searchInvoiceByIssueDateRange(const std::string &startDate, const std::string &endDate)
    {
        std::vector<Invoice> result;
        for (const auto &invoice : invoices)
        {
            if (
                DateUtility::compareDates(invoice.getIssueDate(), startDate) >= 0 
                && DateUtility::compareDates(invoice.getIssueDate(), endDate) <= 0)
            {
                result.push_back(invoice);
            }
        }
        return result;
    }

    void sortInvoicesByTotalValueAscending()
    {
        std::sort(invoices.begin(), invoices.end(), [](const Invoice &invoice1, const Invoice &invoice2)
                  { return invoice1.getTotalValue() < invoice2.getTotalValue(); });
    }

    void sortInvoicesByTotalValueDescending()
    {
        std::sort(invoices.begin(), invoices.end(), [](const Invoice &invoice1, const Invoice &invoice2)
                  { return invoice1.getTotalValue() > invoice2.getTotalValue(); });
    }

    void sortInvoicesByIssueDateAscending()
    {
        std::sort(invoices.begin(), invoices.end(), [](const Invoice &invoice1, const Invoice &invoice2)
                  { return DateUtility::compareDates(invoice1.getIssueDate(), invoice2.getIssueDate()) < 0; });
    }

    void sortInvoicesByIssueDateDescending()
    {
        std::sort(invoices.begin(), invoices.end(), [](const Invoice &invoice1, const Invoice &invoice2)
                  { return DateUtility::compareDates(invoice1.getIssueDate(), invoice2.getIssueDate()) > 0; });
    }
};

void displayMenu()
{
    std::cout << "\n\n================= MENU ================\n";
    std::cout << "(*). Enter -1 to exit.\n";
    std::cout << "(*). Enter 0 to add test invoices.\n";
    std::cout << "1. Display All Invoices\n";
    std::cout << "2. Add Invoice at End\n";
    std::cout << "3. Add Invoice at Start\n";
    std::cout << "4. Add Invoice at Specific Position\n";
    std::cout << "5. Edit Invoice by ID\n";
    std::cout << "6. Change Invoice Position in the List\n";
    std::cout << "7. Delete Invoice by ID\n";
    std::cout << "8. Delete Invoice by Customer Name\n";
    std::cout << "9. Delete Invoice at a Specific Position\n";
    std::cout << "10. Search for Invoice Position by ID\n";
    std::cout << "11. Search for Invoice by Customer Name\n";
    std::cout << "12. Search for Invoice by Issue Date Range\n";
    std::cout << "13. Sort Invoices by Total Value (Ascending)\n";
    std::cout << "14. Sort Invoices by Total Value (Descending)\n";
    std::cout << "15. Sort Invoices by Issue Date (Ascending)\n";
    std::cout << "16. Sort Invoices by Issue Date (Descending)\n";
    std::cout << "=====================================\n";
}

int main()
{
    InvoiceManager manager;
    int choice;

    displayMenu();

    while (true)
    {
        std::cout << "\n\nEnter your choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cerr << "Invalid choice.\n";
            continue;
        }

        switch (choice)
        {
        case -1:
            return 0;
        case 0:
            manager.addInvoice(Invoice(12, "Customer 12", "12/01/2021", 1200));
            manager.addInvoice(Invoice(7, "Customer 7", "07/01/2021", 700));
            manager.addInvoice(Invoice(8, "Customer 8", "08/01/2021", 800));
            manager.addInvoice(Invoice(1, "Customer 1", "01/01/2021", 100));
            manager.addInvoice(Invoice(9, "Customer 9", "09/01/2021", 900));
            manager.addInvoice(Invoice(11, "Customer 11", "11/01/2021", 1100));
            manager.addInvoice(Invoice(2, "Customer 2", "02/01/2021", 200));
            manager.addInvoice(Invoice(3, "Customer 3", "03/01/2021", 300));
            manager.addInvoice(Invoice(4, "Customer 4", "04/01/2021", 400));
            manager.addInvoice(Invoice(5, "Customer 5", "05/01/2021", 500));
            manager.addInvoice(Invoice(6, "Customer 6", "06/01/2021", 600));
            manager.addInvoice(Invoice(10, "Customer 10", "10/01/2021", 1000));
            break;
        case 1:
        {
            std::cout << "\n----- All invoices -----\n\n";
            manager.displayAll();
            break;
        }
        case 2:
        {
            std::cout << "\n----- Add Invoice at End -----\n\n";
            manager.addInvoice(manager.enterInvoiceData());
            std::cout << "\nInvoice added.";
            break;
        }
        case 3:
        {
            std::cout << "\n----- Add Invoice at Start -----\n\n";
            manager.addInvoiceAtStart(manager.enterInvoiceData());
            std::cout << "\nInvoice added.";
            break;
        }
        case 4:
        {
            std::cout << "\n----- Add Invoice at Specific Position -----\n\n";
            int position;
            std::cout << "Enter position (starting from 0): ";
            std::cin >> position;
            manager.addInvoiceAtPosition(manager.enterInvoiceData(), position);
            std::cout << "\nInvoice added.";
            break;
        }
        case 5:
        {
            std::cout << "\n----- Edit Invoice by ID -----\n\n";
            int id;
            std::cout << "Enter ID: ";
            std::cin >> id;
            manager.editInvoiceById(id);
            std::cout << "\nInvoice edited.";
            break;
        }
        case 6:
        {
            std::cout << "\n----- Change Invoice Position in the List -----\n\n";
            int id, newPosition;
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "Enter new position (starting from 0): ";
            std::cin >> newPosition;
            manager.changeInvoicePosition(id, newPosition);
            std::cout << "\nInvoice position changed.";
            break;
        }
        case 7:
        {
            std::cout << "\n----- Delete Invoice by ID -----\n\n";
            int id;
            std::cout << "Enter ID: ";
            std::cin >> id;
            manager.deleteInvoiceById(id);
            std::cout << "\nInvoice deleted.\n";
            break;
        }
        case 8:
        {
            std::cout << "\n----- Delete Invoice by Customer Name -----\n\n";
            std::string customerName;
            std::cout << "Enter customer name: ";
            std::getline(std::cin >> std::ws, customerName);
            manager.deleteInvoiceByCustomerName(customerName);
            std::cout << "\nInvoice deleted.\n";
            break;
        }
        case 9:
        {
            std::cout << "\n----- Delete Invoice at a Specific Position -----\n\n";
            int position;
            std::cout << "Enter position (starting from 0): ";
            std::cin >> position;
            manager.deleteInvoiceAtPosition(position);
            std::cout << "\nInvoice deleted.";
            break;
        }
        case 10:
        {
            std::cout << "\n----- Search for Invoice Position by ID -----\n\n";
            int id;
            std::cout << "Enter ID: ";
            std::cin >> id;
            int position = manager.searchInvoicePositionById(id);
            if (position == -1)
            {
                std::cout << "Invoice with ID " << id << " not found.\n";
            }
            else
            {
                std::cout << "Invoice with ID " << id << " found at position " << position << ".\n";
            }
            break;
        }
        case 11:
        {
            std::cout << "\n----- Search for Invoice by Customer Name -----\n\n";
            std::string customerName;
            std::cout << "Enter customer name: ";
            std::getline(std::cin >> std::ws, customerName);
            int index = manager.searchInvoicePositionByCustomerName(customerName);
            if (index == -1)
            {
                std::cout << "\nInvoice with customer name " << customerName << " not found.\n";
            }
            else
            {
                std::cout << "\nInvoices found:\n";
                manager.displayInvoiceByIndex(index);
            }
            break;
        }
        case 12:
        {
            std::cout << "\n----- Search for Invoice by Issue Date Range -----\n\n";
            std::string startDate, endDate;
            std::cout << "Enter start date (DD/MM/YYYY): ";
            std::cin >> startDate;
            while (!DateUtility::isValidDate(startDate))
            {
                std::cout << "\nThe date format is invalid or the date is later than the current date.\nEnter start date (DD/MM/YYYY): ";
                std::cin >> startDate;
            }
            std::cout << "Enter end date (DD/MM/YYYY): ";
            std::cin >> endDate;
            while (!DateUtility::isValidDate(endDate))
            {
                std::cout << "\nThe date format is invalid or the date is later than the current date.\nEnter end date (DD/MM/YYYY): ";
                std::cin >> endDate;
            }
            std::vector<Invoice> result = manager.searchInvoiceByIssueDateRange(startDate, endDate);
            if (result.empty())
            {
                std::cout << "\nNo invoices found.\n";
            }
            else
            {
                std::cout << "\nInvoices found:\n";
                for (const auto &invoice : result)
                {
                    invoice.display();
                }
            }
            break;
        }
        case 13:
        {
            std::cout << "\n----- Sort Invoices by Total Value (Ascending) -----\n\n";
            manager.sortInvoicesByTotalValueAscending();
            std::cout << "Invoices sorted.";
            break;
        }
        case 14:
        {
            std::cout << "\n----- Sort Invoices by Total Value (Descending) -----\n\n";
            manager.sortInvoicesByTotalValueDescending();
            std::cout << "Invoices sorted.";
            break;
        }
        case 15:
        {
            std::cout << "\n----- Sort Invoices by Issue Date (Ascending) -----\n\n";
            manager.sortInvoicesByIssueDateAscending();
            break;
        }
        case 16:
        {
            std::cout << "\n----- Sort Invoices by Issue Date (Descending) -----\n\n";
            manager.sortInvoicesByIssueDateDescending();
            break;
        }
        default:
            std::cerr << "Invalid choice.\n";
            break;
        }
    }
    return 0;
}
