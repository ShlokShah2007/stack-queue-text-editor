#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

class TextEditor {
private:
    string currentText;
    stack<string> undoStack; // Stores past states to go backward
    stack<string> redoStack; // Stores undone states to go forward
    queue<string> actionLog; // Stores a running history of all actions performed

public:
    TextEditor() {
        currentText = "";
    }

    // Type a new word/text
    void write(string newText) {
        // Save the current state to the undo stack before changing it
        undoStack.push(currentText);
        
        // Clear the redo stack because a new action breaks the redo chain
        while (!redoStack.empty()) {
            redoStack.pop();
        }

        // Update the text
        currentText += newText;
        actionLog.push("Typed: " + newText); // Log the action
    }

    // Undo the last action
    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }

        // Move the current state to the redo stack
        redoStack.push(currentText);

        // Restore the previous state from the undo stack
        currentText = undoStack.top();
        undoStack.pop();
        
        actionLog.push("Action: Undo"); // Log the action
    }

    // Redo the last undone action
    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }

        // Move the current state back to the undo stack
        undoStack.push(currentText);

        // Restore the state from the redo stack
        currentText = redoStack.top();
        redoStack.pop();

        actionLog.push("Action: Redo"); // Log the action
    }

    // Display the current state of the text
    void display() {
        cout << "Current Text: \"" << currentText << "\"" << endl;
    }

    // Display all actions that happened from the beginning
    void showActionLog() {
        cout << "\n--- Action Log (Oldest to Newest) ---" << endl;
        queue<string> tempLog = actionLog; // Copy to print without destroying original
        while (!tempLog.empty()) {
            cout << "- " << tempLog.front() << endl;
            tempLog.pop();
        }
        cout << "-------------------------------------\n" << endl;
    }
};

int main() {
    TextEditor editor;

    // 1. Let's write some text
    editor.write("Hello ");
    editor.write("World!");
    editor.display(); // Output: Hello World!

    // 2. Test Undo
    cout << "\n[Undoing last action...]" << endl;
    editor.undo();
    editor.display(); // Output: Hello 

    // 3. Test Redo
    cout << "\n[Redoing last action...]" << endl;
    editor.redo();
    editor.display(); // Output: Hello World!

    // 4. Write something new after undoing
    cout << "\n[Undoing again and writing something else...]" << endl;
    editor.undo();
    editor.write("C++ Programming");
    editor.display(); // Output: Hello C++ Programming

    // 5. Check our queue-based action log
    editor.showActionLog();

    return 0;
}