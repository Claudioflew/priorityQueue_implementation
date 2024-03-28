#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "PriorityQ.h"
#include "State.h"

using namespace std;

void loadData(const string&, PriorityQ<State>&);
int askRank();
void displayState(int, PriorityQ<State>);

int main() {
    string filePath = "/Users/claudio/Desktop/School/LMC_CS/LMC_Courses/COMSC210_DataStructure/Lab_Assignments/Lab4_PriorityQueue/electricVehicleCountsByState.csv";
    PriorityQ<State> evByState;

    loadData(filePath, evByState);
    cout << "\nLoaded data about the number of Electric Vehicles by states in USA and ranked the data!" << endl;

    while (true) {
        int rank = askRank();
        if (rank == 0) break;

        displayState(rank, evByState);
    }

    cout << "\nThank you for using this program. Have a superior day!" << endl;
}


void loadData(const string& filePath, PriorityQ<State>& evByState) {
    fstream inputFile(filePath, ios::in); // Open file with read mode

    string line;
    // Store each line into string variable line, this looks like "state, 1234"
    while (getline(inputFile, line)) {
        // We want to convert string to sstream to use getline to separate data by comma
        stringstream convert(line);

        string stateName, counts;
        getline(convert, stateName, ',');
        getline(convert, counts, ',');

        State state = State(stateName, stoi(counts));
        evByState.enqueue(state);
    }
    inputFile.close();
}


int askRank() {
    string input;
    int rank = 0;

    cout << "\nPlease enter a rank of interest (1 to 51). To quit, please enter 0: ";
    while (true) {
        getline(cin, input);
        stringstream convert(input);
        if (convert >> rank && rank >= 0 && rank <= 51) break; // Relies on short-circuit eval
        cout << "Invalid entry.. Please enter a valid number: ";
    }

    return rank;
}

// Pass by value, otherwise original prioirty queue will be changed
void displayState(int rank, PriorityQ<State> evByState) {
    for (int i = 0; i < rank - 1; i++) {
        evByState.dequeue();
    }
    State target = evByState.peek();
    cout << "\n<Rank " << rank << ">" << endl;
    cout << target.getName() << ": " << target.getEvCounts() << " electric vehicles" << endl;
}