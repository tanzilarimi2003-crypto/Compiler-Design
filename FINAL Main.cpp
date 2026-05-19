#include <iostream>
#include <string>
using namespace std;
enum State { A, B, C, D, E, DEAD };
State transition(State current, char c) {
   switch (current) {
       case A:
           if (c == 'a') return B;
           return DEAD;
       case B:
           if (c == 'a') return C;
           if (c == 'b') return D;
           return DEAD;
       case C:
           if (c == 'b') return E;
           return DEAD;
       case D:
           if (c == 'b') return D;
           return DEAD;
       case E:
           if (c == 'b') return E;
           return DEAD;
       case DEAD:
           return DEAD;
   }
   return DEAD;
}
bool isAccept(State s) {
   return (s == C || s == D || s == E);
}
string stateName(State s) {
   switch (s) {
       case A:    return "A";
       case B:    return "B";
       case C:    return "C (accept)";
       case D:    return "D (accept)";
       case E:    return "E (accept)";
       case DEAD: return "DEAD";
   }
   return "?";
}
bool runDFA(const string& input) {
   State current = A;
   cout << "  Input: \"" << input << "\"\n";
   cout << "  Trace: " << stateName(A);
   for (char c : input) {
       if (c != 'a' && c != 'b') {
           cout << " -> DEAD (invalid char '" << c << "')\n";
           return false;
       }
       current = transition(current, c);
       cout << " -" << c << "-> " << stateName(current);
   }
   cout << "\n";
   return isAccept(current);
}
int main() {

   cout << " DFA for RE = ab* + [a*(b+)* + ab]+\n";


   struct TestCase {
       string input;
       string description;
   };
   TestCase tests[] = {
       {"ab", "ab matches ab* (base) and ab (Part B)"},
       {"abbb","abbb matches ab* with 3 b's"},
       {"abb","abb matches ab* or ab followed by b"},
       {"b", "b  no leading 'a', should REJECT"},
       {"ba","ba  wrong order, should REJECT"}
   };
   for (auto& tc : tests) {
       cout << "Test: " << tc.description << "\n";
       bool result = runDFA(tc.input);
       cout << "  Result: " << (result ? "ACCEPTED" : "REJECTED") << "\n\n";
   }
   return 0;
}
