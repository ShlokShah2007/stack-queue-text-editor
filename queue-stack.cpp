#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;
class TextEditor{
private:
    string currentText;
    stack<string> undoStack; 
    stack<string> redoStack; 
    queue<string> actionLog; 
public:
    TextEditor(){
        currentText="";
    }
    void write(string newText){
        undoStack.push(currentText);
        while(!redoStack.empty()){
            redoStack.pop();
        }
        currentText+=newText;
        actionLog.push("Typed: "+newText); 
    }
    void undo(){
        if(undoStack.empty()){
            cout <<"Nothing to undo!" <<endl;
            return;
        }
        redoStack.push(currentText);
        currentText=undoStack.top();
        undoStack.pop();
        actionLog.push("Action: Undo"); 
    }
    void redo(){
        if(redoStack.empty()){
            cout<<"Nothing to redo!"<<endl;
            return;
        }
        undoStack.push(currentText);
        currentText=redoStack.top();
        redoStack.pop();
        actionLog.push("Action: Redo"); 
    }
    void display(){
        cout << "Current Text: \"" <<currentText << "\""<< endl;
    }
    void showActionLog(){
        cout << "\n--- Action Log (Oldest to Newest) ---" << endl;
        queue<string> tempLog = actionLog; 
        while (!tempLog.empty()) {
            cout << "- " << tempLog.front() << endl;
            tempLog.pop();
        }
    }
};
int main(){
    TextEditor editor;
    editor.write("Hello ");
    editor.write("World!");
    editor.display(); 
    cout << "\n[Undoing last action...]" << endl;
    editor.undo();
    editor.display(); 
    cout << "\n[Redoing last action...]" << endl;
    editor.redo();
    editor.display(); 
    cout << "\n[Undoing again and writing something else...]" << endl;
    editor.undo();
    editor.write("C++ Programming");
    editor.display(); 
    editor.showActionLog();
    return 0;
}
